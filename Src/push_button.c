
#include "push_button.h"
#include "push_button_config.h"
#include "push_button_driver.h"

#ifndef NULL
  #define NULL   ((void*)0)
#endif    

//-----------------------------------------------------------------
bool pb_init (PushButton_s* pb, uint16_t len) {
  if (pb == NULL || len == 0) {
    return false;
  }
  while (len-- > 0) {
    pb->state                    = onNone;
    pb->callback.fn[onHold]      = NULL;
    pb->callback.fn[onReleased]  = NULL;
    pb->callback.fn[onPressed]   = NULL;
    pb->callback.fn[onNone]      = NULL;
    pb++;
  }
  return true;
}
//-----------------------------------------------------------------
void pb_handle (PushButton_s* pb, uint16_t len) {
  if (pb == NULL || len == 0) {
    return;
  }
  uint8_t pin_value;
  while (len-- > 0) {
    pin_value = pb_hw_gpio_read_pin(pb->gpio, pb->pin);
    if (pb->active == PB_Active_High) {
      pin_value = !pin_value;
    }
    pb->state = ((pb->state << 1) | pin_value) & 0x03;
    if (pb->callback.fn[pb->state] != NULL) {
      pb->callback.fn[pb->state]();
    }
    pb++;
  }
}
//-----------------------------------------------------------------
bool pb_callback_register (PushButton_s* pb, PB_State_e state, void (*callback) (void)) {
  if (pb == NULL || state >= 4) {
    return false;
  }
  pb->callback.fn[state] = callback;
  return true;
}
//-----------------------------------------------------------------
