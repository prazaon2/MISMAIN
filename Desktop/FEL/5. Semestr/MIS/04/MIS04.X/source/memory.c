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



void mem(mem_* mem, bool vstup) { //funkce pameti (ukazatel na promenou ktera ukazuje stav a vystup filtrovaneho tlacitka, hodonta pricházejici z filtru)
    // tady pisu tu funkci :)
    switch(mem->stav){
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
        
    }
}