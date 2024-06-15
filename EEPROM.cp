#line 1 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/EEPROM.c"
#line 1 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/eeprom.h"



void vWriteData(unsigned char *ucType,unsigned int DateSize);
void vReadData(unsigned char *ucType,unsigned int DateSize);
#line 6 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/EEPROM.c"
void vWriteData(unsigned char *ucType,unsigned int DateSize)
{
 unsigned int uiAddress=0x00;

 while(DateSize)
 {
 EEPROM_Write(uiAddress,*ucType);
 DateSize--;
 uiAddress++;
 ucType++;
 }
}


void vReadData(unsigned char *ucType,unsigned int DateSize)
{
 unsigned int uiAddress=0x00;

 while(DateSize)
 {
 *ucType = EEPROM_Read(uiAddress);
 DateSize--;
 uiAddress++;
 ucType++;
 }
}
