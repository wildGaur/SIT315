
// Assigning  pin number for button and LED
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

// Assigning default value for button and LED - it is set as off
uint8_t buttonPrevState = LOW;
uint8_t ledState = LOW;

// Setting up the setup function
void setup()
{
    // Configure BTN_PIN as an input which is 2
    // and enable the internal pull-up resistor
    pinMode(BTN_PIN, INPUT_PULLUP);

    // Make LED_PIN (pin 13) as the output
    pinMode(LED_PIN, OUTPUT);

    // Start serial connection at 9600 bits of data per second
    Serial.begin(9600);
}

void loop()
{
    // Read the pushbutton value into a variable buttonState
    uint8_t buttonState = digitalRead(BTN_PIN);

    // Print the value of pushbutton stored in buttonState variable
    Serial.print(buttonState);

    // Print the value of pushbutton stored in buttonPrevState variable
    Serial.print(buttonPrevState);

    // Print the value of led status stored in ledState
    Serial.print(ledState);
    Serial.println("");

    // Check if the new button value is different to previous state.
    // If true change the ledState and buttonPrevState
    if (buttonState != buttonPrevState)
    {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }

    buttonPrevState = buttonState;

    // Delay for 500 milliseconds
    delay(500);
}