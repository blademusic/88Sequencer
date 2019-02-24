#include "LedControl.h"
#include <rotary.h>
#include <SPI.h>

LedControl lc = LedControl(12, 10, 11, 2); // Pins: DIN,CLK,CS, # of Display connected
Rotary r2 = Rotary(4, 3, 2);        // there is no must for using interrupt pins !!
Rotary r = Rotary(20, 21, 22);
byte Buttonsbuffer[] = {1, 2};
byte ButtonsbufferOld[] = {1, 2};
int x = 0;
int maxNumber = 2;
int bpm = 60;
long bpmMmillis;
long bpmLastRun = 0;
int sequencerStep = 0;
//#define HALF_STEP
bool runSequencer = false;
int menu = 0;
int selectedMatricRow = 0;
int selectedMatricCol = 0;

long selectedDotLastTime = 0;
bool selectedDotStatus = false;

long selectedoutputOnTime = 0;
bool selectedoutputStatus = false;

int row0Step = 0;
int row1Step = 0;
int row2Step = 0;
int row3Step = 0;
int row4Step = 0;
int row5Step = 0;
int row6Step = 15;
int row7Step = 15;

int row0StepDir = 1;
int row1StepDir = 1;
int row2StepDir = 1;
int row3StepDir = 0;
int row4StepDir = 1;
int row5StepDir = 1;
int row6StepDir = 2;
int row7StepDir = 2;

byte TrackOutputs = 0x00;
#define   SSin  9
#define   SSout  7
boolean registers[16];
SPISettings Settings165( SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0);

int ploadPin         = 8;
int clockEnablePin   = 9;

#define   Load  8
void setup()
{
  Serial.begin(9600);   // only for debugging, comment out later
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Initialized");


  pinMode(ploadPin, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(SSout, OUTPUT);
  pinMode( SSin  , OUTPUT );
  pinMode( Load  , OUTPUT );

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();

  digitalWrite(MISO, LOW);
  digitalWrite(ploadPin, HIGH);

  digitalWrite(SSout, HIGH);
  SPI.transfer(255);
  SPI.transfer(TrackOutputs);
  digitalWrite(SSout, LOW);

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
  runSequencer = !runSequencer;
  menu = 1;
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
  if (runSequencer && menu == 1)
  {
    Sequence();
  }
}
