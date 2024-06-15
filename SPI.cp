#line 1 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/SPI.c"
#line 1 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/spi.h"
#line 16 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/spi.h"
void SPI1_Enable(void);
void SPI1_Disable(void);
unsigned char SPI1_ucGetByte(void);
unsigned char SPI1_vSendByte(unsigned char ucData);
void SPI_vInit(void);
#line 38 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/SPI.c"
sbit MISO_DDR at DDC1_bit;
sbit SCLK_DDR at DDC2_bit;
sbit MOSI_DDR at DDC3_bit;
sbit CS_DDR at DDC4_bit;

sbit MISO_Port at PORTC1_bit;
#line 74 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/SPI.c"
void SPI_vInit(void)
{
 MOSI_DDR = 1;
 MISO_DDR = 0;
 SCLK_DDR = 1;
 CS_DDR = 1;
 MISO_Port = 1;
  if(1){PORTC4_bit=1;}else{PORTC4_bit=0;} ;
  if(1){PORTC3_bit=1;}else{PORTC3_bit=0;} ;
  if(0){PORTC2_bit=1;}else{PORTC2_bit=0;} ;
}


unsigned char SPI1_vSendByte(unsigned char ucData)
{
 unsigned char ucTransmitBuffer =  0x80 ;
 unsigned char ucReceiveBuffer =  0x00 ;
  if( 0 ){PORTC2_bit=1;}else{PORTC2_bit=0;} ;
  if( 1 ){PORTC3_bit=1;}else{PORTC3_bit=0;} ;
 while(ucTransmitBuffer)
 {
 if(ucData & ucTransmitBuffer)
 {
  if( 1 ){PORTC3_bit=1;}else{PORTC3_bit=0;} ;
 }
 else
 {
  if( 0 ){PORTC3_bit=1;}else{PORTC3_bit=0;} ;
 }
 delay_us( 10 );
  if( 1 ){PORTC2_bit=1;}else{PORTC2_bit=0;} ;
 delay_us( 10 );
 ucReceiveBuffer = ucReceiveBuffer<< 1 ;
 ucTransmitBuffer = ucTransmitBuffer>> 1 ;
 delay_us( 10 );
 if( PINC1_bit )
 {
 ucReceiveBuffer = ucReceiveBuffer |0x01;
 }
  if( 0 ){PORTC2_bit=1;}else{PORTC2_bit=0;}  ;
 delay_us( 10 );;
 }
  if( 1 ){PORTC3_bit=1;}else{PORTC3_bit=0;} ;
 delay_us( 10 );
 return (ucReceiveBuffer);
}
#line 134 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/SPI.c"
unsigned char SPI1_ucGetByte(void)
{
 unsigned char ucReceivedData;
 ucReceivedData = SPI1_vSendByte( 0xFF );
 return(ucReceivedData);
}

void SPI1_Enable(void)
{
  if(0){PORTC4_bit=1;}else{PORTC4_bit=0;} ;
}

void SPI1_Disable(void)
{
  if(1){PORTC4_bit=1;}else{PORTC4_bit=0;} ;
}
