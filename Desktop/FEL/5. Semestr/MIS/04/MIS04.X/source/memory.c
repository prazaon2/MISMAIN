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
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

    

#include "memory.h"
#include <stdbool.h>


void mem(mem_* mem, bool vstup) { //funkce pameti (ukazatel na promenou ktera ukazuje stav a vystup filtrovaneho tlacitka, hodonta pricházejici z filtru)
    
    switch(mem->stav){
        case 0:         
        {
            if(vstup==1) {
                mem->stav = 1;
            }
            else{
                mem->stav = 0;
            }
            
            break;
        }    
        case 1:             // kdyz tlcitko stale drzim jsem setrvavam ve stavu 1 a vystup je 1
        {
            mem->vystup = 1;            //pkud jsem ve stavu jedna tlacitka bylo zmacknuto a je t?eba p?epast vystup
            if(vstup==1) {
                mem->stav = 1;
            }
            else{                               // kdyz tlacitko pustim jdu do stavu 2
                mem->stav = 2;
            }

            break;
        }    
        case 2:                 // zde pokud je tlacitko stale pustene tak se nic nemení a jsem zacyklen zde
        {
            if(vstup==1) {      // pokud vsak zmacknu tlacitko posunu se na stav 3
                mem->stav = 3;
            }
            else{
                mem->stav = 2;
            }
           
            break;
        }    
        case 3:             // zde doslo k opakovanemu stisknuti tlacitka tedy je nutno zmenit vystup na 0
        {
            mem->vystup = 0;
            if(vstup==1) {          // pokud tlacitko porad drzim nic se nedeje a vystup zustava 0
                mem->stav = 3;
            }
            else{                      // pokud tlacitko pustim jdu na stav 0 a cely cyklus se opakuje
                mem->stav = 0;
            }

            break;
        }    
    }
}