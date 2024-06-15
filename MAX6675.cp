#line 1 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/MAX6675.c"
#line 1 "d:/ipdu_all using boards_data/drusti/avr_based/avr/max6675.h"
#line 27 "d:/ipdu_all using boards_data/drusti/avr_based/avr/max6675.h"
unsigned int gettemp(void);
void init_6675(void);
unsigned char getTC(void);
#line 9 "D:/iPDU_All using Boards_Data/Drusti/AVR_Based/AVR/MAX6675.c"
unsigned int gettemp(void);
void initavr(void);





unsigned int gettemp(void){
 unsigned char ibit = 0, bitnr = 12;
 unsigned char foo1 = 0;
 unsigned int Rohdata = 0;



  PORTC  &= ~(1 <<  1 );

 for(foo1 = 0 ; foo1 < 16 ; foo1++){

 ibit = 15 - foo1;


  PORTC  |= (1 <<  2 );


 if((ibit <= 14) && (ibit >= 3)){

 if(( PINC  & (1 <<  0 ))){
 bitnr--;
 Rohdata |= (1 << bitnr);
 }else{
 bitnr--;
 Rohdata &= ~(1 << bitnr);
 }

 }else{
 bitnr = 12;
 }

  PORTC  &= ~(1 <<  2 );
 }


  PORTC  |= (1 <<  1 );


 return Rohdata;
}




unsigned char getTC(void){
 unsigned char TC = 0;
 unsigned char foo1 = 0;



  PORTC  &= ~(1 <<  1 );

 for(foo1 = 0 ; foo1 < 16 ; foo1++){


  PORTC  |= (1 <<  2 );


 if(foo1 == 2){

 if(( PINC  & (1 <<  0 ))){
 TC = 0;
 }else{
 TC = 255;
 }

 }


  PORTC  &= ~(1 <<  2 );


 }



  PORTC  |= (1 <<  1 );


 return TC;
}





void init_6675(void){

  DDRC  &= ~(1 <<  0 );
  DDRC  |= (1 <<  1 );
  DDRC  |= (1 <<  2 );

  PORTC  |= (1<< 0 );

  PORTC  |= (1 <<  1 );
  PORTC  &= ~(1 <<  2 );


}
