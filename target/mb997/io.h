//-----------------------------------------------------------------------------
/*

IO Pin Assignments

*/
//-----------------------------------------------------------------------------

#ifndef IO_H
#define IO_H

//-----------------------------------------------------------------------------

#include "stm32f4_soc.h"

//-----------------------------------------------------------------------------

#define IO_PUSH_BUTTON GPIO_NUM(PORTA, 0)  // GPIO: pushbutton (0=open,1=pressed)
#define IO_UART_TX GPIO_NUM(PORTA, 2)      // AF7: serial port tx
#define IO_UART_RX GPIO_NUM(PORTA, 3)      // AF7: serial port rx

#define IO_LED_GREEN GPIO_NUM(PORTD, 12)  // GPIO: green led
#define IO_LED_AMBER GPIO_NUM(PORTD, 13)  // GPIO: amber led
#define IO_LED_RED GPIO_NUM(PORTD, 14)    // GPIO: red led
#define IO_LED_BLUE GPIO_NUM(PORTD, 15)   // GPIO: blue led

//-----------------------------------------------------------------------------

#endif  // IO_H

//-----------------------------------------------------------------------------
