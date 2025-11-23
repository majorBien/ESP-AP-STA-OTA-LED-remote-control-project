/*
 * wifi_sta.c
 *
 *  Created on: 25 paź 2025
 *      Author: majorBien
 */

#include "wifi_sta.h"
#include <string.h>   

extern nvs_network_data_t network_data;  

static const char *TAG = "WIFI_STA";

static EventGroupHandle_t s_wifi_event_group;
const int WIFI_CONNECTED_BIT = BIT0;

// Event handler
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG, "WiFi STA started, connecting...");
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "Disconnected from AP, retrying...");
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

// Initialize WiFi STA
esp_err_t wifi_sta_init(void)
{
    esp_err_t ret;

    // Load WiFi credentials
    ret = nvs_load_network_data(&network_data);
    if(ret != ESP_OK){
        ESP_LOGW(TAG, "No WiFi data found in NVS");
        return ret;
    }

    // Create default WiFi STA
    esp_netif_create_default_wifi_sta();

    // Initialize WiFi with default config
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ret = esp_wifi_init(&cfg);
    if(ret != ESP_OK) return ret;

    // Create event group
    s_wifi_event_group = xEventGroupCreate();

    // Register handlers
    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                        &wifi_event_handler, NULL, &instance_any_id);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                        &wifi_event_handler, NULL, &instance_got_ip);

    // Set WiFi mode STA
    ret = esp_wifi_set_mode(WIFI_MODE_STA);
    if(ret != ESP_OK) return ret;

    return ESP_OK;
}

// Connect to WiFi using network_data
esp_err_t wifi_sta_connect(void)
{
    wifi_config_t wifi_config = {0};
    strncpy((char*)wifi_config.sta.ssid, network_data.ssid, sizeof(wifi_config.sta.ssid)-1);
    strncpy((char*)wifi_config.sta.password, network_data.password, sizeof(wifi_config.sta.password)-1);

    ESP_LOGI(TAG, "Connecting to SSID: %s", wifi_config.sta.ssid);

    esp_err_t ret = esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    if(ret != ESP_OK) return ret;

    ret = esp_wifi_start();
    if(ret != ESP_OK) return ret;

    // Wait for connection
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT,
                                           pdFALSE,
                                           pdTRUE,
                                           pdMS_TO_TICKS(10000));
    if(bits & WIFI_CONNECTED_BIT){
        ESP_LOGI(TAG, "WiFi connected successfully");
        return ESP_OK;
    } else {
        ESP_LOGE(TAG, "Failed to connect within timeout");
        return ESP_FAIL;
    }
}
