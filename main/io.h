/*
 * io.h
 *
 *  Created on: 12 paź 2025
 *      Author: majorBien
 */
#ifndef IO_H
#define IO_H

#include "esp_err.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==============================
// GPIO definitions for LEDs
// ==============================
#ifndef LED1_GPIO
#define LED1_GPIO   GPIO_NUM_21   // Built-in LED on some ESP32 boards
#endif

#ifndef LED2_GPIO
#define LED2_GPIO   GPIO_NUM_19   // Example external LED pin
#endif

// ==============================
// LED logical states
// ==============================
typedef enum {
    LED_OFF = 0,
    LED_ON  = 1
} led_state_t;

// ==============================
// Function declarations
// ==============================

/**
 * @brief Initialize GPIOs used for LEDs.
 *
 * Sets LED1_GPIO and LED2_GPIO as outputs and turns them off.
 */
void io_init(void);

/**
 * @brief Set LED state (ON/OFF).
 *
 * @param led_id LED index (1 or 2)
 * @param state LED_ON or LED_OFF
 * @return ESP_OK if success, ESP_ERR_INVALID_ARG on invalid LED ID
 */
esp_err_t io_led_set(int led_id, led_state_t state);

/**
 * @brief Toggle LED state.
 *
 * @param led_id LED index (1 or 2)
 * @return ESP_OK if success, ESP_ERR_INVALID_ARG otherwise
 */
esp_err_t io_led_toggle(int led_id);

/**
 * @brief Get current LED state.
 *
 * @param led_id LED index (1 or 2)
 * @return LED_ON / LED_OFF, or -1 if invalid ID
 */
int io_led_get_state(int led_id);

#ifdef __cplusplus
}
#endif

#endif // IO_H
