#include <stdio.h>
#include <stdlib.h>
#include "xparameters.h"		// 參數集.
#include "xgpio.h"	// 簡化PS對PL的GPIO操作的函數庫.

// 延遲用.
void delay(int dly)
{
    int i, j;
    for (i = 0; i < dly; i++) {
    	for (j = 0; j < 0xffff; j++) {
    		;
        }
    }
}

// 主程式.
int main()
{
    XGpio LED_XGpio;		// 宣告一個GPIO用的結構

    XGpio_Initialize(&LED_XGpio, XPAR_AXI_GPIO_0_DEVICE_ID);	// 初始化LED_XGpio.
    XGpio_SetDataDirection(&LED_XGpio, 1, 0);		// 設置通道.
    int LED_num[4] = {0b00000011, 0b00001100, 0b00110000, 0b11000000};
    printf("Start!!!");
    int i = 0;
    while(1) {
    	printf("LED_num = 0x%x\n", LED_num[i]);

    	XGpio_DiscreteWrite(&LED_XGpio, 1, LED_num[i]);

    	i = i + 1;

        if (i >= 4) {
            i = 0;
        }
    	delay(1000);
    }

    return 0;
}





