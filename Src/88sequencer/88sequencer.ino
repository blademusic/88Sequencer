#include "LedControl.h"
#include <rotary.h>

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected
Rotary r = Rotary(4, 3, 2);        // there is no must for using interrupt pins !!
Rotary r2=Rotary(7,6,5);

const int  buttonPin = 8;
int OutPut0 = 9;
int OutPut1 = 13;

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
long selectedDotLastTime=0;
bool selectedDotStatus=false;

long selectedoutputOnTime=0;
bool selectedoutputStatus=false;

int row0Step=0;
int row1Step=0;
int row2Step=0;
int row3Step=0;
int row4Step=0;
int row5Step=0;
int row6Step=15;
int row7Step=15;

int row0StepDir=1;
int row1StepDir=1;
int row2StepDir=1;
int row3StepDir=0;
int row4StepDir=1;
int row5StepDir=1;
int row6StepDir=2;
int row7StepDir=2;

void setup()
{
  pinMode(buttonPin, INPUT);
pinMode(OutPut0, OUTPUT);
pinMode(OutPut1, OUTPUT);
 digitalWrite(OutPut0, LOW);
  digitalWrite(OutPut1, LOW);


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



  bpmMmillis = (float)60 / (float)bpm * (float)1000;


  Serial.println("Bpm:");
  Serial.println(String(bpmMmillis));
  Serial.println("---------------");

  SetStartMatrix();

}


String originalMatrix[] =
{
  "0001000000010000",
  "0100100001001000",
  "1001000010010000",
  "0000000000000000",
  "0000000000000000",
  "0011001000110010",
  "0000000000000000",
  "0101100101011001"  
};
void loop()
{
  CheckButton();
  if (runSequencer && menu==1)
  {
    Sequence();
  }
}
