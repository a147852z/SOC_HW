# 使用 FPGA GPIO 產生中斷之實作

## 專案簡介

本專案說明如何在 FPGA（以 Xilinx Zynq 為例）環境下，透過 AXI GPIO 產生中斷，並使用 SDK (C 語言) 進行對應的中斷服務與 LED 控制。當按鈕被觸發時，將會進入中斷服務程序 (ISR)，點亮 LED 並進行閃爍效果，驗證硬體與軟體整合。

## 目標與前瞻性應用

本設計可作為嵌入式中斷系統、人機互動介面、或自動化設備控制的基礎。未來可擴充為：

* 多按鈕/多輸入感測的事件處理
* 以 GPIO 中斷驅動複雜任務（如即時訊號採集）
* 連接外部 IOT 設備實現遠端控制

## 硬體需求

* FPGA 開發板（如 Zynq-7000/EGX）
* AXI GPIO IP（需於 Vivado 設計整合）
* 一顆按鈕作為輸入
* 多顆 LED 作為輸出（示範用 8 顆）

## 使用說明

### 硬體配置

* 將按鈕與 LED 連接至 AXI GPIO 相對應的管腳

### 軟體編譯與下載

* 編譯無誤後下載至開發板。
* 開啟 UART/Serial 終端，觀察 `xil_printf` 的訊息輸出。

### 功能驗證

* 按下按鈕時，可觀察到終端顯示 `Button Interrupt Triggered!`。
* LED 閃爍十次後熄滅。

## 主要流程說明

* **系統初始化**：初始化 GPIO 與中斷控制器，設定輸入/輸出方向
* **註冊中斷與啟用**：連結 ISR 與中斷號，啟用全域中斷
* **中斷處理**：進入中斷服務程序，記錄旗標並清除中斷，在主迴圈中依旗標執行 LED 控制

## 前瞻性擴充建議

* **多通道支援**：擴充更多 GPIO 輸入/輸出，實現複雜控制。
* **除彈跳機制**：軟體端實作按鈕防彈跳（debounce）。
* **中斷優先序**：結合多來源中斷的管理，支援即時系統應用。
* **FPGA + AI/邊緣運算**：結合影像感測/機器學習判斷，實現智能反應。


## demo影片連結 https://youtu.be/vo342awh1ts
* 拉一下代表中斷一次






# IRQ numbers
![image](https://github.com/user-attachments/assets/bb6d2be1-e7c2-4847-a724-83d0c74f4155)

# IRQ ID Port
![image](https://github.com/user-attachments/assets/89d49c4d-5e03-4971-9e13-86b11de1b415)

# Pending Register
![image](https://github.com/user-attachments/assets/59bfd201-94d3-43e1-8fc6-8015beeed611)

# Disable / Mask Register
![image](https://github.com/user-attachments/assets/f30f481d-385b-42e6-8080-6706c9990d46)
