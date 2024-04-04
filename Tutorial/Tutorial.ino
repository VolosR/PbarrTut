#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

unsigned short gray=0x6B6D;
unsigned short back=TFT_BLACK;

int progress=0;   // 0 is min, 100 is max
int seg=0;

void setup() {
  pinMode(0,INPUT_PULLUP);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  sprite.createSprite(320,170);

     //brightness
     ledcSetup(0, 10000, 8);
     ledcAttachPin(38, 0);
     ledcWrite(0, 160);
}

void draw()
  {
    sprite.fillSprite(back); 
    
     for(int i=0;i<12;i++)
     if(i<seg)
     {sprite.drawWedgeLine(60+(i*18), 110, 68+(i*18), 80, 5, 5, TFT_WHITE,back);}
     else
      {sprite.drawWedgeLine(60+(i*18), 110, 68+(i*18), 80, 5, 5, gray,back);}
   
    sprite.fillRect(55,110,220,8,back);
    sprite.fillRect(60,75,220,8,back);
    sprite.drawString(String(progress),55,10,7);
    sprite.pushSprite(0,0);
  }

void loop() {
  if(digitalRead(0)==0)
  { 
    if(progress<100)
      progress++;
  }
  else {
    if(progress>0)
      progress--;
  }

  seg=map(progress,0,100,0,12);
  
  draw();
}