// C++ code
//

const byte LED_PIN = 13;
const byte METER_PIN = A4;
double timerFrequency = 1;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(METER_PIN, INPUT);

    Serial.begin(9600);

    startTimer(timerFrequency);
}

void loop()
{
    /* The value of Potentiometer range from 0 to 1023 at 250 Kohm
     So we can divide the value by 250 to get a range of 0-4 sec
     */
    double timerInput = analogRead(METER_PIN) / (double)250;
    Serial.print("Timer Input: ");
    Serial.println(timerInput);
    if (timerInput != timerFrequency)
    {
        timerFrequency = timerInput;
        startTimer(timerFrequency);
    }
    delay(2000);
}

void startTimer(double timerFrequency)
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

    /* Old code
    OCR1A = 31250;

    // Set value of TCCR1A
    // Wave generation mode bit is set to 1 as we are using timer on compare
    // CS12 is set to 0, CS11 to 0 and CS10 to 1 to represent 1024 prescaler.
    TCCR1B |= 0b00001101;

    // Set value ofTIMSK1
    // OCIEB is set to 1 to enable compare match interrupt
    TIMSK1 |= 0b00000010;
    */

    // First step to determine the OCR1A
    OCR1A = timerFrequency / (double)0.000064;

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
    digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
}
