void Sequence()
{
  long now = millis();

  if (now >= (bpmLastRun + bpmMmillis))
  {
    Serial.println(String(now));
    loopLed(sequencerStep);
    sequencerStep++;
    if (sequencerStep == 8)
    {
      sequencerStep = 0;
    }
    bpmLastRun = now;
  }





}
