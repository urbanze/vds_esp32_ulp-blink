#include <C:/msys32/ESP32/ESP32/components/arduino/cores/esp32/Arduino.h>
#include <C:/msys32/ESP32/esp-idf/components/driver/include/driver/rtc_io.h>
#include <C:/msys32/ESP32/esp-idf/components/ulp/ulp.c>
#include <C:/msys32/ESP32/ESP32/build/main/ulp_main.h>
//Pode ser preciso arrumar os diretorios das bibliotecas

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[] asm("_binary_ulp_main_bin_end");

void ulp();

extern "C" void app_main()
{
	initArduino();//Inicia algumas configuracoes do Arduino Core, se voce nao usa Arduino component, apague essa linha
	ulp();//carrega e inicia o ULP

	ESP.deepSleep(1800000000);//entra em deep sleep
}

void ulp()
{
	rtc_gpio_init(GPIO_NUM_2);//inicia o GPIO2 no RTC DOMAIN
	rtc_gpio_set_direction(GPIO_NUM_2, RTC_GPIO_MODE_OUTPUT_ONLY);//Define o GPIO2 como saida

	ulp_load_binary(0, ulp_main_bin_start, (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));//Carrega o binario do codigo assembly na memoria
	ulp_run((&ulp_main - RTC_SLOW_MEM) / sizeof(uint32_t));//Inicia o ULP
}
