 # 🔐 ESP32-S3 Hardware Password Vault (Version 1.0)

A standalone, physical hardware security tool built using an **ESP32-S3** and a **ST7789 TFT Display**. This device acts as a secure offline credential manager, mimicking a physical USB/Bluetooth keyboard (HID) to automatically type complex usernames and passwords at the press of a button.

---

## 🎯 Project Overview

The goal of this project is to eliminate password reuse by outsourcing credential storage to a dedicated microcontroller. The ESP32-S3 handles the data logic and acts as a Bluetooth Human Interface Device (HID). The $240 \times 320$ TFT screen serves as a dynamic viewport, allowing the user to navigate a custom-built menu using just two physical buttons.

### Core Features:
* 🖥️ **Silky-Smooth UI:** Dynamic, flicker-free rendering of stored accounts.
* 🕹️ **Two-Button Navigation:** Dual-purpose button logic using timed hardware polling.
* ⌨️ **Automated HID Injection:** Emulates a standard keyboard to type out strings instantly across Windows, Mac, Linux, iOS, and Android.
* 🌐 **Wireless Connectivity:** Connects effortlessly over Bluetooth Low Energy (BLE).

---

##  Hardware Architecture & Pin Map

| Component | ESP32-S3 GPIO | Description |
| :--- | :--- | :--- |
| **TFT CS** | GPIO 13 | Chip Select |
| **TFT RST** | GPIO 10 | Reset |
| **TFT DC** | GPIO 9 | Data/Command |
| **TFT MOSI** | GPIO 11 | SPI Data |
| **TFT SCLK** | GPIO 12 | SPI Clock |
| **Button DOWN** | GPIO 4 | External Push-Button (Scroll Down / Select / Inject) |
| **Button UP** | GPIO 0 | Built-in BOOT Button (Scroll Up / Back to Menu) |

---

## 📈 Evolutionary Development Log (Subversions)

### 🔹 Subversion 1: Proof of Concept (`inject_password_1`)
* **Objective:** Establish a stable HID Bluetooth connection and auto-type a single hardcoded credential string using the onboard `BOOT` button.
* **Layout Scan-Code Glitch & Fix:** > **The Bug:** Characters like `@` inside strings were appearing as `"` on the computer. This happens because the BLE library defaults to a US layout, while the host computer expects a UK keyboard layout (where `Shift + 2` is `"` instead of `@`).
  >
  > **The Fix:** Implemented a compiler layout cheat. By escaping double quotes (`\"`) inside the C++ string array, the host operating system translates the scan-code back into a perfect literal `@`.

### 🔹 Subversion 2: The UI Engine (`simple_menu_select`)
* **Objective:** Render a scrollable list of multiple text entries without screen flicker.
* **Implementation:** Developed the `drawMenu()` function. Configured selective row rendering by passing text and background colors simultaneously (`tft.setTextColor(Text, Background)`). This eliminates global screen wipes (`tft.fillScreen`), yielding completely seamless selection transitions.
* **UX Bug Fix:** Resolved a persistent rendering overlay bug by introducing an explicit `tft.fillScreen(ST77XX_BLACK)` immediately upon the user releasing a confirmation hold loop.

### 🔹 Subversion 3: The Finite State Machine (`dynamic_select_1`)
* **Objective:** Expand the capability of a 2-button system to support entering sub-menus and backing out.
* **Implementation:** Introduced millisecond-accurate stopwatch loops (`millis()`). 
  * **Short Press (< 800ms):** Steps sequentially through the database array.
  * **Long Press (> 800ms):** Interrupts the UI loop, switches the application code state (`Mode = 1`), and opens an isolated account detail panel.
* **Data Migration:** Upgraded the simple text array (`const char* menu[]`) to an organized **Array of Structs**:
  ```c++
  struct VaultEntry {
    const char* siteName;
    const char* username;
    const char* password;
  };

To take this project to an industry-grade standard before entering Year 2, the following features are actively under development:
🔐 Cryptographic Storage Engine: Integrate an AES-256 block-cipher library (mbedtls). Passwords will sit encrypted in the ESP32's flash storage, protecting data against direct hardware extraction.
🟩 PIN-Code Gatekeeper: Implement a boot-up lock screen requiring a custom directional sequence code (e.g., Down $\rightarrow$ Down $\rightarrow$ Up $\rightarrow$ Down) to unlock the cryptographic keys.
📁 Dynamic Credential Scopes: Separate selections to inject either the Username only, Password only, or Full Auto-Form Fill (User + TAB + Pass + ENTER).🔌
Dual-Mode Connectivity (Wired HID): Add conditional logic allowing the device to drop BLE radios and transmit keystrokes entirely over native wired USB (USBHIDKeyboard.h) for compatibility with legacy systems.
