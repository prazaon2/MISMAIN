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

#include "messengerMIS.h"
#include "rtm.h"
#include <stdbool.h>
#include <stdio.h>

unsigned char recBuf[40];  //inicializace pole prichozi zpravy
unsigned char sendBuf[40];  //inicializace pole obsahujiciho odesilanou zpravu


void rtm(bool mem_S1, bool mem_S2) { 
    
    static int delay = 0; 
    static char delka = 0;
    static char typ = 0;
    static int stav_tabulka = 0;
  
    
    delay = delay+1; //inkcementace
    
    if(delay >= 40){
        
        getMessageUSB(recBuf,0); //pripravena funkce - prijme zpravu z PC a uloziji do pole recBuf
            delka = recBuf[0];  // na pozici 0 se nachazi informace o delce zpravy. Bude se hodit kdyz budu chtit pridat kontrolu prijate zpravy
            typ = recBuf[1];    //na pozici 1 se nachazi informace o typu prijate zpravy => jaky COM jsem vybral na PC
            
            switch(typ){   
                case 0:{    //COM0 preruseni komunikace
                    break;
                }
                case 1:         //COM1 odesilej hodnotu potenciometru
                {
                    sendBuf[0]= One_Int_Len; //uvedeni delky zpravy
                    integerToBytes(getPotentiometerValue(),&sendBuf[1]); //priprava zpravy
                    sendMessageUSB(sendBuf,0); //odeslani do PC
                    break;
                }
                case 2:         //COM2 odesilej hodnotu tlacitek s pameti
                {
                    sendBuf[0]= Two_Int_Len;  //uvedeni delky zpravy
                    integerToBytes(mem_S1,&sendBuf[1]); //priprava zpravy
                    integerToBytes(mem_S2,&sendBuf[3]);//priprava zpravy
                    sendMessageUSB(sendBuf,0); //odeslani do PC
                    break;
                }
                case 3:     //COM3 tabulka - jalikoz nelze zapsat vice bunek najednou tak kazdy cyklus 40ms zapise jednu bunku
                {
                    
                    switch(stav_tabulka){
                        case 0: //zapis prvni bunky
                        {    
                            sprintf(sendBuf,"Hodnota AD = %d", getPotentiometerValue()); //za %d se dosadi hodnota potenciometru
                            sendTableTerminalMessageUSB("1A",sendBuf); //odesle zpravu do prvni bunky tabulky
                            stav_tabulka = 1;
                            break;
                        }
                        case 1:         //zapis druhe bunky
                        {
                            sprintf(sendBuf,"Tlacitko S1 = %d", mem_S1); //za %d se dosadi hodnota memS1
                            sendTableTerminalMessageUSB("2A",sendBuf); //odesle zpravu do druhe bunky tabulky 
                            stav_tabulka = 2;
                            break;
                        }
                        case 2:         //zapis treti bunky
                        {
                            sprintf(sendBuf,"Tlacitko S2 = %d", mem_S2); //za %d se dosadi hodnota memS2
                            sendTableTerminalMessageUSB("3A",sendBuf); //odesle zpravu do treti bunky tabulky 
                            stav_tabulka = 0;
                            break;
                        }
                    
                    break;
                    }
                }
            }
    }  
}
        
        
        
        
        
        
        
        
    
           
   
