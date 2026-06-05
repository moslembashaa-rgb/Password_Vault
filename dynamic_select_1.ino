#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>

#define TFT_CS         13  
#define TFT_RST        10  
#define TFT_DC         9   
#define TFT_MOSI       11  
#define TFT_SCLK       12  

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const int down = 4;
const int up   = 0; 

// 1. Create a custom structure to hold all our account info together
struct VaultEntry {
  const char* siteName;
  const char* username;
  const char* password;
};

// 2. Turn our simple list into our structured vault array!
// (Remember to use your trick of swapping '@' for '"' if your keyboard layout requires it)
VaultEntry vault[] = {
  {"GOOGLE",     "moslembashaa@gmail.com", "####"},
  {"GITHUB",     "moslembashaa-rgb",     "--------"},
  {"UNIVERSITY", "mi251@student.le.ac.uk",    "//////"},
  {"PSN",        "Mos-med@33",     "PlaySta"}
};

// Automatically calculate how many accounts are in our vault
const int total = sizeof(vault) / sizeof(vault[0]); 
int item = 0;
int Mode = 0; // 0 = Menu, 1 = Selected Lock

void setup() {
  pinMode(down, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  
  tft.init(240, 320);
  tft.fillScreen(ST77XX_BLACK);
  
  drawMenuHeader();
  drawMenu(); 
}

void loop() {
  // --- MODE 0: MENU NAVIGATION ---
  if (Mode == 0) {
    if (digitalRead(down) == LOW) {
      unsigned long press = millis();
      bool Long = false;

      while (digitalRead(down) == LOW) {
        if (millis() - press > 800) {
          Long = true;
          Mode = 1; 
          showSelectedScreen(); // Updates the display with matching account details
          while(digitalRead(down) == LOW); 
        }
      }

      if (!Long) {
        item = (item + 1) % total;
        drawMenu();
        delay(150);
      }
    }

    if (digitalRead(up) == LOW) {
      item = item - 1;
      if (item < 0) {
        item = total - 1;
      }
      drawMenu();
      delay(200);
    }
  }
  
  // --- MODE 1: SELECTED LOCKED MODE ---
  else if (Mode == 1) {
    if (digitalRead(up) == LOW) {
      unsigned long press = millis();
      bool back = false;

      while (digitalRead(up) == LOW) {
        if (millis() - press > 800) {
          back = true;
          Mode = 0; 
          
          tft.fillScreen(ST77XX_BLACK);
          drawMenuHeader();
          drawMenu(); 
          
          while(digitalRead(up) == LOW); 
        }
      }
      delay(50);
    }
  }
}

void drawMenuHeader() {
  tft.setCursor(10, 20);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("Password Vault");
  tft.println("--------------------");
}

void drawMenu() {
  tft.setCursor(0, 60); 
  for (int i = 0; i < total; i++) {
    if (i == item) {
      tft.setTextColor(ST77XX_BLACK, ST77XX_YELLOW);
      tft.print(" > ");
      tft.println(vault[i].siteName); // Pulls name from struct
    } else {
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.print("   "); 
      tft.println(vault[i].siteName); // Pulls name from struct
    }
  }
}

// 3. Updated display engine to dynamically show the account data!
void showSelectedScreen() {
  tft.fillScreen(ST77XX_BLACK);
  
  // Header
  tft.setCursor(10, 30);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println(vault[item].siteName); // Dynamic site title
  tft.println("====================");
  
  // Username block
  tft.setCursor(10, 80);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.println("USERNAME:");
  tft.setCursor(10, 100);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println(vault[item].username); // Dynamic username
  
  // Password block
  tft.setCursor(10, 150);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.println("PASSWORD:");
  tft.setCursor(10, 170);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println(vault[item].password); // Dynamic password!
  
  // Footer
  tft.setCursor(10, 280);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hold UP Button to Exit");
}