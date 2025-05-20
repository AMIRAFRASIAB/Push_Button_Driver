
#ifndef __PB_CONFIG_H_INCLUDED__
#define __PB_CONFIG_H_INCLUDED__

#ifdef __cplusplus 
  extern "C"{
#endif //__cplusplus 


#define STM32_SERIES                          F4



//-----------------------------------------------------------------
//-----------------------   Don't Touch   -------------------------
//-----------------------------------------------------------------
#define __PB_CONCAT(x, y)    x ## y
#define PB_CONCAT(x, y)      __PB_CONCAT(x, y)
#define __PB_TO_STRING(x)    #x
#define PB_TO_STRING(x)      __PB_TO_STRING(x)
#include PB_TO_STRING(PB_CONCAT(PB_CONCAT(stm32, STM32_SERIES), xx_ll_gpio.h))
//-----------------------------------------------------------------


#ifdef __cplusplus 
  };
#endif //__cplusplus 
#endif
