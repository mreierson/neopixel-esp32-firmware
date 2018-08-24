#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

extern "C" {
    #include "mqtt.h"
}
#include "mpack.h"

#include "EffectManager.h"

#define PIN0 5

EffectManager effectManager(PIN0);
mqtt_settings settings;

SemaphoreHandle_t xSemaphore;
TaskHandle_t taskHandle;

uint32_t stepCounter = 0;
double timeCounter;

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}

void vStepTask(void *pvParameters)
{
    while (true) {
        effectManager.step();
    }
}

void connected_cb(void *self, void *params)
{
    mqtt_client *client = (mqtt_client *) self;
    mqtt_subscribe(client, "neopixel", 0);
}

void disconnected_cb(void *self, void *params)
{}

void reconnect_cb(void *self, void *params)
{}

void subscribe_cb(void *self, void *params)
{}

void publish_cb(void *self, void *params)
{}

void data_cb(void *self, void *params)
{
    mqtt_client *client = (mqtt_client *) self;
    mqtt_event_data_t *event_data = (mqtt_event_data_t *) params;


    if (event_data->data_length > 0) {

        printf("Received %d bytes\n", event_data->data_length);

        uint8_t strand = -1;
        uint16_t pixels = -1;
        uint8_t func = -1;
        uint8_t params[15];
        uint32_t numParams = 0;

        mpack_reader_t reader;
        mpack_reader_init_data(&reader, event_data->data, event_data->data_length);

        uint32_t size = mpack_expect_map(&reader);

        for (uint32_t i = 0; i < size; ++i) {

            int key = mpack_expect_int(&reader);

            if (key == 0x01) {

                strand = mpack_expect_int(&reader);

            } else if (key == 0x02) {

                pixels = mpack_expect_int(&reader);

            } else if (key == 0x03) {

                func = mpack_expect_int(&reader);

            } else if (key == 0x04) {

                numParams = mpack_expect_array(&reader);
                for (uint32_t j = 0; j < size; ++j) {
                    params[j] = mpack_expect_int(&reader);
                }
                mpack_done_array(&reader);

            } else {

                printf("Unknown key = %d\n", key);

            }

        }

        mpack_done_map(&reader);

        printf("strand = %d, pixels = %d, function = %d, param0 = %d, param1 = %d, param2 = %d, param3 = %d\n",
               strand, pixels, func, params[0], params[1], params[2], params[3]);

        effectManager.setNumPixels(pixels);
        effectManager.setEffect(func, numParams, params);
    }
}




static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
    case SYSTEM_EVENT_STA_START:
        ESP_ERROR_CHECK(esp_wifi_connect());
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
        mqtt_start(&settings);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        mqtt_destroy();
        ESP_ERROR_CHECK(esp_wifi_connect());
        break;

    default:
        break;
    }
    return ESP_OK;
}

extern "C" {

void app_main(void)
{
    xSemaphore = xSemaphoreCreateMutex();

    strcpy(settings.host, "HOST");
    settings.port = 1883;
    strcpy(settings.client_id, "neo32");
    settings.clean_session = 0;
    settings.keepalive = 120;
    settings.connected_cb = connected_cb;
    settings.disconnected_cb = disconnected_cb;
    settings.reconnect_cb = reconnect_cb;
    settings.subscribe_cb = subscribe_cb;
    settings.publish_cb = publish_cb;
    settings.data_cb = data_cb;

    wifi_config_t sta_config;
    strcpy((char*) sta_config.sta.ssid, "SSID");
    strcpy((char*) sta_config.sta.password, "PASSWORD");
    sta_config.sta.bssid_set = false;

    nvs_flash_init();
    tcpip_adapter_init();

    ESP_ERROR_CHECK( esp_event_loop_init(wifi_event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );

    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_wifi_connect() );

    printf("neopixel-esp32 WROOM WROOM WROOM!\n");

    while (true) {
        effectManager.step();
    }
}

}
