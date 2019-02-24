void read74HC165()
{
  digitalWrite (Load, LOW);        // - Read the push Button state into the 74HC165 SPI Reg
  digitalWrite (Load, HIGH);       // - drop Load state
  SPI.beginTransaction( Settings165 );
  digitalWrite (SSin, LOW);        // - Enable 74HC165 / Clock
  SPI.transfer(Buttonsbuffer, sizeof(Buttonsbuffer));
  bool changed = false;
  for (int i = 0; i < sizeof(Buttonsbuffer); i++)
  {
    if (Buttonsbuffer[i] != ButtonsbufferOld[i])
    {
      changed = true;
      ButtonsbufferOld[i] = Buttonsbuffer[i];
    }
  }
  if (changed)
  {
    Serial.println("changed");
    Serial.println(Buttonsbuffer[0], BIN);
    Serial.println(Buttonsbuffer[1], BIN);
    Serial.println("klar");
  }
  SPI.endTransaction();
}

void CheckButton()
{
  read74HC165() ;
  switch (menu) {
    case 3:
      if ( millis() > selectedDotLastTime + 300)
      {

        Serial.println(selectedDotStatus);
        if (selectedDotStatus)
        {
          //off
          lc.setLed(0, selectedMatricRow, selectedMatricCol, false);
          selectedDotStatus = false;
        }
        else
        {
          //on
          lc.setLed(0, selectedMatricRow, selectedMatricCol, true);
          selectedDotStatus = true;
        }
        selectedDotLastTime = millis();
      }
      break;
  }
  volatile unsigned char result = r.process();
  if (result != 0)
  {
    Serial.println(result);
  }
  if (result) {
    if (result == r.clockwise()) {
      switch (menu) {
        case 2:
          HandleMatrixRowCW();
          break;
        case 3:
          HandleMatrixColCW();
          break;
      }
    }
    else if (result == r.counterClockwise()) {
      switch (menu) {
        case 2:
          HandleMatrixRowCCW();
          break;
        case 3:
          HandleMatrixColCCW();
          break;
      }
    }
  }

  if (r.buttonPressedReleased(25)) {

    switch (menu)
    {
      case 1:
        ClearAll();
        runSequencer = false;
        menu = 2;
        selectedMatricRow = 0;
        lc.setRow(0, selectedMatricRow, B11111111);
        break;
      case 2:
        ClearAll();
        SetStartMatrix();
        menu = 3;
        selectedMatricCol = 0;
        lc.setLed(0, selectedMatricRow, selectedMatricCol, true);
        break;
      case 3:
        ChangeMatrix(selectedMatricRow, selectedMatricCol);
        break;
    }
  }
}

void CheckRotary2()
{
  volatile unsigned char result = r2.process();
  if (result != 0)
  {
    Serial.println(result + "--2");
  }
  if (result) {
    if (result == r2.clockwise()) {
      Serial.println("Clockwise --2");
      bpm--;
      bpmMmillis = (float)60 / (float)bpm * (float)1000;
      //      WriteText7Segment("B-" + String(bpm));
    }
    else if (result == r2.counterClockwise()) {
      Serial.println("Counter-Clockwise  --2");
      bpm++;
      bpmMmillis = (float)60 / (float)bpm * (float)1000;
      //      WriteText7Segment("B-" + String(bpm));
    }
  }
  if (r2.buttonPressedReleased(25)) {
    runSequencer = !runSequencer;
    menu = 1;
    if (runSequencer && menu == 1)
    {
      //      WriteText7Segment("B-" + String(bpm));
    }
  }
}
