# Push Button Driver for STM32 (Bare-Metal)

A portable and lightweight push button driver written in C for STM32 microcontrollers using LL drivers. This driver handles GPIO input, debouncing using a hardware timer, and callback execution in interrupt context.

---

## ✅ Features

- Bare-metal STM32 support
- Configurable for active-high or active-low buttons
- Debouncing with hardware timer
- Supports callback functions (executed in interrupt context)

---

## 🚀 Quick Integration Guide

### 1. Clone the Repository
```bash
git clone https://github.com/AMIRAFRASIAB/Push_Button_Driver.git
```

### 2. Add Source Files to Your Project
- Add all `.c` files from the `Src/` folder to your **compiler source path**.

### 3. Add Header Files
- Add the `Inc/` folder to your **include path**.

### 4. Copy Driver Folder
- Copy the entire driver folder to your project directory **outside of the Git repository**.

### 5. Modify Configuration
- Edit the copied config and driver files as needed for your board.

### 6. Add Driver Folder to Include Path
- Include the path to the copied driver in your project settings.

### 7. Include the Header
```c
#include "push_button.h"
```

### 8. Declare Global Push Button Array
Create and initialize your button objects:

```c
PushButton_s pb[4] = {
  [0] = {.gpio = GPIOA, .pin = LL_GPIO_PIN_0, .active = PB_Active_Low},
  [1] = {.gpio = GPIOB, .pin = LL_GPIO_PIN_1, .active = PB_Active_Low},
  [2] = {.gpio = GPIOC, .pin = LL_GPIO_PIN_2, .active = PB_Active_Low},
  [3] = {.gpio = GPIOD, .pin = LL_GPIO_PIN_3, .active = PB_Active_Low},
};
```

### 9. Configure Timer for Debouncing
- Set up a timer (e.g. TIM6) with a **50ms period**.
- In the timer ISR, call `pb_handle()`:

```c
void TIM6_IRQHandler(void) {
  pb_handle(pb, sizeof(pb) / sizeof(PushButton_s));
}
```

### 10. Register Callback Function

- Register a callback using `pb_callback_register()`.
- Keep callbacks **short** since they run in **interrupt context**.

Example:
```c
void system_shutdown_function(void) {
  xTaskNotifyFromISR(hTaskPower, 1UL << 0, eSetBit, NULL);
}
```

Main loop example:
```c
int main(void) {
  pb_init(pb, 4);
  pb_callback_register(&pb[3], onPressed, &system_shutdown_function);

  while (1) {
    // Main loop code
  }
}

## ⚠️ Notes
- Callbacks are executed in **handler mode**, so avoid long operations.


## 👤 Author

Developed by [AMIRAFRASIAB](https://github.com/AMIRAFRASIAB)
