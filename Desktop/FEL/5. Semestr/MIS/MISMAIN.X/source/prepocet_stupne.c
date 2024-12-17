
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
#include "prepocet_stupne.h"





int prepocet_stupne(int celk_hodnota) { // funkce prepoctu celkove hodnoty z O az 255 na 0 az 90
    
    celk_hodnota = (celk_hodnota*90)/255;
     
    
    return celk_hodnota;
}

/* ****************
 
 
 
 *************************************************************
 End of File
 */