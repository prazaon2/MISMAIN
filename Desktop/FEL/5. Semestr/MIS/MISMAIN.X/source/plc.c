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
#include "prepocet_stupne.h"



void plc(plc_* plc, int vstup_zatezovatel, int vstupS4, int vstupS5, int vstupS6, int vstupS7, int vstupS8) { 
    
    int static pocet_zapsani;
    int static index = 0;
    int static indexRUN = 0;
    int static indexTEST = 0;
    int static zapsano = 1;
    static int delay = 0;
    static int delayTEST = 0;
    static int SETpole[10];
    
    switch(plc->stav){
        
        case 0: //PROG
        {
            plc->rtm_stav = 0;
            indexRUN = 0;
            indexTEST = 0;
            if(vstupS7 == 1 && index < 10 && zapsano == 1){
                zapsano = 0;
                plc->rtm_zatezovatel = prepocet_stupne(vstup_zatezovatel);
                plc->rtm_index = index;
                
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
            plc->rtm_stav = 1;
            pocet_zapsani = index;
            index = 0;
            indexTEST = 0;
            
            delay++;
            if(delay >= 2000){
                
                plc->rtm_index = indexRUN;
                plc->rtm_zatezovatel = prepocet_stupne(SETpole[indexRUN]);
                OC16RS = ((SETpole[indexRUN]/(255.0))*1875)+1875;
                indexRUN++;
                delay=0;
            }
            if(indexRUN > pocet_zapsani){
                indexRUN = 0;
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
            plc->rtm_stav = 2;
            plc->rtm_index = indexRUN;
            plc->rtm_zatezovatel = prepocet_stupne(SETpole[indexRUN]);
            
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
            indexRUN = 0;
            index = 0;
            
            delayTEST++;
            if(delayTEST >= 2000){
                
                plc->rtm_index = indexTEST;
                plc->rtm_zatezovatel = prepocet_stupne(SETpole[indexTEST]);                
                indexTEST++;
                delayTEST = 0;
            }
            if(indexTEST > pocet_zapsani){
                indexTEST = 0;
            }
            
            if(vstupS8 == 1){
                indexTEST = 0;
            }
            
            plc->rtm_stav = 4;
            
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
