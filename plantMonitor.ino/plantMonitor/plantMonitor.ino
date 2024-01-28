#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
int var;
 
void setup(){
  //buzzer
  pinMode(2,OUTPUT);
  pinMode(A1, INPUT);

  Serial.begin(9600);
   
}//end "setup()"
 
void loop(){
  //Start of Program 
  if(Serial.available()) {
    var=Serial.read();
    if(var == 'A') {
      tone(2, 500);
    }
    if(var == 'B') {
      noTone(2);
    }
  }
    DHT.read11(dht_apin);
    Serial.print("humidity = ");
    Serial.print(DHT.humidity); 
    Serial.println("% ");

    delay(500);
   Serial.println( 1023 - analogRead(A1));

   delay(500);


    
    //delay(150);//Wait 5 seconds before accessing sensor again.
  //Fastest should be once every two seconds.
 
}// end loop()
