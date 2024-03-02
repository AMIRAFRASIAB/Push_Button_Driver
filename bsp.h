
#ifndef __BSP_H_INCLUDED__
#define __BSP_H_INCLUDED__
#ifdef __cplusplus 
  extern "C"{
#endif  

#include "zal.h"

/* Public APIs */
bool vio_init (const vio_t* const PVIO, bool lock/*?*/);



/* IRQ PRIORITY MANAGER */
//-------------------------------------------------------------------------------------------
/* MOTOR */
#define TIM11_MOTOR_SPEED_CRUISE_IRQ_PRIORITY       8
#define TIM3_MOTOR_PID                              6
/* NRF */   
#define NRF_EXTI_IRQ_PRIORITY                       5
/* OPTO Counter */
#define OPTO_COUNTER_IRQ_PRIORITY                   5
/* RS485 */
#define RS485_IRQ_PRIORITY                          8
/* RS232 TX_DMA */
#define RS232_TX_DMA_IRQ_PRIORITY                   8
#define RS232_UART_IRQ_PRIORITY                     8
/* KEY */
#define KEY_TIM_IRQ_PRIORITY                        7
/* LED */
#define LED_DMA_IRQ_PRIORITY                        8
/* FEEDBACK */
#define FEEDBACK_DMA_IRQ_PRIORITY                   7
#define FEEDBACK_ADC_IRQ_PRIORITY                   7
/* ENCODER */
#define ENC_TIM8_CC_IRQ_PRIORITY                    5
#define ENC_TIM8_UE_IRQ_PRIORITY                    4
/* BPI */
#define BPI_UART_DMA_TX_IRQ_PRIORITY                6
#define BPI_UART_RX_IRQ_PRIORITY                    6



/* TASK MANAGER */
//-------------------------------------------------------------------------------------------
/* MOTOR */
#define MOTOR_STACK_SIZE                          1024
#define MOTOR_TASK_PRIORITY                       3
/* PUBLIC */
#define PUBLIC_STACK_SIZE                         1024
#define PUBLIC_TASK_PRIORITY                      2
/* KERNEL */
#define KERNEL_STACK_SIZE                         1024
#define KERNEL_TASK_PRIORITY                      2
/* SCANNER */
#define SCANNER_STACK_SIZE                        512                   
#define SCANNER_TASK_PRIORITY                     4
/* API */
#define API_STACK_SIZE                            256
#define API_TASK_PRIORITY                         4
/* NRF */
#define NRF24L01_STACK_SIZE                       1024  
#define NRF24L01_TASK_PRIORITY                    4
/* LOG */
#define LOG_STACK_SIZE                            512
#define LOG_TASK_PRIORITY                         1
/* DEBUG */
#define DEBUG_STACK_SIZE                          256
#define DEBUG_TASK_PRIORITY                       1











extern const vio_t VIO_MAX232_TX;
extern const vio_t VIO_MAX232_RX;
/* RS485 */ 
extern const vio_t VIO_MAX485_DR;
extern const vio_t VIO_MAX485_TX;
extern const vio_t VIO_MAX485_RX;
/* nRF24L01+ */ 
extern const vio_t VIO_NRF_CE;   
extern const vio_t VIO_NRF_CSN;  
extern const vio_t VIO_NRF_IRQ;  
extern const vio_t VIO_NRF_CLK;  
extern const vio_t VIO_NRF_MISO; 
extern const vio_t VIO_NRF_MOSI; 
/* PWM LED */
extern const vio_t VIO_PWM_LED;  
/* OPTO  */
extern const vio_t VIO_OPTO;
/* PUSH BUTTON */
extern const vio_t VIO_PUSH_BT;  
/* ALPHA SW */
extern const vio_t VIO_ALPHA_SW;
/* BPI */
extern const vio_t VIO_BPI_TX;
extern const vio_t VIO_BPI_RX;
/* XGCU */
extern const vio_t VIO_XGCU_TRG; 
/* FEEDBACK */
extern const vio_t VIO_FB_BAT;   
extern const vio_t VIO_FB_ADJ;
extern const vio_t VIO_FB_MTR;
/* MOTOR */
extern const vio_t VIO_MOTOR_DIR;
extern const vio_t VIO_MOTOR_PWM;
extern const vio_t VIO_MOTOR_SLP;
extern const vio_t VIO_MOTOR_FLT;
extern const vio_t VIO_MOTOR_DAC;
/* ENC */
extern const vio_t VIO_ENC_CH1;  
extern const vio_t VIO_ENC_CH2;  
/* POWER */
extern const vio_t VIO_PWR_ADJ;   
extern const vio_t VIO_PWR_5;    
extern const vio_t VIO_PWR_3V3;

  
#ifdef __cplusplus 
  };
#endif  

#endif //__BSP_H_INCLUDED__