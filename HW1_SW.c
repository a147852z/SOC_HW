#include "xparameters.h"
#include "xil_io.h"
#include "xil_printf.h"

#define COUNTER_BASE_ADDR 0x43C00000  // 根據 block design 記憶體映射設定

int main() {
    u32 threshold = 100; // 你要計數到的值

    xil_printf("Setting threshold to %d...\r\n", threshold);

    Xil_Out32(COUNTER_BASE_ADDR, threshold);  // 寫入 AXI-Lite threshold 寄存器

    while (1) {
        // 假設你也加入了讀回目前 count 值的 register，可加以下：
        // u32 count = Xil_In32(COUNTER_BASE_ADDR + 4);
        // xil_printf("Current Count: %d\\n", count);
    }

    return 0;
}
