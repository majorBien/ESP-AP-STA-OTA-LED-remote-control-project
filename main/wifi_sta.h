/*
 * wifi_sta.h
 *
 *  Created on: 25 paź 2025
 *      Author: lenovo
 */

#ifndef MAIN_WIFI_STA_H_
#define MAIN_WIFI_STA_H_


#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include "nvs_utils.h" 


// Initialize Wi-Fi as STA using stored NVS credentials
esp_err_t wifi_sta_init(void);



#endif /* MAIN_WIFI_STA_H_ */
