// C++ code
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd_1(0);

// define the pins
const uint8_t interruptPin0 = 2;
const uint8_t interruptPin1 = 3;
const uint8_t interruptPin2 = A1;
const uint8_t interruptPin3 = 8;
const uint8_t led_r = 13;
const uint8_t led_g = 12;
const uint8_t led_b = 11;
const uint8_t led_y = 10;

const uint8_t triggerPin = A0;

// Globals
volatile uint8_t flag = 0;
double timerFrequency = 2;

// State of the both LED set to off
volatile uint8_t state_r = LOW;
volatile uint8_t state_g = LOW;
volatile uint8_t state_b = LOW;

// Declaring the variable
int sensorValue_r = 0;
int sensorValue_g = 0;
int sensorValue_b = 0;

int distanceValue;
int duration;

void setup()
{
    pinMode(interruptPin0, INPUT);
    pinMode(interruptPin1, INPUT);
    pinMode(interruptPin2, INPUT);
    pinMode(interruptPin3, INPUT);
    pinMode(triggerPin, OUTPUT);
    lcd_1.begin(16, 2);

    Serial.begin(9600);     // BAUD rate
    pinMode(led_r, OUTPUT); // led
    pinMode(led_g, OUTPUT); // led
    pinMode(led_b, OUTPUT); // led
    pinMode(led_y, OUTPUT); // led

    // system interrupt
    attachInterrupt(digitalPinToInterrupt(interruptPin0), motion, CHANGE);
    attachInterrupt(digitalPinToInterrupt(interruptPin1), objCloser, CHANGE);

    // Timer
    startTimer();
}

void loop()
{
    sensorValue_r = analogRead(interruptPin0); // Retriving value from sensor
    Serial.print("Motion Sensor red output = ");
    Serial.println(sensorValue_r); // Print value from sensor

    sensorValue_g = analogRead(interruptPin2); // Retriving value from sensor
    Serial.print("Motion Sensor green output = ");
    Serial.println(sensorValue_g); // Print value from sensor

    sensorValue_b = analogRead(interruptPin3); // Retriving value from sensor
    Serial.print("Motion Sensor blue output = ");
    Serial.println(sensorValue_b); // Print value from sensor

    // Clears the trigPin condition
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(interruptPin1, HIGH);

    // Calculating the distance
    distanceValue = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

    // Print value from sensor
    Serial.print("Distance: ");
    Serial.print(distanceValue);
    Serial.println(" cm");

    if (flag == 1)
    {
        lcd_1.clear();
        lcd_1.print("Distance: ");
        lcd_1.print(distanceValue);
        flag = 0;
    }
    else
    {
        lcd_1.clear();
        lcd_1.print("No detection");
    }
    cli();               // switch interrupts off while messing with their settings
    PCICR |= 0b00000011; // Enable PCINT interrupt for port b and c
    PCMSK0 |= 0b00000001;
    PCMSK1 |= 0b00000010;
    sei(); // turn interrupts back on

    delay(500); // Wait for 500 millisecond(s)
}

void motion()
{
    // Light up LED if motion is detected
    state_r = !state_r;
    digitalWrite(led_r, state_r);
}

void objCloser()
{
    // Light up LED if motion is detected
    if (distanceValue < 326)
    {
        flag = 1;
    }
}

ISR(PCINT1_vect)
{
    state_g = !state_g;
    digitalWrite(led_g, state_g);
}

ISR(PCINT0_vect)
{
    state_b = !state_b;
    digitalWrite(led_b, state_b);
}

void startTimer()
{

    Serial.print("Timer Frequency: ");
    Serial.println(timerFrequency);

    // Stop all interrupts
    noInterrupts();

    // Set entire TCCR1A and TCCR1B register to 0

    TCCR1A = 0;
    TCCR1B = 0;

    // Initialise timer register as 0
    TCNT1 = 0;

    /* System clock 16 Mhz and Prescalar 1024
    Timer 1 speed = 16Mhz/1024 = 15.625 Khz
    Pulse time = 1/15.625 Khz = 0.064 ms
    We need to turn led every 2 sec.
    Count upto = 2 sec / 0.064 ms = 31250
    Which is set to Output compare register
    */

    OCR1A = 31250;

    // Set value of TCCR1A
    // Wave generation mode bit is set to 1 as we are using timer on compare
    // CS12 is set to 0, CS11 to 0 and CS10 to 1 to represent 1024 prescaler.
    TCCR1B |= 0b00001101;

    // Set value ofTIMSK1
    // OCIEB is set to 1 to enable compare match interrupt
    TIMSK1 |= 0b00000010;

    // Enable interrupt
    interrupts();
}
ISR(TIMER1_COMPA_vect)
{
    digitalWrite(led_y, digitalRead(led_y) ^ 1);
}