#line 1 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/TRAIC.c"
#line 1 "d:/ipdu_all using boards_data/drusti/avr_based/avr/comm.h"
#line 39 "d:/ipdu_all using boards_data/drusti/avr_based/avr/comm.h"
struct stDevicePar
{
 unsigned char ucRed;
 unsigned char ucGreen;
 unsigned char ucBlue;
 unsigned char ucFanSpeed;
 unsigned char ucFlouid;
};



void vSerialInit(void);
unsigned char ucFindIndex( unsigned char *ucSource,unsigned char ucData,unsigned char ucIndex);
char putchar (char c);
void vCheckPacket(unsigned char usRecData);
void vInitDefaultData(void);
void vDecodePacket(void);

void vReadCommand(void);
void vWriteCommand(void);
#line 74 "d:/ipdu_all using boards_data/drusti/avr_based/avr/comm.h"
extern unsigned char ucBuff[20];

extern unsigned char bFlag;
extern unsigned char ucInputPassBuf[ 20 ];
extern unsigned char ucInputPass[ 20 ];
extern struct stDevicePar stDeviceConfig;
#line 1 "d:/ipdu_all using boards_data/drusti/avr_based/avr/display.h"
#line 13 "d:/ipdu_all using boards_data/drusti/avr_based/avr/display.h"
void vInitDisplay(void);
void vPushDataAdd(void);
void vPushDataSub(void);
void vDisplayData(unsigned char ucData);
void vTestDisplay(void);
void vDisplayDigits(void);
void vDisplayInt(unsigned int uiData);





extern unsigned char ucDisData[3];
extern unsigned char code ucDisplayLoopUp[36];
#line 1 "d:/ipdu_all using boards_data/drusti/avr_based/avr/displaysm.h"



void vUpdateStateMachine(unsigned char ucKeyPress);
unsigned char BCDToDecimal (unsigned char bcdByte);
unsigned char DecimalToBCD (unsigned char decimalByte);
void vInitSM(void);
#line 51 "d:/ipdu_all using boards_data/drusti/avr_based/avr/displaysm.h"
extern bit bAirPumpTrigger;
extern bit bFlouidPumpTrigger;

extern bit bBtModule;
extern bit bBtStatus;

extern unsigned char scOldFanSpeed;
extern unsigned char scOldFlouidSpeed;
extern unsigned char scOldRed;
extern unsigned char scOldGreen;
extern unsigned char scOldBlue;

extern unsigned char scRed;
extern unsigned char scGreen;
extern unsigned char scBlue;
extern unsigned char scFanSpeed;
extern unsigned char scFlouidSpeed;
extern unsigned char ucEffectsState;
extern unsigned char ucModes;

extern bit bUpdateStateMachine;
extern bit bPowerStatus;
extern bit bPowerOff;
extern bit bPowerOn;
extern bit bDelayMode;
#line 1 "d:/ipdu_all using boards_data/drusti/avr_based/avr/traic.h"





void vTraicControl(void);
void vInitTraicModule(void);
void vFanGateTrig(void);


unsigned int uiReloadCount;
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
#line 10 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/TRAIC.c"
bit bFfire;
bit bFANfire;







void vFlouidGateTrig(void);
void vFiring_Angle_Count(unsigned int uiHexCount1);
unsigned char ucIndication;
#line 56 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/TRAIC.c"
unsigned char ucSerialCheck;
unsigned char ucPower;
float fTimePeroid;

unsigned int uiFlouidCount;
unsigned int uiFanCount;

unsigned long ulTotalCount;

unsigned int uiTotal_count;
bit bDataReadyFlag;
bit bPower_On;





bit bTest;
unsigned int ucFireCount,ucFireCount1;

void vTraicControl(void)
{
 if(bFfire)
 {
 ucFireCount++;
 if(ucFireCount>80)
 {

 bFfire = 0;
  PORTB0_bit  = 0;
 ucFireCount=0;
 }
 }

 if(bFANfire)
 {
 ucFireCount1++;
 if(ucFireCount1>80)
 {
 bFANfire = 0;
  PORTD4_bit  = 0;
 ucFireCount1=0;
 }
 }

 if(scOldFanSpeed!=scFanSpeed)
 {
 scOldFanSpeed = scFanSpeed ;
 uiReloadCount = (((100-scFanSpeed)/(float)100)*8.5*0.001)/(float)(1/(float)2000000);
 uiReloadCount = uiReloadCount + 0xBD97;




 OCR1BH = uiReloadCount>>8;
 OCR1BL = uiReloadCount;
 }

 if(1)
 {
 if(scOldFlouidSpeed!=scFlouidSpeed)
 {
 scOldFlouidSpeed = scFlouidSpeed;
 uiReloadCount = (((100-scFlouidSpeed)/(float)100)*8.5*0.001)/(float)(1/(float)2000000);
 uiReloadCount = uiReloadCount + 0xBD97;



 OCR1AH = uiReloadCount>>8;
 OCR1AL = uiReloadCount;
 }
 }

 if(scOldRed!=scRed)
 {
 scOldRed = scRed;
 pwm_dutycycle(CHAN_BLUE,scRed);
 }

 if(scOldGreen!=scGreen)
 {
 scOldGreen = scGreen;
 pwm_dutycycle(CHAN_GREEN,scGreen);

 }

 if(scOldBlue!=scBlue)
 {
 scOldBlue = scBlue;
 pwm_dutycycle(CHAN_RED,scBlue);

 }


}


unsigned int uiIntCount;
void vInt0_ISR() org IVT_ADDR_INT0
{






 TCNT1H = 0XB1;
 TCNT1L = 0XDF;

  CS10_bit = 0;CS11_bit = 1;CS12_bit = 0; ;
}


void vInitTraicModule(void)
{
 bPower_On = 0;

 ucIndication = 1;

 DDRD &= ~(1 << DDD2);


 PORTD |= (1 << PORTD2);




 EICRA |= (1 << ISC01);
 EICRA &= ~(1 << ISC00);

 EIMSK |= (1 << INT0);


 CS10_bit = 0;
 CS11_bit = 1;
 CS12_bit = 0;

 TOIE1_bit = 1;

 TCNT1H = 0;
 TCNT1L = 0;


 WGM10_bit = 0;
 WGM11_bit = 0;
 WGM12_bit = 0;
 WGM13_bit = 0;

 COM1A1_bit = 0;
 COM1A0_bit = 0;
 COM1B1_bit = 0;
 COM1B0_bit = 0;

 OCIE1A_bit = 1;
 OCIE1B_bit = 1;

 OCR1AH = 0XD5;
 OCR1AL = 0x07;

 OCR1BH = 0xD5;
 OCR1BL = 0x07;



 uiIntCount = 0;


}

void vTimer1_ISR() org IVT_ADDR_TIMER1_OVF
{
  CS10_bit = 0;CS11_bit = 0;CS12_bit = 0; ;
 TCNT1H = 0XB1;
 TCNT1L = 0XDF;


}

void Timer1_COMPA(void) iv IVT_ADDR_TIMER1_COMPA
{
 if(bFlouidPumpTrigger)
 {
  PORTB0_bit  = 1;
 bFfire = 1;
 }
 else
 {
  PORTB0_bit  = 0;
 bFfire = 0;
 }


}
void Timer1_COMPB(void) iv IVT_ADDR_TIMER1_COMPB
{
 if(bAirPumpTrigger)
 {
  PORTD4_bit  = 1;
 bFANfire = 1;
 }
 else
 {
 bFANfire = 0;
  PORTD4_bit  = 0;
 }

}
