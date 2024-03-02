
#include "bsp.h"
#include "zal.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"

/*             NAME       = { PORT      PIN       MODE              AF      SPEED           PULL        OUTTYPE }; */
/*-----------------------------------------------------------------------------------------------------------------*/
/* RS232 */ 
const vio_t VIO_MAX232_TX = { PORT(B)   PIN(6)    MODE(ALTERNATE)   AF(7)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MAX232_RX = { PORT(B)   PIN(7)    MODE(ALTERNATE)   AF(7)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
/* RS485 */ 
const vio_t VIO_MAX485_DR = { PORT(B)   PIN(0)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MAX485_TX = { PORT(A)   PIN(2)    MODE(ALTERNATE)   AF(7)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MAX485_RX = { PORT(A)   PIN(3)    MODE(ALTERNATE)   AF(7)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
/* nRF24L01+ */ 
const vio_t VIO_NRF_CE    = { PORT(D)   PIN(2)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_NRF_CSN   = { PORT(C)   PIN(12)   MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_NRF_IRQ   = { PORT(C)   PIN(11)   MODE(INPUT)       NO      SPEED(LOW)      PULL(UP)    TYPE(PUSHPULL)  };
const vio_t VIO_NRF_CLK   = { PORT(B)   PIN(3)    MODE(ALTERNATE)   AF(5)   SPEED(HIGH)     PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_NRF_MISO  = { PORT(B)   PIN(4)    MODE(ALTERNATE)   AF(5)   SPEED(HIGH)     PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_NRF_MOSI  = { PORT(B)   PIN(5)    MODE(ALTERNATE)   AF(5)   SPEED(HIGH)     PULL(NO)    TYPE(PUSHPULL)  };
/* PWM LED */
const vio_t VIO_PWM_LED   = { PORT(B)   PIN(9)    MODE(ALTERNATE)   AF(2)   SPEED(MEDIUM)   PULL(NO)    TYPE(PUSHPULL)  };
/* OPTO  */
const vio_t VIO_OPTO      = { PORT(B)   PIN(8)    MODE(INPUT)       NO      SPEED(LOW)      PULL(UP)    TYPE(PUSHPULL)  };
/* PUSH BUTTON */
const vio_t VIO_PUSH_BT   = { PORT(A)   PIN(0)    MODE(INPUT)       NO      SPEED(LOW)      PULL(UP)    TYPE(PUSHPULL)  };
/* ALPHA */
const vio_t VIO_ALPHA_SW  = { PORT(C)   PIN(2)    MODE(INPUT)       NO      SPEED(LOW)      PULL(UP)    TYPE(PUSHPULL)  };
/* BPI */
const vio_t VIO_BPI_TX    = { PORT(B)   PIN(10)   MODE(ALTERNATE)   AF(7)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_BPI_RX    = { PORT(B)   PIN(11)   MODE(ALTERNATE)   AF(7)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
/* XGCU */
const vio_t VIO_XGCU_TRG  = { PORT(A)   PIN(1)    MODE(ALTERNATE)   AF(2)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
/* FEEDBACK */
const vio_t VIO_FB_BAT    = { PORT(C)   PIN(0)    MODE(ANALOG)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_FB_ADJ    = { PORT(C)   PIN(1)    MODE(ANALOG)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_FB_MTR    = { PORT(B)   PIN(1)    MODE(ANALOG)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
/* MOTOR */
const vio_t VIO_MOTOR_DIR = { PORT(A)   PIN(9)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MOTOR_PWM = { PORT(A)   PIN(8)    MODE(ALTERNATE)   AF(1)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MOTOR_SLP = { PORT(C)   PIN(9)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MOTOR_FLT = { PORT(B)   PIN(12)   MODE(ALTERNATE)   AF(1)   SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_MOTOR_DAC = { PORT(A)   PIN(4)    MODE(ANALOG)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
/* ENC */
const vio_t VIO_ENC_CH1   = { PORT(C)   PIN(6)    MODE(ALTERNATE)   AF(3)   SPEED(LOW)      PULL(UP)    TYPE(PUSHPULL)  };
const vio_t VIO_ENC_CH2   = { PORT(C)   PIN(7)    MODE(ALTERNATE)   AF(3)   SPEED(LOW)      PULL(UP)    TYPE(PUSHPULL)  };
/* POWER */
const vio_t VIO_PWR_5     = { PORT(A)   PIN(5)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_PWR_ADJ   = { PORT(A)   PIN(6)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };
const vio_t VIO_PWR_3V3   = { PORT(A)   PIN(7)    MODE(OUTPUT)      NO      SPEED(LOW)      PULL(NO)    TYPE(PUSHPULL)  };

//------------------------------------------------------------------------------------------------------------------------
/* Static APIs */
static void __vio_clockEnable (const vio_t* const PVIO) {
  switch ((uintptr_t)(PVIO->port)) {
    case (uintptr_t)GPIOA:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
      break;
    case (uintptr_t)GPIOB:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
      break;
    case (uintptr_t)GPIOC:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
      break;
    case (uintptr_t)GPIOD:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
      break;
    case (uintptr_t)GPIOE:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
      break;
    case (uintptr_t)GPIOF:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
      break;
    case (uintptr_t)GPIOG:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
      break;
    case (uintptr_t)GPIOH:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
      break;
    case (uintptr_t)GPIOI:
      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
      break;
  };
  __DSB();
}
//------------------------------------------------------------------------------------------------------
/* Public APIs */
bool vio_init (const vio_t* const PVIO, bool lock/*?*/) {
  __vio_clockEnable(PVIO);
  bool status = true;
  /* Mode */
  LL_GPIO_SetPinMode(LL_VIO((*PVIO)), PVIO->mode);
  __DSB();
  status = status && LL_GPIO_GetPinMode(LL_VIO((*PVIO))) == PVIO->mode;
  /* AF */
  if (PVIO->pin < LL_GPIO_PIN_8) {
    LL_GPIO_SetAFPin_0_7(LL_VIO((*PVIO)), PVIO->af);
    __DSB();
    status = status && LL_GPIO_GetAFPin_0_7(LL_VIO((*PVIO))) == PVIO->af;
  }
  else {
    LL_GPIO_SetAFPin_8_15(LL_VIO((*PVIO)), PVIO->af);
    __DSB();
    status = status && LL_GPIO_GetAFPin_8_15(LL_VIO((*PVIO))) == PVIO->af;
  }
  /* Pull */
  LL_GPIO_SetPinPull(LL_VIO((*PVIO)), PVIO->pull);
  __DSB();
  status = status && LL_GPIO_GetPinPull(LL_VIO((*PVIO))) == PVIO->pull;
  /* Speed */
  LL_GPIO_SetPinSpeed(LL_VIO((*PVIO)), PVIO->speed);
  __DSB();
  status = status && LL_GPIO_GetPinSpeed(LL_VIO((*PVIO))) == PVIO->speed;
  /* Output Type */
  LL_GPIO_SetPinOutputType(LL_VIO((*PVIO)), PVIO->outType);
  __DSB();
  status = status && LL_GPIO_GetPinOutputType(LL_VIO((*PVIO))) == PVIO->outType;
  /* Lock */
  if (lock == true) {
    LL_GPIO_LockPin(LL_VIO((*PVIO)));
    __DSB();
    status = status && LL_GPIO_IsPinLocked(LL_VIO((*PVIO)));
  }
  return status;
}
//------------------------------------------------------------------------------------------------------
