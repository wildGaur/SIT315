// C++ code

// define the pins
const uint8_t interruptPin0 = 2;
const uint8_t interruptPin1 = 3;
const uint8_t led_m = 13;
const uint8_t led_d = 12;

const uint8_t triggerPin = A0;

// State of the both LED set to off
volatile uint8_t state_m = LOW;
volatile uint8_t state_d = LOW;

// Declaring the variable
int sensorValue = 0;
int distanceValue = 0;
int duration;

void setup()
{
    pinMode(interruptPin0, INPUT);
    pinMode(interruptPin1, INPUT);
    pinMode(triggerPin, OUTPUT);

    Serial.begin(9600);     // BAUD rate
    pinMode(led_m, OUTPUT); // led
    pinMode(led_d, OUTPUT); // led
    attachInterrupt(digitalPinToInterrupt(interruptPin0), motion, CHANGE);
    attachInterrupt(digitalPinToInterrupt(interruptPin1), distance, CHANGE);
}

void loop()
{
    sensorValue = analogRead(interruptPin0); // Retriving value from sensor
    Serial.print("Motion Sensor output = ");
    Serial.println(sensorValue); // Print value from sensor

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

    delay(500); // Wait for 500 millisecond(s)
}

void motion()
{
    // Light up LED if motion is detected
    state_m = !state_m;
    digitalWrite(led_m, state_m);
}

void distance()
{
    // Light up LED if motion is detected
    state_d = !state_d;
    digitalWrite(led_d, state_d);
}