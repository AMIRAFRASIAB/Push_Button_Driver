

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

#define LEN(x)  (sizeof(x) / sizeof(*x))

/* Key Drivers ProtoTypes */
void    key_initPin (const Key_pinConfig* config);
uint8_t key_readPin (const Key_pinConfig* config);
void    key_callbacks_set (void);
void    key_timer_init (void);
//--------------------------------------------------------------------------------------------------------------
/* Key Callbacks ProtoTypes */
void key_1_onHold (void);
void key_2_onReleased (void);
//--------------------------------------------------------------------------------------------------------------
/* Key Configs Array */
const Key_pinConfig  KEY_CONFIGS[] = {
  {&VIO_KEY_1, ACTIVE_HIGH},      /* Key 1 */
  {&VIO_KEY_2, ACTIVE_LOW},       /* Key 2 */
};
const uint8_t KEY_LEN = LEN(KEY_CONFIGS);
Key keys[LEN(KEY_CONFIGS)];
//--------------------------------------------------------------------------------------------------------------
// key drivers 
Key_driver keyDriver = {
  .initPin      = key_initPin,
  .readPin      = key_readPin,
  .callbackSet  = key_callbacks_set,
  .timerInit    = key_timer_init,
};
//--------------------------------------------------------------------------------------------------------------
void key_initPin (const Key_pinConfig* config) {
  vio_init(config->VIO, true);
}
uint8_t key_readPin (const Key_pinConfig* config) {
  return LL_GPIO_IsInputPinSet(LL_VIO(config->VIO[0]));
}
void key_callbacks_set (void) {
  keys[0].callBack.onHold     = key_1_onHold;
  keys[1].callBack.onReleased = key_2_onReleased;
}
void key_timer_init (void) {
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
  LL_TIM_DisableCounter(TIM6);
  uint32_t tim6Clock = __LL_RCC_CALC_PCLK1_FREQ(SystemCoreClock, LL_RCC_GetAPB1Prescaler()) * (LL_RCC_GetAPB1Prescaler() == LL_RCC_APB1_DIV_1? 1 : 2);  
  LL_TIM_SetPrescaler(TIM6, __LL_TIM_CALC_PSC(tim6Clock, 100000));
  LL_TIM_SetAutoReload(TIM6, __LL_TIM_CALC_ARR(tim6Clock, LL_TIM_GetPrescaler(TIM6), 20));
  LL_TIM_EnableIT_UPDATE(TIM6);
  LL_TIM_ClearFlag_UPDATE(TIM6);
  NVIC_SetPriority(TIM6_DAC_IRQn, KEY_TIM_IRQ_PRIORITY);
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
  LL_TIM_EnableCounter(TIM6);
}
//--------------------------------------------------------------------------------------------------------------
/* Key Callbacks Implementation */
void key_1_onHold (void) {
}
void key_2_onReleased (void) {
}

void TIM6_DAC_IRQHandler (void) {
  LL_TIM_ClearFlag_UPDATE(TIM6);
  key_handle();
}


#warning "Export This Values"
//exported values
extern Key_driver keyDriver;
extern const uint8_t KEY_LEN;
extern Key keys[];
extern const Key_pinConfig  KEY_CONFIGS[];