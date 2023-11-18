void ferma_WARD() {
  int i;
  for ( i = 1; i <= Numero_Ante_Slave  ; i = i + 1)
  {
    inVia(i, "2221",3841); delay(10);
    apertura = false;
    solopassaggio = false;
    _Dir = 0;
    delay(1);
  }
  char w[5] = {'s', 't', 'o', 'p', '/'};
  //   ordina_Web(w);
}



void fast_ward() {
  int i;
  for ( i = 1; i <= Numero_Ante_Slave  ; i = i + 1)
  { //ordina("2225/", Ante_Slave[i], 12);  // -- FAST PER NON ANDARE IN COLLISIONE
    inVia(i, "2225",89365);
    Serial.print("fast,"); Serial.print(i); Serial.println(",18");
    delay(1);
  }
}
