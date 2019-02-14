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
  else if(dir==2)
  {
    stepinput--;
    if(stepinput==-1)
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

void SequenceOutput(int stepNr)
{

  for (int i = 0; i < 8; i++)
  {

    String row = originalMatrix[i];

    char point = row[stepNr];
    Serial.println(point);
    if (point == '1')
    {
      //on
      switch (i)
      {
        case 0:
          digitalWrite(OutPut0, HIGH);
          break;
        case 1:
          digitalWrite(OutPut1, HIGH);
          break;

      }
    }
    else
    {
      //off
      switch (i)
      {
        case 0:
          digitalWrite(OutPut0, LOW);
          break;
        case 1:
          digitalWrite(OutPut1, LOW);
          break;

      }
    }




  }
}
