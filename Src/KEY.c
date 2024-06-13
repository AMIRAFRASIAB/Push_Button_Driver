
/* In The Name of GOD */
#include "KEY.h"
//---------------------------------------------------------------------------
static const Key_driver* __DRIVER = NULL;
//---------------------------------------------------------------------------
bool key_init (Key* keys,const Key_pinConfig* CONFIGS, uint8_t len, const Key_driver* DRIVER){
  __DRIVER = DRIVER;
  if (DRIVER == NULL || keys == NULL || CONFIGS == NULL || len == 0) {
    return false;
  }
  while (len-- > 0) {
    __DRIVER->initPin(CONFIGS);
    keys->config = CONFIGS;
    keys->state = onNone;
    keys->callBack.fn[onHold]           = NULL;
    keys->callBack.fn[onReleased]       = NULL;
    keys->callBack.fn[onPressed]        = NULL;
    keys->callBack.fn[onNone]           = NULL;
    keys++;
    CONFIGS++;
  }
  __DRIVER->callbackSet();
  __DRIVER->timerInit();
  return true;
}
//---------------------------------------------------------------------------
void key_handle (Key* keys, uint8_t len){
  uint8_t pin_value;
  while (len-- > 0) {
    pin_value = __DRIVER->readPin(keys->config);
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
