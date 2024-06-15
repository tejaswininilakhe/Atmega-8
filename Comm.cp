#line 1 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Comm.c"
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








unsigned char ucBuff[50];
struct sCommData SerialData;





unsigned char bFlag;

unsigned char ucInputPassBuf[ 20 ];
unsigned char ucInputPass[ 20 ];
bit bWriteFlag;
#line 4 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Comm.c"
unsigned char ucIndex;
unsigned char ucState;
volatile unsigned char bTxCom;










void vCheckPacket(unsigned char usRecData)
{


 if(1)
 {

 if(1)
 {

 switch(ucState)
 {
 case  0x01 :
 ucIndex = 0;
 if(usRecData == '<')
 {
 ucState =  0x02 ;


 }
 break;

 case  0x02 :
 if(usRecData == '>')
 {
 ucState =  0x01 ;
 ucInputPass[ucIndex]='\0';
 bFlag = 1;

 }
 else
 {
 ucInputPass[ucIndex++]= usRecData;
 if(ucIndex> 20 -1 || usRecData=='<')
 {
 ucState =  0x01 ;
 }
 }
 break;

 case  0x03 :;
 ucState =  0x01 ;
 break;
 }
 }
 else
 {

 }
 }

}
#line 123 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Comm.c"
unsigned char ucFindIndex( unsigned char *ucSource,unsigned char ucData,unsigned char ucIndex)
{
 unsigned char ucIndex1=0;
 unsigned char ucIndex2=0;
 unsigned char ucCount = 0;

 while(*ucSource!='\0')
 {
 if(*ucSource==ucData)
 {
 switch(ucIndex)
 {
 case 0:
 ucIndex2 = ucIndex1;
 ucCount++;
 if(ucCount>=1)
 {

 }
 break;

 case 1:
 ucIndex2 = ucIndex1;
 if(ucCount>=2)
 {

 }
 break;

 case 2:
 break;

 }

 }
 if(ucCount==(ucIndex+1))
 break;
 ucSource++;
 ucIndex1++;
 }

 return ucIndex2;
}

void vSerialInit(void)
{
 ucState =  0x01 ;

}

void vDecodePacket(void)
{
 switch(ucInputPassBuf[0])
 {
 case 'R':
 vReadCommand();
 break;
 case 'W':
 vWriteCommand();
 break;

 default:;
 }
}


void vReadCommand(void)
{
 unsigned int uiCommand;
 unsigned char uiIndex =0 ;
 unsigned int uiCount;

 uiCommand = atoi(&ucInputPassBuf[2]);

 switch(uiCommand)
 {
 case 0:
 sprintf(ucBuff,"<R:0:%8.8f>",SerialData.fCalibFact_VtgR);
 UART1_Write_Text(ucBuff);
 break;

 case 1:
 sprintf(ucBuff,"<R:1:%8.8f>",SerialData.fCalibFact_VtgY);
 UART1_Write_Text(ucBuff);
 break;

 case 2:
 sprintf(ucBuff,"<R:2:%8.8f>",SerialData.fCalibFact_VtgB);
 UART1_Write_Text(ucBuff);
 break;

 case 3:
 sprintf(ucBuff,"<R:3:%8.8f>",SerialData.fCalibFact_CurA);
 UART1_Write_Text(ucBuff);
 break;

 case 4:
 sprintf(ucBuff,"<R:4:%8.8f>",SerialData.fCalibFact_CurB);
 UART1_Write_Text(ucBuff);
 break;

 case 5:
 sprintf(ucBuff,"<R:5:%8.8f>",SerialData.fCalibFact_CurC);
 UART1_Write_Text(ucBuff);
 break;

 case 6:
 sprintf(ucBuff,"<R:6:%u>",SerialData.uiROverVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 7:
 sprintf(ucBuff,"<R:7:%u>",SerialData.uiYOverVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 8:
 sprintf(ucBuff,"<R:8:%u>",SerialData.uiBOverVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 9:
 sprintf(ucBuff,"<R:9:%u>",SerialData.uiRUndVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 10:
 sprintf(ucBuff,"<R:10:%u>",SerialData.uiYUndVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 11:
 sprintf(ucBuff,"<R:11:%u>",SerialData.uiBUndVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 12:
 sprintf(ucBuff,"<R:12:%u>",SerialData.uiRDryRun);
 UART1_Write_Text(ucBuff);
 break;

 case 13:
 sprintf(ucBuff,"<R:13:%u>",SerialData.uiYDryRun);
 UART1_Write_Text(ucBuff);
 break;

 case 14:
 sprintf(ucBuff,"<R:14:%u>",SerialData.uiBDryRun);
 UART1_Write_Text(ucBuff);
 break;

 case 15:
 sprintf(ucBuff,"<R:15:%u>",SerialData.uiROverCur);
 UART1_Write_Text(ucBuff);
 break;

 case 16:
 sprintf(ucBuff,"<R:16:%u>",SerialData.uiYOverCur);
 UART1_Write_Text(ucBuff);
 break;


 case 17:
 sprintf(ucBuff,"<R:17:%u>",SerialData.uiBOverCur);
 UART1_Write_Text(ucBuff);
 break;

 case 18:
 sprintf(ucBuff,"<R:18:%u>",SerialData.uiPowerOnDelay);
 UART1_Write_Text(ucBuff);
 break;

 case 19:
 sprintf(ucBuff,"<R:19:%u>",SerialData.uiDryRunCheck);
 UART1_Write_Text(ucBuff);
 break;

 case 20:
 sprintf(ucBuff,"<R:20:%u>",SerialData.uiSinglePhaseTh);
 UART1_Write_Text(ucBuff);
 break;

 case 21:
 sprintf(ucBuff,"<R:21:%u>",SerialData.uiOLTh);
 UART1_Write_Text(ucBuff);
 break;

 case 22:
 sprintf(ucBuff,"<R:22:%u>",SerialData.uiDryRunTh);
 UART1_Write_Text(ucBuff);
 break;
 case 23:
 sprintf(ucBuff,"<R:23:%u>",SerialData.uiOvVtgTh);
 UART1_Write_Text(ucBuff);
 break;
 case 24:
 sprintf(ucBuff,"<R:24:%u>",SerialData.uiUvVtgTh);
 UART1_Write_Text(ucBuff);
 break;

 default:;

 }
}
#line 482 "D:/iPDU_All using Boards_Data/Lakshmi/AVR_10_6_2016/Comm.c"
void vWriteCommand(void)
{
 unsigned int uiCommand,uiIndex;




 uiIndex = ucFindIndex(&ucInputPassBuf,':',1);
 ucInputPassBuf[uiIndex] = '\0';

 uiCommand = atoi(&ucInputPassBuf[2]);
 ucInputPassBuf[uiIndex] = ':';

 switch(uiCommand)
 {
 case 0:
 SerialData.fCalibFact_VtgR = atof(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:0:%8.8f>",SerialData.fCalibFact_VtgR);
 UART1_Write_Text(ucBuff);

 break;

 case 1:
 SerialData.fCalibFact_VtgY = atof(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:1:%8.8f>",SerialData.fCalibFact_VtgY);
 UART1_Write_Text(ucBuff);
 break;

 case 2:
 SerialData.fCalibFact_VtgB = atof(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:2:%8.8f>",SerialData.fCalibFact_VtgB);
 UART1_Write_Text(ucBuff);
 break;

 case 3:
 SerialData.fCalibFact_CurA = atof(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:3:%8.8f>",SerialData.fCalibFact_CurA);
 UART1_Write_Text(ucBuff);
 break;

 case 4:
 SerialData.fCalibFact_CurB = atof(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:4:%8.8f>",SerialData.fCalibFact_CurB);
 UART1_Write_Text(ucBuff);
 break;

 case 5:
 SerialData.fCalibFact_CurC = atof(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:5:%8.8f>",SerialData.fCalibFact_CurC);
 UART1_Write_Text(ucBuff);
 break;

 case 6:
 SerialData.uiROverVtg = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:6:%u>",SerialData.uiROverVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 7:
 SerialData.uiYOverVtg = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:7:%u>",SerialData.uiYOverVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 8:
 SerialData.uiBOverVtg = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:8:%u>",SerialData.uiBOverVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 9:
 SerialData.uiRUndVtg = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:9:%u>",SerialData.uiRUndVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 10:
 SerialData.uiYUndVtg = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:10:%u>",SerialData.uiYUndVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 11:
 SerialData.uiBUndVtg = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:11:%u>",SerialData.uiBUndVtg);
 UART1_Write_Text(ucBuff);
 break;

 case 12:
 SerialData.uiRDryRun = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:12:%u>",SerialData.uiRDryRun);
 UART1_Write_Text(ucBuff);
 break;

 case 13:
 SerialData.uiYDryRun = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:13:%u>",SerialData.uiYDryRun);
 UART1_Write_Text(ucBuff);
 break;

 case 14:
 SerialData.uiBDryRun = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:14:%u>",SerialData.uiBDryRun);
 UART1_Write_Text(ucBuff);
 break;

 case 15:
 SerialData.uiROverCur = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:15:%u>",SerialData.uiROverCur);
 UART1_Write_Text(ucBuff);
 break;

 case 16:
 SerialData.uiYOverCur = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:16:%u>",SerialData.uiYOverCur);
 UART1_Write_Text(ucBuff);
 break;

 case 17:
 SerialData.uiBOverCur = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:17:%u>",SerialData.uiBOverCur);
 UART1_Write_Text(ucBuff);
 break;

 case 18:
 SerialData.uiPowerOnDelay = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:18:%u>",SerialData.uiPowerOnDelay);
 UART1_Write_Text(ucBuff);
 break;

 case 19:
 SerialData.uiDryRunCheck = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:19:%u>",SerialData.uiDryRunCheck);
 UART1_Write_Text(ucBuff);
 break;

 case 20:
 SerialData.uiSinglePhaseTh = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:20:%u>",SerialData.uiSinglePhaseTh);
 UART1_Write_Text(ucBuff);
 break;

 case 21:
 SerialData.uiOLTh = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:21:%u>",SerialData.uiOLTh);
 UART1_Write_Text(ucBuff);
 break;

 case 22:
 SerialData.uiDryRunTh = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:22:%u>",SerialData.uiDryRunTh);
 UART1_Write_Text(ucBuff);
 break;

 case 23:
 SerialData.uiOvVtgTh = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:23:%u>",SerialData.uiOvVtgTh);
 UART1_Write_Text(ucBuff);
 break;

 case 24:
 SerialData.uiUvVtgTh = atoi(&ucInputPassBuf[uiIndex+1]);
 sprintf(ucBuff,"<W:24:%u>",SerialData.uiUvVtgTh);
 UART1_Write_Text(ucBuff);
 break;



 default:;

 }
 bWriteFlag = 1;
}
