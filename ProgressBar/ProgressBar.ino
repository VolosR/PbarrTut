#include <TFT_eSPI.h>
#include "Noto.h"
#include "NotoBig.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

unsigned short dark=0x1804;
unsigned short back2=0x1003;
unsigned short back=0x020D;
unsigned short yel=0xD581;

int cur_progress=68;
int segments=0;

void setup() {
  
  pinMode(0,INPUT_PULLUP);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  sprite.createSprite(320,170);

     //brightness
     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 140);
}

void draw()
  {
    sprite.fillSprite(back2); 
    sprite.fillSmoothRoundRect(38, 8, 250, 152, 6, back,back2);


    //draw bar
    for(int i=0;i<12;i++)
    sprite.drawWedgeLine(60+(i*18),110,68+(i*18),80,5,5,dark,back);

    for(int i=0;i<segments;i++)
    sprite.drawWedgeLine(60+(i*18),110,68+(i*18),80,5,5,0xE71C,back);

    sprite.fillRect(55,110,220,8,back);
    sprite.fillRect(60,75,220,8,back);

    //frame rect
    sprite.drawRect(45,72,235,50,0x869F);

    //round rectangles
    sprite.fillSmoothRoundRect(45, 14, 70, 48, 3, yel,back);
    sprite.fillSmoothRoundRect(96, 16, 16, 14, 3, TFT_BLACK,yel);
    sprite.fillSmoothRoundRect(250, 14, 30, 48, 3, TFT_BLACK,back);
    sprite.fillSmoothRoundRect(252, 16, 26, 20, 3, TFT_RED,TFT_BLACK);
    
    
    sprite.loadFont(NotoBig);
    sprite.setTextDatum(4);
    sprite.setTextColor(TFT_BLACK,yel);
    sprite.drawString(String(cur_progress),80,50);
     sprite.setTextColor(TFT_MAGENTA,back2);
     sprite.setTextDatum(0);
   
    sprite.unloadFont();

    sprite.drawFastHLine(125, 32, 110, TFT_SILVER);
    sprite.loadFont(Noto);
    sprite.setTextDatum(0);
    sprite.setTextColor(TFT_SILVER,back);
    sprite.drawString("PROGRESS BAR",125,14);
    sprite.drawString("TFT_ESPI LIB",125,36);
    sprite.setTextColor(TFT_WHITE,TFT_RED);
    sprite.drawString("ESP",253,20);
    sprite.setTextColor(TFT_SILVER,TFT_BLACK);
    sprite.drawString("32",257,41);
    sprite.setTextColor(dark,back);
    sprite.drawString("#sandwich",196,142);
    
    sprite.unloadFont();

    sprite.setTextColor(TFT_SILVER,back);
    sprite.drawString("3 Minute Code with Volos",45,132);
    sprite.setTextColor(TFT_SILVER,TFT_BLACK);
    sprite.drawString("%",102,20);
    sprite.pushSprite(0,0);
  }

void loop() {
  
  if(digitalRead(0)==0)
  {
    if(cur_progress<100) cur_progress=cur_progress+4;
  }else {
    if(cur_progress>64) cur_progress=cur_progress-2;
  }

  segments=map(cur_progress,0,100,0,12);
  draw();
}