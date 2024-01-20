#define echoPin A0;
#define LED 13
#define BUZZER 8
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  
  Serial.println( 1023 - analogRead(A0));
  bool criticalReached = 1023 - analogRead(A0) > 300;

  if(criticalReached) {
    digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)

      digitalWrite(BUZZER, HIGH);
      delay(1000);
      digitalWrite(BUZZER, LOW);
      delay(1000);

  }
  else{
     digitalWrite(LED, LOW);
  }
  delay(1000);
}