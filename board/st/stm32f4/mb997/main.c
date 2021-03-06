//-----------------------------------------------------------------------------
/*

*/
//-----------------------------------------------------------------------------

#include "stm32f4xx_hal.h"

#include "gpio.h"
#include "debounce.h"
#include "timers.h"
#include "usart.h"

//#define DEBUG
#include "logging.h"

//-----------------------------------------------------------------------------

extern int picolisp_main(int ac, char *av[]);

//-----------------------------------------------------------------------------

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  while (1);
}
#endif

void Error_Handler(void) {
  while (1);
}

//-----------------------------------------------------------------------------

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  // Enable Power Control clock
  __HAL_RCC_PWR_CLK_ENABLE();

  // The voltage scaling allows optimizing the power consumption when the device is
  // clocked below the maximum system frequency, to update the voltage scaling value
  // regarding system frequency refer to product datasheet.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // Enable HSE oscillator and configure the PLL to reach the max system frequency (168MHz)
  // when using HSE oscillator as PLL clock source. */
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

  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers.
  // The SysTick 1 msec interrupt is required for the HAL process (Timeout management); by default
  // the configuration is done using the HAL_Init() API, and when the system clock configuration
  // is updated the SysTick configuration will be adjusted by the HAL_RCC_ClockConfig() API.
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    Error_Handler();
  }

  // STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported
  if (HAL_GetREVID() == 0x1001) {
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }

  // Output SYSCLK divided by 2 on MCO2 pin(PC9)
  HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_2);
}

//-----------------------------------------------------------------------------

void debounce_on_handler(uint32_t bits) {
  if (bits & (1 << PUSH_BUTTON_BIT)) {
    gpio_set(LED_RED);
  }
}

void debounce_off_handler(uint32_t bits) {
  if (bits & (1 << PUSH_BUTTON_BIT)) {
    gpio_clr(LED_RED);
  }
}

//-----------------------------------------------------------------------------

int main(void) {
  char *argv[] = {"", 0};

  log_init();

  HAL_Init();
  SystemClock_Config();
  gpio_init();
  debounce_init();
  usart_init();

  picolisp_main(2, argv);
  return 0;
}

//-----------------------------------------------------------------------------
