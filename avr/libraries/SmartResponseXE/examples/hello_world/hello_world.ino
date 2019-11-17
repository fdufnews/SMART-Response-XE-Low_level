/*
 * This sofware is more a test for the terminal than a simple Hello world
 * (but it still blink an LED)
 * It draws text and graphic on the LCD screen
 * Test keyboard activity (returns text and code of pressed keys)
 * Test the added LED (blink the LED after reset, toggles LED state when l is pressed)
 * Test the added Buzzer (buzz after reset, plays sound when b, n or m are pressed)
 * Evaluate text display with the different fonts (when t is pressed)
 */

#include <SmartResponseXE.h>

int TEXT_WIDTH = 384;
int TEXT_HEIGHT = 136;
int DRAW_WIDTH = 128;
int DRAW_HEIGHT = 136;
unsigned long lastState;
unsigned long lastKey;
const unsigned long timeState=1000;
const unsigned long timeKey=100;
const int POWER_BUTTON=20;
byte ledState=LOW;

unsigned int counter = 0;
char buf[10];

// DAC configuration
// Select 1.6V ref voltage
// Select A0 as input
void setBatStat(void){
  ADMUX = 0xC0; // Int ref 1.6V
  ADCSRA = 0x87; // Enable ADC
  ADCSRB = 0x00; // MUX5= 0, freerun
  ADCSRC = 0x54; // Default value
  ADCSRA = 0x97; // Enable ADC
  //delay(5);
  ADCSRA|=(1<<ADSC);// start conversion
}

// getBatStat
// returns battery's voltage in millivolts
// Battery is connected through a resistor divider (825k and 300k) with gain of 0.266666
// ADC ref is 1.6V with 1024 steps
// to simplify the calculation we will neglect 1024 and round it to 1000
// so we will use a conversion factor of 1.6/0.26666 which is 6
// This will give an error of 24/1000 which is acceptable in this case
uint16_t getBatStat(void){
  uint16_t low, high;
  ADCSRA|=(1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  low=ADCL;
  high=ADCH;
  
  return ((high<<8) + low) * 6;
}

// Draw display background
void initAppDisplay(void){

  SRXEFill(0);
  // Next, you can draw some text or rectangles. The color can be 0-3 (0=off, 3=fully on)
  SRXEWriteString(60,2,"Hello World!", FONT_LARGE, 3, 0); // (int x, int y, char *szMsg, int iSize, int iFGColor, int iBGColor)
  SRXEWriteString(60,22,"Battery:", FONT_LARGE, 3, 0); 
  SRXEWriteString(60,42,"Uptime :", FONT_LARGE, 3, 0); 
  SRXEWriteString(60,62,"Key    :", FONT_LARGE, 3, 0); 
  
  // Draw a rectanle on each side of the screen
  SRXERectangle(0, 0, 17, 135, 0x1, 0x1); // (int x, int y, int cx, int cy, byte color, byte bFilled)
  SRXERectangle(110, 0, 17, 135, 0x1, 0x1);

  // Draw arrows pointing to the soft keys
  SRXEWriteString(0, 2,  "< A", FONT_LARGE, 3, 1);
  SRXEWriteString(0, 32, "< B", FONT_LARGE, 3, 1);
  SRXEWriteString(0, 62, "< C", FONT_LARGE, 3, 1);
  SRXEWriteString(0, 92, "< D", FONT_LARGE, 3, 1);
  SRXEWriteString(0, 122,"< E", FONT_LARGE, 3, 1);
  
  int charnum = 3;
  int rightColX = TEXT_WIDTH - (16 * charnum);
  SRXEWriteString(rightColX, 2,  "F >", FONT_LARGE, 3, 1);
  SRXEWriteString(rightColX, 32, "G >", FONT_LARGE, 3, 1);
  SRXEWriteString(rightColX, 62, "H >", FONT_LARGE, 3, 1);
  SRXEWriteString(rightColX, 92, "I >", FONT_LARGE, 3, 1);
  SRXEWriteString(rightColX, 122,"J >", FONT_LARGE, 3, 1);

  // Draw some rectangles with various fill and color
  SRXERectangle(25, 115, 15, 15, 0x3, 0x0);
  SRXERectangle(45, 115, 15, 15, 0x1, 0x1);
  SRXERectangle(70, 115, 15, 15, 0x2, 0x1);
  SRXERectangle(90, 115, 15, 15, 0x3, 0x1);

  SRXEWriteString(60, 82, "Small 0123456789", FONT_SMALL, 3, 0);
  SRXEWriteString(168, 82, "Normal 0123456789", FONT_NORMAL, 3, 0);
  SRXEWriteString(60, 92, "Medium 0123456789", FONT_MEDIUM, 3, 0);

  // Draw a vertical and horizontal line
  SRXEVerticalLine(DRAW_WIDTH/2, 107, TEXT_HEIGHT-84, 0x3); // int x, int y, int height, byte color // color options: 0x0 - 0x3
  SRXEHorizontalLine(17, 107, 93, 0x3, 2); // (int x, int y, int length, byte color, int thickness)  
}

// Function that put the terminal in sleep mode
// When waking up restore the display and the ADC configuration
void goToSleep(void){
  digitalWrite(LED,LOW);
  SRXESleep(); // go into sleep mode and wait for an event (power button)
  // returning from sleep
  initAppDisplay(); // restore screen background
  setBatStat(); // restore ADC configuration
  digitalWrite(LED,ledState); // restore LED state
  lastState=millis();
  lastKey=lastState;  
}

// testText
// Test how long it takes to fill the screen with text
// using either one of the font
void testText(void){
  unsigned long startTime;
  unsigned long timeItTook[4]={0,0,0,0};
  char* myString={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?"};
  uint8_t line;
  uint8_t nbLine;

  for(uint8_t font=0;font<4;font++){
    uint8_t inc=(font & 2)?16:8; // line increment
    SRXEFill(0); // clear screen
    startTime=micros();
    for(line=0, nbLine=0;line<(TEXT_HEIGHT-inc+1);line+=inc, nbLine++){
      SRXEWriteString(0,line,myString,font,3,0);
    }
    timeItTook[font]=micros()-startTime;
    SRXERectangle(8, 16, 48, 54, 0, 1);
    SRXERectangle(8, 16, 48, 54, 3, 0);
    snprintf(buf, sizeof(buf)-1, "%2d", nbLine);
    SRXEWriteString(33,20,buf,FONT_MEDIUM,3,0);
    SRXEWriteString(69,20,"Lines",FONT_MEDIUM,3,0);
    snprintf(buf, sizeof(buf)-1, "%u us", timeItTook[font]);
    SRXEWriteString(33,36,buf,FONT_MEDIUM,3,0);
    SRXEWriteString(30,52,"Press a key",FONT_MEDIUM,3,0);

    while(SRXEGetKey()==0);
  }
  SRXEFill(0);
  SRXEWriteString(30,20,"Normal: ",FONT_MEDIUM,3,0);
  snprintf(buf, sizeof(buf)-1, "%u us", timeItTook[0]);
  SRXEWriteString(150,20,buf,FONT_MEDIUM,3,0);
  SRXEWriteString(30,40,"Small : ",FONT_MEDIUM,3,0);
  snprintf(buf, sizeof(buf)-1, "%u us", timeItTook[1]);
  SRXEWriteString(150,40,buf,FONT_MEDIUM,3,0);
  SRXEWriteString(30,60,"Medium: ",FONT_MEDIUM,3,0);
  snprintf(buf, sizeof(buf)-1, "%u us", timeItTook[2]);
  SRXEWriteString(150,60,buf,FONT_MEDIUM,3,0);
  SRXEWriteString(30,80,"Large : ",FONT_MEDIUM,3,0);
  snprintf(buf, sizeof(buf)-1, "%u us", timeItTook[3]);
  SRXEWriteString(150,80,buf,FONT_MEDIUM,3,0);
  while(SRXEGetKey()==0);
}

// initialize system
// display
// blink the LED, generate some beep
void setup() {
  setBatStat(); // ADC setup

  SRXEInit(0xe7, 0xd6, 0xa2); // initialize and clear display // CS, D/C, RESET

  initAppDisplay();
  
  lastState=millis();
  lastKey=lastState;

  // set Power button input
  pinMode(POWER_BUTTON,INPUT_PULLUP);
  // Test LED output
  // Blink the LED (an Hello World would not be an Hello World without a blink!!)
  pinMode(LED,OUTPUT);
  for(byte count=0;count<5;count++){
    ledState=!ledState;
    digitalWrite(LED,ledState);
    delay(500);
  }

  // Test BUZZER output
  pinMode(BUZZER,OUTPUT);
  for(int sweep=0;sweep<600;sweep+=150){
    tone(BUZZER,250+sweep,150);
    delay(140);
  }
  noTone(BUZZER);
}

void loop() {
  // if power button pressed go into sleep mode
  if(digitalRead(POWER_BUTTON)==0){
    goToSleep();
  }

  // Every timeState (1s )
  //  get battery state
  //  increment counter
  //
  if((millis()-lastState) > timeState){
    lastState = millis();
    // Battery state
    memset (buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf)-1, "%u", getBatStat());
    SRXEWriteString(189, 22, "      ", FONT_LARGE, 3, 0);
    SRXEWriteString(189, 22, buf, FONT_LARGE, 3, 0);
  
    // clear the previous text and draw new uptime
    memset (buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf)-1, "%u", counter);
    SRXEWriteString(189, 42, "      ", FONT_LARGE, 3, 0);
    SRXEWriteString(189, 42, buf, FONT_LARGE, 3, 0);
 
    counter++;
  }

  // Every timeKey
  // Scan keyboard
  // and test for some "special" keypress
  if((millis()-lastKey) > timeKey){
    lastKey = millis();
    // clear the previous text and draw new key
    if (char key = SRXEGetKey()){
      memset (buf, 0, sizeof(buf));
      snprintf(buf, sizeof(buf)-1, "%c, %02X", key<0x20?0x20:key, (byte)key);
      SRXEWriteString(189, 62, "      ", FONT_LARGE, 3, 0);
      SRXEWriteString(189, 62, buf, FONT_LARGE, 3, 0);
      // action linked to some keypress
      // l key toggle LED state
      if(key=='l'){
        ledState=!ledState;
        digitalWrite(LED,ledState);
      }
      // n, b, m keys play a sound
      if(key=='n') tone(BUZZER,1000,250);
      if(key=='b') tone(BUZZER,2000,250);
      if(key=='m') tone(BUZZER,500,250);

      // if key is t go for a screen text filling test
      if(key=='t'){
        testText();
        initAppDisplay();  
        lastState=millis();
        lastKey=lastState;
      }
        
    }
  }
}
