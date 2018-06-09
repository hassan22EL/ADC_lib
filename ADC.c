/*
 * File:   ADC.c
 * Author: Hassan
 *
 * Created on February 28, 2018, 3:20 PM
 */


#include <xc.h>

#include "ADC.h"
#define _XTAL_FREQ 8000000
void Select_Clock(char Clock) {
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
     */
    switch (Clock) {
        case 0: //Clock 0 the Clock FOSC/2
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 0;
            ADCON1bits.ADCS2 = 0;
            break;
        case 1: //Clock 1 the Clock FOSC/8
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 0;
            ADCON1bits.ADCS2 = 0;
            break;
        case 2: //Clock 2 the Clock FOSC/32
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 1;
            ADCON1bits.ADCS2 = 0;
            break;
        case 3: //Clock 3 the Clock FOSC/4
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 0;
            ADCON1bits.ADCS2 = 1;
            break;
        case 4: //Clock 4 the Clock FOSC/16
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 0;
            ADCON1bits.ADCS2 = 1;
            break;
        case 5: //Clock 5 the Clock FOSC/64
            ADCON0bits.ADCS0 = 0;
            ADCON0bits.ADCS1 = 1;
            ADCON1bits.ADCS2 = 1;
            break;
        case 6: //Clock 0 the Clock  FRC
            ADCON0bits.ADCS0 = 1;
            ADCON0bits.ADCS1 = 1;
            break;
    }
}

void Select_Channel(char Channel) {
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
    switch (Channel) {
        case 0: //at channel 0  select channel AN0  
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            break;
        case 1: ////at channel 1  select channel AN1 
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 0;
            break;
        case 2: ////at channel 2 select channel AN2  
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            break;
        case 3: //at channel 3  select channel AN3 
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 0;
            break;
        case 4://at channel 4 select channel AN4  
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            break;
        case 5://at channel 5  select channel AN5
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS2 = 1;
            break;
        case 6: //at channel 6  select channel AN6  
            ADCON0bits.CHS0 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            break;
        case 7: //at channel 7  select channel AN7 
            ADCON0bits.CHS0 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS2 = 1;
            break;
    }
}

void conrol_bit(){
    /*this table select channel Analog or Digital and AN3 select Analog or Digital or VREF+ , AN2 analog 
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
     *
     */
    switch (ANDEL) {
        case 0x00://ALL pins Analog 
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x01:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x02:
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x03:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x04:
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x05:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x06://ALL pins Digital 
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 0;
            break;
        case 0x07:
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x08:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x09:
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x0A:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 0;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x0B:
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x0C:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 0;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x0D:
            ADCON1bits.PCFG0 = 0;
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 1;
            break;
        case 0x0E:
            ADCON1bits.PCFG0 = 1;
            ADCON1bits.PCFG1 = 1;
            ADCON1bits.PCFG2 = 1;
            ADCON1bits.PCFG3 = 1;
            break;
    }

}

unsigned int Read_ADC(char channel){
    /*
     ***********************
     * Channel from 0 to 7 *
     * Clock From 0 To 7   *
     * *********************
     */
    if (channel > 7)
        return 0;
    ADCON0 = ADCON0 & 0xC5; // clear channel selection bits  
    ADCON0 = ADCON0 | (channel << 3); // Setting ADCON0 up to Selected bits
    __delay_ms(2);
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}

void ADC_Init(char channel, char Clock) {
    Select_Channel(channel);
    Select_Clock(Clock);
    conrol_bit();
    ADCON1bits.ADFM = 1;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO_nDONE = 0;
}