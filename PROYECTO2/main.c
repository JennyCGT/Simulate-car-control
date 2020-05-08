#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void conf_micro();
void conf_timer();
void conf_ADC();
void config_comun();
void tomardatos();
void luces();
void motor();
void cargardatos();
void transmitir(int dato);

int acelerador=0,freno=0,nivel=0, temp=0,b,veces=0, encoder=0;
double velocidad=0,niv=0;
int datovelo=0, datodista=0, datonivel=0, datotemp=0, datoluces=0; 
int c=0,temperatura=0,calculo=0,puerto=0;
int y=94;
double angulo=0,distancia=0,velo=0;
unsigned char prender,B,L;
unsigned char x;

void servo();
int main(void)
{
	conf_ADC();
	conf_micro();
	conf_timer();
	config_comun();
	
	while (1)
	{
		sei();
		luces();
		tomardatos();
		motor();
		servo();
		cargardatos();
		
	}
	
}


void conf_micro()
{
	DDRA=0b11110000;
	DDRB=0b11000000;
	PORTB=0b11111111;
	DDRC=0b11111111;
	DDRD=0b11111110;
	
}

void conf_ADC()
{
	ADMUX=0b01100000;
	ADCSRA=0b11000110;
	DIDR0=0b00000111;
}
void tomardatos(){
	
	//acelerador
	ADMUX=0b01100000;
	ADCSRA=0b11000110;
	while(ADCSRA&(1<<6));
	ADCSRA=0b01000110;
	acelerador=ADCH;
	//freno
	ADMUX=0b01100001;
	ADCSRA=0b11000110;
	while(ADCSRA&(1<<6));
	ADCSRA=0b01000110;
	freno=ADCH;
	//nivel
	ADMUX=0b01100010;
	ADCSRA=0b11000110;
	while(ADCSRA&(1<<6));
	ADCSRA=0b01000110;
	nivel=ADCH;
	//temp
	ADMUX=0b01100011;
	ADCSRA=0b11000110;
	while(ADCSRA&(1<<6));
	ADCSRA=0b01000110;
	temp=ADCH;
}


void luces()
{
	int a=PINB;
	//luces delanteras
	if((a&(0b00000010))==0b00000010){
		PORTC|=0b00000001;
	}
	if((a&(0b00000010))==0){
		PORTC&=0b11111110;
	}
	//parqueo
	if((a&(0b00010000))==0b00010000){
		
		//dir d
		if((a&(0b00000100))==0b00000100){
			PORTC&=0b11111011;
		}
		if((a&(0b00000100))==0){
			if (c>=200)
			{ PORTC|=0b00000100;
				c++;
				if (c==400)
				{
					c=0;
				}
				
				}else{
				PORTC&=0b11111011;
				c++;
			}
			
			

		}
		//dir iz
		if((a&(0b00001000))==0b00001000){
			PORTC&=0b11110111;
		}
		if((a&(0b00001000))==0){
			if (c>=200)
			{ PORTC|=0b00001000;
				c++;
				if (c==400)
				{
					c=0;
				}
				
				}else{
				PORTC&=0b11110111;
				c++;
			}
			
		}
	}
	
	if((a&(0b00010000))==0){
		if (c>=200)
		{	PORTC|=0b00000100;
			PORTC|=0b00001000;
			c++;
			if (c==400)
			{
				c=0;
			}
			
			}else{
			PORTC&=0b11110111;
			PORTC&=0b11111011;
			c++;
		}
		
		
		
	}

	//marcha
	if((a&(0b00100000))==0b00100000){
		if (b==1)
		{
			if (OCR1B<10)
			{
				PORTC&=0b11111101;
				b=0;
			}
		}
		if (b==0)
		{
			if(freno>180){
				PORTC|=0b00000010;
			}
			if (freno<180){
				PORTC&=0b11111101;
			}
		}
		
	}
	if((a&(0b00100000))==0){
		
		if (OCR1B<10)
		{	b=1;
			PORTC|=0b00000010;
		}
	}
	
	
}

void servo()
{
	angulo=0.005*OCR1B+6;
	OCR2B=angulo;
	temperatura=1.96*temp;
}
void conf_timer()
{
	//timer0 encoder
	TCCR0A=0b00000000;
	TCCR0B=0b00000111;
	TIMSK0=0b00000001;
	TCNT0=0;
	//timer1 pwm dc
	TCCR1A=0b00100011;
	TCCR1B=0b00011010;
	OCR1A=999;
	OCR1B=46;
	TCNT1=0;
	//timer2 servo y tiempo encoder
	TCCR2A=0b00100011;
	TCCR2B=0b00001111;
	OCR2A=156;
	OCR2B=6;//1ms
	//calculo vel
	TIMSK2=0b00000010;
	TCNT2=0;
	sei();
}
	ISR(TIMER0_OVF_vect){
 	veces++;
 }
ISR(TIMER2_COMPA_vect){
	calculo++;
	if (calculo==50)
	{
	
	encoder=TCNT0+(veces*256);
	velocidad = encoder*0.28;//60/210pulsos por rev
	distancia=distancia+(velocidad*0.0002);//velocidad*(2pi/60)*radio en metros(15 pulgadas=0.381)/ dista en metros
	veces=0;
	TCNT0=0;
	calculo=0;	
	}
		
}

void motor(){
	if (OCR1B<10)
	{
		PORTC&=0b11011111;
	}
	else{
		PORTC|=0b00100000;
		
	}
	if (acelerador>freno+1)
	{
		if (OCR1B==999)
		{ OCR1B=999;
			}else {
			OCR1B++;
			_delay_ms(1);
		}
	}
	if (freno>(acelerador+10))
	{
		if (OCR1B==0)
		{ OCR1B=0;
			}else {
			OCR1B--;
			_delay_ms(1);
		}
	}
	
}


void config_comun(){
	UBRR0L=51;
	UBRR0H=0;
	UCSR0A|=(1<<7);
	UCSR0B=0b10011000;
	UCSR0C=0b00000110;
}
void transmitir(int dato){
	 x=dato;
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=x;
}
void cargardatos(){
	 
	 velo=velocidad*0.27;//numero maximo/100
	 velo=velo;
	datovelo=velo;
	datodista=distancia;//velocidad*(2pi/60)*radio en metros(15 pulgadas=0.381)/ dista en metros
	niv=(nivel*9.09)-227.27;
	datonivel=niv;//ec nivel
	datotemp=temperatura;
	if (b==0)
	{
		PORTC&=0b10111111;	
	}
	if (b==1)
	{
		PORTC|=0b01000000;		
	}
	
	datoluces=PORTC;
	

}
ISR(USART0_RX_vect){
	prender=UDR0;
	
	PORTC|=(1<<7);
// 	if (prender=='L')
// 	{
// 		transmitir(datovelo);
// 		
// // 		transmitir(datodista);
// // 		transmitir(datonivel);
// // 		transmitir(datotemp);
// // 		transmitir(datoluces);
// // 		transmitir(y);
// 	}
// 	if (prender=='C')
// 	{
// 		transmitir(datodista);
// 	}
// 	if (prender=='V')
// 	{
// 		transmitir(datonivel);
// 	}
// 	if (prender=='N')
// 	{
// 		transmitir(datotemp);
// 	}
// 	if (prender=='M')
// 	{
// 		transmitir(datoluces);
// 	}
	
}
