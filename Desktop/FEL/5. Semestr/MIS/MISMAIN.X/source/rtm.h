//Hlavicka funkce rtm


#ifndef _RTM_H    /* Guard against multiple inclusion */
#define _RTM_H

#include <stdbool.h>

#define One_Int_Len 3    //definuju delku zpravy jednoho cisla pro potenciomet
#define Two_Int_Len 5   //definuju delku zpravy dvou cisel pro tlacitka s pameti
#define Three_Int_Len 7 //definuju delku zpravy tri cisel pro tlacitka s pameti

void rtm(bool mem_S1, bool mem_S2, int sviti9, int sviti12, int POT_DEK);

#endif 