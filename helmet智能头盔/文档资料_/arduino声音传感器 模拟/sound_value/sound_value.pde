int ledPins[] =  {3,4,5,6,7,8,9,10};
int switchPin = 2;
int soundPin = 0;

boolean showPeak = false;
int peakValue = 0;

void setup()
{
  for(int i = 0;i < 8; i++)
  {
     pinMode(ledPins[i],OUTPUT);
  }
  pinMode(switchPin,INPUT);
}

void loop()
{
  if (digitalRead(switchPin))
  {
    showPeak = !showPeak;
    peakValue = 0;
    delay(200);
  }
  int value = analogRead(soundPin);
  int topLED = map(value,0,400,0,12)-1;
  if(topLED>peakValue)
  {
    peakValue = topLED;
  }
  for(int i = 0;i < 8;i++)
  {
    digitalWrite(ledPins[i],(i <= topLED||(showPeak && i == peakValue)));
  }
}

