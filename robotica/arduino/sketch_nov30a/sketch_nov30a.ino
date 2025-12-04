int pinLed = 13;

void setup()
{
  
  pinMode(pinLed, OUTPUT);
  
}

void loop()
{
  
  digitalWrite(pinLed, HIGH);
  
  delay(2000);
  
  digitalWrite(pinLed, LOW);
  
  delay(2000);
}
