
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
#include "PWM.h"
#include "plc.h"


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
filtr_ filtrS3;
filtr_ filtrS4; 
filtr_ filtrS5;
filtr_ filtrS6;
filtr_ filtrS7; 
filtr_ filtrS8;
filtr_ filtrA;  
filtr_ filtrB; 
rtmPWM_ rtmCOM4;
mem_ memS1;
mem_ memS2;
mem_ memS3;
dekoder_ dekoderDEK;        //promena pro hodnotu dekoderu
int potenciometrPOT;        //promena pro hodnotu potenciometru
int celkovy_vystup;         //promena pro hodnotu vystupu po zvoleni dekoderu nebo potenciometru
int svitiV9;                //pomocna promena pro zobrazeni stavu LEDV9 v RTM
int svitiV12;               //pomocna promena pro zobrazeni stavu LEDV12 v RTM
plc_ plc1;

//---- Functions --------------------------------------------------------------

void configApplication(void){//------------------------------------------------
  //--- User defined functions ---
    // tady inicializuju promeny
    filtrS1.vystup = 0;     //inicializace pro filtr tlacitka S1
    filtrS1.stav = 0;
    
    filtrS2.vystup = 0;     //inicializace pro filtr tlacitka S2
    filtrS2.stav = 0;
    
    filtrS3.vystup = 0;     //inicializace pro filtr tlacitka S3
    filtrS3.stav = 0;
    
    filtrS4.vystup = 0;     //inicializace pro filtr tlacitka S4
    filtrS4.stav = 0;
    
    filtrS5.vystup = 0;     //inicializace pro filtr tlacitka S5
    filtrS5.stav = 0;
    
    filtrS6.vystup = 0;     //inicializace pro filtr tlacitka S6
    filtrS6.stav = 0;
    
    filtrS7.vystup = 0;     //inicializace pro filtr tlacitka S7
    filtrS7.stav = 0;
    
    filtrS8.vystup = 0;     //inicializace pro filtr tlacitka S8
    filtrS8.stav = 0;
    
    filtrA.vystup = 0;      //inicializace pro filtr koderu kanal A 
    filtrA.stav = 0;
    
    filtrB.vystup = 0;      //inicializace pro filtr koderu kanal B 
    filtrB.stav = 0;
    
    memS1.vystup = 0;      //inicializace pro pamet tlacitka S1 
    memS1.stav = 0;
    
    memS2.vystup = 0;      //inicializace pro pamet tlacitka S2 
    memS2.stav = 0;
    
    memS3.vystup = 0;       //inicializace pro pamet tlacitka S3 
    memS3.stav =0;
    
    dekoderDEK.hodnota_dek = 0;
    dekoderDEK.stav = 0;
    
    rtmCOM4.hodnota_par = 0;
    //rtmCOM4.stav = 0;
    
    potenciometrPOT = 0;
    
    celkovy_vystup = 0;
    
    svitiV9 = 0;
    svitiV12 = 0;
    
    iniCasovac();       // provede inicializaci casovace (Timer2))
    iniOC();            // provede inicializaci OC16 jednotky
    startCasovacOC();   // spusti casovac i OC jednotku
    
    
}// configApplication() END 

//===>>>> Call it every 1ms <<<<===

void runApplication(void) {//--------------------------------------------------
  // sem volat moje funkce
    
    filtr(&filtrA,getCoderChannelA());      //zde filtruji tlacitka koderu
    filtr(&filtrB,getCoderChannelB());
    
    filtr(&filtrS1,getButtonS1());          //zde filtruji tlacitka S1 S2
    filtr(&filtrS2,getButtonS2());
    filtr(&filtrS3,getButtonS3());
    filtr(&filtrS4,getButtonS4());
    filtr(&filtrS5,getButtonS5());
    filtr(&filtrS6,getButtonS6());
    filtr(&filtrS7,getButtonS7());
    filtr(&filtrS8,getButtonS8());
    
    
    
    mem(&memS1,filtrS1.vystup);             //volani funkce pameti jejiz vstupem je vystup z filtru tlacitka S1
    mem(&memS2,filtrS2.vystup);             //volani funkce pameti jejiz vstupem je vystup z filtru tlacitka S2
    mem(&memS3,filtrS3.vystup);             //volani funkce pameti jejiz vstupem je vystup z filtru tlacitka S3
    
    setCoderLedA(filtrA.vystup);            //rozsviceni led vyfiltrovaneho signalu koderu
    setCoderLedB(filtrB.vystup); 
    
    setLedV1(memS1.vystup);                             //rozviceni led z pameti tlacitka S1 az S3
    setLedV2(memS2.vystup); 
    setLedV3(memS3.vystup); 
    
   
    dekoder(&dekoderDEK, filtrA.vystup, filtrB.vystup);     //volani fukce dekoderu - urci smer a dle nej pricita/odecita pocet hran kvadraturniho signalu na intervalu 0 az 255
    potenciometr(&potenciometrPOT);                         // volani funkce potenciometru - precte hodnotu potenciometru a tu upravi do zadaneho intervalu 0 az 255
    
    
    
    
    
    
    //----------------------------------------------------------------------------------------------------------------------
    

    
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
  //-----------------------zde volame RTM------------------------------------------------------------                                
  rtm(&rtmCOM4, memS1.vystup, memS2.vystup, memS3.vystup, svitiV9, svitiV12, celkovy_vystup, plc1.rtm_stav, plc1.rtm_index, plc1.rtm_zatezovatel); //volani funkce RTM 40ms delay je implementovan uvnitr funkce
   
  
  
   //----------------------zde se rozhoduje zda je bereme hodnotu z DEK nebo RTM------------------------------------------------------
   
  if(memS1.vystup == 1){ //pokud prisla spravna hodnota do COM4 a tlacitkoS1/diodaV1  je aktivni tak na vstupu PWM prepise hodnotu z DEK na hodotu z RTM
       celkovy_vystup = rtmCOM4.hodnota_par;
   }
  
  else{
    if((memS2.vystup) == 1){                                
        celkovy_vystup = dekoderDEK.hodnota_dek;
    }
    
    else if((memS2.vystup) == 0){
        celkovy_vystup = potenciometrPOT;
    }
  }
 
  setFpgaVxValue(celkovy_vystup); //rozsvici led 13 az 24 dle celkove vystupni hodnoty
  
  
  //----------------------zde se rozhoduje zda odesilat hodnotu z DEK/RTM nebo odesilat pouze nulovou hodnotu--------------------------------------------------
   /*if(memS3.vystup == 1){        //pokud je tlacitko S3 zmackle aktivuje vstup do PWM        
        OC16RS = ((celkovy_vystup/(255.0))*1875)+1875;  //prepocita a zapise hodnotu z dekoderu nebo reostatu do registru OC jednotky
   }
    
   else {
        OC16RS = 1875;      // hodnota PWM bude nastavena na 1 ms "nulov� hodnota"
   }
    */
    
  plc(&plc1, celkovy_vystup, filtrS4.vystup, filtrS5.vystup, filtrS6.vystup, filtrS7.vystup, filtrS8.vystup); 
    
    
    
    
}// runApplication() END)




