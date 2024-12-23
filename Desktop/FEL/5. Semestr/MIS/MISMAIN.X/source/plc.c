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
                        SETpole[0] = vstup_zatezovatel;
                        break;
                    }
                    case 1:
                    {
                        SETpole[1] = vstup_zatezovatel;
                        break;
                    }
                    case 2:
                    {
                        SETpole[2] = vstup_zatezovatel;
                        break;
                    }
                    case 3:
                    {
                        SETpole[3] = vstup_zatezovatel;
                        break;
                    }
                    case 4:
                    {
                        SETpole[4] = vstup_zatezovatel;
                        break;
                    }
                    case 5:
                    {
                        SETpole[5] = vstup_zatezovatel;
                        break;
                    }
                    case 6:
                    {
                        SETpole[6] = vstup_zatezovatel;
                        break;
                    }
                    case 7:
                    {
                        SETpole[7] = vstup_zatezovatel;
                        break;
                    }
                    case 8:
                    {
                        SETpole[8] = vstup_zatezovatel;
                        break;
                    }
                     case 9:
                    {
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
            if(index2 >= pocet_zapsani){
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
            plc->rtm_index = 0;
            plc->rtm_zatezovatel = 0;
            plc->rtm_stav = 0;
            
            
            for(int i = 0; i<10; i++){
                SETpole[i] = 0;
            }
            
            plc->stav = 0;
            
            break;
        }
        case 4: //TEST
        {
            
            
            
        if(vstupS5 == 1){
                plc->stav = 1;
            }
        
        if(vstupS6 == 1){
                plc->stav = 3;
            }
        
        }
    }
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */
