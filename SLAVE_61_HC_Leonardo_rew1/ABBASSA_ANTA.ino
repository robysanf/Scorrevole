void Abbassa_Anta() {
  //ferma_WARD(30);
  Stato_Alzata[0] = 'D';
  digitalWrite(4, LOW);
  return; 
}

void Alza_Anta() {
  //ferma_WARD(30);
  Stato_Alzata[0] = 'U';
  digitalWrite(4, LOW);
  return;
}
