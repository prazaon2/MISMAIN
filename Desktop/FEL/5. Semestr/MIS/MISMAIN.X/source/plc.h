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
    int h1;
    int h2;
    int h3;
    int h4;
    int h5;
    int h6;
    int h7;
    int h8;
    int h9;
    int h10;
}plc_;

void plc(plc_* plc, int vstup_zatezovatel, int vstupS4, int vstupS5, int vstupS6, int vstupS7, int vstupS8);


#endif 

/* *****************************************************************************
 End of File
 */