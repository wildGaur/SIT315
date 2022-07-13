// C++ code


int sensorValue = 0; //Declaring the variable

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600); //BAUD rate
  pinMode(6, OUTPUT); //Red color 
  pinMode(7, OUTPUT); //Blue color
  pinMode(8, OUTPUT); //Green color
  
}

void loop()
{
  digitalWrite(A0, HIGH); // Power applied to the PIR sensor
  delay(10); // 10 ms wait
  sensorValue = analogRead(A1); // Retriving value from sensor
  Serial.print("Sensor output = ");
  Serial.println(sensorValue); // Print value from sensor
 
  
  // Turn off the sensor to save power
  digitalWrite(A0, LOW);
  
  // set start state of RGB led as off
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  
  //Activate RGB based on sensor value
  if (sensorValue == 826) {
    digitalWrite(8, HIGH); // Motion detected
    Serial.println("Motion detected");
    Serial.println();
  } else {
    digitalWrite(6, HIGH); //No motion detected
    Serial.println("No Motion detected");
    Serial.println();
  }
  delay(500); // Wait for 100 millisecond(s)
}