#line 1 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/DisplaySM.c"
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
#line 21 "d:/ipdu_all using boards_data/drusti/avr_based/avr/displaysm.h"
bit bAirPumpTrigger;
bit bFlouidPumpTrigger;

bit bBtModule;
bit bBtStatus;
bit bPowerStatus;
bit bPowerOff;
bit bPowerOn;


unsigned char scFanSpeed;
unsigned char scFlouidSpeed;
unsigned char scRed;
unsigned char scGreen;
unsigned char scBlue;

unsigned char scOldFanSpeed;
unsigned char scOldFlouidSpeed;
unsigned char scOldRed;
unsigned char scOldGreen;
unsigned char scOldBlue;


unsigned char ucEffectsState;
unsigned char ucModes;
bit bDelayMode;

bit bUpdateStateMachine;
#line 13 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/DisplaySM.c"
bit bPartStatus;
bit bRandomStatus;
bit bDelayStatus;


bit bModeSaved;
bit bEffectsSaved;

signed char scDelay;

unsigned char ucModesOld,ucEffectsOLd;

void vUpdateStateMachine(unsigned char ucKeyPress)
{
 unsigned char i;

 if(ucKeyPress &  0x04 )
 {
 bEffectsSaved = 0;
 if(!bModeSaved)
 {
 ucModesOld = ucModes;
 ucModes = 0xFF;
 ucEffectsState = ucEffectsOLd;
 bModeSaved = 1;
 }
 }
 if(ucKeyPress &  0x02 )
 {
 bModeSaved = 0;
 if(!bEffectsSaved)
 {
 ucEffectsOLd = ucEffectsState;
 ucEffectsState = 0xFF;
 ucModes = ucModesOld;
 bEffectsSaved = 1;
 }
 }

 switch(ucModes)
 {
 case  0x00 :
 ucDisData[0] = ucDisplayLoopUp[25];
 ucDisData[1] = ucDisplayLoopUp[27];


 if(ucKeyPress &  0x08 )
 {
 bPartStatus = 0;
 }

 if(ucKeyPress &  0x01 )
 {
 bPartStatus = 1;
 }
 if(ucKeyPress &  0x02 )
 {
 ucModes =  0x01 ;
 }
 if(bPartStatus)
 {
 ucDisData[2] = ucDisplayLoopUp[1];
 }
 else
 {
 ucDisData[2] = ucDisplayLoopUp[0];
 }
 break;

 case  0x01 :
 ucDisData[0] = ucDisplayLoopUp[27];
 ucDisData[1] = ucDisplayLoopUp[13];

 if(ucKeyPress &  0x08 )
 {
 bRandomStatus = 0;
 }

 if(ucKeyPress &  0x01 )
 {
 bRandomStatus = 1;
 }

 if(bRandomStatus)
 {
 ucDisData[2] = ucDisplayLoopUp[1];
 }
 else
 {
 ucDisData[2] = ucDisplayLoopUp[0];
 }

 if(ucKeyPress &  0x02 )
 {
 ucModes =  0x02 ;
 }
 break;

 case  0x02 :
 ucDisData[0] = ucDisplayLoopUp[13];

 if(ucKeyPress &  0x01  )
 {
 scDelay++;
 if(scDelay>99)
 scDelay = 0;
 }
 if(ucKeyPress &  0x08 )
 {
 scDelay--;
 if(scDelay==0)
 scDelay = 99;
 }
 i = DecimalToBCD(scDelay);

 ucDisData[1] = ucDisplayLoopUp[(i>>4)];
 ucDisData[2] = ucDisplayLoopUp[(i&0x0F)];
 if(ucKeyPress &  0x02 )
 {
 ucModes =  0x03 ;
 }
 break;

 case  0x03 :
 ucDisData[0] = ucDisplayLoopUp[11];
 ucDisData[1] = ucDisplayLoopUp[21];

 if(ucKeyPress &  0x08 )
 {
 bBtStatus = 0;
 }

 if(ucKeyPress &  0x01 )
 {
 bBtStatus = 1;
 }

 if(bBtStatus)
 {
 ucDisData[2] = ucDisplayLoopUp[1];
 }
 else
 {
 ucDisData[2] = ucDisplayLoopUp[0];
 }

 if(ucKeyPress &  0x02 )
 {
 ucModes =  0x00 ;
 }
 break;

 default:;
 }

 if(1)
 {
 switch(ucEffectsState)
 {
 case  0x00 :
 if(ucKeyPress &  0x08 )
 {
 scFlouidSpeed--;
 if(scFlouidSpeed==0)
 scFlouidSpeed = 99;
 }
 if(ucKeyPress &  0x01 )
 {
 scFlouidSpeed++;
 if(scFlouidSpeed>99)
 scFlouidSpeed = 00;
 }
 if(ucKeyPress &  0x04 )
 {
 ucEffectsState =  0x01 ;
 }

 i = DecimalToBCD(scFlouidSpeed);
 ucDisData[0] = ucDisplayLoopUp[21];
 ucDisData[1] = ucDisplayLoopUp[(i>>4)];
 ucDisData[2] = ucDisplayLoopUp[(i&0x0F)];


 break;

 case  0x01 :
 if(ucKeyPress &  0x08 )
 {
 scFanSpeed--;
 if(scFanSpeed==0)
 scFanSpeed = 99;
 }
 if(ucKeyPress &  0x01 )
 {
 scFanSpeed++;
 if(scFanSpeed>99)
 scFanSpeed = 0;
 }
 if(ucKeyPress &  0x04 )
 {
 ucEffectsState =  0x02 ;
 }

 i = DecimalToBCD(scFanSpeed);
 ucDisData[0] = ucDisplayLoopUp[15];
 ucDisData[1] = ucDisplayLoopUp[(i>>4)];
 ucDisData[2] = ucDisplayLoopUp[(i&0x0F)];

 break;

 case  0x02 :
 if(ucKeyPress &  0x08 )
 {
 scRed--;
 if(scRed==0)
 scRed = 99;
 }
 if(ucKeyPress &  0x01 )
 {
 scRed++;
 if(scRed>99)
 scRed = 0;
 }
 if(ucKeyPress &  0x04 )
 {
 ucEffectsState =  0x03 ;
 }

 i = DecimalToBCD(scRed);
 ucDisData[0] = ucDisplayLoopUp[27];
 ucDisData[1] = ucDisplayLoopUp[(i>>4)];
 ucDisData[2] = ucDisplayLoopUp[(i&0x0F)];

 break;

 case  0x03 :
 if(ucKeyPress &  0x08 )
 {
 scGreen--;
 if(scGreen==0)
 scGreen = 99;
 }
 if(ucKeyPress &  0x01 )
 {
 scGreen++;
 if(scGreen>99)
 scGreen = 0;
 }
 if(ucKeyPress &  0x04 )
 {
 ucEffectsState =  0x04 ;
 }

 i = DecimalToBCD(scGreen);

 ucDisData[0] = ucDisplayLoopUp[16];
 ucDisData[1] = ucDisplayLoopUp[(i>>4)];
 ucDisData[2] = ucDisplayLoopUp[(i&0x0F)];

 break;

 case  0x04 :
 if(ucKeyPress &  0x08 )
 {
 scBlue--;
 if(scBlue==0)
 scBlue = 99;

 }
 if(ucKeyPress &  0x01 )
 {
 scBlue++;
 if(scBlue>99)
 scBlue = 0;
 }

 if(ucKeyPress &  0x04 )
 {
 ucEffectsState =  0x00 ;
 }

 i = DecimalToBCD(scBlue);

 ucDisData[0] = ucDisplayLoopUp[11];
 ucDisData[1] = ucDisplayLoopUp[(i>>4)];
 ucDisData[2] = ucDisplayLoopUp[(i&0x0F)];

 break;

 default:;
 }
 bUpdateStateMachine = 0;
 }
 vDisplayDigits();

}


unsigned char BCDToDecimal (unsigned char bcdByte)
{
 return (((bcdByte & 0xF0) >> 4) * 10) + (bcdByte & 0x0F);
}


unsigned char DecimalToBCD (unsigned char decimalByte)
{
 return (((decimalByte / 10) << 4) | (decimalByte % 10));
}


void vInitSM(void)
{
 ucEffectsState =  0x00 ;
 ucModes =  0x00 ;
 ucModesOld =  0x00 ;
 ucEffectsOLd =  0x00 ;
 bEffectsSaved = 0;
 bModeSaved = 0;
}
