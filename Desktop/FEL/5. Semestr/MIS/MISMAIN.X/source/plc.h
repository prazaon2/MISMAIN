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

#ifndef _PLC_H    /* Guard against multiple inclusion */
#define _PLC_H

#include "platformMIS32mk.h"
#include "PWM.h"


typedef struct plc_{
    
    char stav;
    int rtm_index;
    int rtm_zatezovatel;
    int rtm_stav;
    
}plc_;

void plc(plc_* plc, int vstup_zatezovatel, int vstupS4, int vstupS5, int vstupS6, int vstupS7, int vstupS8);


#endif 

/* *****************************************************************************
 End of File
 */