

#include "stdbool.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_tim.h"
#include "stm32f4xx_ll_rcc.h"

#include "FreeRTOS.h"
#include "task.h"

#include "KEY.h"
#include "kernel.h"
#include "bsp.h"


void    key_initPin (const Key_pinConfig* config);
uint8_t key_readPin (const Key_pinConfig* config);
void    key_callbacks_set (void);
//--------------------------------------------------------------------------------------------------------------
// key callbacks
/* Key_1 : Push Button */
void key_1_onHold (void);
void key_1_onReleased (void);
/* Key_2 : Alpha Switch */
void key_2_onReleased (void);
//--------------------------------------------------------------------------------------------------------------
const Key_pinConfig  KEY_CONFIGS[] = {
  {&VIO_PUSH_BT, ACTIVE_HIGH},      /* Push Button */
  {&VIO_ALPHA_SW, ACTIVE_LOW},      /* Alpha Switch */
};
const uint8_t KEY_LEN = LEN(KEY_CONFIGS);
Key keys[LEN(KEY_CONFIGS)];
//--------------------------------------------------------------------------------------------------------------
// key drivers 
Key_driver keyDriver = {
  .initPin  = key_initPin,
  .readPin  = key_readPin,
};
//--------------------------------------------------------------------------------------------------------------
void key_initPin (const Key_pinConfig* config) {
  static bool first_call = true;
  if (first_call == true) {
    /* Timer Configuration For Key Bouncing */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
    LL_TIM_DisableCounter(TIM6);
    uint32_t tim6Clock = __LL_RCC_CALC_PCLK1_FREQ(SystemCoreClock, LL_RCC_GetAPB1Prescaler()) * (LL_RCC_GetAPB1Prescaler() == LL_RCC_APB1_DIV_1? 1 : 2);  
    LL_TIM_SetPrescaler(TIM6, __LL_TIM_CALC_PSC(tim6Clock, 100000));
    LL_TIM_SetAutoReload(TIM6, __LL_TIM_CALC_ARR(tim6Clock, LL_TIM_GetPrescaler(TIM6), 20));
    LL_TIM_EnableIT_UPDATE(TIM6);
    LL_TIM_ClearFlag_UPDATE(TIM6);
    NVIC_SetPriority(TIM6_DAC_IRQn, KEY_TIM_IRQ_PRIORITY);
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
    first_call = false;
  }
  vio_init(config->VIO, true);
}

uint8_t key_readPin (const Key_pinConfig* config) {
  return LL_GPIO_IsInputPinSet(LL_VIO(config->VIO[0]));
}
//--------------------------------------------------------------------------------------------------------------
void key_callbacks_set (void) {
  keys[0].callBack.onHold     = key_1_onHold;
  keys[0].callBack.onReleased = key_1_onReleased;
  keys[1].callBack.onReleased = key_2_onReleased;
  LL_TIM_EnableCounter(TIM6);
}
//--------------------------------------------------------------------------------------------------------------
/* Key Callbacks */
//--------------------------------------------------------------------------------------------------------------
static uint8_t onHoldCounter = 0;
void key_1_onHold (void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  onHoldCounter++;
  if (onHoldCounter >= 18) {
    xTaskNotifyFromISR(tKernelHandle, 1 << 0, eSetBits, &xHigherPriorityTaskWoken);
  }
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
//--------------------------------------------------------------------------------------------------------------
void key_1_onReleased (void) {
  onHoldCounter = 0;
}
//--------------------------------------------------------------------------------------------------------------
void key_2_onReleased (void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xTaskNotifyFromISR(tKernelHandle, 1 << 0, eSetBits, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
//--------------------------------------------------------------------------------------------------------------
void TIM6_DAC_IRQHandler (void) {
  LL_TIM_ClearFlag_UPDATE(TIM6);
  key_handle(keys, KEY_LEN);
}
