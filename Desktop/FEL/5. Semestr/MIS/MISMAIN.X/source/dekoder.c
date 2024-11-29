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


#include "dekoder.h"

int pricti(int hodnotaDEK)      // funkce pro inkrementaci hodnoty dekoderu a opatreni proti preteceni hodnoty
{
    if(hodnotaDEK < 255){
        hodnotaDEK++;
    }
    return hodnotaDEK;
}

int odecti(int hodnotaDEK)      // funkce pro dekrementaci hodnoty a opatreni proti "preteceni" hodnoty
{
    if(hodnotaDEK > 0){
        hodnotaDEK--;
    }
    return hodnotaDEK;
}

void dekoder(dekoder_* dekoder, int vstupA, int vstupB) { 
    
    static int delay = 0;         
    
    
    if(delay > 0){         //vynecha prvni iteraci, ta je totiz vzdy A=0; B=0
        
        
        
        switch(dekoder->stav){      //logika dle stavoeho diagramu (fukce_dekoder)
            case 0:    
            {
                if(vstupA == 0 && vstupB == 0){
                    dekoder->stav = 1;
                }
                else if(vstupA == 1 && vstupB == 0){
                    dekoder->stav = 2;
                }
                else if(vstupA == 1 && vstupB == 1){
                    dekoder->stav = 3;
                }
                else if(vstupA == 0 && vstupB == 1){
                    dekoder->stav = 4;
                }
                    
                break;
            }
            
            case 1:
            { 
                if(vstupA == 1 && vstupB == 0){ //nastaneli tocim dekoderem smerem doprava
                    dekoder->stav = 2;
                    dekoder->hodnota_dek = pricti(dekoder->hodnota_dek);
                }
                
                else if(vstupA == 0 && vstupB == 1){ //nastaneli tocim dekoderem smerem doleva
                    dekoder->stav = 4;
                    dekoder->hodnota_dek = odecti(dekoder->hodnota_dek);
                }
                
                break;
            }
            
            case 2:
            {
                if(vstupA == 1 && vstupB == 1){ //nastaneli tocim dekoderem smerem doprava
                    dekoder->stav = 3;
                    dekoder->hodnota_dek = pricti(dekoder->hodnota_dek);
                }
                
                else if(vstupA == 0 && vstupB == 0){ //nastaneli tocim dekoderem smerem doleva
                    dekoder->stav = 1;
                    dekoder->hodnota_dek = odecti(dekoder->hodnota_dek);
                }
                break;
            }
            
            case 3:
            {
                if(vstupA == 0 && vstupB == 1){ //nastaneli tocim dekoderem smerem doprava
                    dekoder->stav = 4;
                    dekoder->hodnota_dek = pricti(dekoder->hodnota_dek);
                }
                
                else if(vstupA == 1 && vstupB == 0){ //nastaneli tocim dekoderem smerem doleva
                    dekoder->stav = 2;
                    dekoder->hodnota_dek = odecti(dekoder->hodnota_dek);
                }
                break;
            }
            
             case 4:
            {
                if(vstupA == 0 && vstupB == 0){ //nastaneli tocim dekoderem smerem doprava
                    dekoder->stav = 1;
                    dekoder->hodnota_dek = pricti(dekoder->hodnota_dek);
                }
                
                else if(vstupA == 1 && vstupB == 1){ //nastaneli tocim dekoderem smerem doleva
                    dekoder->stav = 3;
                    dekoder->hodnota_dek = odecti(dekoder->hodnota_dek);
                }
                break;
            }
            
        }
         
    }
    else {
    delay = delay+1; // inkrementace delay pro vynechani prvni iterace
    }
    
    
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */