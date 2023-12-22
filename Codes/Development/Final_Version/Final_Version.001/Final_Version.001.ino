#include <DallasTemperature.h> // Water Temperature System
#include <OneWire.h>
#define ONE_WIRE_BUS 2
#define IdealTemperature 35

#define SensorResolution 

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int Relay[3] = {8, 9, 10};
int x;

bool Temperature;

void setup() {
  // put your setup code here, to run once:
  
  sensors.begin();
  Serial.begin(9600);
  
  pinMode(4, INPUT);

  for (x = 0; x <= 2; x = x + 1) {
    pinMode(Relay[x], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  sensors.requestTemperatures();

  Serial.print("Temperature:");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("C   |  ");

  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("F");

  Serial.println(analogRead(A0));
  Serial.print("Flow: ");

  Temperature = false;

  if (digitalRead(4) > 0) {
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);

    if (sensors.getTempCByIndex(0) >= IdealTemperature) {

    Temperature = true;
      
    }

    while (sensors.getTempCByIndex(0) >= IdealTemperature  or Temperature == true) {

      sensors.requestTemperatures();

      Serial.print("Temperature:");
      Serial.print(sensors.getTempCByIndex(0));
      Serial.print("C   |  ");
    
      Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
      Serial.println("F");
    
      Serial.println(digitalRead(4));
      Serial.print("Flow: ");

      
      digitalWrite(10, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);

      if (digitalRead(4) < 1) {

        break;
        
      }

    }

  }

  else {

    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    
  }
  
  delay(10);
  
}
