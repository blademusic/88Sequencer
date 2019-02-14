/* Set the status of a single Led.
   Params :
     addr  address of the display
     row   the row of the Led (0..7)
     col   the column of the Led (0..7)
     state If true the led is switched on, if false it is switched off
*/
void WriteText7Segment(String text)
{

  int lost = 8 - (text.length());
  for (int i = 0; i < lost; i++)
  {
    text = text + ' ';
  }


  char copy[9];
  text.toCharArray(copy, 9);
  int pos = 8;
  for (int i = 0; i < 8; i++)
  {
    pos--;
    if (copy[i] == ' ')
    {
      lc.setChar(1, pos, ' ', false);
    }
    else
    {
      lc.setChar(1, pos, copy[i], false);
    }
  }
}


void SetStartMatrix()
{
  for (int i = 0; i < 8; i++)
  {
    String row = originalMatrix[i];
    for (int j = 0; j < 8; j++)
    {
      char pos0 = row[j];
      if (pos0 == '1')
      {
        lc.setLed(0, i, j, true);
      }
      else
      {
        lc.setLed(0, i, j, false);
      }
    }
  }
}




void ResetMatrixCol(int col)
{
  for (int i = 0; i < 8; i++)
  {
    String row = originalMatrix[i];
    char pos0 = row[col];
    if (pos0 == '1')
    {
      lc.setLed(0, i, col, true);
    }
    else
    {
      lc.setLed(0, i, col, false);
    }
  }
}



void loopLed(int i)
{
  if (i == 0)
  {
    //clear all
    //ClearAll();
    //reset 8
    ResetMatrixCol(7);
    for (int l = 0; l < 8; l++)
    {
      lc.setLed(0, l, i, true);
    }

  }
  else
  {
    ResetMatrixCol(i - 1);
    for (int k = 0; k < 8; k++)
    {
      lc.setLed(0, k, i, true);
    }

  }
}



void ClearAll()
{


  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, B00000000);
  }

}

void FillAll()
{




  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, B11111111);
  }

}
