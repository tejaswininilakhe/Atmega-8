
_main:
	LDI        R27, 255
	OUT        SPL+0, R27
	LDI        R27, 0
	OUT        SPL+1, R27
	IN         R28, SPL+0
	IN         R29, SPL+1
	SBIW       R28, 4
	OUT        SPL+0, R28
	OUT        SPL+1, R29
	ADIW       R28, 1

;ModBus.c,45 :: 		void main()
;ModBus.c,50 :: 		LED_DDR = 1;
	PUSH       R2
	PUSH       R3
	PUSH       R4
	PUSH       R5
	IN         R27, DDB5_bit+0
	SBR        R27, 32
	OUT        DDB5_bit+0, R27
;ModBus.c,51 :: 		USART_Init();
	CALL       _USART_Init+0
;ModBus.c,52 :: 		vInitTimer_1();
	CALL       _vInitTimer_1+0
;ModBus.c,53 :: 		SREG_I_bit = 1;
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,54 :: 		Lcd_Init();                        // Initialize LCD
	CALL       _Lcd_Init+0
;ModBus.c,55 :: 		Lcd_Cmd(_LCD_CLEAR);               // Clear display
	LDI        R27, 1
	MOV        R2, R27
	CALL       _Lcd_Cmd+0
;ModBus.c,56 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
	LDI        R27, 12
	MOV        R2, R27
	CALL       _Lcd_Cmd+0
;ModBus.c,57 :: 		Lcd_Out(1,1,"  Lakshmi Solar ");                 // Write text in first row
	LDI        R27, #lo_addr(?lstr1_ModBus+0)
	MOV        R4, R27
	LDI        R27, hi_addr(?lstr1_ModBus+0)
	MOV        R5, R27
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 1
	MOV        R2, R27
	CALL       _Lcd_Out+0
;ModBus.c,59 :: 		USART_SendByte('L');
	LDI        R27, 76
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,60 :: 		USART_SendByte('A');
	LDI        R27, 65
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,61 :: 		USART_SendByte('K');
	LDI        R27, 75
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,62 :: 		USART_SendByte('S');
	LDI        R27, 83
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,63 :: 		USART_SendByte('H');
	LDI        R27, 72
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,64 :: 		USART_SendByte('M');
	LDI        R27, 77
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,65 :: 		USART_SendByte('I');
	LDI        R27, 73
	MOV        R2, R27
	CALL       _USART_SendByte+0
;ModBus.c,66 :: 		LED_DATA = 0;
	IN         R27, PORTB5_bit+0
	CBR        R27, 32
	OUT        PORTB5_bit+0, R27
;ModBus.c,67 :: 		vClearBuffer();
	CALL       _vClearBuffer+0
;ModBus.c,68 :: 		while(1)
L_main0:
;ModBus.c,70 :: 		ucPacketIndex=0;
	LDI        R27, 0
	STS        _ucPacketIndex+0, R27
;ModBus.c,71 :: 		SREG_I_bit = 0;
	IN         R27, SREG_I_bit+0
	CBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,72 :: 		RXEN0_bit = 0;
	LDS        R27, RXEN0_bit+0
	CBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,73 :: 		vSendPacket(&ucVoltage,8);
	LDI        R27, 8
	MOV        R4, R27
	LDI        R27, #lo_addr(_ucVoltage+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_ucVoltage+0)
	MOV        R3, R27
	CALL       _vSendPacket+0
;ModBus.c,74 :: 		SREG_I_bit = 1;
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,75 :: 		RXEN0_bit = 1;
	LDS        R27, RXEN0_bit+0
	SBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,76 :: 		delay_ms(1000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main2:
	DEC        R16
	BRNE       L_main2
	DEC        R17
	BRNE       L_main2
	DEC        R18
	BRNE       L_main2
	NOP
	NOP
	NOP
	NOP
;ModBus.c,77 :: 		if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
	LDS        R16, _ucPacket+2
	CPI        R16, 131
	BRNE       L__main44
	JMP        L__main38
L__main44:
	LDS        R16, _ucPacket+1
	CPI        R16, 0
	BRNE       L__main45
	JMP        L__main37
L__main45:
L__main36:
;ModBus.c,79 :: 		uiVoltage = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
	LDS        R16, _ucPacket+4
	MOV        R19, R16
	CLR        R18
	LDS        R16, _ucPacket+5
	LDI        R17, 0
	OR         R16, R18
	OR         R17, R19
	STS        _uiVoltage+0, R16
	STS        _uiVoltage+1, R17
;ModBus.c,80 :: 		bCommStatus = 1;
	LDS        R27, _bCommStatus+0
	SBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;ModBus.c,81 :: 		}
	JMP        L_main7
;ModBus.c,77 :: 		if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
L__main38:
L__main37:
;ModBus.c,84 :: 		bCommStatus = 0;
	LDS        R27, _bCommStatus+0
	CBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;ModBus.c,85 :: 		}
L_main7:
;ModBus.c,86 :: 		vClearBuffer();
	CALL       _vClearBuffer+0
;ModBus.c,88 :: 		ucPacketIndex=0;
	LDI        R27, 0
	STS        _ucPacketIndex+0, R27
;ModBus.c,89 :: 		SREG_I_bit = 0;
	IN         R27, SREG_I_bit+0
	CBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,90 :: 		RXEN0_bit = 0;
	LDS        R27, RXEN0_bit+0
	CBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,91 :: 		vSendPacket(&ucCurrent,8);
	LDI        R27, 8
	MOV        R4, R27
	LDI        R27, #lo_addr(_ucCurrent+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_ucCurrent+0)
	MOV        R3, R27
	CALL       _vSendPacket+0
;ModBus.c,92 :: 		SREG_I_bit = 1;
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,93 :: 		RXEN0_bit = 1;
	LDS        R27, RXEN0_bit+0
	SBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,94 :: 		delay_ms(1000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main8:
	DEC        R16
	BRNE       L_main8
	DEC        R17
	BRNE       L_main8
	DEC        R18
	BRNE       L_main8
	NOP
	NOP
	NOP
	NOP
;ModBus.c,95 :: 		if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
	LDS        R16, _ucPacket+2
	CPI        R16, 131
	BRNE       L__main46
	JMP        L__main40
L__main46:
	LDS        R16, _ucPacket+1
	CPI        R16, 0
	BRNE       L__main47
	JMP        L__main39
L__main47:
L__main35:
;ModBus.c,97 :: 		uiCurrent = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
	LDS        R16, _ucPacket+4
	MOV        R19, R16
	CLR        R18
	LDS        R16, _ucPacket+5
	LDI        R17, 0
	OR         R16, R18
	OR         R17, R19
	STS        _uiCurrent+0, R16
	STS        _uiCurrent+1, R17
;ModBus.c,98 :: 		bCommStatus = 1;
	LDS        R27, _bCommStatus+0
	SBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;ModBus.c,99 :: 		}
	JMP        L_main13
;ModBus.c,95 :: 		if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
L__main40:
L__main39:
;ModBus.c,102 :: 		bCommStatus = 0;
	LDS        R27, _bCommStatus+0
	CBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;ModBus.c,103 :: 		}
L_main13:
;ModBus.c,104 :: 		vClearBuffer();
	CALL       _vClearBuffer+0
;ModBus.c,106 :: 		ucPacketIndex=0;
	LDI        R27, 0
	STS        _ucPacketIndex+0, R27
;ModBus.c,107 :: 		SREG_I_bit = 0;
	IN         R27, SREG_I_bit+0
	CBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,108 :: 		RXEN0_bit = 0;
	LDS        R27, RXEN0_bit+0
	CBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,109 :: 		vSendPacket(&ucFreq,8);
	LDI        R27, 8
	MOV        R4, R27
	LDI        R27, #lo_addr(_ucFreq+0)
	MOV        R2, R27
	LDI        R27, hi_addr(_ucFreq+0)
	MOV        R3, R27
	CALL       _vSendPacket+0
;ModBus.c,110 :: 		SREG_I_bit = 1;
	IN         R27, SREG_I_bit+0
	SBR        R27, 128
	OUT        SREG_I_bit+0, R27
;ModBus.c,111 :: 		RXEN0_bit = 1;
	LDS        R27, RXEN0_bit+0
	SBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,112 :: 		delay_ms(1000);
	LDI        R18, 82
	LDI        R17, 43
	LDI        R16, 0
L_main14:
	DEC        R16
	BRNE       L_main14
	DEC        R17
	BRNE       L_main14
	DEC        R18
	BRNE       L_main14
	NOP
	NOP
	NOP
	NOP
;ModBus.c,113 :: 		if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
	LDS        R16, _ucPacket+2
	CPI        R16, 131
	BRNE       L__main48
	JMP        L__main42
L__main48:
	LDS        R16, _ucPacket+1
	CPI        R16, 0
	BRNE       L__main49
	JMP        L__main41
L__main49:
L__main34:
;ModBus.c,115 :: 		uiFreq = ((unsigned int)(ucPacket[4]<<8))|ucPacket[5];
	LDS        R16, _ucPacket+4
	MOV        R19, R16
	CLR        R18
	LDS        R16, _ucPacket+5
	LDI        R17, 0
	OR         R16, R18
	OR         R17, R19
	STS        _uiFreq+0, R16
	STS        _uiFreq+1, R17
;ModBus.c,116 :: 		bCommStatus = 1;
	LDS        R27, _bCommStatus+0
	SBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;ModBus.c,117 :: 		}
	JMP        L_main19
;ModBus.c,113 :: 		if(ucPacket[2] != 0x83 && ucPacket[1] != 0x00)
L__main42:
L__main41:
;ModBus.c,120 :: 		bCommStatus = 0;
	LDS        R27, _bCommStatus+0
	CBR        R27, BitMask(_bCommStatus+0)
	STS        _bCommStatus+0, R27
;ModBus.c,121 :: 		}
L_main19:
;ModBus.c,122 :: 		vClearBuffer();
	CALL       _vClearBuffer+0
;ModBus.c,124 :: 		if(bCommStatus)
	LDS        R27, _bCommStatus+0
	SBRS       R27, BitPos(_bCommStatus+0)
	JMP        L_main20
;ModBus.c,126 :: 		sprintf(ucBuff,"V%3u I%5.1f F%3u",uiVoltage,(uiCurrent/(float)10),(uiFreq));
	LDS        R16, _uiCurrent+0
	LDS        R17, _uiCurrent+1
	LDI        R18, 0
	MOV        R19, R18
	CALL       _float_ulong2fp+0
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 32
	LDI        R23, 65
	CALL       _float_fpdiv1+0
	LDS        R20, _uiFreq+0
	LDS        R21, _uiFreq+1
	PUSH       R21
	PUSH       R20
	PUSH       R19
	PUSH       R18
	PUSH       R17
	PUSH       R16
	LDS        R16, _uiVoltage+0
	LDS        R17, _uiVoltage+1
	PUSH       R17
	PUSH       R16
	LDI        R27, hi_addr(?lstr_2_ModBus+0)
	PUSH       R27
	LDI        R27, #lo_addr(?lstr_2_ModBus+0)
	PUSH       R27
	LDI        R27, hi_addr(_ucBuff+0)
	PUSH       R27
	LDI        R27, #lo_addr(_ucBuff+0)
	PUSH       R27
	CALL       _sprintf+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 12
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;ModBus.c,128 :: 		sprintf(ucBuff,"V%3u I%3.1f F%3.1f",uiVoltage,(uiCurrent/(float)10),(float)(uiFreq/(float)100));
	LDS        R16, _uiFreq+0
	LDS        R17, _uiFreq+1
	LDI        R18, 0
	MOV        R19, R18
	CALL       _float_ulong2fp+0
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 200
	LDI        R23, 66
	CALL       _float_fpdiv1+0
	STD        Y+0, R16
	STD        Y+1, R17
	STD        Y+2, R18
	STD        Y+3, R19
	LDS        R16, _uiCurrent+0
	LDS        R17, _uiCurrent+1
	LDI        R18, 0
	MOV        R19, R18
	CALL       _float_ulong2fp+0
	LDI        R20, 0
	LDI        R21, 0
	LDI        R22, 32
	LDI        R23, 65
	CALL       _float_fpdiv1+0
	LDD        R20, Y+0
	LDD        R21, Y+1
	LDD        R22, Y+2
	LDD        R23, Y+3
	PUSH       R23
	PUSH       R22
	PUSH       R21
	PUSH       R20
	PUSH       R19
	PUSH       R18
	PUSH       R17
	PUSH       R16
	LDS        R16, _uiVoltage+0
	LDS        R17, _uiVoltage+1
	PUSH       R17
	PUSH       R16
	LDI        R27, hi_addr(?lstr_3_ModBus+0)
	PUSH       R27
	LDI        R27, #lo_addr(?lstr_3_ModBus+0)
	PUSH       R27
	LDI        R27, hi_addr(_ucBuff+0)
	PUSH       R27
	LDI        R27, #lo_addr(_ucBuff+0)
	PUSH       R27
	CALL       _sprintf+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 14
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;ModBus.c,129 :: 		Lcd_Out(2,1,ucBuff);
	LDI        R27, #lo_addr(_ucBuff+0)
	MOV        R4, R27
	LDI        R27, hi_addr(_ucBuff+0)
	MOV        R5, R27
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _Lcd_Out+0
;ModBus.c,130 :: 		}
	JMP        L_main21
L_main20:
;ModBus.c,133 :: 		sprintf(ucBuff,"V--- I--- F-----");
	LDI        R27, hi_addr(?lstr_4_ModBus+0)
	PUSH       R27
	LDI        R27, #lo_addr(?lstr_4_ModBus+0)
	PUSH       R27
	LDI        R27, hi_addr(_ucBuff+0)
	PUSH       R27
	LDI        R27, #lo_addr(_ucBuff+0)
	PUSH       R27
	CALL       _sprintf+0
	IN         R26, SPL+0
	IN         R27, SPL+1
	ADIW       R26, 4
	OUT        SPL+0, R26
	OUT        SPL+1, R27
;ModBus.c,134 :: 		Lcd_Out(2,1,ucBuff);
	LDI        R27, #lo_addr(_ucBuff+0)
	MOV        R4, R27
	LDI        R27, hi_addr(_ucBuff+0)
	MOV        R5, R27
	LDI        R27, 1
	MOV        R3, R27
	LDI        R27, 2
	MOV        R2, R27
	CALL       _Lcd_Out+0
;ModBus.c,135 :: 		}
L_main21:
;ModBus.c,136 :: 		}
	JMP        L_main0
;ModBus.c,137 :: 		}
L_end_main:
L__main_end_loop:
	JMP        L__main_end_loop
; end of _main

_vSerialRx_ISR:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;ModBus.c,141 :: 		void vSerialRx_ISR() org IVT_ADDR_USART__RX      // This funtion is Interrupt Funtion
;ModBus.c,144 :: 		if ( FE0_bit)
	LDS        R27, FE0_bit+0
	SBRS       R27, 4
	JMP        L_vSerialRx_ISR22
;ModBus.c,147 :: 		}
	JMP        L_vSerialRx_ISR23
L_vSerialRx_ISR22:
;ModBus.c,150 :: 		dmxByte = UDR0;
; dmxByte start address is: 19 (R19)
	LDS        R19, UDR0+0
;ModBus.c,151 :: 		ucPacket[ucPacketIndex]=dmxByte;
	LDI        R17, #lo_addr(_ucPacket+0)
	LDI        R18, hi_addr(_ucPacket+0)
	LDS        R16, _ucPacketIndex+0
	MOV        R30, R16
	LDI        R31, 0
	ADD        R30, R17
	ADC        R31, R18
	ST         Z, R19
; dmxByte end address is: 19 (R19)
;ModBus.c,152 :: 		ucPacketIndex++;
	LDS        R16, _ucPacketIndex+0
	SUBI       R16, 255
	STS        _ucPacketIndex+0, R16
;ModBus.c,153 :: 		LED_DATA = ~LED_DATA;
	IN         R0, PORTB5_bit+0
	LDI        R27, 32
	EOR        R0, R27
	OUT        PORTB5_bit+0, R0
;ModBus.c,154 :: 		}
L_vSerialRx_ISR23:
;ModBus.c,155 :: 		}
L_end_vSerialRx_ISR:
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _vSerialRx_ISR

_USART_Init:

;ModBus.c,165 :: 		void USART_Init(void){
;ModBus.c,168 :: 		UBRR0L = BAUD_PRESCALE_9600;// Load lower 8-bits into the low byte of the UBRR register
	LDI        R27, 103
	STS        UBRR0L+0, R27
;ModBus.c,169 :: 		UBRR0H = (BAUD_PRESCALE_9600 >> 8);
	LDI        R27, 0
	STS        UBRR0H+0, R27
;ModBus.c,173 :: 		}
L_USART_Init25:
;ModBus.c,177 :: 		TXEN0_bit = 1;
	LDS        R27, TXEN0_bit+0
	SBR        R27, 8
	STS        TXEN0_bit+0, R27
;ModBus.c,178 :: 		RXEN0_bit = 1;
	LDS        R27, RXEN0_bit+0
	SBR        R27, 16
	STS        RXEN0_bit+0, R27
;ModBus.c,179 :: 		RXCIE0_bit = 1;
	LDS        R27, RXCIE0_bit+0
	SBR        R27, 128
	STS        RXCIE0_bit+0, R27
;ModBus.c,181 :: 		}
L_end_USART_Init:
	RET
; end of _USART_Init

_USART_SendByte:

;ModBus.c,183 :: 		void USART_SendByte(unsigned char u8Data){
;ModBus.c,189 :: 		UDR0 = u8Data;
	STS        UDR0+0, R2
;ModBus.c,190 :: 		while(UDRE0_bit == 0);
L_USART_SendByte26:
	LDS        R27, UDRE0_bit+0
	SBRC       R27, 5
	JMP        L_USART_SendByte27
	JMP        L_USART_SendByte26
L_USART_SendByte27:
;ModBus.c,191 :: 		}
L_end_USART_SendByte:
	RET
; end of _USART_SendByte

_vSendPacket:

;ModBus.c,194 :: 		void vSendPacket(unsigned char *Data,unsigned char ucLen)
;ModBus.c,196 :: 		unsigned char ucCount=0;
; ucCount start address is: 17 (R17)
	LDI        R17, 0
; ucCount end address is: 17 (R17)
;ModBus.c,197 :: 		while(ucLen)
L_vSendPacket28:
; ucCount start address is: 17 (R17)
	TST        R4
	BRNE       L__vSendPacket57
	JMP        L_vSendPacket29
L__vSendPacket57:
;ModBus.c,199 :: 		ucLen--;
	MOV        R16, R4
	SUBI       R16, 1
	MOV        R4, R16
;ModBus.c,200 :: 		USART_SendByte(Data[ucCount]);
	MOV        R30, R17
	LDI        R31, 0
	ADD        R30, R2
	ADC        R31, R3
	LD         R16, Z
	PUSH       R3
	PUSH       R2
	MOV        R2, R16
	CALL       _USART_SendByte+0
	POP        R2
	POP        R3
;ModBus.c,201 :: 		ucCount++;
	MOV        R16, R17
	SUBI       R16, 255
	MOV        R17, R16
;ModBus.c,202 :: 		}
; ucCount end address is: 17 (R17)
	JMP        L_vSendPacket28
L_vSendPacket29:
;ModBus.c,203 :: 		}
L_end_vSendPacket:
	RET
; end of _vSendPacket

_vTimer1_ISR:
	PUSH       R30
	PUSH       R31
	PUSH       R27
	IN         R27, SREG+0
	PUSH       R27

;ModBus.c,206 :: 		void vTimer1_ISR() org IVT_ADDR_TIMER1_OVF
;ModBus.c,209 :: 		TCNT1H = 0XF8;
	LDI        R27, 248
	STS        TCNT1H+0, R27
;ModBus.c,210 :: 		TCNT1L = 0X2F;
	LDI        R27, 47
	STS        TCNT1L+0, R27
;ModBus.c,212 :: 		uci++;
	LDS        R16, _uci+0
	LDS        R17, _uci+1
	MOVW       R18, R16
	SUBI       R18, 255
	SBCI       R19, 255
	STS        _uci+0, R18
	STS        _uci+1, R19
;ModBus.c,213 :: 		if(uci>1000)
	LDI        R16, 232
	LDI        R17, 3
	CP         R16, R18
	CPC        R17, R19
	BRLO       L__vTimer1_ISR59
	JMP        L_vTimer1_ISR30
L__vTimer1_ISR59:
;ModBus.c,215 :: 		uci = 0;
	LDI        R27, 0
	STS        _uci+0, R27
	STS        _uci+1, R27
;ModBus.c,216 :: 		bSec = 1;
	LDS        R27, _bSec+0
	SBR        R27, BitMask(_bSec+0)
	STS        _bSec+0, R27
;ModBus.c,217 :: 		}
L_vTimer1_ISR30:
;ModBus.c,219 :: 		}
L_end_vTimer1_ISR:
	POP        R27
	OUT        SREG+0, R27
	POP        R27
	POP        R31
	POP        R30
	RETI
; end of _vTimer1_ISR

_vInitTimer_1:

;ModBus.c,221 :: 		void vInitTimer_1(void)
;ModBus.c,225 :: 		CS10_bit = 0;
	LDS        R27, CS10_bit+0
	CBR        R27, 1
	STS        CS10_bit+0, R27
;ModBus.c,226 :: 		CS11_bit = 1;
	LDS        R27, CS11_bit+0
	SBR        R27, 2
	STS        CS11_bit+0, R27
;ModBus.c,227 :: 		CS12_bit = 0;
	LDS        R27, CS12_bit+0
	CBR        R27, 4
	STS        CS12_bit+0, R27
;ModBus.c,229 :: 		TOIE1_bit = 1;
	LDS        R27, TOIE1_bit+0
	SBR        R27, 1
	STS        TOIE1_bit+0, R27
;ModBus.c,231 :: 		TCNT1H = 0;
	LDI        R27, 0
	STS        TCNT1H+0, R27
;ModBus.c,232 :: 		TCNT1L = 0;
	LDI        R27, 0
	STS        TCNT1L+0, R27
;ModBus.c,233 :: 		}
L_end_vInitTimer_1:
	RET
; end of _vInitTimer_1

_vInitDefaultData:

;ModBus.c,235 :: 		void vInitDefaultData(void)
;ModBus.c,239 :: 		}
L_end_vInitDefaultData:
	RET
; end of _vInitDefaultData

_vClearBuffer:

;ModBus.c,241 :: 		void vClearBuffer(void)
;ModBus.c,243 :: 		unsigned char ucCounter=0;
;ModBus.c,244 :: 		for(ucCounter=0;ucCounter<20;ucCounter++)
; ucCounter start address is: 18 (R18)
	LDI        R18, 0
; ucCounter end address is: 18 (R18)
L_vClearBuffer31:
; ucCounter start address is: 18 (R18)
	CPI        R18, 20
	BRLO       L__vClearBuffer63
	JMP        L_vClearBuffer32
L__vClearBuffer63:
;ModBus.c,246 :: 		ucPacket[ucCounter] = 0x00;
	LDI        R16, #lo_addr(_ucPacket+0)
	LDI        R17, hi_addr(_ucPacket+0)
	MOV        R30, R18
	LDI        R31, 0
	ADD        R30, R16
	ADC        R31, R17
	LDI        R27, 0
	ST         Z, R27
;ModBus.c,244 :: 		for(ucCounter=0;ucCounter<20;ucCounter++)
	MOV        R16, R18
	SUBI       R16, 255
	MOV        R18, R16
;ModBus.c,247 :: 		}
; ucCounter end address is: 18 (R18)
	JMP        L_vClearBuffer31
L_vClearBuffer32:
;ModBus.c,248 :: 		}
L_end_vClearBuffer:
	RET
; end of _vClearBuffer
