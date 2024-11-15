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
#include "filtr.h"
#include <stdbool.h>


void filtr(filtr_* filtr, bool vstup) { //funkce filtru (ukazatel na promenou ktera ukazuje stav a vystup tlacitka, hodonta pricházejici z tlacitka)
    // tady pisu tu funkci :)
    switch(filtr->stav){
        case 0:
        {
            if(vstup==1) {
                filtr->stav = 1;
            }
            else{
                filtr->stav = 3;
            }
            break;
        }    
        case 1:
        {
            if(vstup==1) {
                filtr->stav = 2;
            }
            else{
                filtr->stav = 3;
            }
            break;
        }    
        
        case 2:
        {
            if(vstup==1) {
                filtr->stav = 2;
                filtr->vystup = 1; // trikrat za sebou byla 1 tak nastavi vystup na 1
            }
            else{
                filtr->stav = 3;
                
            }
            
            break;
        }
        case 3:
        {
            if(vstup==1) {
                filtr->stav = 1;
            }
            else{
                filtr->stav = 4;
            }
            break;
        }
        case 4:
        {
            if(vstup==1) {
                filtr->stav = 1;
            }
            else{
                filtr->stav = 4;
                filtr->vystup = 0; // trikrat za sebou byla 0 tak nastavi vystup na 0
            }
            
            break;
        }
    }
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */
