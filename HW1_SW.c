#include "xparameters.h"
#include "xil_io.h"
#include "xil_printf.h"

#define THRESHOLD_REG_ADDR 0x43C00000  // 假設 threshold_val 對應的 AXI 記憶體地址

int main() {
    u32 threshold = 100; // 設定 FPGA 計數器的閾值

    xil_printf("設定 threshold = %d...\r\n", threshold);

    // 寫入 AXI 寄存器
    Xil_Out32(THRESHOLD_REG_ADDR, threshold);

    while (1) {
        // 若有 count register 可讀取可加入以下（可選）
        // u32 current = Xil_In32(THRESHOLD_REG_ADDR + 4);
        // xil_printf("目前計數：%d\\n", current);
    }

    return 0;
}
