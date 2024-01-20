#define echoPin A0;
#define LEDD 13
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(LEDD, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  
  Serial.println( 1023 - analogRead(A0));
  if(1023 - analogRead(A0) < 300){
    digitalWrite(LEDD, HIGH);  // turn the LED on (HIGH is the voltage level)
  }
  else{
     digitalWrite(LEDD, LOW);
  }
  delay(10);
}


//TESTING num 1
//TESTING num 2