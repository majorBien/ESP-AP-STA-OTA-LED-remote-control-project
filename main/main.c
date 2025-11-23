/*
 * main.c
 *
 *  Created on: 28 sie 2024
 *      Author: majorBien
 */


#include "nvs_flash.h"
#include "wifi_app.h"
#include "freertos/task.h"
#include "io.h"
#include "nvs_utils.h"
#include "wifi_sta.h"


void app_main(void){
    // Initialize NVS
    esp_err_t ret = nvs_init_storage();
    ESP_ERROR_CHECK(ret);

    // Start tasks
    // Initialize the TCP stack
	ESP_ERROR_CHECK(esp_netif_init());
	wifi_app_start();
	io_init();
	//wifi_sta_init();

}

