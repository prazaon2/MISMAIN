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
    
    int static pocet_zapsani;
    int static index = 0;
    int static index2 = 0;
    int static zapsano = 1;
    static int delay = 0;
    static int SETpole[10];
    
    switch(plc->stav){
        
        case 0: //PROG
        {
            index2 = 0;
            if(vstupS7 == 1 && index < 10 && zapsano == 1){
                zapsano = 0;
                switch(index){
                    case 0:
                    {
                        plc->h1 = vstup_zatezovatel;
                        SETpole[0] = vstup_zatezovatel;
                        break;
                    }
                    case 1:
                    {
                        plc->h2 = vstup_zatezovatel;
                        SETpole[1] = vstup_zatezovatel;
                        break;
                    }
                    case 2:
                    {
                        plc->h3 = vstup_zatezovatel;
                        SETpole[2] = vstup_zatezovatel;
                        break;
                    }
                    case 3:
                    {
                        plc->h4 = vstup_zatezovatel;
                        SETpole[3] = vstup_zatezovatel;
                        break;
                    }
                    case 4:
                    {
                        plc->h5 = vstup_zatezovatel;
                        SETpole[4] = vstup_zatezovatel;
                        break;
                    }
                    case 5:
                    {
                        plc->h6 = vstup_zatezovatel;
                        SETpole[5] = vstup_zatezovatel;
                        break;
                    }
                    case 6:
                    {
                        plc->h7 = vstup_zatezovatel;
                        SETpole[6] = vstup_zatezovatel;
                        break;
                    }
                    case 7:
                    {
                        plc->h8 = vstup_zatezovatel;
                        SETpole[7] = vstup_zatezovatel;
                        break;
                    }
                    case 8:
                    {
                        plc->h9 = vstup_zatezovatel;
                        SETpole[8] = vstup_zatezovatel;
                        break;
                    }
                     case 9:
                    {
                        plc->h10 = vstup_zatezovatel;
                        SETpole[9] = vstup_zatezovatel;
                        break;
                    }
                    
                     
                }
                index++;
               
            
            }
            if(vstupS7 == 0){
                zapsano = 1;
            }
            
            if(vstupS5 == 1){
                plc->stav = 1;
            }
            
            if(vstupS8 == 1){
                plc->stav = 4;
            }
            
            if(vstupS6 == 1){
                plc->stav = 3;
            }
            
           
            
            break;
        }   
        
        case 1: //RUN
        {
            pocet_zapsani = index;
            index = 0;
            
            delay++;
            if(delay >= 1000){
                
                OC16RS = ((SETpole[index2]/(255.0))*1875)+1875;
                index2++;
                delay=0;
            }
            if(index2 > pocet_zapsani){
                index2 = 0;
            }
            
            if(vstupS6 == 1){
                plc->stav = 3;
            }
            if(vstupS4 == 1){
                plc->stav = 2;
            }
            
            
            
            
            break;
        }
        case 2: //STOP
        {
            if(vstupS5 == 1){
                plc->stav = 1;
            }
            break;
        }
        case 3:  //RESET
        {
            plc->h1 = 0;
            plc->h2 = 0;
            plc->h3 = 0;
            plc->h4 = 0;
            plc->h5 = 0;
            plc->h6 = 0;
            plc->h7 = 0;
            plc->h8 = 0;
            plc->h9 = 0;
            plc->h10 = 0;
            
            for(int i = 0; i<10; i++){
                SETpole[i] = 0;
            }
            
            plc->stav = 0;
            
            break;
        }
        case 4: //TEST
        {
            
        
        
        }
    }
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */
