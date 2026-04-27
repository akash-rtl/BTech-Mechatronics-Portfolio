const int bjt = 10;
const int led = 7;
const int inp = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(bjt, OUTPUT);
  pinMode(inp, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(bjt, HIGH);
  delay(17000);
  int state = digitalRead(inp);
  delay(1000);

  if(state == 1){
    digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
  delay(500);
  state = 0;

}
