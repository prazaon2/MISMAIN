//Hlavicka funkce rtm


#ifndef _RTM_H    /* Guard against multiple inclusion */
#define _RTM_H

#include <stdbool.h>

#define One_Int_Len 3    //definuju delku zpravy jednoho cisla pro potenciomet
#define Two_Int_Len 5   //definuju delku zpravy dvou cisel pro tlacitka s pameti
#define Three_Int_Len 7 //definuju delku zpravy tri cisel pro tlacitka s pameti


typedef struct rtmPWM_ {
    int hodnota_par;    //zde bude zapsana hodnota parametru1 prijata pomoci rtm
    //bool stav;          //zde bude stav 1 pokud doslo k volani COM4 a zapisu parametru ve spravnem intervalu

    } rtmPWM_;

void rtm(rtmPWM_* COM4, bool mem_S1, bool mem_S2, bool mem_S3, int sviti9, int sviti12, int POT_DEK, int plcSTAV, int plcINDEX, int plcZATEZOVATEL);
    
#endif 