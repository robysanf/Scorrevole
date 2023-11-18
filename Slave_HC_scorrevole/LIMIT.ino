boolean limit() {
  int amp_2 = 0;
  int x1, x2, y1, y2;
  if (tensione < 0) {
    tensione = -tensione;
  }
  if (tensione == 0) {
    tensione = 1;
  }

  if (tensione < 50) {
    x1 = 0;
  }
  else {
    x1 = floor(tensione / 50.00);
  }
  x2 = (x1 + 1) * 50;
  y1 = limiti[x1];
  y2 = limiti[x1 + 1];
  //  Serial.print("\n limit x1 = "); Serial.print(x1);
  //   Serial.print("\n limit x2 = "); Serial.print(x2);
  // Serial.print("\n tensione limit = "); Serial.print(tensione);

  amp_2 = y1 + (tensione - (x1 * 50)) * (y2 - y1) / (x2 - x1 * 50);
  int amp_1 = fai_media();//md.getM2CurrentMilliamps();
  //Serial.print("\n amp1 = "); Serial.print(amp_1);
  // Serial.print("\n amp2 = "); Serial.print(amp_2);
  if (amp_1 >= amp_2 * marginelimite / 100) {
    Serial.print("\n superato limit = "); Serial.print(amp_1);
    Serial.print("\n amp curva = "); Serial.print(amp_2 * marginelimite / 100);
    for (int ic = 0; ic < 20; ic++) {
      Serial.print("corrente " + String(ic) ); Serial.println(" = " + String(corrente[ic]));
    }
    Serial.print("\n tensione = "); Serial.print(tensione);
    return true;
  }
  return false;
} // -- fine limit


void setLimitCurve() {

  //spinge per x millisecodi mantenendo la tensione fissa e memorizzando la corrente massima
  str_limit = "";
  for ( int i = 100; i <= TopSpeed; i = i + 100) {

    int consumo = 0;
    int consumo_max = 0;
    for (int c = 10; c <= i; c = c + 10) {
      md.setM2Speed(c * _Dir * motore);
      consumo = md.getM2CurrentMilliamps();
      if (consumo > 3000) {
        md.setM2Speed(0);
        consumo = 3000;
      }
      consumo_max = max(consumo, consumo_max);
      delay(100);
    }
    md.setM2Speed(0);
    str_limit = str_limit + consumo_max + "--";
    limiti[i / 100] = consumo_max;
  }//for
  str_limit = str_limit.substring(0, str_limit.length() - 1) ; //verificare il length-1
}


void spacchetta_limit(String str) {
  char list[255];
  str.toCharArray(list, 255);
  char * pch;

  pch = strtok (list, "--");
  int lim = String(pch).toInt();
  limiti[1] = lim;
  lim = 0;
  for (int i = 2; i < 13; i++) {
    lim = 0;
    pch = strtok (NULL, "--");
    lim = String(pch).toInt();
    limiti[i] = lim;
  }

}

int fai_media() {

  conta_corrente = conta_corrente + 1;
  if (conta_corrente > 19) {
    conta_corrente = 0;
  }
  corrente[conta_corrente] = md.getM2CurrentMilliamps();
  int tot = 0;
  for (int i = 0; i < 20; i++) {
    tot = tot + corrente[i];
  }
  return tot / 20;
}
