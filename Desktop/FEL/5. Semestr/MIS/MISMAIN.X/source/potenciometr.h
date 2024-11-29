/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _POTENCIOMETR_H    /* Guard against multiple inclusion */
#define _POTENCIOMETR_H


#include "platformMIS32mk.h"

#define Max_Hodnota_Re 2047     //maximalni hodnota kterou natocim na potenciometru
#define Max_Hodnota_Pre 255     //maximalni hodnota po prepoctu intervalu

    
void potenciometr(int* hodnota_pot_u);





#endif /* _FILTR_H */

/* *****************************************************************************
 End of File
 */
