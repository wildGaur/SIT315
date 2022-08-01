// C++ code

// define the pins
const uint8_t interruptPin = 2;
const uint8_t led = 8;
volatile uint8_t state = LOW; // State of the LED on or off
int sensorValue = 0;          // Declaring the variable

void setup()
{
    pinMode(interruptPin, INPUT);
    Serial.begin(9600);   // BAUD rate
    pinMode(led, OUTPUT); // led
    attachInterrupt(digitalPinToInterrupt(interruptPin), motion, CHANGE);
}

void loop()
{
    sensorValue = analogRead(interruptPin); // Retriving value from sensor
    Serial.print("Sensor output = ");
    Serial.println(sensorValue); // Print value from sensor
    delay(500);                  // Wait for 100 millisecond(s)
}

void motion()
{
    // Light up LED if motion is detected
    state = !state;
    digitalWrite(led, state);
}
