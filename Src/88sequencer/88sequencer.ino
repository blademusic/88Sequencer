#include "LedControl.h"
#include <rotary.h>

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected
Rotary r = Rotary(4, 3, 2);        // there is no must for using interrupt pins !!
Rotary r2=Rotary(7,6,5);



const int  buttonPin = 8;

int x = 0;
int maxNumber = 2;
int bpm = 60;
long bpmMmillis;
long bpmLastRun = 0;
int sequencerStep = 0;
#define HALF_STEP
bool runSequencer = false;
int menu=0;
int selectedMatricRow=0;
int selectedMatricCol=0;
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup()
{
  pinMode(buttonPin, INPUT);


  Serial.begin(9600);   // only for debugging, comment out later
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Initialized");


  lc.shutdown(0, false); // Wake up displays
  lc.setIntensity(0, 5); // Set intensity levels
  lc.clearDisplay(0);  // Clear Displays
  lc.shutdown(1, false); // Wake up displays
  lc.setIntensity(1, 5); // Set intensity levels
  lc.clearDisplay(1);  // Clear Displays





  WriteText7Segment("D blade.");
  delay(2000);
  lc.clearDisplay(1);


  bpmMmillis = (float)60 / (float)bpm * (float)1000;


  Serial.println("Bpm:");
  Serial.println(String(bpmMmillis));
  Serial.println("---------------");

  SetStartMatrix();

}


char *originalMatrix[] =
{
  "00010000",
  "01001000",
  "10010000",
  "00000000",
  "00000000",
  "00110010",
  "00000000",
  "01011001"
};





void loop()
{
  CheckButton();
  if (runSequencer && menu==1)
  {
    Sequence();
  }
}
