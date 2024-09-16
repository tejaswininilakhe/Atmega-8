/****************************************************************************/
File created by Tejaswini dated 16.09.2024 
Code is written for serial communication
/************************************************************************************/

#ifndef _COMM_H_
#define _COMM_H_


#define bMuxCtrl_DDR  DDC5_bit
#define bMuxCtrl      PORTC5_bit


#define CYCLE_COUNT        10



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

/*#define LED_DDR  DDB5_bit
#define LED_DATA PORTB5_bit

#define BLOWER_DDR  DDD4_bit
#define BLOWER_DATA PORTD4_bit

#define FLOUID_DDR  DDB0_bit
#define FLOUID_DATA PORTB0_bit

#define AIR_PUMP_DDR  DDB5_bit
#define AIR_PUMP_DATA PORTB5_bit

#define HEATER_DDR  DDD7_bit
#define HEATER_DATA PORTD7_bit

#define MUX_DDR  DDC6_bit
#define MUX_DATA PORTC6_bit*/


#define BUFFER_SIZE        20

/*#define PARTY_MODE                         0x00
#define RANDOMIZE_MODE         0x01
#define SET_DELAY_MODE         0x02
#define BLUETOOTH_MODE         0x03

#define LIQUID                         0x00
#define FAN                                 0x01
#define RED                                 0x02
#define GREEN                         0x03
#define BLUE                           0x04
*/


/*struct stDevicePar
{
  unsigned char ucRed;
  unsigned char ucGreen;
  unsigned char ucBlue;
  unsigned  char ucFanSpeed;
  unsigned  char ucFlouid;
};*/



void vSerialInit(void);
unsigned char ucFindIndex( unsigned char *ucSource,unsigned char ucData,unsigned char ucIndex);
char putchar (char c);
void vCheckPacket(unsigned char usRecData);
void         vInitDefaultData(void);
void         vDecodePacket(void);
//float fCalibFactor[5];
void         vReadCommand(void);
void         vWriteCommand(void);

#define LED_DDR  DDB5_bit
#define LED_DATA PORTB5_bit




#ifdef Comm
unsigned char ucBuff[50];
struct sCommData SerialData;
//unsigned char bPowerStatus;
//unsigned char ucEffectsState;
//unsigned char ucModes;
//int iDifference;
//struct stDevicePar stDeviceConfig;
unsigned char bFlag;
//unsigned int uiAverageValue;
unsigned char ucInputPassBuf[BUFFER_SIZE];
unsigned char ucInputPass[BUFFER_SIZE];
bit bWriteFlag;
#else
//extern unsigned int uiAverageValue;
extern struct sCommData SerialData;
extern unsigned char ucBuff[50];
//extern int iDifference;
//extern unsigned char bPowerStatus;
extern unsigned char bFlag;
extern unsigned char ucInputPassBuf[BUFFER_SIZE];
extern unsigned char ucInputPass[BUFFER_SIZE];
extern bit bWriteFlag;
//extern struct stDevicePar stDeviceConfig;
//extern unsigned char ucEffectsState;
//extern unsigned char ucModes;
#endif

#endif
