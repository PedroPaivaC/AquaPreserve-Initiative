float Flow;
float Average = 0;
int Count;
float I = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  attachInterrupt(0, inc, RISING);
  //Serial.print("Beginning");
  

}

void loop() {
  // put your main code here, to run repeatedly:

  Count = 0;
  sei(); 
  delay(1000);
  cli();

  Flow = Count / 5.5;
  //Average = Average + Flow;
  //I = I + 0.1;

  Serial.print(Flow);
  Serial.println("L / Min ");
  //Serial.println(I);
  //Serial.println("s");

  if (Count >= 2) {

    digitalWrite(7, HIGH);
    
  }

  else {
    digitalWrite(7, LOW);
  }
  
}

void inc() {

  Count++;
  
}
