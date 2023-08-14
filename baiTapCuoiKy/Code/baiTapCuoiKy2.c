#include <avr/interrupt.h>
#define sign 9

void setup(){
   Serial.begin(9600);
  pinMode(sign, OUTPUT);
  TIMER1();
}

void TIMER1(){
  noInterrupts();
  //reset thanh ghi 
  TCCR1A = 0; 
  TCCR1B = 0; 
  
  //Chon kieu Counter
    //che do fast mode 
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13);
    /*che do phase mode 
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM13);*/
  
  //Chon kieu so sanh
  TCCR1A |= (1 << COM1A1); //non inverting
  //TCCR1A |= (1 << COM1A1)|(1 << COM1A0); //invert
  
  ICR1 = 65535;  
  OCR1A = 16838; //25% duty cycle   
  TCCR1B |= (1 << CS10);                   //1 prescaller
  //TCCR1B |= (1 << CS11);                   //8 prescaller
  //TCCR1B |= (1 << CS10)|(1 << CS11);       //64 prescaller
  //TCCR1B |= (1 << CS12);                   //256 prescaller
  //TCCR1B |= (1 << CS12)|(1 << CS10);       //1024 prescaller
  interrupts(); 
}

void loop(){
}