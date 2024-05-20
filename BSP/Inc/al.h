
#ifndef __ZAL_H_INCLUDED__
#define __ZAL_H_INCLUDED__

#include "stm32f4xx.h"
#include "core_cm4.h"
#include <stdbool.h>
#include <stdint.h>



#define KHz     * 1000
#define MHz     * 1000000

#define AWAIT_TILL(cond)                                                       \
  while (!(cond))                                                              \
  vTaskDelay(100)
#define AWAIT_WHILE(cond)                                                      \
  while (cond)                                                                 \
  vTaskDelay(100)
#define AWAIT_NBIT(addr, field)                                                \
  ;                                                                            \
  while (((addr) & (field)) == (field)) {                                      \
    vTaskDelay(100);                                                           \
  }
  
#define RMW(ptr, set, reset) RMW_(&(ptr), (set), (reset))
#define len(arr) (sizeof((arr)) / sizeof((arr)[0]))
#define foreach(i, arr) for (unsigned int i = 0; i<len(arr); i++)
#define repeat(count) for (unsigned int i = 0; i < (count); i++)

#define AssertFail(cond, fail)                                                 \
  if (!(cond))                                                                 \
  goto fail
#define try bool __HadError = false;
#define catch(x)                                                               \
  ExitJmp:                                                                     \
  if (__HadError)
#define throw(x)                                                               \
  {                                                                            \
    __HadError = true;                                                         \
    goto ExitJmp;                                                              \
  }

static inline void RMW_(volatile void *ptr, uint32_t field, uint32_t mask) {
  (*((uint32_t *)ptr)) = ((*((uint32_t *)ptr)) & (~mask)) | field;
}
	
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

typedef unsigned int uint;
	
	
#define MaxOf(v1,v2) (v1)>(v2)?(v1):(v2)	
#define MinOf(v1,v2) (v1)<(v2)?(v1):(v2)	
	
#define CheckBit(bit, ptr) __CheckBit((uint32_t)bit, (uint32_t)ptr)

static inline bool __CheckBit(uint32_t bit, uint32_t ptr) {
  if (bit & ptr)
    return true;
  else
    return false;
}

static inline void clear_buf(void *src, uint8_t len) {
  uint8_t *ptr = src;
  for (uint8_t i = 0; i < len; i++) {
    ptr[i] = 0;
  }
}


typedef struct {
  GPIO_TypeDef*  port;
  uint32_t       pin;
  uint32_t       mode;
  uint32_t       af;
  uint32_t       speed;
  uint32_t       pull;
  uint32_t       outType;
} vio_t;

#define  NO            LL_GPIO_AF_0,
#define  PIN(pin)      LL_GPIO_PIN_##pin,
#define  PORT(port)    GPIO##port,
#define  AF(af)        LL_GPIO_AF_##af,
#define  MODE(mode)    LL_GPIO_MODE_##mode,
#define  SPEED(speed)  LL_GPIO_SPEED_FREQ_##speed,
#define  TYPE(type)    LL_GPIO_OUTPUT_##type,
#define  PULL(pull)    LL_GPIO_PULL_##pull,
#define  LL_VIO(vio)   vio.port, vio.pin


#define  InRange(val, Min, Max) (((val) > (Min)) && ((val) < (Max)))


#endif //__ZAL_H_INCLUDED__






