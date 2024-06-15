#line 1 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/PWM.c"
#line 1 "d:/ipdu_all using boards_data/drusti/avr_based/avr/pwm.h"



enum PWM_CHANNEL {


 CHAN_RED = 1,
 CHAN_GREEN = 1<<1,
 CHAN_YELLOW = 1<<2,
 CHAN_BLUE = 1<<3,


 CHAN_1 = 1,
 CHAN_2 = 1<<1,
 CHAN_3 = 1<<2,
 CHAN_4 = 1<<3,


 CHAN_PD6 = 1,
 CHAN_PD5 = 1<<1,
 CHAN_PB3 = 1<<2,
 CHAN_PD3 = 1<<3,


 CHAN_OC0A = 1,
 CHAN_OC0B = 1<<1,
 CHAN_OC2A = 1<<2,
 CHAN_OC2B = 1<<3

};

void pwm_initialize(void);
void pwm_enable(enum PWM_CHANNEL channel);
void pwm_disable(enum PWM_CHANNEL channel);
void pwm_dutycycle(enum PWM_CHANNEL channel, unsigned char dutycycle);
#line 4 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/PWM.c"
void pwm_initialize(void)
{


 TCCR0A |= (1<<WGM00 | 1<<WGM01);
 TCCR2A |= (1<<WGM20 | 1<<WGM21);


 TCCR0B |= (1<<CS01);
 TCCR2B |= (1<<CS21);


 OCR0A = 0x80;
 OCR0B = 0x80;
 OCR2A = 0x80;
 OCR2B = 0x80;



 DDRD |= 1<<DDD3;
 DDRD |= 1<<DDD5;
 DDRD |= 1<<DDD6;

 pwm_enable(CHAN_RED);
 pwm_enable(CHAN_GREEN);
 pwm_enable(CHAN_YELLOW);
 pwm_enable(CHAN_BLUE);

}


void pwm_enable(enum PWM_CHANNEL channel) {
 if (channel & CHAN_OC0A) TCCR0A |= 1<<COM0A1;
 if (channel & CHAN_OC0B) TCCR0A |= 1<<COM0B1;
 if (channel & CHAN_OC2A) TCCR2A |= 1<<COM2A1;
 if (channel & CHAN_OC2B) TCCR2A |= 1<<COM2B1;
}


void pwm_disable(enum PWM_CHANNEL channel) {
 if (channel & CHAN_OC0A) TCCR0A &= ~(1<<COM0A1);
 if (channel & CHAN_OC0B) TCCR0A &= ~(1<<COM0B1);
 if (channel & CHAN_OC2A) TCCR2A &= ~(1<<COM2A1);
 if (channel & CHAN_OC2B) TCCR2A &= ~(1<<COM2B1);
}


void pwm_dutycycle(enum PWM_CHANNEL channel, unsigned char dutycycle)
{
 if (channel & CHAN_OC0A) OCR0A = dutycycle;
 if (channel & CHAN_OC0B) OCR0B = dutycycle;
 if (channel & CHAN_OC2A) OCR2A = dutycycle;
 if (channel & CHAN_OC2B) OCR2B = dutycycle;
}
