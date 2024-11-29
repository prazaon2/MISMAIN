//Hlavicka funkce rtm


#ifndef _RTM_H    /* Guard against multiple inclusion */
#define _RTM_H

#include <stdbool.h>

#define One_Int_Len 3    //definuju delku zpravy jednoho cisla pro potenciomet
#define Two_Int_Len 5   //definuju delku zpravy dvou cisel pro tlacitka s pameti

void rtm(bool mem_S1, bool mem_S2,int hodnota_dek_r,int hodnota_pot_r);

#endif 