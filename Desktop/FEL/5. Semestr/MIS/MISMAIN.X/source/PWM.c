/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */


#include "PWM.h"

void iniCasovac (void){
    T2CON = 0;      // zastavi casovac
    T2CONbits.TCS = 0; // nastavi interni hodnoty jako zdroj ticku
    T2CONbits.TCKPS = 0b101;    // nasvavy prescaler na 1:32
    TMR2 = 0;               // "vypne timer count registr" (moc nerozumim co presne dela)
    PR2 = 37499;        //nastvaeni doby periody (20 ms) s ohledem na 60MHz a 32 prescaler
}



void iniOC (void) {
  
}
    
void startCasovacOC (void) {
   
}



/* ****************
 
 
 
 *************************************************************
 End of File
 */