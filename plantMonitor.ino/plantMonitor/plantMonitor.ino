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
int criticalTemp = 1;
const int buttonPin = 4;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status

int maxSoilContent = 1;
int minSoilContent = 1;
int criticalSoilContent = 1;
int curPhase = 0;

void stringDisplay(String s){

  display.clearDisplay();

  // display temperature
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  switch(curPhase){
    case 0:
      display.print("Calibration phase: ");
      break;
    case 1:
      display.print("Plant Monitor: ");
      break;
    case 2:
      display.print("WARNING:  ");
  }
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(s);
  display.print(" ");

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
  display.print(h*100);
  display.print(" %"); 
  
  display.display(); 
}

void setLimits(){
  stringDisplay("click to  calibrate");
  delay(1000);
  stringDisplay("3");
  delay(1000);
  stringDisplay("2");
  delay(1000);
  stringDisplay("1");
  delay(1000);

  stringDisplay("click to  set min");
  buttonState = digitalRead(buttonPin);
  while(buttonState == HIGH){
    buttonState = digitalRead(buttonPin);
  }
  minSoilContent = 1023 - analogRead(A1);

  delay(2000);
  buttonState = 0;
  buttonState = digitalRead(buttonPin);
  stringDisplay("click to  set max");
  while(buttonState == HIGH){
    buttonState = digitalRead(buttonPin);
  }
  maxSoilContent = 1023 - analogRead(A1);
  
  criticalSoilContent = (maxSoilContent - minSoilContent)*0.5 + minSoilContent;
  //czujnik skalibrowany
  
  stringDisplay("Calibrated");
  delay(2000);
  curPhase = 1;
}
 
void setup(){
  //buzzer
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(A1, INPUT);
  pinMode(4,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  stringDisplay("WITAM");
  delay(2000);
  setLimits();

 
}


void loop(){
  //Start of Program 
  if(Serial.available()) {
    char cvar = Serial.read();

    if(cvar == 'S'){
      String message = "";
      while (Serial.available() > 0) {
        char nextChar = Serial.read();
        if (nextChar == 'E') {
          // Znaleziono znak końcowy, zakończ odczytywanie
          break;
        } else {
          // Dodaj znak do komunikatu
          message += nextChar;
        }
      }
      double temp = message.toInt();
      criticalSoilContent = (maxSoilContent - minSoilContent) * (temp / 100) + minSoilContent;

    }else if(cvar == 'T'){
      String message = "";
      while (Serial.available() > 0) {
        char nextChar = Serial.read();
        if (nextChar == 'E') {
          // Znaleziono znak końcowy, zakończ odczytywanie
          break;
        } else {
          // Dodaj znak do komunikatu
          message += nextChar;
        }
      }        
      
      criticalTemp = message.toInt();
    }
    Serial.flush();
  }

  DHT.read11(dht_apin); // read sensors
  double curTemp = (DHT.temperature);
  double curHumidity = 1023 - analogRead(A1);
    

    if(curHumidity < criticalSoilContent){  //water content critical
      curPhase = 2;
      stringDisplay("WATER ME");
      tone(2, 1000);
    }
    else if(curTemp < criticalTemp){ //temperature critical
      curPhase = 2;
      stringDisplay("TOO COLD");
      tone(2, 2000);
    }
    else{ //parameters ok
      noTone(2);
      curPhase = 1;
      double temp = static_cast<double>(curHumidity - minSoilContent) / (maxSoilContent - minSoilContent) ;      

      parametersDisplay(curTemp, temp);
    }
    delay(150);
    
}