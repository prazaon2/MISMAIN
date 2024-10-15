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
#include "filtr.h"

void filtr(filtr_t* filtr, bool input) {
    // tady pisu tu funkci :)
    switch(filtr->state){
        case 0:
        {
            if(input) {
                filtr->state = 1;
            }
            else{
                filtr->state = 3;
            }
        //logika
            break;
        }
    }
}

/* *****************************************************************************
 End of File
 */
