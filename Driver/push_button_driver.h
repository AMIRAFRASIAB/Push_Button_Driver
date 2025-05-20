
#ifndef __PB_HW_DRIVER_H_INCLUDED__
#define __PB_HW_DRIVER_H_INCLUDED__

#ifdef __cplusplus 
  extern "C"{
#endif //__cplusplus 


#include <stdbool.h>
#include "push_button.h"

//-----------------------------------------------------------------
static __inline void pb_hw_gpio_init (GPIO_TypeDef* GPIOx, uint32_t pin, PB_ActiveType_e active) {
  // Initialize the clock
  // Initialize the pin
  LL_GPIO_SetPinMode(GPIOx, pin, LL_GPIO_MODE_INPUT);
  if (active == PB_Active_Low) {
    LL_GPIO_SetPinPull(GPIOx, pin, LL_GPIO_PULL_UP);
  }
  else {
    LL_GPIO_SetPinPull(GPIOx, pin, LL_GPIO_PULL_DOWN);
  }
  LL_GPIO_LockPin(GPIOx, pin);
}
//-----------------------------------------------------------------
static __inline uint32_t pb_hw_gpio_read_pin (GPIO_TypeDef* GPIOx, uint32_t pin) {
  return LL_GPIO_IsInputPinSet(GPIOx, pin);
}
//-----------------------------------------------------------------

#ifdef __cplusplus 
  };
#endif //__cplusplus 
#endif