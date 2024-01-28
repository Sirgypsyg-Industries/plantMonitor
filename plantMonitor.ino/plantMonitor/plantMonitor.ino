#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
int var;
int minTemp = 15;
int curTemp = 10;

int maxSoilContent = 1;
int minSoilContent = 1;
double criticalSoilContent = 1;



void setLimits(){
  delay(5000);
  //poloz w suchym miejscu
  Serial.println("suche miejsce");
  delay(8000);
  minSoilContent = 1023 - analogRead(A1);
  
  //wloz czujnik do wody
  Serial.println("do wody");
  delay(8000);
  maxSoilContent = 1023 - analogRead(A1);
  
  criticalSoilContent = (maxSoilContent - minSoilContent)*0.5 + minSoilContent;
  //czujnik skalibrowany
  delay(2000);
  Serial.println("jest git");
}
 
void setup(){
  //buzzer
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(A1, INPUT);

  setLimits();

 
}


void loop(){
  //Start of Program 
  if(Serial.available()) {
    var=Serial.read();

    switch (var) {
      case 'A':
        tone(2, 500);
        break;

      case 'B':
        noTone(2);
        break;

      case 'S':
        var = Serial.read();
        int temp = maxSoilContent - minSoilContent;
        criticalSoilContent = temp * (var / 100) + minSoilContent;
        break;

      case 'T':
        var = Serial.read();
        minTemp = var;
        break;
      default:
        break;
    }
  }


    while(1023 - analogRead(A1) < criticalSoilContent){
      Serial.println("WATER ME");
      tone(2, 100);
      delay(1000);
    }
    noTone(2);
    Serial.print("Current soil Content = "); 
    int temp = 1023 - analogRead(A1);
    double curValue = static_cast<double>(temp - minSoilContent) / (maxSoilContent - minSoilContent) ;      
    Serial.print(curValue * 100); 
    Serial.println("%");
    delay(1000);
    
    
    DHT.read11(dht_apin);
    Serial.print("humidity = ");
    Serial.print(DHT.humidity); 
    Serial.println("% ");

   delay(1000);


    
    //delay(150);//Wait 5 seconds before accessing sensor again.
  //Fastest should be once every two seconds.
 
}