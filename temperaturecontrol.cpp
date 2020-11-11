
#include <string.h>
#include <stdio.h>
#include <avr/io.h>

#define F_CPU   16000000UL
#define DDRA    0x1000
#define ADC     0x2000
#define TIMER   0x3000
#define COMPARE_VALUE 41 //  Sensor at 20*C = 200mV. ADC Value = 200 * 1024 / 5000.
    
int main()
{   
    DDRA = 0xFF;
    TCCR1B |= (1 << CS10); // Set up timer
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    ADCSRA |= _BV(ADSC);
    TCCR1B = (1<<CS10) | (1<<CS12); //set the pre-scalar as 1024
	OCR1A = 15620; 	   //1000ms delay
	TCNT1 = 0;
    while(1)
    {
        while(ADCSRA & _BV(ADSC))
        {
        }
        if(ADCH >= COMPARE_VALUE)
        {
            PORTA=0b00000001;
        }
        else if(ADCH < COMPARE_VALUE)
        {
            while((TIFR & (1<<OCF1A)) == 0);// wait till the timer overflow flag is SET
            PORTA=0b00000010;
            TCNT1 = 0; 
            TIFR |= (1<<OCF1A) ;
            PORTA=0b00000000;
            
        }
    }

}
