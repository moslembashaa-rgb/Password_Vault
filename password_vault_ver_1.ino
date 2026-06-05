#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>

#include <HijelHID_BLEKeyboard.h>

#define TFT_CS         13  
#define TFT_RST        10  
#define TFT_DC         9   
#define TFT_MOSI       11  
#define TFT_SCLK       12  

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

HijelHID_BLEKeyboard Keyb("cheap keyb");

const int down = 4;
const int up   = 0; 

struct VaultEntry {
  const char* siteName;
  const char* username;
  const char* password;
};

VaultEntry vault[] = {
  {"GOOGLE",     "moslembashaa\"gmail.com", "Misnooplogg\"1"},
  {"GITHUB",     "moslembashaa-rgb",     "Misnooplogg\"1"},
  {"UNIVERSITY", "mi251\"student.le.ac.uk",    "Misnooplogg\"1"},
  {"PSN",        "Mos-med\"33",     "Misnooplogg1"},
  {"Ansys", "moslembashaa\"gmail.com", "Mosmed\"2006"},
  {"Instagram", "m05lem", "Misnooplogg\"1"}
};


const int total = sizeof(vault) / sizeof(vault[0]); 
int item = 0;
int Mode = 0;

void setup() {
  pinMode(down, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  
  tft.init(240, 320);
  tft.fillScreen(ST77XX_BLACK);
  
  Keyb.begin();

  
  drawMenuHeader();
  drawMenu(); 
}

void loop() {

  if (Mode == 0) {
    if (digitalRead(down) == LOW) {
      unsigned long press = millis();
      bool Long = false;

      while (digitalRead(down) == LOW) {
        if (millis() - press > 800) {
          Long = true;
          Mode = 1; 
          showSelectedScreen(); 
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
  

  else if (Mode == 1) {
    if (digitalRead(down) == LOW) {
      unsigned long press = millis();
      bool inject = false;

      while (digitalRead(down) == LOW) {
        if (millis() - press > 800) {
          inject = true;
          
        
          if (Keyb.isConnected()) {
           // Inject the string
            Keyb.print(vault[item].password);
            delay(100);
          
          } else {
            
            tft.fillRect(10, 220, 220, 40, ST77XX_RED);
            tft.setCursor(20, 230);
            tft.setTextColor(ST77XX_WHITE);
            tft.setTextSize(1);
            tft.println("ERROR: NO BLE PAIR!");
            delay(1500);
            tft.fillRect(10, 220, 220, 40, ST77XX_BLACK);
          }
          
          while(digitalRead(down) == LOW); 
        }
      }
      delay(50);
    }

  
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
      tft.println(vault[i].siteName); 
    } else {
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.print("   "); 
      tft.println(vault[i].siteName); 
    }
  }
}




void showSelectedScreen() {
  tft.fillScreen(ST77XX_BLACK);  
  tft.setCursor(10, 30);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.println(vault[item].siteName); 
  tft.println("====================");

  tft.setCursor(10, 80);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.println("USERNAME:");
  tft.setCursor(10, 100);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println(vault[item].username);
  
 
  tft.setCursor(10, 150);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.println("PASSWORD:");
  tft.setCursor(10, 170);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println(vault[item].password); 
  
  
  tft.setCursor(10, 280);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hold UP Button to Exit");
}