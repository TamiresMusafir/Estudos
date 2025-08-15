#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 4000000

ISR(TIMER2_COMPA_vect) {
  PINC = 0x0E; //
}

int main() {
  
  setup_hardware();
  return 0;
}

void setup_hardware(){

  cli();

  // Ligar os pinos PB, PC, PD
  PORTB = 0X00; // 0000 0000
        // PB   // 7654 3210
  PORTC = 0X00; // 0000 0000
  PORTD = 0X00; // 0000 0000

  // Definir saída ou entrada nos pinos
  DDRB = 0xFF; // 1111 1111
  DDRC = 0x0E; // 0000 1110
  DDRD = 0x00; // 0000 0000

  // Conifugração da interrupção externa
  EICRA = 0x0A; // 0000 1010 borda de descida
  EIMSK = 0x03; // 0000 0011
  EIFR  = 0x00;

  // Setup Timer 2 para 5 milissegundos 
  TCCR2A = 0x02; // 0000 0010 
  TCC2B  = 0x05; // 0000 0101

  TCNT2  = 0; //0000 0000
  OCR2A  = 155; //
  OCR2B  = 0; //0000 0000
  timsk2 = 0x02; //0000 0010

  TIFR2 = 0x00; //0000 0000
  ASSR = 0x00; //0000 0000
  GTCCR = 0x00;// 0000 0000

  sei();
}

void f_rtos(){

  //

  if (count_1<max1)
}