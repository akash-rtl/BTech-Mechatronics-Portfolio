void setup() {
  // put your setup code here, to run once:
 
 Serial.begin(9600);
 
  pinMode(A0, INPUT);





}

void loop() {
  // put your main code here, to run repeatedly:

int a = map(analogRead(A0), 0, 1023, 1000, 0);

//int a = analogRead(A0);

Serial.println(a);


}
