/* 
 * File:   ADC Module 
 * Author:  Hassan Elsaied Mohammed  Mohammed 
 * Comments:Explain module 
 * *****************************************************************************************************
 * convert the analog signal to the Digital signal.....................................................*                                                  
 * pic16f877a use  10 bit resolution since the Resolution = ((VR+) +(VR-) /2^n -1 at n= 10bit..........*          
 * convert analog signal...............................................................................*                                                                             
 * simple of this signal and the output simpler input to the q_level at Q_level = (Full scale )/(2^n-1)*
 * for example in the pic16f877a the Full scale= 5v  so that Q_level= 5v/((2^10)-1) Q_level =0.004887V *
 * the Resolution = 0.004887V and the Scale 0 to 1024 in Y  and the Resolution  in x...................*                   
 * Digital number 0 to 1024 stay each number equivalent scales in x....................................*                                 
 * the result Store into two Register   (ADRESH  and ADRESL)...........................................*                                           
 * Right Store Result into 8 bit to ADRESH and 2 bit  to ADRESL........................................*                                        
 * Left Store   Result into 8 bit to ADRESL and 2 bit to ADRESH............................ ...........*
 * *****************************************************************************************************
 *   /*this table select channel Analog or Digital and AN3 select Analog or Digital or VREF+ , AN2 analog 
     * or Digital or VREF- 
     ********************************************************************************************************* 
     *PCFG3  PCFG2  PCFG1 PCFG0     AN7    AN6    AN5  AN4      AN3     AN2    AN1  AN0  VREF+  VREF-   C/R  *
     * 0      0       0    0        A       A     A     A        A       A      A    A    VDD    VSS    8/0  *
     * 0      0       0    1        A       A     A     A      VREF+     A      A    A    AN3    VSS    7/1  *
     * 0      0       1    0        D       D     D     A        A       A      A    A    VDD    VSS    5/0  *
     * 0      0       1    1        D       D     D     A      VREF+     A      A    A    AN3    VSS    4/1  *
     * 0      1       0    0        D       D     D     D       A        D      A    A    VDD    VSS    3/0  *
     * 0      1       0    1        D       D     D     D      VREF+     D      A    A    AN3    VSS    2/1  *
     * 0      1       1    x        D       D     D     D        D       D      D    D     ?     ?     0/0  *
     * 1      0       0    0        A       A     A     A      VREF+    VREF-   A    A    AN3    AN2    6/2  *
     * 1      0       0    1        D       D     A     A        A        A     A    A    VDD    VSS    6/0  *
     * 1      0       1    0        D       D     A     A       VREF+     A     A    A    AN3    VSS    5/1  *
     * 1      0       1    1        D       D     A     A       VREF+    VREF-  A    A    AN3    AN2    4/2  *
     * 1      1       0    0        D       D     D     A       VREF+    VREF-  A    A    AN3    AN2    3/2  *
     * 1      1       0    1        D       D     D     D       VREF+    VREF-  A    A    AN3    AN2    2/2  *
     * 1      1       1    0        D       D     D     D         D        D    D    A    VDD    VSS    1/0  *
     * 1      1       1    1        D       D     D     D        VREF+    VREF- D    A    AN3    AN2    1/2  *
     * *******************************************************************************************************
     * Register ANDEL  Selects mode in the ADC 
     * *******************************************************************************************************
     */
     
#ifndef  _ADC_H
#define  _ADC_H
#include  <xc.h>
#define ANDEL  ANDEL 

extern volatile unsigned char ANDEL @ 0x001;

typedef union {
    unsigned ANDELA0 : 1; //AN0
    unsigned ANDELA1 : 1; //AN1
    unsigned ANDELA2 : 1; //AN2
    unsigned ANDELA3 : 1; //AN3
    unsigned ANDELA5 : 1; //AN4
    unsigned ANDELE0 : 1; //AN5
    unsigned ANDELE1 : 1; //AN6
    unsigned ANDELE2 : 1; //AN7
} ANDELbits_t;
extern volatile ANDELbits_t ANDELbits @ 0x001;
 /*
     ***********************************************************************
     * this method select  ADC Conversion clock Select bits................*
     * in the pic16f877a the ADCON0 Register address into SFR 0x1F ........*
     * this Register contains of to bits ADCS1 and ADCS0 this bits ........*
     * select ADC Conversion and Register ADCON1 contains bit (ADCS2)......*
     * three bits Selects Clock look at table..............................*
     * ADCS2.........ADCS1           ADCS0.....Conversion clock............*
     * 0...............0...............0..........FOSC/2...................*
     * 0...............0...............1..........FOSC/8...................*
     * 0...............1...............0..........FOSC/32..................*
     * 0...............1...............1..........FRC .....................*
     * 1...............0...............0..........FOSC/4...................*
     * 1...............0...............1..........FOSC/16..................*
     * 1...............1...............0..........FOSC/64..................*
     * 1...............1...............1..........FRC......................*
     * if Clock 0 the Clock FOSC/2.........................................*
     * if Clock 1 the Clock FOSC/8.........................................*
     * if Clock 2 the Clock FOSC/32........................................* 
     * if Clock 3 the Clock FOSC/4.........................................*
     * if Clock 4 the CLock Fosc/16........................................*
     * if Clock 5 the Clock FOSC/64........................................*
     * if Clock 6 the Clock FRC............................................*
     * *********************************************************************
    * Revision history: Not
 */
void Select_Clock(char Clock);
 /*
     ***********************************************************************
     * this method select  ADC channel Select bits from 7 channel          *
     * in the pic16f877a the ADCON0 Register address into SFR 0x1F         *
     * this Register contains of to bits CHS0 and  CHS1 and CHS2           *
     * three bits Selects Channel  look at table                           *
     * CHS            CHS1            CHS0       Channel_Select            *
     * 0               0               0          AN0                      *
     * 0               0               1          AN1                      *
     * 0               1               0          AN2                      *
     * 0               1               1          AN3                      *
     * 1               0               0          AN4                      *
     * 1               0               1          AN5                      *
     * 1               1               0          AN6                      *
     * 1               1               1          AN7                      *
     * if Channel 0  Select AN0                                            *
     * if Channel 1  Select AN1                                            *
     * if Channel 2  Select AN2                                            * 
     * if Channel 3  Select AN3                                            *
     * if Channel 4  Select AN4                                            *
     * if Channel 5  Select AN5                                            *
     *if Channel 6 Select AN6                                              *
     *if Channel 7  Select AN7                                             *
     * *********************************************************************
     */
void Select_Channel(char Channel);
/*
* *****************************************************************************************************
 * convert the analog signal to the Digital signal.....................................................*                                                  
 * pic16f877a use  10 bit resolution since the Resolution = ((VR+) +(VR-) /2^n -1 at n= 10bit..........*          
 * convert analog signal...............................................................................*                                                                             
 * simple of this signal and the output simpler input to the q_level at Q_level = (Full scale )/(2^n-1)*
 * for example in the pic16f877a the Full scale= 5v  so that Q_level= 5v/((2^10)-1) Q_level =0.004887V *
 * the Resolution = 0.004887V and the Scale 0 to 1024 in Y  and the Resolution  in x...................*                   
 * Digital number 0 to 1024 stay each number equivalent scales in x....................................*                                 
 * the result Store into two Register   (ADRESH  and ADRESL)...........................................*                                           
 * Right Store Result into 8 bit to ADRESH and 2 bit  to ADRESL........................................*                                        
 * Left Store   Result into 8 bit to ADRESL and 2 bit to ADRESH............................ ...........*
 * *****************************************************************************************************
 * */
unsigned int Read_ADC(char channel);
void ADC_Init(char channel, char Clock);
#endif	/* ADC */

