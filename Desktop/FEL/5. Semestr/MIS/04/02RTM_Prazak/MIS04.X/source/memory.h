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

#ifndef _MEMORY_H    /* Guard against multiple inclusion */
#define _MEMORY_H
#include <stdbool.h>


typedef struct mem_{
    bool vystup;
    char stav;
}mem_;

void mem(mem_* mem, bool input);


#endif /* _FILTR_H */

/* *****************************************************************************
 End of File
 */
