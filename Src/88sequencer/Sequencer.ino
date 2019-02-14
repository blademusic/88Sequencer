void Sequence()
{
  long now = millis();

  if (now >= (bpmLastRun + bpmMmillis))
  {

    loopLed(sequencerStep);
    SequenceOutput(sequencerStep);
    sequencerStep++;
    if (sequencerStep == 8)
    {
      sequencerStep = 0;
    }
    bpmLastRun = now;
  }





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
      switch(i)
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
         switch(i)
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
