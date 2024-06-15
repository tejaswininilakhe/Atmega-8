#line 1 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Keys.c"
#line 1 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/comm.h"
#line 13 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/comm.h"
struct sCommData
{
 float fCalibFact_VtgR;
 float fCalibFact_VtgY;
 float fCalibFact_VtgB;
 float fCalibFact_CurA;
 float fCalibFact_CurB;
 float fCalibFact_CurC;
 unsigned int uiROverVtg;
 unsigned int uiYOverVtg;
 unsigned int uiBOverVtg;

 unsigned int uiRUndVtg;
 unsigned int uiYUndVtg;
 unsigned int uiBUndVtg;

 unsigned int uiRDryRun;
 unsigned int uiYDryRun;
 unsigned int uiBDryRun;

 unsigned int uiROverCur;
 unsigned int uiYOverCur;
 unsigned int uiBOverCur;

 unsigned int uiPowerOnDelay;
 unsigned int uiDryRunCheck;

 unsigned int uiSinglePhaseTh;
 unsigned int uiOLTh;
 unsigned int uiDryRunTh;
 unsigned int uiOvVtgTh;
 unsigned int uiUvVtgTh;

};
#line 93 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/comm.h"
void vSerialInit(void);
unsigned char ucFindIndex( unsigned char *ucSource,unsigned char ucData,unsigned char ucIndex);
char putchar (char c);
void vCheckPacket(unsigned char usRecData);
void vInitDefaultData(void);
void vDecodePacket(void);

void vReadCommand(void);
void vWriteCommand(void);
#line 124 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/comm.h"
extern struct sCommData SerialData;
extern unsigned char ucBuff[50];


extern unsigned char bFlag;
extern unsigned char ucInputPassBuf[ 20 ];
extern unsigned char ucInputPass[ 20 ];
extern bit bWriteFlag;
#line 1 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/keys.h"



void vReadKey(void);
void vKeysInit(void);
#line 29 "d:/ipdu_all using boards_data/lakshmi/avr_10_6_2016/keys.h"
bit bKeyLeft;
bit bEffects;
bit bModes;
bit bKeyRight;
bit bKey2_Trigger;
#line 6 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Keys.c"
unsigned char ucKeyState[4];
unsigned int uiKeyArrayPress[4];
unsigned int uiKeyArrayRel[4];
#line 22 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Keys.c"
void vReadKey(void)
{

 if(! PINB1_bit )
 {

 uiKeyArrayRel[0] = 0;
 uiKeyArrayPress[0]++;

 if(uiKeyArrayPress[0]> 100  && ucKeyState[0] ==  0 )

 {
 bKeyLeft = 1;
  PORTB5_bit  = 1;
 uiKeyArrayPress[0] = 0;
 ucKeyState[0] =  1 ;
 }
 }
 else
 {

 uiKeyArrayPress[0] = 0;
 uiKeyArrayRel[0]++;
 if(uiKeyArrayRel[0]> 100  && ucKeyState[0] ==  1 )
 {
 uiKeyArrayRel[0] = 0;
 ucKeyState[0] =  0 ;
 }
 }

 if(! PINB2_bit )
 {

 uiKeyArrayRel[1] = 0;
 uiKeyArrayPress[1]++;
 if(uiKeyArrayPress[1]> 100  && ucKeyState[1] ==  0 )
 {
 bEffects = 1;

 uiKeyArrayPress[1] = 0;
 ucKeyState[1] =  1 ;
 }
 }
 else
 {
 uiKeyArrayPress[1] = 0;
 uiKeyArrayRel[1]++;
 if(uiKeyArrayRel[1]> 100  && ucKeyState[1] ==  1 )
 {

 uiKeyArrayRel[1] = 0;
 ucKeyState[1] =  0 ;
 }
 }


 if(! PINB3_bit )
 {

 uiKeyArrayRel[2] = 0;
 uiKeyArrayPress[2]++;
 if(uiKeyArrayPress[2]> 100  && ucKeyState[2] ==  0 )
 {
 bKeyRight = 1;
 uiKeyArrayPress[2] = 0;
 ucKeyState[2] =  1 ;
 }
 }
 else
 {
 uiKeyArrayPress[2] = 0;
 uiKeyArrayRel[2]++;
 if(uiKeyArrayRel[2]> 100  && ucKeyState[2] ==  1 )
 {

 uiKeyArrayRel[2] = 0;
 ucKeyState[2] =  0 ;
 }
 }

 if(! PINB4_bit )
 {
 uiKeyArrayRel[3] = 0;
 uiKeyArrayPress[3]++;
 if(uiKeyArrayPress[3]> 100  && ucKeyState[3] ==  0 )
 {
 bKey2_Trigger = 1;
 uiKeyArrayPress[3] = 0;
 ucKeyState[3] =  1 ;
 }
 }
 else
 {
 uiKeyArrayPress[3] = 0;
 uiKeyArrayRel[3]++;
 if(uiKeyArrayRel[3]> 100  && ucKeyState[3] ==  1 )
 {
 uiKeyArrayRel[3] = 0;
 ucKeyState[3] =  0 ;
 }
 }
}


void vKeysInit(void)
{
  DDB1_bit  = 0;
  DDB2_bit  = 0;
  DDB3_bit  = 0;
  DDB4_bit  = 0;

  PORTB1_bit  = 1;
  PORTB2_bit  = 1;
  PORTB3_bit  = 1;
  PORTB4_bit  = 1;

 bKey2_Trigger = 0;
 bKeyLeft = 0;
 bKeyRight = 0;

 ucKeyState[0] = 0;
 ucKeyState[1] = 0;
 ucKeyState[2] = 0;
 ucKeyState[3] = 0;
}
