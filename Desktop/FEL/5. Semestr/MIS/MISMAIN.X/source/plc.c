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
    int static index = 0;   //index pro rezim PROG
    int static indexRUN = 0;    
    int static indexTEST = 0;
    int static zapsano = 1; //zapsano je hodnota ktera je vyuzita pro detekci vymacknuti tlacitka SET
    static int delay = 0;   //delay pro rezim RUN
    static int delayTEST = 0;
    static int SETpole[10]; //pole ve kterem budou ulozeny hodnoty zatezovatele
    
    switch(plc->stav){  
        
        case 0: //PROG
        {
            plc->rtm_stav = 0; //odeslani stavu do RTM
            indexRUN = 0;   //reset indexu pro jine stavy, aby vzdy zacilai od 0 kdy? dojde k prepnuti
            indexTEST = 0;  
            
            if(vstupS7 == 1 && index < 10 && zapsano == 1){ //rozhodne zda ma ulozit zatezovatele
                zapsano = 0; //reset hodnoty zapsano
                plc->rtm_zatezovatel = prepocet_stupne(vstup_zatezovatel);  //odeslani zatezovatele do RTM s prepoctem na 0 az 90 stupnu
                plc->rtm_index = index; //odeslani indexu do RTM
                
                switch(index){  //zapis hodnot zatezovatele do jednotlivich policek pole (lze resit i jinak a mnohem jednoduseji, toto je spise takova debug verze, ktera ale funguje takze ji radsi nechci menit)
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
            if(vstupS7 == 0){   //pokud vymacknu tlacitko S7 nastavvi zapssano na 1
                zapsano = 1;
            }
            
            if(vstupS5 == 1){   // pokud zmacknu S5 spusti rezim RUN (nejnizsi priorita)
                plc->stav = 1;
            }
            
            if(vstupS8 == 1){   // pokud zmacknu S8 spusti rezim TEST
                plc->stav = 4;
            }
            
            if(vstupS6 == 1){   // pokud zmacknu S6 spusti rezim RESET (nejvyssi priorita v tomto stavu)
                plc->stav = 3;
            }
            
           
            
            break;
        }   
        
        case 1: //RUN
        {
            plc->rtm_stav = 1;  //odesle hodnotu stavu do RTM
            pocet_zapsani = index;  //Uloti pocet zapsanych zatezovatlu v rezimu PROG
            index = 0;  //reset indexu pro jine stavy, aby vzdy zacilai od 0 kdy? dojde k prepnuti
            indexTEST = 0;
            
            delay++;
            if(delay >= 2000){  //delay 2ms (Opet lze resit lepe. Toto reseni neni nejpresnejsi ale funkcni)
                
                plc->rtm_index = indexRUN;  //odeslani poradi nacitane hodnoty zatezovatele do RTM
                plc->rtm_zatezovatel = prepocet_stupne(SETpole[indexRUN]);  //odesilani aktualni hodnoty zatezovatele do RTM + prepoctani na interval 0 az 90
                OC16RS = ((SETpole[indexRUN]/(255.0))*1875)+1875;   //Zapis hodnoty do registru pro PWM
                indexRUN++;
                delay=0;    //reset delaye
            }
            if(indexRUN > pocet_zapsani){   //pokud dojde az na konec pole resetuje index a hodnoty se budou opakovat
                indexRUN = 0;
            }
            
            if(vstupS6 == 1){   //pri zmacknuti tlaccitka S6 k resetu vsech nastavenych zatezovatelu a navraceni do rezimu PROG (nizsi priorita nez rezim STOP)
                plc->stav = 3;
            }
            if(vstupS4 == 1){   //pri zmacknuti tlacitka S4 dojde k zastaveni (rezim STOP) (ma vyssi prioritu nez rezim RESET)
                plc->stav = 2;
            }
            
            break;
        }
        
        case 2: //STOP
        {
            plc->rtm_stav = 2;  //odeslani stavu do RTM
            plc->rtm_index = indexRUN;  //odeslani indexu na kterem doslo k zataveni do RTM
            plc->rtm_zatezovatel = prepocet_stupne(SETpole[indexRUN]);  //odeslani hodnoty zatezovatele na kterem doslo k zastaveni do RTM
            
            if(vstupS5 == 1){   //pokudzmacknu tlacitko S5 bude stav RUN pokracovat v behu tam kde skoncil
                plc->stav = 1;
            }
            break;
        }
        case 3:  //RESET
        {
            plc->rtm_index = 0;
            plc->rtm_zatezovatel = 0;
            plc->rtm_stav = 0;
            
            
            for(int i = 0; i<10; i++){  //nastaveni nulove hodnoty vsech policek v poli 
                SETpole[i] = 0;
            }
            
            plc->stav = 0;
            
            break;
        }
        case 4: //TEST
        {
            plc->rtm_stav = 4;  //odeslani stavu do RTM
            indexRUN = 0;   //reset indexu pro jine stavy, aby vzdy zacilai od 0 kdy? dojde k prepnuti
            index = 0;
            
            delayTEST++;
            if(delayTEST >= 2000){  //cekani 2ms
                
                plc->rtm_index = indexTEST; //odesilani aktualniho indexu do RTM
                plc->rtm_zatezovatel = prepocet_stupne(SETpole[indexTEST]);    //odesilani aktualni hodnoty zatezovatele do RTM            
                indexTEST++;
                delayTEST = 0;
            }
            if(indexTEST > pocet_zapsani){  //opakovani po preteceni vsech ulozenych hodnot
                indexTEST = 0;  
            }
            
            if(vstupS8 == 1){   //pokud zmacknu tlacitko S8 spusti rezim TEST od zacatku
                indexTEST = 0;
            }
            
            
            
            if(vstupS5 == 1){   //pokud zmacknu tlacitko S5 jdu do stavu RUN
                plc->stav = 1;
            }
        
            if(vstupS6 == 1){   //pokud zmacknu tlacitko S6 resetuju hodnoty
                plc->stav = 3;
            }
        
        }
    }
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */
