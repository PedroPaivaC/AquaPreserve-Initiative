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

float Flow; // Water Flow / Pressure System
int Count;


void setup() {
  // put your setup code here, to run once:
  
  sensors.begin();
  Serial.begin(9600);
  
  pinMode(4, INPUT); // Water Temperature Sensor
  pinMode(3, INPUT); // Water Flow / Pressure Sensor
  attachInterrupt(1, inc, CHANGE);

  for (x = 0; x <= 2; x = x + 1) {
    pinMode(Relay[x], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  Count = 0; // Water Flow / Pressure System
  sei();
  delay(1000);
  cli();

  Flow = Count / 5.5;

  sensors.requestTemperatures(); // Water Temperature Sensor

  Serial.print("Temperature:");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("C   |  ");

  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print("F   |   ");
  
  Serial.print(Flow); // Water Flow / Pressure Sensor
  Serial.print("L / Min   |   ");
  
  Serial.println("System Status: OFF");
  
  Temperature = false;

  if (Flow >= 0.50) {
    digitalWrite(10, LOW); // Turns Relay ON - Activates Valve
    digitalWrite(9, LOW); // Turns Relay ON - Activates Valve
    digitalWrite(8, LOW); // Turns Relay ON - Activates Valve

    if (sensors.getTempCByIndex(0) >= IdealTemperature) {

    Temperature = true;
      
    }

    while (sensors.getTempCByIndex(0) >= IdealTemperature  or Temperature == true) {

      Count = 0;
      sei();
      delay(1000);
      cli();

      Flow = Count / 5.5;

      sensors.requestTemperatures();

      Serial.print("Temperature:"); // Water Temperature Sensor
      Serial.print(sensors.getTempCByIndex(0));
      Serial.print("C   |  ");
    
      Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
      Serial.print("F   |   ");    
      
      Serial.print(Flow); // Water Flow / Pressure Sensor
      Serial.print("L / Min   |   ");
      
      Serial.println("System Status: ON");
      
      digitalWrite(10, HIGH); // Turns Relay OFF - Deactivates Valve
      digitalWrite(9, HIGH); // Turns Relay OFF - Deactivates Valve
      digitalWrite(8, HIGH); // Turns Relay OFF - Deactivates Valve

      if (Flow < 1) {

        break;
        
      }

    }

  }

  else {

    digitalWrite(10, HIGH); // Turns Relay OFF - Deactivates Valve
    digitalWrite(9, HIGH); // Turns Relay OFF - Deactivates Valve
    digitalWrite(8, HIGH); // Turns Relay OFF - Deactivates Valve
    
  }
  
  delay(10);
  
}

void inc() {

  Count++;
  
}
