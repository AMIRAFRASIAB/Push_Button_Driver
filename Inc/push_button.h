
#ifndef __PUSH_BUTTON_H_INCLUDED__
#define __PUSH_BUTTON_H_INCLUDED__

#ifdef __cplusplus
  extern "C"{
#endif //__cplusplus  

#include <stdint.h>
#include <stdbool.h>
#include "push_button_config.h"


#include PB_TO_STRING(PB_CONCAT(PB_CONCAT(stm32, STM32_SERIES), xx_ll_gpio.h))
//-----------------------------------------------------------------
typedef union {
  struct {
    void (*onHold    ) (void);
    void (*onReleased) (void);
    void (*onPressed ) (void);
    void (*onNone    ) (void);
  };
  struct {
      void (*fn[4]   ) (void);
  };
} PB_Callback_s;
//-----------------------------------------------------------------
typedef enum {
  onHold        = 0x00,
  onReleased    = 0x01,
  onPressed     = 0x02,
  onNone        = 0x03,
} PB_State_e;
//-----------------------------------------------------------------
typedef enum {
  PB_Active_Low  = 0x00,
  PB_Active_High = 0x01,
} PB_ActiveType_e;
//-----------------------------------------------------------------
typedef struct {
  PB_Callback_s    callback;
  GPIO_TypeDef*    gpio;
  uint32_t         pin;
  PB_State_e       state;
  PB_ActiveType_e  active;
} PushButton_s;
//-----------------------------------------------------------------
bool pb_init (PushButton_s* pb, uint16_t len);
void pb_handle (PushButton_s* pb, uint16_t len);
bool pb_callback_register (PushButton_s* pb, PB_State_e state, void (*callback) (void));

  
#ifdef __cplusplus
  };
#endif //__cplusplus  
#endif //__PUSH_BUTTON_H_INCLUDED__