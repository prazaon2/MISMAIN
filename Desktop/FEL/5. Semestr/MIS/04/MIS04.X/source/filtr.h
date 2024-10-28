/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _FILTR_H    /* Guard against multiple inclusion */
#define _FILTR_H
#include <stdbool.h>

enum {s0,s1,s2,s3,s4};

typedef struct filtr_{
    bool vystup;
    char stav;
}filtr_;

void filtr(filtr_* filtr, bool input);


#endif /* _FILTR_H */

/* *****************************************************************************
 End of File
 */
