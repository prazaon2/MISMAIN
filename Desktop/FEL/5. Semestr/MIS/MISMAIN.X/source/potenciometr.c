
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
#include "potenciometr.h"





void potenciometr(int* hodnota_pot_u) { // funkce prepoctu potenciometru z hodnoty -2047 az 2047 na 0 az 255
    
    
    static int realna_hodnota_pot = 0;
    static int pot = 0;
    
    
    realna_hodnota_pot = getPotentiometerValue(); //ulozim realnou hodnotu potenciometru
    
    pot = realna_hodnota_pot + Max_Hodnota_Re;  //z itervalu -2047 az 2047 udelam interval 0 az 4096
    
    *hodnota_pot_u = (Max_Hodnota_Pre*pot)/(Max_Hodnota_Re*2);  //pomoci trojclenky prepocitam na zadany interval ovsem jmenovatel musim nasobit dvemi kvuli predeslemu pricteni hodnoty
                                                                // vystup funkce je realizovan pomoci ukazatele - dereferencovani
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */