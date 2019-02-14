/* Set the status of a single Led.
   Params :
     addr  address of the display
     row   the row of the Led (0..7)
     col   the column of the Led (0..7)
     state If true the led is switched on, if false it is switched off
*/
void WriteText7Segment(String text)
{

int lost=8-(text.length());
for(int i=0; i<lost; i++)
{
  text=text+' ';
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
    char* row = originalMatrix[i];
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


void ChangeMatrix(int r, int c)
{
   Serial.println(String(r)+":"+String(c));

   char* row = originalMatrix[r];
    Serial.println(row);
   char point = row[c];
   if(point=='1')
   {
    point='0';
   }
   else
   {
    point='1';
   }
   row[c]=point;
   originalMatrix[r]=row;
   
      char* row2 = originalMatrix[r];
    Serial.println(row2);
}

void ResetMatrixCol(int col)
{
  for (int i = 0; i < 8; i++)
  {
    char* row = originalMatrix[i];
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

  byte clearAll[] =
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  };


  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, clearAll[i]);
  }

}

void FillAll()
{

  byte clearAll[] =
  {
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111
  };


  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, clearAll[i]);
  }

}


void sinvader1b()
{

  byte invader1b[] =
  {
    B00000000,  // second frame of invader #1

    B11111111,
    B00000000,
    B11111111,
    B00000000,
    B11111111,
    B00000000,
    B11111111
  };

  for (int i = 0; i < 8; i++)
  {
    // lc.setRow(0,i,invader1b[i]);



    /* Set the status of a single Led.
       Params :
         addr  address of the display
         row   the row of the Led (0..7)
         col   the column of the Led (0..7)
         state If true the led is switched on, if false it is switched off
    */

    lc.setLed(0, i, 0, true);
    lc.setLed(0, i, 5, true);
  }

}
