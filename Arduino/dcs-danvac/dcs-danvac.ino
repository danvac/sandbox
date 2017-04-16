/*
  Tell DCS-BIOS to use a serial connection and use the default Arduino Serial
  library. This will work on the vast majority of Arduino-compatible boards,
  but you can get corrupted data if you have too many or too slow outputs
  (e.g. when you have multiple character displays), because the receive
  buffer can fill up if the sketch spends too much time updating them.
  
  If you can, use the IRQ Serial connection instead.
*/
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

#include <TM1638.h>
#define TM1638_COLOR_RED    2
#define TM1638_COLOR_GREEN  1

//TM1638 module0(9,8,7,true,1);

TM1638 module1(9,8,6,true,1);
bool updateModule1 = true;
char module1Text[9];

int iasRoof = 333;
unsigned int fuelQty = 0;

#define POS(SV,EV,SA,EA,A) (float((float(SV - EV) / (SA - EA) * (A - SA) + SV)))

void onIasRoofChange(unsigned int newValue) {
  unsigned int angle = newValue;
  #define SA 0
  #define EA 5079
  #define SV 0
  #define EV 20
  if (angle >= SA && angle < EA) iasRoof = POS(SV,EV,SA,EA,angle);
  #define SA 5079
  #define EA 11821
  #define SV 20
  #define EV 30
  else if (angle >= SA && angle < EA) iasRoof = POS(SV,EV,SA,EA,angle);
  #define SA 11821
  #define EA 19697
  #define SV 30
  #define EV 40
  else if (angle >= SA && angle < EA) iasRoof = POS(SV,EV,SA,EA,angle);
  #define SA 19697
  #define EA 24159
  #define SV 40
  #define EV 50
  else if (angle >= SA && angle < EA) iasRoof = POS(SV,EV,SA,EA,angle);
  #define SA 24159
  #define EA 53152
  #define SV 50
  #define EV 124
  else if (angle >= SA && angle < EA) iasRoof = POS(SV,EV,SA,EA,angle);
  #define SA 53152
  #define EA 62337
  #define SV 124
  #define EV 150
  else iasRoof = POS(SV,EV,SA,EA,angle);
  updateModule1 = true;
}
DcsBios::IntegerBuffer iasRoofBuffer(0x145e, 0xffff, 0, onIasRoofChange);

void onFuelQtyChange(unsigned int newValue) {
    fuelQty = newValue;
}
DcsBios::IntegerBuffer fuelQtyBuffer(0x1476, 0xffff, 0, onFuelQtyChange);

TM1638 module2(9,8,5,true,1);
bool updateModule2 = true;
char module2Text[9];

int gmcCrs1 = 666;
int gmcHdg = 666;

void onGmcCrs1Change(unsigned int newValue) {
  gmcCrs1 = 360.0 * newValue / 65535.0;
  updateModule2 = true;
}
DcsBios::IntegerBuffer gmcCrs1Buffer(0x142a, 0xffff, 0, onGmcCrs1Change);

void onGmcHdgChange(unsigned int newValue) {
  gmcHdg = 360.0 * newValue / 65535.0;
  updateModule2 = true;
}
DcsBios::IntegerBuffer gmcHdgBuffer(0x1430, 0xffff, 0, onGmcHdgChange);

TM1638 module3(9,8,4,true,1);
bool updateModule3 = true;
char module3Text[9];

int pAlt = 6666;
unsigned int vviP = 32768;
char rAlt[5];

void onRaltDisplayChange(char* newValue) {
  strncpy(rAlt, newValue, sizeof(rAlt));
  updateModule3 = true;
}
DcsBios::StringBuffer<4> raltDisplayBuffer(0x14aa, onRaltDisplayChange);

void onPalt1000Change(unsigned int newValue) {
  pAlt = 100000.0 * newValue / 65535.0;
  updateModule3 = true;
}
DcsBios::IntegerBuffer palt1000Buffer(0x144e, 0xffff, 0, onPalt1000Change);

void onVviPChange(unsigned int newValue) {
  vviP = newValue;
  updateModule3 = true;
}
DcsBios::IntegerBuffer vviPBuffer(0x1482, 0xffff, 0, onVviPChange);

void progressVVI(TM1638 module, unsigned int value) {
  const unsigned int MIN = 0;
  const unsigned int CENTER = 32768;
  const unsigned int MAX = 65535;
  const unsigned int MARK = 2730;

  if(value < CENTER - 1024) {
         if(value < MIN + 1024)        module.setLEDs(0b0000111100000000);
    else if(value < CENTER -11 * MARK) module.setLEDs(0b0000111100001000);
    else if(value < CENTER -10 * MARK) module.setLEDs(0b0000111100001100);
    else if(value < CENTER - 9 * MARK) module.setLEDs(0b0000111100001110);
    else if(value < CENTER - 8 * MARK) module.setLEDs(0b0000111100001111);
    else if(value < CENTER - 7 * MARK) module.setLEDs(0b0000011100001111);
    else if(value < CENTER - 6 * MARK) module.setLEDs(0b0000001100001111);
    else if(value < CENTER - 5 * MARK) module.setLEDs(0b0000000100001111);
    else if(value < CENTER - 4 * MARK) module.setLEDs(0b0000000000001111);
    else if(value < CENTER - 3 * MARK) module.setLEDs(0b0000000000001110);
    else if(value < CENTER - 2 * MARK) module.setLEDs(0b0000000000001100);
    else if(value < CENTER - 1024    ) module.setLEDs(0b0000000000001000);
  }
  else if(value > CENTER + 1024) {
         if(value > MAX - 1024)        module.setLEDs(0b1111000000000000);
    else if(value > CENTER +11 * MARK) module.setLEDs(0b1111000000010000);
    else if(value > CENTER +10 * MARK) module.setLEDs(0b1111000000110000);
    else if(value > CENTER + 9 * MARK) module.setLEDs(0b1111000001110000);
    else if(value > CENTER + 8 * MARK) module.setLEDs(0b1111000011110000);
    else if(value > CENTER + 7 * MARK) module.setLEDs(0b1110000011110000);
    else if(value > CENTER + 6 * MARK) module.setLEDs(0b1100000011110000);
    else if(value > CENTER + 5 * MARK) module.setLEDs(0b1000000011110000);
    else if(value > CENTER + 4 * MARK) module.setLEDs(0b0000000011110000);
    else if(value > CENTER + 3 * MARK) module.setLEDs(0b0000000001110000);
    else if(value > CENTER + 2 * MARK) module.setLEDs(0b0000000000110000);
    else if(value > CENTER + 1024    ) module.setLEDs(0b0000000000010000);
  }
  else module.setLEDs(0b0000000000011000);
}

/*
void onEngRpmChange(unsigned int newValue) {

}
DcsBios::IntegerBuffer engRpmBuffer(0x1462, 0xffff, 0, onEngRpmChange);

void onClockHChange(unsigned int newValue) {

}
DcsBios::IntegerBuffer clockHBuffer(0x1478, 0xffff, 0, onClockHChange);

void onClockMChange(unsigned int newValue) {

}
DcsBios::IntegerBuffer clockMBuffer(0x147a, 0xffff, 0, onClockMChange);

void onClockSChange(unsigned int newValue) {

}
DcsBios::IntegerBuffer clockSBuffer(0x147c, 0xffff, 0, onClockSChange);


void onAdfVorSwChange(unsigned int newValue) {

}
DcsBios::IntegerBuffer adfVorSwBuffer(0x14fc, 0x8000, 15, onAdfVorSwChange);
*/

#include <U8glib.h>

// 6 lines
#define FONT u8g_font_8x13 // 16x6
#define FONT u8g_font_7x13 // 18x6
#define FONT u8g_font_6x13 // 21x6
#define FONT_HEIGHT 9 // font height in pixels
#define LINE_SPACING 2 // spacing between lines
#define LINE_SPACING 4 // spacing between lines
/*
// 7 lines
#define FONT u8g_font_profont12 // 21x7
#define FONT u8g_font_ncenR08 // 25x7
#define FONT_HEIGHT 8 // font height in pixels
#define LINE_SPACING 1 // spacing between lines

// 8 lines
#define FONT u8g_font_profont11 // 21x7
//#define FONT u8g_font_ncenR08 // 25x7
#define FONT_HEIGHT 7 // font height in pixels
#define LINE_SPACING 1 // spacing between lines
*/
/*
// 9 lines
#define FONT u8g_font_profont10 // 21x7
#define FONT_HEIGHT 6 // font height in pixels
#define LINE_SPACING 1 // spacing between lines
*/
/*
// 10 lines
#define FONT u8g_font_baby // 21x7
#define FONT_HEIGHT 5 // font height in pixels
#define LINE_SPACING 1 // spacing between lines
*/
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

String line0 = "12345678901234567890123456";
String line1 = "234567890123456";
String line2 = "34567890123456";
String line3 = "4567890123456";
String line4 = "567890123456";
String line5 = "67890123456";
String line6 = "7890123456";
String line7 = "890123456";
String line8 = "90123456";
String line9 = "0123456";
String line10 = "123456";

String uhfFreq = "225.00";
String vhfComm = "126.675";
String vhfNav = "107.00";
bool redraw = true;

void onUhfFreqChange(char* newValue) {
  uhfFreq = newValue;
  redraw = true;
}
DcsBios::StringBuffer<6> uhfFreqBuffer(0x14e2, onUhfFreqChange);

void onVhfcommFreqChange(char* newValue) {
  vhfComm = newValue;
  redraw = true;
}
DcsBios::StringBuffer<7> vhfcommFreqBuffer(0x14d4, onVhfcommFreqChange);

void onVhfnavFreqChange(char* newValue) {
  vhfNav = newValue;
  redraw = true;
}
DcsBios::StringBuffer<6> vhfnavFreqBuffer(0x14f0, onVhfnavFreqChange);

String fm1 = "3";
String fm2 = "0";
String fm3 = "0";
String fm4 = "0";
String fmComm = "30.00";

void onVhffmFreq1Change(char* newValue) {
  fm1 = newValue;
  fmComm = fm1 + fm2 + '.' + fm3 + fm4;
  redraw = true;
}
DcsBios::StringBuffer<1> vhffmFreq1StrBuffer(0x14ea, onVhffmFreq1Change);

void onVhffmFreq2Change(unsigned int newValue) {
  fm2 = String(newValue);
  fmComm = fm1 + fm2 + '.' + fm3 + fm4;
  redraw = true;
}
DcsBios::IntegerBuffer vhffmFreq2Buffer(0x14de, 0x1e00, 9, onVhffmFreq2Change);

void onVhffmFreq3Change(unsigned int newValue) {
  fm3 = String(newValue);
  fmComm = fm1 + fm2 + '.' + fm3 + fm4;
  redraw = true;
}
DcsBios::IntegerBuffer vhffmFreq3Buffer(0x14ea, 0x0f00, 8, onVhffmFreq3Change);

void onVhffmFreq4Change(char* newValue) {
  fm4 = newValue;
  fmComm = fm1 + fm2 + '.' + fm3 + fm4;
  redraw = true;
}
DcsBios::StringBuffer<1> vhffmFreq4StrBuffer(0x14ec, onVhffmFreq4Change);

#define B190 0 // 190 200 220
#define B400 1 // 400 420 450 500
#define B850 2 // 850 900 1000

String adfNav = "450.0";
String adfSig = "-1";
int adfBand = 0;
unsigned int adfFreq = 0;

#define ADF_FREQ(SF,EF,SV,EV,V) (String(float(((SF - EF) / (SV - EV) * (V - SV) + SF))))

String getAdfFreq(int band, unsigned int val) {
  switch(band) {
    case B190:
      #define SV 0
      #define EV 3200
      #define SF 190
      #define EF 195
      if (val >= SV && val < EV) return ADF_FREQ(SF,EF,SV,EV,val);
      #define SV 3200
      #define EV 48300
      #define SF 195
      #define EF 342
      else if (val >= SV && val < EV) return ADF_FREQ(SF,EF,SV,EV,val);
      #define SV 48300
      #define EV 65535
      #define SF 342
      #define EF 400
      else return ADF_FREQ(SF,EF,SV,EV,adfFreq);
      break;
    case B400:
      if (adfFreq >= 0 && adfFreq < 3200) return ADF_FREQ(400.0,410.0,0.0,3200.0,adfFreq);
      else return ADF_FREQ(410.0,850.0,3200.0,65535.0,adfFreq);
      break;
    case B850:
      if (adfFreq >= 0 && adfFreq < 3200) return ADF_FREQ(850,875,0,3200,adfFreq);
      else return ADF_FREQ(875,1800,3200,65535,adfFreq);
      break;
  }
  return String('?');
}

void onAdfBandChange(unsigned int newValue) {
  adfBand = newValue;
  adfNav = getAdfFreq(adfBand,adfFreq);
  redraw = true;
}
DcsBios::IntegerBuffer adfBandBuffer(0x14fc, 0x0003, 0, onAdfBandChange);

void onAdfFreqChange(unsigned int newValue) {
  adfFreq = newValue;
  adfNav = getAdfFreq(adfBand,adfFreq);
  redraw = true;
}
DcsBios::IntegerBuffer adfFreqBuffer(0x1426, 0xffff, 0, onAdfFreqChange);

void onAdfSignalChange(unsigned int newValue) {
    adfSig = String((float)newValue / 65535.0);
    redraw = true;
}
DcsBios::IntegerBuffer adfSignalBuffer(0x1428, 0xffff, 0, onAdfSignalChange);

void onLowRpmIndChange(unsigned int newValue) {
    //module1.setLED(TM1638_COLOR_RED, newValue);
}
DcsBios::IntegerBuffer lowRpmIndBuffer(0x1416, 0x0080, 7, onLowRpmIndChange);

DcsBios::LED lowRpmInd(0x1416, 0x0080, 13);

/* paste code snippets from the reference documentation here */
void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
  if (redraw) {
    line0 = "UHF: " + uhfFreq;
    line1 = "VHF: " + vhfComm;
    line2 = "FM:   " + fmComm;
    line3 = "NAV: " + vhfNav;
    line4 = "NAV: " + adfNav + " " + adfSig;

    u8g.firstPage();
    do {
      draw();
    } while( u8g.nextPage() );
    redraw = false;
  }
  if (updateModule1) {
    snprintf(module1Text, sizeof(module1Text), "    %4d", iasRoof);
    module1.setDisplayToString(module1Text);
    updateModule1 = false;
  }
  if (updateModule2) {
    snprintf(module2Text, sizeof(module2Text), "%4d%4d", gmcCrs1, gmcHdg);
    module2.setDisplayToString(module2Text);
    updateModule2 = false;
  }
  if (updateModule3) {
    snprintf(module3Text, sizeof(module3Text), "%3s%5d", rAlt, pAlt);
    module3.setDisplayToString(module3Text);
    progressVVI(module3,vviP);
    updateModule3 = false;
  }
}

void draw(void) {
  u8g.setFont(FONT);
  u8g.setPrintPos(0, FONT_HEIGHT); u8g.print(line0);
  u8g.setPrintPos(0, FONT_HEIGHT*2+1*LINE_SPACING); u8g.print(line1);
  u8g.setPrintPos(0, FONT_HEIGHT*3+2*LINE_SPACING); u8g.print(line2);
  u8g.setPrintPos(0, FONT_HEIGHT*4+3*LINE_SPACING); u8g.print(line3);
  u8g.setPrintPos(0, FONT_HEIGHT*5+4*LINE_SPACING); u8g.print(line4);
  /*
  u8g.setPrintPos(0, FONT_HEIGHT*6+5*LINE_SPACING); u8g.print(line5);
  u8g.setPrintPos(0, FONT_HEIGHT*7+6*LINE_SPACING); u8g.print(line6);
  u8g.setPrintPos(0, FONT_HEIGHT*8+7*LINE_SPACING); u8g.print(line7);
  u8g.setPrintPos(0, FONT_HEIGHT*9+8*LINE_SPACING); u8g.print(line8);
  u8g.setPrintPos(0, FONT_HEIGHT*10+9*LINE_SPACING); u8g.print(line9);
  */
}
