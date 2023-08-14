// sd cs-10
// sd mosi-11
// sd miso-12
// sd sck-13

#include <DHT.h> // khai báo thư viện DHT
#include <Wire.h> 
#include <SD.h>	
#include <SPI.h>
#include "rgb_lcd.h" // khai báo thư viện LCD

long seconds=00;
long minutes=00;
long hours=00;
int CS_pin = 10;

const int DHTPIN = 1; // Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  // Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(DHTPIN, DHTTYPE);

File sd_file;
rgb_lcd lcd;
int coi = 0;
int i;
int pin[8];
int Led[8] = {9,8,7,6,5,4,3,2};  // khai báo các chân led 8
float a = 6.25; // a là độ rộng mỗi mức nhiệt độ (8 mức)

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
  pinMode(CS_pin, OUTPUT);
  dht.begin();  
  lcd.begin(16,2);
  lcd.createChar(1, Degree);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(0,1); // (cột, hàng)
  lcd.print("Hum : ");
  
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

  // Hiển thị số liệu đo được lên LCD
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
     

// Còi cảnh báo khi nhiệt độ vượt quá mức cho phép
  if(t>32){
      digitalWrite(coi, HIGH);
      delay(100);
      digitalWrite(coi, LOW);
      delay(100);
    }

 Hiển thị mức nhiệt độ trực quan lên thanh LED 8x1.
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
          //delay(100);
        }
      else{
          digitalWrite(Led[i],LOW);
          //delay(100);
        }      
      }
}

void senddata()  {
  for(long seconds = 00; seconds < 60; seconds=seconds+2)  {
    float temp = dht.readTemperature(); //Reading the temperature as Celsius and storing in temp
    float hum = dht.readHumidity();     //Reading the humidity and storing in hum
    float fah = dht.readTemperature(true);

    sd_file.print(hours);
    sd_file.print(":");
    sd_file.print(minutes);
    sd_file.print(":");
    sd_file.print(seconds);
    sd_file.print(",  ");
    sd_file.print(hum);
    sd_file.print(",    ");
    sd_file.print(temp);

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