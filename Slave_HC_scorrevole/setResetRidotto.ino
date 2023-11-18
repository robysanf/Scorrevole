void set_reset_chiudo() {
  velocita_crocera = 0 ;
  v_attuale = 0;
  iCrocera = 0;
  Stato_Anta[0] = 'V';
  //lento = 0;
  _Dir = 0;
  set = 0;
  //solopassaggio = false;
  porta_tutta_chiusa = false;
  porta_tutta_aperta = false;

  //digitalWrite (RELAY1, HIGH);// TIRO SU IL DROPBOLT  LOW
  
  digitalWrite(4, HIGH); // ABILITA I MOTORI
  md.setM1Speed(400);
  md.setM2Speed(0);
  int i = 0;
  // ACCELERO
  int pos_vecchio = 0;
  velocita_crocera = velocita_crocera_SET; // POTREI METTERE velocita_crocera_SET UGUALE ALLA velocita_crocera_MIN COSI' RISPARMIO UNA VARIABILE E MEMORIZZO LO SFORZO ALLA VELICITA' PIU BASSA
  for ( i = -70; i >= -TopSpeed ; i = i - 1) {
    md.setM2Speed(i * motore);
    //Serial.print("\n motore ="); Serial.print(motore);
    tensione = i + 1;
    if (abs(i) > 850 && abs(pos - pos_vecchio ) <= 1 ) {
      // -- QUESTA POTREBBE ESSERE LA PESEUDO VELOCITA' PER CAPIRE CHE SE A 500(lo possiamo anche alzare)
      // -- NON CAMBIA IL POS ALLORA SIAMO BLOCCATI CONTRO IL FINECORSA
      Serial.println("pos invariato reset chiudo stop");
      ferma_WARD(30);
      return;
    }
    pos_vecchio = pos;
    if (limit()) {
      Serial.println("limit acc reset chiudo stop");
      ferma_WARD(30);

      return;
    }
    if  (crocera(1)) {
      Serial.print("\n RAGGIUNTA VELOCITà CROCERA , TENSIONE = ");
      Serial.println(tensione);
      break;
    }
    Ascolta_Master();
    if (str == 2221 || str == 2223 ) {
      Serial.print("azione stop");
      ferma_WARD(7);
      str = 0;
      return;
    }
    delay(2);
  }
  v_attuale = i;
  tensione = i;
  Stato_Anta[0] = 'V';
  int tempo_chiudi = 0;
  pos_vecchio = 0;
  while (true) {            // STO CHIUDENDO
    _Dir = -1;                    // MI SERVE PER IL CONTROLLO DELLA VELOCITA'
    delay(1);
    //amp = amp + md.getM2CurrentMilliamps();
    // if(amp<50){Serial.print("no consumo ");break;}          // SE NON HO CONSUMO ... QUALCOSA NON VA ESCO DAL SET_RESET
    velocita_misurata = Tachi_Metro();
    if (velocita_misurata < velocita_crocera * attrito * 0.6) {
      Serial.print("SET RESET CHIUDO VEL BASSA stop");
      ferma_WARD(30);
      break;
    }
    if (limit()) {
      Serial.print("limit stop set chiudo");
      ferma_WARD(30);
      delay(2000);
      break;
    }
    if (tempo_chiudi > 11000) {
      Serial.println(" stop tempo_chiudi < 11000");
      ferma_WARD(30);
      break;
    }
    if (abs(pos - pos_vecchio ) <= 1 ) {
      // -- QUESTA POTREBBE ESSERE LA PESEUDO VELOCITA' PER CAPIRE CHE SE A 500(lo possiamo anche alzare)
      // -- NON CAMBIA IL POS ALLORA SIAMO BLOCCATI CONTRO IL FINECORSA
      Serial.println("pos invariato reset chiudo stop");
      ferma_WARD(30);
      break;
    }
    pos_vecchio = pos;

    Ascolta_Master();
    if (str == 2221 || str == 2223 ) {
      Serial.print("PREMUTO PULSANTE stop set chiudo");
      ferma_WARD(7);
      str = 0;
      return;
    }
    delay(5);
    tempo_chiudi++;
  }
}

void set_reset_pos() {

  digitalWrite(4, HIGH);
  for (int i = 0 ; i > -300 ; i--) {
    md.setM2Speed(i * motore);
    delay(1);
  }
  //tensione = -300;
  delay(150);
  ferma_WARD(7);
  //tensione = 1;
  digitalWrite(4, LOW);
  delay(10); // FORSE QUI FUNZIONA MEGLIO
  pos = 0;
  delay(100); // DEVO VALUTARE SE SERVE
  digitalWrite(4, HIGH);
  Serial.print("TROVATA POSIZIONE ZERO");
  if (set == 0) {
    Stato_Anta[0] = 'O';
  }
  delay(1); // DEVO VALUTARE SE SERVE
}



void set_reset_apro() { // adesso tutto è fermo di nuovo
  // ora apro contemporaneamente le due ante fino alla fine di entrambe
  // ACCELERO
  Stato_Anta[0] = 'V';
  digitalWrite(4, HIGH); // ABILITA I MOTORI
  Serial.print("\n apro");
  int i;
  // ACCELERO
  velocita_crocera = velocita_crocera_SET;
  for ( i = 70; i <= TopSpeed; i = i + 1) {
    md.setM2Speed(i * motore);
    tensione = i + 1;
    if (limit()) {
      ferma_WARD(30);
      break;
    }
    if  (crocera(1)) {
      break;
    }
    delay(2);
  }
  v_attuale = i;
  tensione = i;
  Stato_Anta[0] = 'V';
  Serial.print("\n sto aprendo ");
  // STO APRENDO

  while (true) {
    fai_media();
    _Dir = 1;                  // MI SERVE PER IL CONTROLLO DELLA VELOCITA'
    velocita_misurata = Tachi_Metro();
    if (velocita_misurata < velocita_crocera * attrito) {
      ferma_WARD(30);
      break;
    }
    if (limit()) {
      ferma_WARD(30);
      break;
    }

  }

  delay(1);

  Stato_Anta[0] = 'F';
  // FATTO, TROVATA POSIZIONE TUTTO APERTO
  //set = 1;
}
