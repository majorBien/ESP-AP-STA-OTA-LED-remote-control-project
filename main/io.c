/*
 * io.c
 *
 *  Created on: 12 paź 2025
 *      Author: majorBien
 */

#include "io.h"
#include "esp_log.h"

static const char *TAG = "IO";

/* --- Local LED state tracking --- */
static led_state_t led_states[2] = { LED_OFF, LED_OFF };

void io_init(void)
{
    ESP_LOGI(TAG, "Initializing GPIOs for LEDs");

    gpio_reset_pin(LED1_GPIO);
    gpio_set_direction(LED1_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED1_GPIO, LED_OFF);

    gpio_reset_pin(LED2_GPIO);
    gpio_set_direction(LED2_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED2_GPIO, LED_OFF);
    
    gpio_reset_pin(LED3_GPIO);
    gpio_set_direction(LED3_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED3_GPIO, LED_OFF);
    
    gpio_reset_pin(LED4_GPIO);
    gpio_set_direction(LED4_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED4_GPIO, LED_OFF);

    led_states[0] = LED_OFF;
    led_states[1] = LED_OFF;
}


esp_err_t io_led_toggle(int led_id)
{
    gpio_num_t gpio;
    int index;

    switch (led_id) {
        case 1: gpio = LED1_GPIO; index = 0; break;
        case 2: gpio = LED2_GPIO; index = 1; break;
        case 3: gpio = LED3_GPIO; index = 2; break;
        case 4: gpio = LED4_GPIO; index = 3; break;
        default:
            ESP_LOGE(TAG, "Invalid LED ID: %d", led_id);
            return ESP_ERR_INVALID_ARG;
    }

    led_states[index] = (led_states[index] == LED_ON) ? LED_OFF : LED_ON;
    gpio_set_level(gpio, (int)led_states[index]);

    ESP_LOGI(TAG, "LED%d toggled to %s", led_id, led_states[index] == LED_ON ? "ON" : "OFF");
    return ESP_OK;
}

int io_led_get_state(int led_id)
{
    int index;

    switch (led_id) {
        case 1: index = 0; break;
        case 2: index = 1; break;
        case 3: index = 2; break;
        case 4: index = 3; break;
        default:
            ESP_LOGE(TAG, "Invalid LED ID: %d", led_id);
            return -1;
    }

    return (int)led_states[index];
}
