/*
 * io.c
 *
 *  Created on: 12 paź 2025
 *      Author: majorBien
 */


//create functions to set LED on pin 15
#include "driver/gpio.h"
#include "io.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN GPIO_NUM_15

static bool state = false;

void gpio_init(void){
	gpio_config_t io_conf;
	//disable interrupt
	io_conf.intr_type = GPIO_INTR_DISABLE;
	//set as output mode
	io_conf.mode = GPIO_MODE_OUTPUT;
	//bit mask of the pins that you want to set,e.g.GPIO15
	io_conf.pin_bit_mask = (1ULL<<LED_PIN);
	//disable pull-down mode
	io_conf.pull_down_en = 0;
	//disable pull-up mode
	io_conf.pull_up_en = 0;
	//configure GPIO with the given settings
	gpio_config(&io_conf);
}

//create output control task
void output_control_task(void *pvParameter){
	while(1){
		if(state)
			gpio_set_level(LED_PIN, 1);
		else
			gpio_set_level(LED_PIN, 0);
	}
}

