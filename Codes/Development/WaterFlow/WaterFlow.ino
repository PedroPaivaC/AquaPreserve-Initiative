
int FlowCount;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  FlowCount = digitalRead(4);

  Serial.println(FlowCount);
  Serial.print("Flow: ");

  if (digitalRead(4) == 1) {
    digitalWrite(13, HIGH);
  }

  else {
    digitalWrite(13, LOW);
  }

  FlowCount = FlowCount++;
  
  delay(500);
  
}

void Flow() {

  FlowCount++;
  
}
