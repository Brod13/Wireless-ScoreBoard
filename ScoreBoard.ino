#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#include <string.h>

/*--------------------- MATRIX PANEL CONFIG -------------------------*/
#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another

MatrixPanel_I2S_DMA *display = nullptr;

// Module configuration
HUB75_I2S_CFG mxconfig(
  PANEL_RES_X,   // module width
  PANEL_RES_Y,   // module height
  PANEL_CHAIN    // Chain length
);

struct team{
  char* name;
  int points;
}


team GSW, LAL;
GSW.name = "GSW";
GSW.points = 120;
LAL.name = "LAL";
LAL.points = 119;


void setup()
{
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);
  delay(200);

  Serial.println("...Starting Display");
  //mxconfig.double_buff = true; // Turn of double buffer
  mxconfig.clkphase = false;
  mxconfig.gpio.e = 32;
  // OK, now we can create our matrix object
  display = new MatrixPanel_I2S_DMA(mxconfig);
  display->begin();  // setup display with pins as pre-defined in the library

  writeText("WELCOME", 7, 20, 10, 2, 1);
  delay(500);

}

void loop()
{
  display->flipDMABuffer(); // not used if double buffering isn't enabled
  delay(25);
  display->clearScreen();
  
    writeText("LAL vs GSW",10, 2, 2, 1, 3);
    writeText("122",3, 0, 11, 2, 1);
    writeText("120",3, 36, 11, 2, 2);
}

void writeText(char* text, int size, int x, int y, int textSize, int color)
{
  uint16_t colorChar = 0;

  if(color == 1)
  {
      colorChar=0xF111;
  }
  else if(color == 2)
  {
    colorChar=0x111F;
  }
  else
  {
    colorChar=0x1FF1;
  }

  for (int i = 0; i <size; i++)
  {
    // Draw rect and then calculate
    display->drawChar(1+x, y, *(text+i), colorChar, 0x0000, textSize);

  if(textSize == 1)
  {
    x+=6; 
  }else if(textSize == 2 && (char[i] == '1;))
  {
    x+=9; 
  }else
  {
    x+=11; 
  }
    

    if(position >=MATRIX_WIDTH-6)
    {
      y+=9;
      // display->setCursor(1,line*8);
    }
  }

  // oldCursorPos = display->getCursorY;

}