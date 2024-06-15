#line 1 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/ADE7758.c"
#line 1 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/spi.h"
#line 16 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/spi.h"
void SPI1_Enable(void);
void SPI1_Disable(void);
unsigned char SPI1_ucGetByte(void);
unsigned char SPI1_vSendByte(unsigned char ucData);
void SPI_vInit(void);
#line 1 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
#line 16 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
typedef unsigned int USHORT;
typedef unsigned char UCHAR;
#line 235 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
typedef union LICHAR
{

 unsigned long ulData;
 signed long slData;
 unsigned short uiData[2];
 signed short siData[2];
 unsigned char ucData[4];
}LICHAR;
#line 253 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
typedef struct stADE7758
{
 float fVRms[3];
 float fIRms[3];
 float fVaHr[3];
 float fVarHr[3];
 float fWattHr[3];
 float fCosPhi[3];
}stADE7758 ;

typedef struct stADE7758_Th
{
 float fVRms[3];
 float fIRms[3];
}stADE7758_Th ;
#line 298 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
void vUpdateADE(void);
#line 309 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
void ADE7758_vInit(void);
#line 317 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
void ADE7758_vUpdateData(void);
#line 330 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
void AD7758_Write7758(UCHAR ucChannel,UCHAR ucCount, LICHAR liData);
#line 343 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
void AD7758_Read7758(UCHAR ucChannel,UCHAR ucCount);
#line 354 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/ade7758.h"
LICHAR liTemp_ADEUpdate;
unsigned char ucSPIData;
stADE7758 stADE;
#line 45 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/ADE7758.c"
void ADE7758_vInit(void)
{
 LICHAR liTemp;

 UCHAR uci,i;
 UCHAR ucChannelCount;
 ucChannelCount = 0;
 SPI_vInit();

 for(uci=0;uci<1;uci++)
 {

 liTemp.ucData[0] = 0x70;
 AD7758_Write7758( (USHORT)0x13 , (USHORT)0x01 ,liTemp);



 liTemp.ucData[0] = 0x9C;
 AD7758_Write7758( (USHORT)0x16 , (USHORT)0x01 ,liTemp);

 liTemp.uiData[0] = 0x0FFF;
 AD7758_Write7758( (USHORT)0x1B , (USHORT)0x02 ,liTemp);

 liTemp.slData = 0x0FC0;
 AD7758_Write7758( (USHORT)0x18 , (USHORT)0x03 ,liTemp);

 liTemp.ucData[0] = 0x70;
 AD7758_Write7758( (USHORT)0x17 , (USHORT)0x01 ,liTemp);

 liTemp.uiData[0] = 0x1F4;
 AD7758_Write7758( (USHORT)0x1C , (USHORT)0x02 ,liTemp);


 liTemp.uiData[0] = 0x0000;
 AD7758_Write7758( (USHORT)0x2A , (USHORT)0x02 ,liTemp);

 liTemp.uiData[0] = 0x0000;
 AD7758_Write7758( (USHORT)0x2B , (USHORT)0x02 ,liTemp);

 liTemp.uiData[0] = 0x0000;
 AD7758_Write7758( (USHORT)0x2C , (USHORT)0x02 ,liTemp);


 liTemp.ucData[0] = 0x00;
 AD7758_Write7758( (USHORT)0x16 , (USHORT)0x01 ,liTemp);

 liTemp.ucData[0] = 0x10;
 AD7758_Write7758( (USHORT)0x42 , (USHORT)0x01 ,liTemp);

 liTemp.ucData[0] = 0x10;
 AD7758_Write7758( (USHORT)0x43 , (USHORT)0x01 ,liTemp);

 liTemp.ucData[0] = 0x10;
 AD7758_Write7758( (USHORT)0x44 , (USHORT)0x01 ,liTemp);



 }



}
#line 123 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/ADE7758.c"
void AD7758_Write7758(unsigned char ucChannel,unsigned char ucCount, LICHAR liData)
{

 SPI1_Enable();
 SPI1_vSendByte(ucChannel |  (USHORT)0x80 );
 switch(ucCount)
 {
 case  (USHORT)0x01 :
 SPI1_vSendByte(liData.ucData[0]);
 break;

 case  (USHORT)0x02 :
 SPI1_vSendByte(liData.ucData[1]);
 SPI1_vSendByte(liData.ucData[0]);
 break;

 case  (USHORT)0x03 :
 SPI1_vSendByte(liData.ucData[2]);
 SPI1_vSendByte(liData.ucData[1]);
 SPI1_vSendByte(liData.ucData[0]);
 break;

 default:;
 break;
 }
 SPI1_Disable();

}
#line 165 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/ADE7758.c"
void AD7758_Read7758(unsigned char ucChannel,unsigned char ucCount)
{

 SPI1_Enable();
 SPI1_vSendByte(ucChannel);

 switch(ucCount)
 {
 case  (USHORT)0x01 :

 liTemp_ADEUpdate.ucData[0] = SPI1_ucGetByte();


 break;

 case  (USHORT)0x02 :
 liTemp_ADEUpdate.ucData[1] = SPI1_ucGetByte();
 liTemp_ADEUpdate.ucData[0] = SPI1_ucGetByte();
 break;

 case  (USHORT)0x03 :;
 liTemp_ADEUpdate.ucData[2] = SPI1_ucGetByte();
 liTemp_ADEUpdate.ucData[1] = SPI1_ucGetByte();
 liTemp_ADEUpdate.ucData[0] = SPI1_ucGetByte();
 break;

 default:;
 break;
 }
 SPI1_Disable();

}
