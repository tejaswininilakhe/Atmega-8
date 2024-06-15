#line 1 "D:/tejaswini/AVR_27_7_2016/ModBus.c"
#line 1 "d:/tejaswini/avr_27_7_2016/lcd.h"

sbit LCD_RS at PORTC3_bit;
sbit LCD_EN at PORTC2_bit;
sbit LCD_D4 at PORTB4_bit;
sbit LCD_D5 at PORTB3_bit;
sbit LCD_D6 at PORTB2_bit;
sbit LCD_D7 at PORTB1_bit;

sbit LCD_RS_Direction at DDC3_bit;
sbit LCD_EN_Direction at DDC2_bit;
sbit LCD_D4_Direction at DDB4_bit;
sbit LCD_D5_Direction at DDB3_bit;
sbit LCD_D6_Direction at DDB2_bit;
sbit LCD_D7_Direction at DDB1_bit;
#line 8 "D:/tejaswini/AVR_27_7_2016/ModBus.c"
void vClearBuffer(void);
 void vSendPacket(unsigned char *Data,unsigned char ucLen);



bit bSec;
#line 27 "D:/tejaswini/AVR_27_7_2016/ModBus.c"
unsigned char ucVoltage[] = {0x01,0x03,0x63,0x06,0x00,0x01,0x7A,0x4F};
unsigned char ucCurrent[] = {0x01,0x03,0x63,0x02,0x00,0x01,0x3B,0x8E};
unsigned char ucFreq[] = {0x01,0x03,0x63,0x01,0x00,0x01,0xCB,0x8E};


unsigned char ucPacketIndex;
unsigned char ucPacket[20];

bit bCommStatus;

unsigned char ucKeyPress;
void USART_Init(void);
void USART_SendByte(unsigned char u8Data);
void vInitTimer_1(void);
unsigned int uiVoltage;
unsigned int uiCurrent;
unsigned int uiFreq;
unsigned char ucBuff[50];
void main()
{

 unsigned char ucData,ucData1;
 unsigned char i;
  DDB5_bit  = 1;
 USART_Init();
 vInitTimer_1();
 SREG_I_bit = 1;
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"  Lakshmi Solar ");

 USART_SendByte('L');
 USART_SendByte('A');
 USART_SendByte('K');
 USART_SendByte('S');
 USART_SendByte('H');
 USART_SendByte('M');
 USART_SendByte('I');
  PORTB5_bit  = 0;
 vClearBuffer();
 while(1)
 {
 ucPacketIndex=0;
 SREG_I_bit = 0;
 RXEN0_bit = 0;
 vSendPacket(&ucVoltage,8);
 SREG_I_bit = 1;
 RXEN0_bit = 1;
 delay_ms(1000);
 if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
 {
 uiVoltage = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
 bCommStatus = 1;
 }
 else
 {
 bCommStatus = 0;
 }
 vClearBuffer();

 ucPacketIndex=0;
 SREG_I_bit = 0;
 RXEN0_bit = 0;
 vSendPacket(&ucCurrent,8);
 SREG_I_bit = 1;
 RXEN0_bit = 1;
 delay_ms(1000);
 if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
 {
 uiCurrent = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
 bCommStatus = 1;
 }
 else
 {
 bCommStatus = 0;
 }
 vClearBuffer();

 ucPacketIndex=0;
 SREG_I_bit = 0;
 RXEN0_bit = 0;
 vSendPacket(&ucFreq,8);
 SREG_I_bit = 1;
 RXEN0_bit = 1;
 delay_ms(1000);
 if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
 {
 uiFreq = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
 bCommStatus = 1;
 }
 else
 {
 bCommStatus = 0;
 }
 vClearBuffer();

 if(bCommStatus)
 {
 sprintf(ucBuff,"V%3u I%5.1f F%3u",uiVoltage,(uiCurrent/(float)10),(uiFreq));

 sprintf(ucBuff,"V%3u I%3.1f F%3.1f",uiVoltage,(uiCurrent/(float)10),(float)(uiFreq/(float)100));
 Lcd_Out(2,1,ucBuff);
 }
 else
 {
 sprintf(ucBuff,"V--- I--- F-----");
 Lcd_Out(2,1,ucBuff);
 }
 }
}



void vSerialRx_ISR() org IVT_ADDR_USART__RX
{
 unsigned char dmxByte;
 if ( FE0_bit)
 {
 dmxByte = UDR0;
 }
 else
 {
 dmxByte = UDR0;
 ucPacket[ucPacketIndex]=dmxByte;
 ucPacketIndex++;
  PORTB5_bit  = ~ PORTB5_bit ;
 }
}









void USART_Init(void){
 if(1)
 {
 UBRR0L =  ((( 16000000  / ( 9600  * 16UL))) - 1) ;
 UBRR0H = ( ((( 16000000  / ( 9600  * 16UL))) - 1)  >> 8);
 }
 else
 {
 }



 TXEN0_bit = 1;
 RXEN0_bit = 1;
 RXCIE0_bit = 1;

}

void USART_SendByte(unsigned char u8Data){





 UDR0 = u8Data;
 while(UDRE0_bit == 0);
}


void vSendPacket(unsigned char *Data,unsigned char ucLen)
{
 unsigned char ucCount=0;
 while(ucLen)
 {
 ucLen--;
 USART_SendByte(Data[ucCount]);
 ucCount++;
 }
}

unsigned int uci;
void vTimer1_ISR() org IVT_ADDR_TIMER1_OVF
{

 TCNT1H = 0XF8;
 TCNT1L = 0X2F;

 uci++;
 if(uci>1000)
 {
 uci = 0;
 bSec = 1;
 }

}

void vInitTimer_1(void)
{


 CS10_bit = 0;
 CS11_bit = 1;
 CS12_bit = 0;

 TOIE1_bit = 1;

 TCNT1H = 0;
 TCNT1L = 0;
}

void vInitDefaultData(void)
{


}

void vClearBuffer(void)
{
 unsigned char ucCounter=0;
 for(ucCounter=0;ucCounter<20;ucCounter++)
 {
 ucPacket[ucCounter] = 0x00;
 }
}
