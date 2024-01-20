#include <U8g2lib.h>
#define sensor A0
#define LED 13
#define BUZZER 8


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // font?


void setup() {
  // put your setup code here, to run once:
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  u8g2.begin();
  Serial.begin(9600);

}

void loop() {

   //handle oled
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr); // font
  u8g2.drawStr(10, 30, "sample test"); // coordinates of text(10, 30)
  u8g2.sendBuffer();
  //

  
  Serial.println( 1023 - analogRead(sensor));
  bool criticalReached = 1023 - analogRead(sensor) > 300;

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
