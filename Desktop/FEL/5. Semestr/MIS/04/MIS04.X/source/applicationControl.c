
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

//-- latform Function prototypes are in "platrformDEP32mk" ---------------------

//--- User function prototypes -------------------------------------------------


//--- Macros ------------------------------------------------------------------


//--- Constants ---------------------------------------------------------------
#define DELAY_ms  500

//--- New variable types ------------------------------------------------------

//--- Global vars -------------------------------------------------------------

//--- External vars -----------------------------------------------------------
// zde deklaruju globální promeny
filtr_ filtrS1; 
filtr_ filtrS2;
filtr_ filtrA;  
filtr_ filtrB; 
mem_ memS1;
mem_ memS2;
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
    // initFiltr(&filtrS1);
  
}// configApplication() END 

//===>>>> Call it every 1ms <<<<===

void runApplication(void) {//--------------------------------------------------
  // sem volat moje funkce
    
   
    setCoderLedA(filtr(&filtrA,getCoderChannelA())); //funkce spoustejici LED A koderu dle toho jaka filtorvana hodnota vyjde z A vystupu
    setCoderLedB(filtr(&filtrB,getCoderChannelB())); //funkce spoustejici LED B koderu dle toho jaka filtorvana hodnota vyjde z B vystupu
    setLedV1(mem(&memS1,filtr(&filtrS1,getButtonS1()))); //funkce spoustejici LED V1 dle toho jaka hodnoto vyjde z pameti do ktere vstupuje filtrovany vystup tlacitka S1
    setLedV2(mem(&memS2,filtr(&filtrS2,getButtonS2()))); //funkce spoustejici LED V2 dle toho jaka hodnota vyjde z pameti do ktere vstupuje filtorvany vystup tlacitka S2
    
}// runApplication() END)

//--- applicationControl.c file END -------------------------------------------


