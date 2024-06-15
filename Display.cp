#line 1 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/Display.c"
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


unsigned char ucDisData[3];
unsigned char code ucDisplayLoopUp[]={0x80,0xED,0x42,0x48,0x2C,0x18,0x10,0xCC,0x00,0x08,0x04,0x30,0x92,0x60,0x12,0x16,0x08,0x34,0xB6,0xE0,0x24,0xB2,0xD4,0x74,0x80,0x06,0x0C,0x76,0x18,0x32,0xA0,0xF0,0xAA,0x24,0x28,0x42,0x7E};
#line 9 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/Display.c"
void vInitDisplay(void)
{
 unsigned char i;
  DDC3_bit  = 1;

  DDC5_bit  = 1;


  PORTC3_bit  = 0;
  PORTC5_bit  = 0;

 for(i=0;i<24;i++)
 {

 }

 delay_ms(1);


 for(i=0;i<24;i++)
 {

  PORTC3_bit  = 0;
 delay_ms(1);
  PORTC5_bit  = 1;
 delay_ms(1);
  PORTC5_bit  = 0;
 delay_ms(1);


 }



 for(i=0;i<24;i++)
 {
  PORTC3_bit  = 1;
 delay_ms(1);
  PORTC5_bit  = 1;
 delay_ms(1);
  PORTC5_bit  = 0;
 delay_ms(1);

 vDisplayData(0x00);
 }

 for(i=0;i<36;i++)
 {


 }
 vDisplayInt(123);

}


void vPushDataAdd(void)
{

 delay_ms( 1 );
  PORTC3_bit  = 1;
 delay_ms( 1 );
  PORTC5_bit  = 1;
 delay_ms( 1 );
  PORTC5_bit  = 0;
 delay_ms( 1 );


}

void vPushDataSub(void)
{

 delay_ms( 1 );
  PORTC3_bit  = 0;
 delay_ms( 1 );
  PORTC5_bit  = 1;
 delay_ms( 1 );
  PORTC5_bit  = 0;
 delay_ms( 1 );

}

void vDisplayData(unsigned char ucData)
{
 unsigned char i;

 for(i=0;i<8;i++)
 {

 delay_ms( 1 );
 if(ucData & 0x80)
 {
  PORTC3_bit  = 1;
 }
 else
 {
  PORTC3_bit  = 0;
 }


 delay_ms( 1 );
  PORTC5_bit  = 1;
 delay_ms( 1 );
  PORTC5_bit  = 0;
 delay_ms( 1 );
 ucData = ucData<<1;
 }

}

void vDisplayDigits(void)
{
 vDisplayData(ucDisData[2]);
 vDisplayData(ucDisData[0]);
 vDisplayData(ucDisData[1]);
}


void vDisplayInt(unsigned int uiData)
{
 unsigned char i,a,b,c,d,e;
 a = uiData/10000;
 b = (uiData%10000)/1000;
 c = ((uiData%10000)%1000)/100;
 d = (((uiData%10000)%1000)%100)/10;
 e = (((uiData%10000)%1000)%100)%10;

 ucDisData[0] = ucDisplayLoopUp[c];
 ucDisData[1] = ucDisplayLoopUp[d];
 ucDisData[2] = ucDisplayLoopUp[e];
 vDisplayDigits();

}
