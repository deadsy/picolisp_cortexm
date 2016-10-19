//-----------------------------------------------------------------------------
/*

GPIO Control for the STM32F4 Discovery Board

*/
//-----------------------------------------------------------------------------

#ifndef GPIO_H
#define GPIO_H

//-----------------------------------------------------------------------------

#include "stm32f4xx_hal.h"

//-----------------------------------------------------------------------------
// port numbers

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
#define PORTG 6
#define PORTH 7
#define PORTI 8

//-----------------------------------------------------------------------------
// gpio macros

#define GPIO_NUM(port, pin) ((port << 4) | (pin))
#define GPIO_PORT(n) (n >> 4)
#define GPIO_PIN(n) (n & 0xf)
#define GPIO_BIT(n) (1 << GPIO_PIN(n))
#define GPIO_BASE(n) ((GPIO_TypeDef  *)(GPIOA_BASE + (GPIO_PORT(n) * 0x400)))

//-----------------------------------------------------------------------------
// gpio assignments

// standard board GPIO
#define LED_GREEN       GPIO_NUM(PORTD, 12)
#define LED_AMBER       GPIO_NUM(PORTD, 13)
#define LED_RED         GPIO_NUM(PORTD, 14)
#define LED_BLUE        GPIO_NUM(PORTD, 15)
#define PUSH_BUTTON     GPIO_NUM(PORTA, 0) // 0 = open, 1 = pressed

// serial port
#define UART_TX         GPIO_NUM(PORTA, 2)
#define UART_RX         GPIO_NUM(PORTA, 3)

//-----------------------------------------------------------------------------
// generic api functions

static inline void gpio_clr(int n)
{
    GPIO_BASE(n)->BSRR = 1 << (GPIO_PIN(n) + 16);
}

static inline void gpio_set(int n)
{
    GPIO_BASE(n)->BSRR = 1 << GPIO_PIN(n);
}

static inline void gpio_toggle(int n)
{
    GPIO_BASE(n)->ODR ^= GPIO_BIT(n);
}

static inline int gpio_rd(int n)
{
    return (GPIO_BASE(n)->IDR >> GPIO_PIN(n)) & 1;
}

static inline int gpio_rd_inv(int n)
{
    return (~(GPIO_BASE(n)->IDR) >> GPIO_PIN(n)) & 1;
}

void gpio_init(void);

//-----------------------------------------------------------------------------
// The input gpios are spread out across several ports. We read and pack them into a
// single uint32_t and debounce them together.

// bit assignment for the debounced state - not all of these are used
#define PUSH_BUTTON_BIT 0

static inline uint32_t debounce_input(void)
{
    // map the gpio inputs to be debounced into the uint32_t debounce state
    return (gpio_rd(PUSH_BUTTON) << PUSH_BUTTON_BIT);
}

//-----------------------------------------------------------------------------

#endif // GPIO_H

//-----------------------------------------------------------------------------
