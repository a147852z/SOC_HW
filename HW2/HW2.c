

#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"

// 對應你在 system.h / xparameters.h 裡的設定
#define GPIO_DEVICE_ID      XPAR_AXI_GPIO_0_DEVICE_ID
#define INTC_DEVICE_ID      XPAR_SCUGIC_SINGLE_DEVICE_ID
#define GPIO_INTERRUPT_ID   XPAR_FABRIC_AXI_GPIO_0_IP2INTC_IRPT_INTR

#define BTN_CHANNEL         1  // channel 1 → 按鈕（輸入）
#define LED_CHANNEL         2  // channel 2 → LED（輸出）

XGpio Gpio;
XScuGic Intc;

volatile int interrupt_flag = 0;

// 中斷服務函數（ISR）
void GpioIsr(void *InstancePtr) {
    // 清除中斷旗標
    XGpio_InterruptClear(&Gpio, BTN_CHANNEL);

    // 記錄事件（也可直接點亮 LED）
    interrupt_flag = 1;

    xil_printf(">> Button Interrupt Triggered!\n");
}

int main() {
    int status;

    xil_printf(">>> Start GPIO Interrupt Test <<<\n");

    // 初始化 GPIO
    status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);
    if (status != XST_SUCCESS) {
        xil_printf("GPIO Init Failed\n");
        return XST_FAILURE;
    }

    // Channel 1 為輸入（按鈕）
    XGpio_SetDataDirection(&Gpio, BTN_CHANNEL, 0xFFFFFFFF);
    // Channel 2 為輸出（LED）
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x00000000);

    // 開啟中斷
    XGpio_InterruptEnable(&Gpio, BTN_CHANNEL);
    XGpio_InterruptGlobalEnable(&Gpio);

    // 初始化中斷控制器
    XScuGic_Config *IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
    XScuGic_CfgInitialize(&Intc, IntcConfig, IntcConfig->CpuBaseAddress);

    // 註冊中斷處理函式
    XScuGic_Connect(&Intc, GPIO_INTERRUPT_ID, (Xil_ExceptionHandler)GpioIsr, &Gpio);
    XScuGic_Enable(&Intc, GPIO_INTERRUPT_ID);

    // 啟用 CPU 端中斷
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 &Intc);
    Xil_ExceptionEnable();

    xil_printf("System initialized, waiting for button...\n");

    while (1) {
        if (interrupt_flag) {
            interrupt_flag = 0;

            // LED 全亮
            XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, 0xFF);
            xil_printf("LEDs ON\n");

            // 延遲後關閉 LED
            for (int i = 0; i < 10; ++i) {
                XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, 0xFF);   // ON
                usleep(100000);                                  // 0.1 s
                XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, 0x00);   // OFF
                usleep(100000);                                  // 0.1 s
            }
            xil_printf("LEDs OFF\n");
        }
    }
}
