// Assigning  pin number for button and LED
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

// Assigning default value for button as off
uint8_t buttonState = 0;

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

    // Attach an interrupt to check if button is pressed
    attachInterrupt(0, btnPress, CHANGE);
}

void loop()
{
    // No code required
}

// Custom interrupt function
void btnPress()
{
    buttonState = digitalRead(BTN_PIN);
    digitalWrite(LED_PIN, buttonState);
}