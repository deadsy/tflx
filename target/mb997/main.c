//-----------------------------------------------------------------------------
/*

MB997C Board

*/
//-----------------------------------------------------------------------------

#include <stdio.h>

#include "debounce.h"
#include "io.h"
#include "stm32f4_soc.h"
#include "utils.h"

#define DEBUG
#include "logging.h"

//-----------------------------------------------------------------------------
// IO configuration

static const struct gpio_info gpios[] = {
    // leds
    {IO_LED_RED, GPIO_MODER_OUT, GPIO_OTYPER_PP, GPIO_OSPEEDR_LO, GPIO_PUPD_NONE, GPIO_AF0, 0},
    {IO_LED_BLUE, GPIO_MODER_OUT, GPIO_OTYPER_PP, GPIO_OSPEEDR_LO, GPIO_PUPD_NONE, GPIO_AF0, 0},
    {IO_LED_GREEN, GPIO_MODER_OUT, GPIO_OTYPER_PP, GPIO_OSPEEDR_LO, GPIO_PUPD_NONE, GPIO_AF0, 0},
    {IO_LED_AMBER, GPIO_MODER_OUT, GPIO_OTYPER_PP, GPIO_OSPEEDR_LO, GPIO_PUPD_NONE, GPIO_AF0, 0},
    // push buttons
    {IO_PUSH_BUTTON, GPIO_MODER_IN, GPIO_OTYPER_PP, GPIO_OSPEEDR_LO, GPIO_PUPD_NONE, GPIO_AF0, 0},
    // serial port (usart2 function)
    {IO_UART_TX, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_HI, GPIO_PUPD_NONE, GPIO_AF7, 0},
    {IO_UART_RX, GPIO_MODER_AF, GPIO_OTYPER_PP, GPIO_OSPEEDR_HI, GPIO_PUPD_NONE, GPIO_AF7, 0},
};

//-----------------------------------------------------------------------------

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  while (1)
    ;
}
#endif

void Error_Handler(void) {
  while (1)
    ;
}

//-----------------------------------------------------------------------------

void NMI_Handler(void) {}
void HardFault_Handler(void) {
  while (1)
    ;
}
void MemManage_Handler(void) {
  while (1)
    ;
}
void BusFault_Handler(void) {
  while (1)
    ;
}
void UsageFault_Handler(void) {
  while (1)
    ;
}
void SVC_Handler(void) {}
void DebugMon_Handler(void) {}
void PendSV_Handler(void) {}

void SysTick_Handler(void) {
  uint32_t ticks = HAL_GetTick();
  // blink the green led every 512 ms
  if ((ticks & 511) == 0) {
    gpio_toggle(IO_LED_GREEN);
  }
  // sample debounced inputs every 16 ms
  if ((ticks & 15) == 0) {
    debounce_isr();
  }
  HAL_IncTick();
}

//-----------------------------------------------------------------------------

static void SystemClock_Config(void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  // Enable Power Control clock
  __PWR_CLK_ENABLE();

  // The voltage scaling allows optimizing the power consumption when the device is
  // clocked below the maximum system frequency, to update the voltage scaling value
  // regarding system frequency refer to product datasheet.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // Enable HSE Oscillator and activate PLL with HSE as source
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }
}

//-----------------------------------------------------------------------------
// key debouncing (called from the system tick isr)

#define PUSH_BUTTON_BIT 0

// handle a key down
void debounce_on_handler(uint32_t bits) {
  if (bits & (1 << PUSH_BUTTON_BIT)) {
    // TODO
  }
}

// handle a key up
void debounce_off_handler(uint32_t bits) {
  if (bits & (1 << PUSH_BUTTON_BIT)) {
    // TODO
  }
}

// map the gpio inputs to be debounced into the 32 bit debounce state
uint32_t debounce_input(void) { return gpio_rd(IO_PUSH_BUTTON) << PUSH_BUTTON_BIT; }

//-----------------------------------------------------------------------------
// Console serial port (on USART2)

struct usart_cfg serial_cfg = {
    .base = USART2_BASE,
    .baud = 115200,
    .data = 8,
    .parity = 0,
    .stop = 1,
};

struct usart_drv serial_drv;

void USART2_IRQHandler(void) { usart_isr(&serial_drv); }

//-----------------------------------------------------------------------------

int tfl_main(void);

int main(void) {
  int rc;

  HAL_Init();
  SystemClock_Config();

  // logging init
  rc = log_init();
  if (rc != 0) {
    goto exit;
  }
  // gpio init
  rc = gpio_init(gpios, sizeof(gpios) / sizeof(struct gpio_info));
  if (rc != 0) {
    DBG("gpio_init failed %d\r\n", rc);
    goto exit;
  }
  // debounce init
  rc = debounce_init();
  if (rc != 0) {
    DBG("debounce_init failed %d\r\n", rc);
    goto exit;
  }
  // serial port init
  rc = usart_init(&serial_drv, &serial_cfg);
  if (rc != 0) {
    DBG("usart_init failed %d\r\n", rc);
    goto exit;
  }
  // setup the interrupts for the serial port
  HAL_NVIC_SetPriority(USART2_IRQn, 10, 0);
  NVIC_EnableIRQ(USART2_IRQn);

  DBG("init good\r\n");
  printf("\n%s, line %d\n", __FILE__, __LINE__);

  tfl_main();
  while (1)
    ;

exit:
  while (1)
    ;
  return 0;
}

//-----------------------------------------------------------------------------
