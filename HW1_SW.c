#include "xparameters.h"
#include "xil_io.h"
#include "xil_printf.h"

#define THRESHOLD_REG_ADDR 0x43C00000  // 根據 block design 自訂 base addr

int main() {
    u32 threshold = 200; // 設定 8-bit 計數閾值（計數到 200 就重設）

    xil_printf("設定 threshold = %d\r\n", threshold);

    // 將 threshold 寫入 AXI 寄存器
    Xil_Out32(THRESHOLD_REG_ADDR, threshold);

    while (1) {
        // 可加入延遲或顯示文字（非必要）
    }

    return 0;
}
