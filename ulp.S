#include "soc/soc_ulp.h"
#include "soc/rtc_io_reg.h"
#include "soc/sens_reg.h"
#include "soc/rtc_cntl_reg.h"


.bss//Variaveis sao declaradas dentro da secao .bss


.text//O codigo é feito dentro da secao .text

	.global main
	main://O codigo e iniciado aqui, equivale ao void setup()

		

	jump loop//Isso nao e necessario, mas foi colocado para organizacao
 
	loop:
		
		WRITE_RTC_REG(RTC_GPIO_OUT_W1TS_REG, RTC_GPIO_OUT_DATA_W1TS_S+12, 1, 1)//GPIO2 HIGH
		stage_rst
		1: stage_inc 1
		wait 32000
		jumps 1b, 125, lt//delay 500ms
		

		WRITE_RTC_REG(RTC_GPIO_OUT_W1TC_REG, RTC_GPIO_OUT_DATA_W1TC_S+12, 1, 1)//GPIO2 LOW
		stage_rst
		1: stage_inc 1
		wait 32000
		jumps 1b, 125, lt//delay 500ms

		
		jump loop//volta ao inicio do loop
