
void Sequence()
{
  long now = millis();

  if (now >= (bpmLastRun + bpmMmillis))
  {
    
    UpdateStep();
    bpmLastRun = now;
  }
}
void UpdateStep()
{  
  LoopLeds();
  TrigTrackOut();
  row0Step = GetStep(row0Step, row0StepDir);
  row1Step = GetStep(row1Step, row1StepDir);
  row2Step = GetStep(row2Step, row2StepDir);
  row3Step = GetStep(row3Step, row3StepDir);
  row4Step = GetStep(row4Step, row4StepDir);
  row5Step = GetStep(row5Step, row5StepDir);
  row6Step = GetStep(row6Step, row6StepDir);
  row7Step = GetStep(row7Step, row7StepDir);
}

int GetStep(int stepinput, int dir)
{
  if (dir == 1)
  {
    stepinput++;
    if (stepinput == 16)
    {
      return 0;
    }
    return stepinput;
  }
  else if (dir == 2)
  {
    stepinput--;
    if (stepinput == -1)
    {
      return 15;
    }
    else
    {
      return stepinput;
    }
  }
  return stepinput;
}
void TrigTrackOut()
{
  for (int i = 0; i < 8; i ++ )
  {
    switch (i)
    {
      case 0:
        TrackTrig(i, row0Step);
        break;
      case 1:
        TrackTrig(i, row1Step);
        break;
      case 2:
        TrackTrig(i, row2Step);
        break;
      case 3:
        TrackTrig(i, row3Step);
        break;
      case 4:
        TrackTrig(i, row4Step);
        break;
      case 5:
        TrackTrig(i, row5Step);
        break;
      case 6:
        TrackTrig(i, row6Step);
        break;
      case 7:
        TrackTrig(i, row7Step);
        break;
    }
  }
}

void TrackTrig(int r, int c)
{


  
  String row = originalMatrix[r];
  char col = row[c];
  if (col == '1')
  {
    bitWrite(TrackOutputs, r, 1);
  }
  else
  {
    bitWrite(TrackOutputs, r, 0);
  }
  SPI.transfer(255);
  SPI.transfer(TrackOutputs);

  digitalWrite(SSout, HIGH);
  digitalWrite(SSout, LOW);

}
