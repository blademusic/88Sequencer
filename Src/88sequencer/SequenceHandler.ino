void HandleMatrixRowCW()
{
  lc.clearDisplay(0);
  selectedMatricRow++;
  if (selectedMatricRow == 8)
  {
    selectedMatricRow = 0;
  }
  lc.setRow(0, selectedMatricRow, B11111111);
}
void HandleMatrixRowCCW()
{
  lc.clearDisplay(0);
  selectedMatricRow--;
  if (selectedMatricRow == -1)
  {
    selectedMatricRow = 7;
  }
  lc.setRow(0, selectedMatricRow, B11111111);
}
void HandleMatrixColCW()
{
  SetStartMatrix();
  selectedMatricCol++;
  if (selectedMatricCol == 8)
  {
    selectedMatricCol = 0;
  }
  lc.setLed(0, selectedMatricRow, selectedMatricCol, true);
}
void HandleMatrixColCCW()
{
  SetStartMatrix();
  selectedMatricCol--;
  if (selectedMatricCol == -1)
  {
    selectedMatricCol = 7;
  }
  lc.setLed(0, selectedMatricRow, selectedMatricCol, true);
}
void ChangeMatrix(int r, int c)
{
  Serial.println(String(r) + ":" + String(c));

  String row = originalMatrix[r];
  Serial.println(row);
  char point = row[c];
  if (point == '1')
  {
    point = '0';
  }
  else
  {
    point = '1';
  }
  row[c] = point;
  originalMatrix[r] = row;

  String row2 = originalMatrix[r];
  Serial.println(row2);
}
