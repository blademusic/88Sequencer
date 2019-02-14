void CheckButton()
{
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:

      Serial.println("on");
       SetStartMatrix();


    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(300);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  CheckRotary2();

  volatile unsigned char result = r.process();
  if (result != 0)
  {
    Serial.println(result);
  }
  if (result) {
    if (result == r.clockwise()) {
      switch (menu) {
        case 2:
          lc.clearDisplay(0);
          selectedMatricRow++;
          if (selectedMatricRow == 8)
          {
            selectedMatricRow = 0;
          }
          lc.setRow(0, selectedMatricRow, B11111111);
          break;
        case 3:
          SetStartMatrix();
          selectedMatricCol++;
          if (selectedMatricCol == 8)
          {
            selectedMatricCol = 0;
          }
          lc.setLed(0, selectedMatricRow, selectedMatricCol,true);
          break;
      }
    }
    else if (result == r.counterClockwise()) {
      switch (menu) {
        case 2:
          lc.clearDisplay(0);
          selectedMatricRow--;
          if (selectedMatricRow == -1)
          {
            selectedMatricRow = 7;
          }
          lc.setRow(0, selectedMatricRow, B11111111);
          break;
        case 3:
          SetStartMatrix();
          selectedMatricCol--;
          if (selectedMatricCol == -1)
          {
            selectedMatricCol = 7;
          }
          lc.setLed(0, selectedMatricRow, selectedMatricCol,true);
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
        lc.setLed(0, selectedMatricRow, selectedMatricCol,true);
        break;
      case 3:
        ChangeMatrix(selectedMatricRow, selectedMatricCol);
        SetStartMatrix();
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
      WriteText7Segment("B-" + String(bpm));
    }
    else if (result == r2.counterClockwise()) {
      Serial.println("Counter-Clockwise  --2");
      bpm++;
      bpmMmillis = (float)60 / (float)bpm * (float)1000;
      WriteText7Segment("B-" + String(bpm));
    }
  }
  if (r2.buttonPressedReleased(25)) {
    runSequencer = !runSequencer;
    menu = 1;
    if (runSequencer && menu == 1)
    {
      WriteText7Segment("B-" + String(bpm));
    }
  }
}
