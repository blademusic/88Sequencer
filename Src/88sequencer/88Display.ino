/* Set the status of a single Led.
   Params :
     addr  address of the display
     row   the row of the Led (0..7)
     col   the column of the Led (0..7)
     state If true the led is switched on, if false it is switched off
*/
void SetStartMatrix()
{
  for (int i = 0; i < 8; i++)
  {
    String row = originalMatrix[i];
    for (int j = 0; j < 16; j++)
    {
      int matrix = 0;
      if (j > 7)
      {
        matrix = 1;
      }
      char pos0 = row[j];

      if (pos0 == '1')
      {
        if (matrix == 0)
        {
          lc.setLed(matrix, i, j, true);
        }
        else
        {
          lc.setLed(matrix, i, j - 8, true);
        }
      }
      else
      {
        if (matrix == 0)
        {
          lc.setLed(matrix, i, j, false);
        }
        else
        {
          lc.setLed(matrix, i, j - 8, false);
        }
      }
    }
  }
}




void ResetMatrixCol(int r, int col, int dir)
{
  if (dir == 1)
  {
    if (col == 0)
    {
      col = 15;
    }
    else
    {
      col--;
    }
  }
 else if (dir == 2)
  {
    if (col == 15)
    {
      col = 0;
    }
    else
    {
      col++;
    }
  }

  int matrix = 0;
  if (col > 7)
  {
    matrix = 1;
  }
  int c = col;

  String row = originalMatrix[r];
  char pos0 = row[c];
  if (pos0 == '1')
  {
    if (matrix == 0)
    {
      lc.setLed(matrix, r, c, true);
    }
    else
    {
      lc.setLed(matrix, r, c - 8, true);
    }

  }
  else
  {
    if (matrix == 0)
    {
      lc.setLed(matrix, r, c, false);
    }
    else
    {
      lc.setLed(matrix, r, c - 8, false);
    }
  }

}



void LoopLeds()
{
  for (int i = 0; i < 8; i ++ )
  {
    switch (i)
    {
      case 0:
        LoopLedRow(i, row0Step,row0StepDir);
        break;
      case 1:
        LoopLedRow(i, row1Step,row1StepDir);
        break;
      case 2:
        LoopLedRow(i, row2Step,row2StepDir);
        break;
      case 3:
        LoopLedRow(i, row3Step,row3StepDir);
        break;
      case 4:
        LoopLedRow(i, row4Step,row4StepDir);
        break;
      case 5:
        LoopLedRow(i, row5Step,row5StepDir);
        break;
      case 6:
        LoopLedRow(i, row6Step,row6StepDir);
       
        break;
      case 7:
        LoopLedRow(i, row7Step,row7StepDir);
        break;

    }
  }
}
void LoopLedRow(int r, int rowstep,int dir)
{
  ResetMatrixCol(r, rowstep,dir);
  int matrix = 0;
  if (rowstep > 7)
  {
    matrix = 1;
  }
  if (matrix == 0)
  {
    lc.setLed(matrix, r, rowstep, true);
  }
  else
  {
    lc.setLed(matrix, r, rowstep - 8, true);
  }
}


void ClearAll()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, B00000000);
    lc.setRow(1, i, B00000000);
  }
}
void FillAll()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, B11111111);
    lc.setRow(1, i, B11111111);
  }
}
