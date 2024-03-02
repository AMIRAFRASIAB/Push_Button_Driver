
/* In The Name of GOD */
#include "KEY.h"
//---------------------------------------------------------------------------
static const Key_driver* __driver = NULL;
//---------------------------------------------------------------------------
void key_init (Key* keys,const Key_pinConfig* configs, uint8_t len, const Key_driver* driver){
  __driver = driver;
  while (len-- > 0) {
    __driver->initPin(configs);
    keys->config = configs;
    keys->state = onNone;
    keys->callBack.fn[onHold]           = NULL;
    keys->callBack.fn[onReleased]       = NULL;
    keys->callBack.fn[onPressed]        = NULL;
    keys->callBack.fn[onNone]           = NULL;
    keys++;
    configs++;
  }
}
//---------------------------------------------------------------------------
void key_handle (Key* keys, uint8_t len){
  uint8_t pin_value;
  while (len-- > 0) {
    pin_value = __driver->readPin(keys->config);
    #if ACTIVE_HIGH_KEYS_ENABLE != 0
    if (keys->config->active_state == ACTIVE_HIGH)
    {
        pin_value = !pin_value;
    }
    #endif // ACTIVE_HIGH_KEYS_ENABLE == 1
    keys->state = ((keys->state << 1) | pin_value) & 0x03;
    if (keys->callBack.fn[keys->state] != NULL)
    {
        keys->callBack.fn[keys->state]();
    }
    keys++;
  }
}
//---------------------------------------------------------------------------
