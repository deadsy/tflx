//-----------------------------------------------------------------------------
/*

Switch Input Debouncing

*/
//-----------------------------------------------------------------------------

#ifndef DEBOUNCE_H
#define DEBOUNCE_H

//-----------------------------------------------------------------------------

#include <inttypes.h>

//-----------------------------------------------------------------------------

int debounce_init(void);
void debounce_isr(void);
uint32_t debounce_input(void);

//-----------------------------------------------------------------------------

#endif  // DEBOUNCE_H

//-----------------------------------------------------------------------------
