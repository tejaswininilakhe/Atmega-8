#line 1 "D:/iPDU_All using Boards_Data/Sachin/AVR_6_4_2016_2/ADC.c"
#line 1 "d:/ipdu_all using boards_data/sachin/avr_6_4_2016_2/adc.h"



unsigned int vADCRead(unsigned char adcx);
void vADCInit(void);
unsigned int vAverageFilter(void);
 float vCalibrateSample(unsigned int uiSample);
#line 1 "d:/ipdu_all using boards_data/sachin/avr_6_4_2016_2/comm.h"










struct sCycle
{
 unsigned char ucDeviceID[11];
 float fPeakValue;

 float fAvgRateOfLoading;
 float fWeight;
 unsigned int uiPeakTime;
};

struct sCommData
{
 float fCalibFact_0;
 float fCalibFact_1;
 float fCalibFact_2;
 float fCalibFact_3;
 float fCalibFact_4;

 struct sCycle sCycleID[ 10 ];

 unsigned int uiSensorZero;
 unsigned int uiCurrentSample;
 unsigned int uiPreviousSample;
 unsigned int uiCalibTh_0;
 unsigned int uiCalibTh_1;
 unsigned int uiCalibTh_2;
 unsigned int uiCalibTh_3;
 unsigned int uiCalibTh_4;
 unsigned char ucCycleCount;

 float fCalibratedSample;
 float fCycleStartTh;
 unsigned char ucPeakStatus[ 10 ];


};
#line 93 "d:/ipdu_all using boards_data/sachin/avr_6_4_2016_2/comm.h"
void vSerialInit(void);
unsigned char ucFindIndex( unsigned char *ucSource,unsigned char ucData,unsigned char ucIndex);
char putchar (char c);
void vCheckPacket(unsigned char usRecData);
void vInitDefaultData(void);
void vDecodePacket(void);

void vReadCommand(void);
void vWriteCommand(void);
#line 126 "d:/ipdu_all using boards_data/sachin/avr_6_4_2016_2/comm.h"
extern struct sCommData SerialData;
extern bit bReadWeight,bWeightRec;
extern unsigned char ucBuff[50];
extern unsigned char ucCycleStarted;


extern unsigned char bFlag;
extern unsigned char ucInputPassBuf[ 20 ];
extern unsigned char ucInputPass[ 20 ];
extern bit bWriteFlag;
#line 5 "D:/iPDU_All using Boards_Data/Sachin/AVR_6_4_2016_2/ADC.c"
unsigned int uiADC0_Array[ 10 ];
unsigned int uiADC;
unsigned int vADCRead(unsigned char ucChannel) {
#line 14 "D:/iPDU_All using Boards_Data/Sachin/AVR_6_4_2016_2/ADC.c"
 ADMUX &= 0xf0;
 ADMUX |= ucChannel;
 DIDR0 = 1 << ucChannel;

 ADSC_bit = 1;
#line 25 "D:/iPDU_All using Boards_Data/Sachin/AVR_6_4_2016_2/ADC.c"
 while ( (ADSC_bit) );
 uiADC = ADCL;
 uiADC = ((unsigned int)ADCH<<8)| uiADC;


 return vAverageFilter();
}

void vADCInit(void)
{

 DDRC = 0 ;
 REFS1_bit = 0;
 REFS0_bit = 1;
 ADLAR_bit = 0;

 ADEN_bit = 1;
 ADPS0_bit = 1;
 ADPS1_bit = 1;
 ADPS2_bit = 1;





}

unsigned int vAverageFilter(void)
{
 unsigned int uiAverageValue;
 unsigned char i;
 unsigned long lAverage;


 if(1)
 {
 for(i=0;i< 10 -1;i++)
 {
 uiADC0_Array[ 10 -1-i] = uiADC0_Array[ 10 -2-i];
 }
 uiADC0_Array[0] = uiADC;

 lAverage = 0;

 for(i=0;i< 10 ;i++)
 {
 lAverage = lAverage + uiADC0_Array[i];
 }
 uiAverageValue = lAverage/ 10 ;

 }
 return uiAverageValue;
}

float vCalibrateSample(unsigned int uiSample)
{
 float fCalibratedSample;
 int iSample;
 iSample = uiSample-SerialData.uiSensorZero;

 if(uiSample<SerialData.uiCalibTh_0)
 {
 fCalibratedSample = iSample * SerialData.fCalibFact_0;
 }
 else if(uiSample>=SerialData.uiCalibTh_0 && uiSample<SerialData.uiCalibTh_1)
 {
 fCalibratedSample = iSample * SerialData.fCalibFact_1;
 }
 else if (uiSample>=SerialData.uiCalibTh_1 && uiSample<SerialData.uiCalibTh_2)
 {
 fCalibratedSample = iSample * SerialData.fCalibFact_2;
 }
 else if (uiSample>=SerialData.uiCalibTh_2 && uiSample<SerialData.uiCalibTh_3)
 {
 fCalibratedSample = iSample * SerialData.fCalibFact_3;
 }
 else
 {
 fCalibratedSample = iSample * SerialData.fCalibFact_4;
 }
 return fCalibratedSample;
}
