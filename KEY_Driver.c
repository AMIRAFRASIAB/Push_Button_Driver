/**
 * @info This File is a Driver For STM32 and 5 PushBottons
 */

#include "KEY.h"
#include "stdbool.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_gpio.h"


void    key_initPin (const Key_pinConfig* config);
uint8_t key_readPin (const Key_pinConfig* config);
void    key_callbacks_set (void);
//--------------------------------------------------
// key callbacks
void key_1_onPressed (void);
void key_2_onPressed (void);
void key_3_onPressed (void);
void key_4_onPressed (void);
void key_5_onPressed (void);
//--------------------------------------------------
static KeyValue key_value = KeyValue_none;
//--------------------------------------------------
const Key_pinConfig  KEY_CONFIGS[] = {
  {GPIOA, LL_GPIO_PIN_0, ACTIVE_HIGH},
  {GPIOB, LL_GPIO_PIN_4, ACTIVE_LOW },
  {GPIOB, LL_GPIO_PIN_5, ACTIVE_LOW },
  {GPIOB, LL_GPIO_PIN_6, ACTIVE_LOW },
  {GPIOB, LL_GPIO_PIN_7, ACTIVE_LOW },
};
const uint8_t KEY_LEN = LEN(KEY_CONFIGS);
Key keys[LEN(KEY_CONFIGS)];
//--------------------------------------------------
// key drivers 
Key_driver keyDriver = {
  .initPin  = key_initPin,
  .readPin  = key_readPin,
};
//--------------------------------------------------
void key_initPin (const Key_pinConfig* config) {
  static bool first_call = true;
  if (first_call == true) {
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    first_call = false;
  }
  LL_GPIO_SetPinMode(config->GPIO, config->pinNumber, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinPull(config->GPIO, config->pinNumber, LL_GPIO_PULL_NO);
  LL_GPIO_LockPin(config->GPIO, config->pinNumber);
}

uint8_t key_readPin (const Key_pinConfig* config) {
  return LL_GPIO_IsInputPinSet(config->GPIO, config->pinNumber);
}
//--------------------------------------------------
void key_callbacks_set (void) {
  keys[0].callBack.onPressed    = key_1_onPressed;
  keys[1].callBack.onPressed    = key_2_onPressed;
  keys[2].callBack.onPressed    = key_3_onPressed;
  keys[3].callBack.onPressed    = key_4_onPressed;
  keys[4].callBack.onPressed    = key_5_onPressed;
}
//--------------------------------------------------
void key_1_onPressed (void) {
  key_value = KeyValue_pwr;
}
void key_2_onPressed (void) {
  key_value = KeyValue_back;
}
void key_3_onPressed (void) {
  key_value = KeyValue_enter;
}
void key_4_onPressed (void) {
  key_value = KeyValue_up;
}
void key_5_onPressed (void) {
  key_value = KeyValue_down;
}
//--------------------------------------------------
void key_reset (void) {
  key_value = KeyValue_none;
}
KeyValue key_get (void) {
  return key_value;
}