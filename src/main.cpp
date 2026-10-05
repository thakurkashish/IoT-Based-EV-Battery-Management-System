#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL3DhaGaUrU"
#define BLYNK_TEMPLATE_NAME "Smart EV"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

char ssid[]="Wokwi-GUEST";
char pass[]="";

#define CELL1 34
#define CELL2 35
#define CELL3 32
#define RED_LED 2
#define GREEN_LED 4
#define YELLOW_LED 5
#define BUZZER 18
#define RELAY 19

float v1,v2,v3;
int p1,p2,p3;
String status;
//function to read voltage
float readVoltage(int pin){
  int raw= analogRead(pin);
  return (raw/4095.0)*3.3;
}
//convert voltage to percentage
int getPercent(float v){
  return constrain(map(v*100,0,330,0,100),0,100);
}

void setup(){
  Serial.begin(115200);
  pinMode(RED_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  pinMode(RELAY,OUTPUT);
  lcd.init();
  lcd.backlight();
  digitalWrite(RELAY,LOW);
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass);
  Serial.println("MULTI CELL BMS");
}
void loop(){
  v1=readVoltage(CELL1);
  v2=readVoltage(CELL2);
  v3=readVoltage(CELL3);

  p1=getPercent(v1);
  p2=getPercent(v2);
  p3=getPercent(v3);
  float avg=(v1+v2+v3)/3.0;

  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(YELLOW_LED,LOW);
  digitalWrite(BUZZER,LOW);

  if (p1< 30 || p2<30 || p3<30){
    status="WEAK CELL";
    digitalWrite(RED_LED,HIGH);
    digitalWrite(BUZZER,HIGH);
    digitalWrite(RELAY,HIGH);

  }
  else if(p1>80 && p2>80 && p3>80){
    status="HIGH VOLTAGE";
    digitalWrite(YELLOW_LED,HIGH);
    digitalWrite(BUZZER,HIGH);
    digitalWrite(RELAY,HIGH);
    
  }
  else {
    status="NORMAL";
    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(RELAY,LOW);
  }
Serial.print("C1: ");Serial.print(v1);
Serial.print("C2: ");Serial.print(v2);
Serial.print("C3: ");Serial.print(v3);

Serial.println(status);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("C1:");
lcd.print(v1,1);
lcd.print(" C2:");
lcd.print(v2,1);
lcd.setCursor(0,1);
lcd.print("C3:");
lcd.print(v3,1);
lcd.print(" ");
lcd.print(status);

Blynk.virtualWrite(V0,avg);
Blynk.virtualWrite(V4,status);
Blynk.virtualWrite(V1,v1);
Blynk.virtualWrite(V2,v2);
Blynk.virtualWrite(V3,v3);
Blynk.run();

delay(1000);


}
