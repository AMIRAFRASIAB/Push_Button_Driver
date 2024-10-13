

/* In The Name Of GOD */

/**
 * @info  if You Need ActiveHigh Keys too, just Enable This Flag
 */
#define ACTIVE_HIGH_KEYS_ENABLE     1

#ifndef __KEY_H_INCLUDED_
#define __KEY_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "bsp.h"



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
//------------------------- KEYState : --------------------------------------
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
//---------------------------------------------------------------------------
/* Configs */
//---------------------------------------------------------------------------
typedef struct {
    const vio_t*                    VIO;
    #if (ACTIVE_HIGH_KEYS_ENABLE == 1)
    const  ActiveState_typeDef      active_state;
    #endif // ACTIVE_HIGH_KEYS_ENABLE
} Key_pinConfig;
//---------------------------------------------------------------------------
/* Key */
//---------------------------------------------------------------------------
typedef struct {
    CallBack                callBack;
    const Key_pinConfig*    config;
    KeyState                state;
} Key;
//---------------------------------------------------------------------------
/* Drivers */
//---------------------------------------------------------------------------
typedef void    (*Key_initPinFn)      (const Key_pinConfig*);
typedef uint8_t (*Key_readPinFn)      (const Key_pinConfig*);
typedef void    (*key_callbackSetFn)  (void);
typedef void    (*key_timerInitFn)    (void);

typedef struct {
    Key_initPinFn       initPin;
    Key_readPinFn       readPin;
    key_callbackSetFn   callbackSet;
    key_timerInitFn     timerInit;
} Key_driver;
//---------------------------------------------------------------------------
void key_handle (void);
bool key_init (Key* keys, const Key_pinConfig* CONFIGS, uint8_t len, const Key_driver* DRIVER);




#ifdef __cplusplus
};
#endif

#endif // AMIR_KEY_H
