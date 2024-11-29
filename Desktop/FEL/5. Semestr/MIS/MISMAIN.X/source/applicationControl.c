
/*
 * File:    applicationControl.c (For MIS)
 * j.z.
 *  
 * MPLABX.IDE v5.10, XC32 v3.00, HW: DEP-PIC32-MK
 * 
 * Created:  2024.06.16
 * Modified: 2024.08.12
 * 
 */

/*==== History trace buffer ===================================================

2024.08.12-Replaced: #include "platformDEP32mk.h" by platformMIS32mk.h
2024.08.09-Mldified: Source code cleaned up.
2024.06.16-New: applicationControl.c TEMPLATE for students MIS 
-------------------------------------------------------------------------------

2023.02.10-New: applicationControl.c TEMPLATE for students DEP 
==== History trace buffer END ================================================*/

//--- Includes ----------------------------------------------------------------
#include <xc.h>
#include <stdbool.h>
#include <sys/attribs.h>
#include "platformMIS32mk.h"
#include "filtr.h"
#include "memory.h"
#include "rtm.h"
#include "dekoder.h"
#include "potenciometr.h"


//-- latform Function prototypes are in "platrformDEP32mk" ---------------------

//--- User function prototypes -------------------------------------------------


//--- Macros ------------------------------------------------------------------


//--- Constants ---------------------------------------------------------------
#define DELAY_ms  500

//--- New variable types ------------------------------------------------------

//--- Global vars -------------------------------------------------------------

//--- External vars -----------------------------------------------------------
// zde deklaruju globalni promenne
filtr_ filtrS1; 
filtr_ filtrS2;
filtr_ filtrA;  
filtr_ filtrB; 
mem_ memS1;
mem_ memS2;
dekoder_ dekoderDEK;        //promena pro hodnotu dekoderu
int potenciometrPOT;        //promena pro hodnotu potenciometru
int celkovy_vystup;         //promena pro hodnotu vystupu po zvoleni dekoderu nebo potenciometru
int svitiV9;                //pomocna promena pro zobrazeni stavu LEDV9 v RTM
int svitiV12;               //pomocna promena pro zobrazeni stavu LEDV12 v RTM


//---- Functions --------------------------------------------------------------

void configApplication(void){//------------------------------------------------
  //--- User defined functions ---
    // tady inicializuju promeny
    filtrS1.vystup = 0;     //inicializace pro filtr tlacitka S1
    filtrS1.stav = 0;
    
    filtrS2.vystup = 0;     //inicializace pro filtr tlacitka S2
    filtrS2.stav = 0;
    
    filtrA.vystup = 0;      //inicializace pro filtr koderu kanal A 
    filtrA.stav = 0;
    
    filtrB.vystup = 0;      //inicializace pro filtr koderu kanal B 
    filtrB.stav = 0;
    
    memS1.vystup = 0;      //inicializace pro pamet tlacitka S1 
    memS1.stav = 0;
    
    memS2.vystup = 0;      //inicializace pro pamet tlacitka S2 
    memS2.stav = 0;
    
    dekoderDEK.hodnota_dek = 0;
    dekoderDEK.stav = 0;
    
    potenciometrPOT = 0;
    
    celkovy_vystup = 0;
    
    svitiV9 = 0;
    svitiV12 = 0;
    
  
}// configApplication() END 

//===>>>> Call it every 1ms <<<<===

void runApplication(void) {//--------------------------------------------------
  // sem volat moje funkce
    
    filtr(&filtrA,getCoderChannelA());      //zde filtruji tlacitka koderu
    filtr(&filtrB,getCoderChannelB());
    
    filtr(&filtrS1,getButtonS1());          //zde filtruji tlacitka S1 S2
    filtr(&filtrS2,getButtonS2());
    
    
    mem(&memS1,filtrS1.vystup);             //volani funkce pameti jejiz vstupem je vystup z filtru tlacitka S1
    mem(&memS2,filtrS2.vystup);             //volani funkce pameti jejiz vstupem je vystup z filtru tlacitka S2
    
    
    setCoderLedA(filtrA.vystup);            //rozsviceni led vyfiltrovaneho signalu koderu
    setCoderLedB(filtrB.vystup); 
    
    setLedV1(memS1.vystup);                             //rozviceni led z pameti tlacitka S1 a S2
    setLedV2(memS2.vystup); 
    
   
    dekoder(&dekoderDEK, filtrA.vystup, filtrB.vystup);     //volani fukce dekoderu - urci smer a dle nej pricita/odecita pocet hran kvadraturniho signalu na intervalu 0 az 255
    potenciometr(&potenciometrPOT);                         // volani funkce potenciometru - precte hodnotu potenciometru a tu upravi do zadaneho intervalu 0 az 255
    
    
    
    
    //----------------------zde rozhoduje zda je nastaven dekoder nebo poteciometr------------------------------------------------------
    
    if((memS2.vystup) == 1){                                
        celkovy_vystup = dekoderDEK.hodnota_dek;
    }
    
    else if((memS2.vystup) == 0){
        celkovy_vystup = potenciometrPOT;
    }
    //----------------------------------------------------------------------------------------------------------------------
    
    setFpgaVxValue(celkovy_vystup); //rozsvici led 13 az 24 dle celkove vystupni hodnoty
    
    //---------zde se rozsvici/zahsina led V9 a V12 pri dosazeni maxima/minima celkove vystupni hodnoty------------------------------------------------------
   
    if (celkovy_vystup <= 0){               //rozsviti LEDV9 kdyz je hodnota potenciometru/dekoderu minimalni
        setCoderLedLL(1);
        svitiV9 = 1;
    }
    else if (celkovy_vystup > 0){       //zhasne LEDV9 kdyz neni hodnota potenciometru/dekoderu minimalni
        setCoderLedLL(0);
        svitiV9 = 0;
    }
    
    if (celkovy_vystup >= 255){        //rozsviti LEDV12 kdyz je hodnota potenciometru/dekoderu maximalni
        setCoderLedHL(1);
        svitiV12 = 1;
    }
    else if (celkovy_vystup < 255){         //zhasne LEDV12 kdyz neni hodnota potenciometru/dekoderu maximalni
        setCoderLedHL(0);
        svitiV12 = 0;
    }
  //----------------------------------------------------------------------------------------------------------------------  
    
    
    rtm(memS1.vystup, memS2.vystup, svitiV9, svitiV12, celkovy_vystup); //volani funkce RTM 40ms delay je implementovan uvnitr funkce
    
    
    
}// runApplication() END)




