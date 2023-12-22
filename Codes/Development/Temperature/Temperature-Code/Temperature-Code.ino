#include <DallasTemperature.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


void setup() {
  // put your setup code here, to run once:

  sensors.begin();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  sensors.requestTemperatures();

  Serial.print("Temperature:");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("C   |  ");

  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("F");

  delay(200);

}
