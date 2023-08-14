#include <DHT.h>
#include <Wire.h> 
#include <SD.h>	
#include <SPI.h>
#include "rgb_lcd.h"

long seconds=00;
long minutes=00;
long hours=00;
int CS_pin = 10;

const int DHTPIN = 1;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

File sd_file;
rgb_lcd lcd;
int coi = 0;
int i;
int pin[8];
int Led[8] = {9,8,7,6,5,4,3,2};
float a = 6.25;

byte Degree[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  dht.begin();  
  lcd.begin(16,2);
  lcd.createChar(1, Degree);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(0,1);
  lcd.print("Hum : ");
  
  pinMode(CS_pin, OUTPUT);
  sd_file = SD.open("data.txt", FILE_WRITE);

  if (sd_file)  {
    sd_file.print("Time");
    sd_file.print(",");
    sd_file.print("Humidity");
    sd_file.print(",");
    sd_file.print("Temperature_C");
    
  }
  sd_file.close(); //closing the file
  pinMode(coi, OUTPUT);
  

  for(i=0;i<8;i++){
      pin[i] = 0;
    }
  
  for(i=0;i<8;i++){
      pinMode(Led[i],OUTPUT); 
    }
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(6,0);
  lcd.print(t);
  lcd.print(" ");
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(6,1);
  lcd.print(h);
  lcd.print(" %");

  sd_file = SD.open("data.txt", FILE_WRITE);
  if (sd_file)  {
    senddata();
  }
  // if the file didn't open, print an error:
  delay(1000);
     

  if(t>32){
      digitalWrite(coi, HIGH);
      delay(100);
      digitalWrite(coi, LOW);
      delay(100);
    }

  float x = t*1.0/a;
  for(i=0;i<8;i++){
    if(i<=x){
        pin[i] = 1;
      }
    else{
      pin[i] = 0; 
    }
   }
   
  for(i=0;i<8;i++){
      if(pin[i] == 1){
          digitalWrite(Led[i],HIGH);
          
        }
      else{
          digitalWrite(Led[i],LOW);
          
        }      
      }
}

void senddata()  {
  for(long seconds = 00; seconds < 60; seconds=seconds+2)  {
    
    sd_file.print(hours);
    sd_file.print(":");
    sd_file.print(minutes);
    sd_file.print(":");
    sd_file.print(seconds);
    sd_file.print(",  ");
    sd_file.print(h);
    sd_file.print(",    ");
    sd_file.print(t);

    if(seconds>=58)  {
      minutes= minutes + 1;
    }

    if (minutes>59)  {
      hours = hours + 1;
      minutes = 0;
    }

    sd_file.flush(); //saving the file

    delay(2000);
  }
  sd_file.close();   //closing the file
}