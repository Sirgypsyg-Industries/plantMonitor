#include "dht.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
#define dht_apin A0 // Analog Pin sensor is connected to

Adafruit_SH1106 display(OLED_RESET);
dht DHT;
int var;
double criticalTemp = 1;

int maxSoilContent = 1;
int minSoilContent = 1;
double criticalSoilContent = 1;

void stringDisplay(String s){

  display.clearDisplay();

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(s);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);

  display.display(); 
}

void parametersDisplay(double t, double h){
  display.clearDisplay();

  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %"); 
  
  display.display(); 
}

void setLimits(){
  delay(5000);
  stringDisplay("poloz w suchym miejscu");
  delay(8000);
  minSoilContent = 1023 - analogRead(A1);
  
  //wloz czujnik do wody
  stringDisplay("wloz czujnik do wody");
  delay(8000);
  maxSoilContent = 1023 - analogRead(A1);
  
  criticalSoilContent = (maxSoilContent - minSoilContent)*0.5 + minSoilContent;
  //czujnik skalibrowany
  delay(2000);
  stringDisplay("jest git");
}
 
void setup(){
  //buzzer
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(A1, INPUT);
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  setLimits();

 
}


void loop(){
  //Start of Program 
  if(Serial.available()) {
    var = Serial.read();

    if(var == 'S' || var == 'ST'){
        var = Serial.read();
        int temp = maxSoilContent - minSoilContent;
        criticalSoilContent = temp * (var / 100) + minSoilContent;
    }else if(var == 'T'){
        var = Serial.read();
        criticalTemp = var;
    }

  }

    //water content critical
    while(1023 - analogRead(A1) < criticalSoilContent){
      stringDisplay("WATER ME");
      tone(2, 100);
      delay(1000);
    }
  
    //temperature critical
    DHT.read11(dht_apin);
    while(DHT.temperature < criticalTemp){
      stringDisplay("TOO COLD");
      tone(2, 100);
      delay(1000);
    }
    
    //parameters ok
    noTone(2);


    //cur temperature
    DHT.read11(dht_apin);
    double curTemperature = (DHT.temperature);
  

    //cur soil Content
    int temp = 1023 - analogRead(A1);
    double curHumidity = static_cast<double>(temp - minSoilContent) / (maxSoilContent - minSoilContent) ;      
    parametersDisplay(curTemperature, curHumidity);

    
    delay(1000);
    


    
    //delay(150);//Wait 5 seconds before accessing sensor again.
  //Fastest should be once every two seconds.
 
}