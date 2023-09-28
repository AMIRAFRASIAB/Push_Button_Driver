//in the name of GOD

/* In The Name Of GOD */

/**
 * @info  if You Need ActiveHigh Keys too, just Enable This Flag
 */
#define ACTIVE_HIGH_KEYS_ENABLE     0

#ifndef __KEY_H_INCLUDED_
#define __KEY_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "gpio.h"
#include <stdio.h>

#define LEN(x)  (sizeof(x) / sizeof(*x))

typedef void (*opFn) (void);
typedef union {
    struct {
    opFn    onHold;
    opFn    onReleased;
    opFn    onPressed;
    opFn    onNone;
    };
    struct {
        opFn    fn[4];
    };
} CallBack;
//------------------------- KEYState : ----------------------------------
typedef enum {
    onHold        = 0x00,
    onReleased    = 0x01,
    onPressed     = 0x02,
    onNone        = 0x03,
} KeyState;
//---------------------------------------------------------------------------
#if ACTIVE_HIGH_KEYS_ENABLE != 0
typedef enum {
    ACTIVE_LOW   = 0x00,
    ACTIVE_HIGH  = 0x01,
} ActiveState_typeDef;
#endif // ACTIVE_HIGH_KEYS_ENABLE
//----------------------- Key_pinConfig : -----------------------------------
typedef struct {
    GPIO_TypeDef*                   GPIO;
    const uint32_t                  pinNumber;

    #if (ACTIVE_HIGH_KEYS_ENABLE == 1)
    const  ActiveState_typeDef      active_state;
    #endif // ACTIVE_HIGH_KEYS_ENABLE
} Key_pinConfig;
//---------------------------- Key : -----------------------------------------
typedef struct {
    CallBack                callBack;
    const Key_pinConfig*    config;
    KeyState                state;
} Key;
//------------------------    Drivers : -------------------------------------
typedef void    (*Key_initPinFn) (const Key_pinConfig*);
typedef uint8_t (*Key_readPinFn) (const Key_pinConfig*);

typedef struct {
    Key_initPinFn   initPin;
    Key_readPinFn   readPin;
} Key_driver;
//---------------------------------------------------------------------------
void key_handle (Key* keys, uint8_t len);
void key_init (Key* keys,const Key_pinConfig* configs, uint8_t len, const Key_driver* driver);


//exported values
extern Key_driver keyDriver;
extern const uint8_t KEY_LEN;
extern Key keys[];
extern const Key_pinConfig  KEY_CONFIGS[];
extern void key_callbacks_set (void);

#ifdef __cplusplus
};
#endif

#endif // AMIR_KEY_H