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
#include "plc.h"



void plc(plc_* plc, int vstup_zatezovatel, int vstupS4, int vstupS5, int vstupS6, int vstupS7, int vstupS8) { 
    
    int static index = 0;
    
    switch(plc->stav){
        
        case 0: //PROG
        {
            if(vstupS7 == 1 && index < 9){
                switch(index){
                    case 0:
                    {
                        plc->h1 = vstup_zatezovatel;
                        break;
                    }
                    case 1:
                    {
                        plc->h2 = vstup_zatezovatel;
                        break;
                    }
                    case 2:
                    {
                        plc->h3 = vstup_zatezovatel;
                        break;
                    }
                    case 3:
                    {
                        plc->h4 = vstup_zatezovatel;
                        break;
                    }
                    case 4:
                    {
                        plc->h5 = vstup_zatezovatel;
                        break;
                    }
                    case 5:
                    {
                        plc->h6 = vstup_zatezovatel;
                        break;
                    }
                    case 6:
                    {
                        plc->h7 = vstup_zatezovatel;
                        break;
                    }
                    case 7:
                    {
                        plc->h8 = vstup_zatezovatel;
                        break;
                    }
                    case 8:
                    {
                        plc->h9 = vstup_zatezovatel;
                        break;
                    }
                     case 9:
                    {
                        plc->h10 = vstup_zatezovatel;
                        break;
                    }
                     
                }
                index++;
               
            
            }
            
            if(vstupS5 == 1){
                plc->stav = 1;
            }
            
            break;
        }    
        case 1:
        {
            index = 0;
            if(vstupS4 == 1){
                plc->stav = 2;
            }
            
            
            break;
        }
        case 2:
        {
        
            break;
        }
    }
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */
