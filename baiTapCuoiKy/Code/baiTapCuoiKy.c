#include <avr/interrupt.h>
#define sign 9
#define adc_pin A2
unsigned int adc;
unsigned int duty;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sign, OUTPUT);
  pinMode(adc_pin, INPUT);
  TIMER1();
}
void TIMER1(){
  noInterrupts();
  //reset thanh ghi 
  TCCR1A = 0; 
  TCCR1B = 0;  
  //Chon kieu Counter
    //che do fast mode ICR1
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);
    /*che do phase mode ICR1
  TCCR1A |= (1 << WGM11)|(1 << WGM10);
  TCCR1B |= (1 << WGM13);*/ 
  //Chon kieu so sanh
  TCCR1A |= (1 << COM1A1); //non inverting
  //TCCR1A |= (1 << COM1A1)|(1 << COM1A0); //invert
  ICR1 = 65535;  
  OCR1A = 8480;  
  duty = OCR1A;
  //TCCR1B |= (1 << CS10)|(1 << CS11); 
  TCCR1B |= (1 << CS10);
  interrupts(); 
}

void angle(unsigned int adc)
{
    if (duty != adc) {
        OCR1A = adc;
        duty = OCR1A;
    }
    else {
        return;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  adc = analogRead(adc_pin);
  Serial.println(adc);
  Serial.println();
  adc = map(adc, 0, 1023, 8480, 38550);
  Serial.println(OCR1A);
  Serial.println();
  angle(adc);
  delay(15);
}

