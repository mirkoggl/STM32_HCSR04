#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "STM32F4_HCSR04.h"
#include <math.h>

static void Delay(__IO uint32_t nTime);
uint32_t temp = 100;

void setup();
void loop();

int main(void) {
	setup();
	while(1){
		loop();
	}
}

void setup(){
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	STM32F4_HCSR04_Init();
}

void loop(){
	if(STM_EVAL_PBGetState(BUTTON_USER) != 0){
		printf("\nLOOP\n");
		int distance = STM32F4_HCSR04_getDistance();
		float res = (distance / 84000000) / 58;
		printf("Differenza: %d\n", distance);
		printf("Distanza: %.16f\n", res);
		Delay(250);
	}

}

void Delay(__IO uint32_t nTime){
  uint32_t x = nTime * 3600;

  while (x != 0)
	  x--;
}
