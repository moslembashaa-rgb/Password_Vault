#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>

// Your screen pins (using the ones that worked yesterday!)
#define TFT_CS         13  
#define TFT_RST        10  
#define TFT_DC         9   
#define TFT_MOSI       11  
#define TFT_SCLK       12  

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const int down = 4;
const int up   = 0;

const char* menu[] = {"GOOGLE", "GITHUB", "UNIVERSITY", "PSN"};
const int total = 4;
int item = 0;

void setup() {
  pinMode(down, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  tft.init(240,320);
  tft.fillScreen(ST77XX_BLACK);
  drawMenu();
  
}

void loop() {
  if (digitalRead(down) == LOW){
    item = item + 1;
    if (item >= total){
      item = 0;
    }
    drawMenu();
    delay(200);
  }

  if (digitalRead(up) == LOW){
    item = item - 1;
    if (item < 0){
      item = total - 1;
    }
    drawMenu();
    delay(200);
  }
}


void drawMenu() {
  tft.setCursor(10,20);
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("Password Vault");
  tft.println("--------------------");
  tft.println("");

  for (int i = 0; i < total; i++){
    if (i == item){
      tft.setTextColor(ST77XX_YELLOW);
      tft.print(">");
      tft.println(menu[i]);
    
    }else{
      tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
      tft.print(" ");
      tft.println(menu[i]);
    }
  }
}