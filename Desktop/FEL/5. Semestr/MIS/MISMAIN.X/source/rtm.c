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
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
int global_data;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

#include "messengerMIS.h"   //knihovna z moodlu
#include "rtm.h"
#include <stdbool.h>        //knihovna potrebna pro datovy typ bool
#include <stdio.h>          //knihovna potrebna pro sprintf
#include "platformMIS32mk.h"

unsigned char recBuf[40];  //inicializace pole prichozi zpravy
unsigned char sendBuf[40];  //inicializace pole obsahujiciho odesilanou zpravu


void rtm(rtmPWM_* COM4, bool mem_S1, bool mem_S2, bool mem_S3, int sviti9, int sviti12, int POT_DEK, int plcSTAV, int plcINDEX, int plcZATEZOVATEL) { //inicializace funkce vstupem jsou funkce mem - pameti tlacitek
    
    static int delay = 0; 
    static char delka = 0;
    static char typ = 0;
    static char parametr1 = 0;
    static int stav_tabulka = 0;
    static int stav_tabulkaPLC = 0;
    
    delay = delay+1; //inkcementace
    
    if(delay >= 40){
        delay = 0;
        getMessageUSB(recBuf,0); //pripravena funkce - prijme zpravu z PC a uloziji do pole recBuf
            delka = recBuf[0];  // na pozici 0 se nachazi informace o delce zpravy. Bude se hodit kdyz budu chtit pridat kontrolu prijate zpravy
            typ = recBuf[1];    //na pozici 1 se nachazi informace o typu prijate zpravy => jaky COM jsem vybral na PC
            parametr1 = bytesToInteger(&recBuf[3]); // na pozici 3 se nachazi parametr1 je nutne ho prevest na integer
            
            switch(typ){   
                case 0:{    //COM0 preruseni komunikace
                    
                    break;
                }
                case 1:         //COM1 odesilej hodnotu potenciometru/dekoderu a stavy na ledkach ukazujici maximum a minimum 
                {
                    sendBuf[0]= Three_Int_Len; //uvedeni delky zpravy
                    integerToBytes(POT_DEK,&sendBuf[1]); //priprava zpravy z potenciometru/dekoderu
                    integerToBytes(sviti9*100,&sendBuf[3]); //priprava zpravy... hodnotu nasobim stem aby byla dobre videt v zobrazovacim SW na PC v porovnani s POT_DEK
                    integerToBytes(sviti12*100,&sendBuf[5]); //priprava zpravy... hodnotu nasobim stem aby byla dobre videt v zobrazovacim SW na PC v porovnani s POT_DEK
                    sendMessageUSB(sendBuf,0); //odeslani do PC
                    break;
                }
                case 2:         //COM2 odesilej hodnotu tlacitek s pameti //narozdil od predeslich ukolu je zde pridano tlacitko S3
                {
                    sendBuf[0]= Three_Int_Len;  //uvedeni delky zpravy
                    integerToBytes(mem_S1*100,&sendBuf[1]); //priprava zpravy... hodnotu nasobim stem aby byla dobre videt v zobrazovacim SW na PC
                    integerToBytes(mem_S2*100,&sendBuf[3]); //priprava zpravy... hodnotu nasobim stem aby byla dobre videt v zobrazovacim SW na PC
                    integerToBytes(mem_S3*100,&sendBuf[5]); //priprava zpravy... hodnotu nasobim stem aby byla dobre videt v zobrazovacim SW na PC
                    sendMessageUSB(sendBuf,0); //odeslani do PC
                    break;
                }
                case 3:     //COM3 tabulka - jelikoz nelze zapsat vice bunek najednou tak kazdy cyklus 40ms zapise jednu bunku //zde stejne
                {
                    
                    switch(stav_tabulka){
                        case 0: //zapis prvni bunky
                        {    
                            sprintf(sendBuf,"Hodnota AD = %d", POT_DEK); //za %d se dosadi hodnota potenciometru
                            sendTableTerminalMessageUSB("1A",sendBuf); //odesle zpravu do prvni bunky tabulky
                            stav_tabulka = 1;
                            break;
                        }
                        case 1:         //zapis druhe bunky
                        {
                            sprintf(sendBuf,"LED V1 = %d", mem_S1); //za %d se dosadi hodnota memS1
                            sendTableTerminalMessageUSB("2A",sendBuf); //odesle zpravu do druhe bunky tabulky 
                            stav_tabulka = 2;
                            break;
                        }
                        case 2:         //zapis treti bunky
                        {
                            sprintf(sendBuf,"LED V2 = %d", mem_S2); //za %d se dosadi hodnota memS2
                            sendTableTerminalMessageUSB("3A",sendBuf); //odesle zpravu do treti bunky tabulky 
                            stav_tabulka = 3;
                            break;
                        }
                         case 3:         //zapis ctvrte bunky
                        {
                            sprintf(sendBuf,"LED V9 = %d", sviti9); //za %d se dosadi hodnota sviti9
                            sendTableTerminalMessageUSB("2C",sendBuf); //odesle zpravu do druhe bunky tretiho sloupce tabulky 
                            stav_tabulka = 4;
                            break;
                        }
                          case 4:         //zapis pate bunky
                        {
                            sprintf(sendBuf,"LEDV12 = %d", sviti12); //za %d se dosadi hodnota sviti12
                            sendTableTerminalMessageUSB("3C",sendBuf); //odesle zpravu treti bunky tretiho sloupce tabulky
                            stav_tabulka = 0;
                            break;
                        }
                    
                    break;
                    }
                  
                }
                
                case 4:         //COM4 precte parametr 1 pokud v nem bude hodnota 0 az 255 a posle ho do PWM
                {
                    if((parametr1 >= 0) && (parametr1 <= 255)){
                        COM4->hodnota_par = parametr1; 
                        //COM4->stav = 1;             // pokud hodnota vyplnena v parametru1 nebude v zadanem intervalu nebude ani odeslana do PWM
                    }
                   // else{
                    //    COM4->stav = 0;
                 //   }
                    break;
                }
                
                case 5: //COM5 pro ulohu PLC
                {
                    switch(stav_tabulkaPLC){
                        case 0: //zapis stavu do bunky
                        {   
                            switch(plcSTAV){        //zvoli dle akrualniho stavu PLC
                                case 0: //PROG
                                {
                                    sprintf(sendBuf,"Prog"); 
                                    sendTableTerminalMessageUSB("1A",sendBuf); 
                                    break;
                                }
                                
                                case 1: //RUN
                                {
                                    sprintf(sendBuf,"Run"); 
                                    sendTableTerminalMessageUSB("1A",sendBuf);
                                    break;
                                }
                                
                                case 2: //STOP
                                {
                                    sprintf(sendBuf,"Stop"); 
                                    sendTableTerminalMessageUSB("1A",sendBuf);
                                    break;
                                }
                                
                                case 4: //TEST
                                {
                                    sprintf(sendBuf,"Test"); 
                                    sendTableTerminalMessageUSB("1A",sendBuf);
                                    break;
                                }
                            
                            }
                          
                            stav_tabulkaPLC = 1;
                            break;
                        }
                        case 1:         //zapis indexu do bunky
                        {
                            sprintf(sendBuf,"index = %d", plcINDEX); //za %d se dosadi hodnota memS1
                            sendTableTerminalMessageUSB("1B",sendBuf); //odesle zpravu do druhe bunky tabulky 
                            stav_tabulkaPLC = 2;
                            break;
                        }
                        case 2:         //zapis zatezovatele do bunky
                        {
                            sprintf(sendBuf,"zatezovatel = %d", plcZATEZOVATEL); //za %d se dosadi hodnota memS2
                            sendTableTerminalMessageUSB("1C",sendBuf); //odesle zpravu do treti bunky tabulky 
                            stav_tabulkaPLC = 0;
                            break;
                        }
                        
                    }
                    break;
                }
            }
            
    }  
}
        
        
        
        
        
        
        
        
    
           
   
