void controlla_assorbimento(int vel_check) {
  if ( digitalRead(A7) == LOW || Stato_Alzata[0] != 'U') {
    Alza_Anta();
  }
   int f=99;
  //digitalWrite(Rele_Blocco, LOW);
  digitalWrite(4, HIGH);                                    // ABILITA I MOTORI
  if (Stato_Anta[0] == 'T') {                                // SE TUTTO CHIUSO APRO
    _Dir = 1;
    f=0;
  }
  else if (Stato_Anta[0] == 'A') {                           // SE TUTTO APERTO CHIUDO
    f=99;
    _Dir = -1;
  }
  else {
    return;                                                 // altrimenti non finziona
  }
  int i = 0;
  int limiteora;
  if ( vel_check > 180){
    vel_check = 180;
  }
  if ( vel_check < 40){
    vel_check = 40;
  }
  velocita_crocera = vel_check;
  for ( i = 70; i <= TopSpeed; i = i + 5) {
     Serial.print("i == ");Serial.println(i);
    md.setM2Speed(i * motore * _Dir);
    tensione = i + 1;
    limiteora = md.getM2CurrentMilliamps();
    if (limiteora > 3500) {
      Serial.print("in accellerazione controlla_assorbimento limite  di " + String(limiteora) + " superato");
       v_attuale=i;
      ferma_WARD(30);
      return;
    }
    if  (crocera(1)) {
      Serial.print("RAGGIUNTA VELOCITA' CROCERA , TENSIONE = "); Serial.println(tensione);
      v_attuale=i;
      break;
    }
    Ascolta_Master();
    if (str == 2221 || str == 2223 ) {
      Serial.println("azione stop annulla test controlla_assorbimento");
       v_attuale=i;
      ferma_WARD(7);
      
      str = 0;
      return;
    }
     v_attuale=i;
    delay(1);
  }
   Serial.print("BeeP ");Serial.print(pos);Serial.print(" - ");Serial.println(_Dir);
 
  int passo = pos_aperto / 100;
  while ((pos < pos_aperto - spazioRallenta && _Dir == 1) || (pos > spazioRallenta && _Dir == -1)) {
    if(_Dir==1){
   if (pos > f * passo ) {
       Ascolta_Master();
        if (str == 2221 || str == 2223 ) {
          ferma_WARD(7); str = 0; return;
          delay(10);
        }
        limiteora = md.getM2CurrentMilliamps();
        if (limiteora > 3500) {
          Serial.println("in controlla_assorbimento limite  di " + String(limiteora) + " superato");
          ferma_WARD(30);
          return;
        }
     array_assorbimento[f] = fai_media();
    f++;
  }
  }
  if(_Dir==-1) {
    Serial.print("f ==");Serial.println(f);
    Serial.print("f*passo ==");Serial.println(f*passo);
    Serial.print("pos ==");Serial.println(pos);
     if (pos < f * passo ) {
       Ascolta_Master();
        if (str == 2221 || str == 2223 ) {
          ferma_WARD(7); str = 0; return;
          delay(10);
        }
        limiteora = md.getM2CurrentMilliamps();
        if (limiteora > 3500) {
          Serial.println("in controlla_assorbimento limite  di " + String(limiteora) + " superato");
          ferma_WARD(30);
          return;
        }
     array_assorbimento[f] = fai_media();
    f--;
  }
  }
 /*   
    for (int i = 0 ; i <= 999; i++) {
      if (pos < i * passo + spazioRallenta) {
        Ascolta_Master();
        if (str == 2221 || str == 2223 ) {
          ferma_WARD(7); str = 0; return;
          delay(10);
        }
        limiteora = md.getM2CurrentMilliamps();
        if (limiteora > 3500) {
          Serial.println("in controlla_assorbimento limite  di " + String(limiteora) + " superato");
          ferma_WARD(30);
          return;
        }
        array_assorbimento[i] = fai_media();
      }
    }*/
  }
  Serial.println("fine controlla_assorbimento");
  ferma_WARD(7);
}

void stampa_assorbimento() {
  Serial.println("stampo gli assorbimenti:");
  for ( int i = 0; i <= 99; i++) {
    Serial.println("   consumo settore " + String(i) + " = " + String(array_assorbimento[i]));
  }
}
