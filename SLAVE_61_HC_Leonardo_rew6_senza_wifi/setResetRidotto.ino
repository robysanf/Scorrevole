void set_reset_chiudo() {  // INIZIO IL SET:
  // IMPOSTO TUTTE LE VARIABILI A 0
  digitalWrite(4, HIGH);  // ABILITA I MOTORI
  digitalWrite(5, HIGH);  // ALZA IL DROP BOLT
  md.setM2Speed(0);
  Stato_Anta[0] = 'F';
  velocita_crocera = 0;
  v_attuale = 0;
  iCrocera = 0;
  Stato_Anta[0] = 'V';
  _Dir = -1;
  set = 0;
  porta_tutta_chiusa = false;
  porta_tutta_aperta = false;
  digitalWrite(4, HIGH);  // ABILITA I MOTORI
  md.setM2Speed(0);
  int i = 0;
  velocita_crocera = velocita_crocera_SET;    // POTREI METTERE velocita_crocera_SET UGUALE ALLA velocita_crocera_MIN COSI' RISPARMIO UNA VARIABILE E MEMORIZZO LO SFORZO ALLA VELICITA' PIU BASSA
  for (i = 70; i <= TopSpeed; i = i + 1) {  // ACCELERO
    md.setM2Speed(i * motore*_Dir);
    tensione = i + 1;
    if (limit_senza_curva(1)) { // il 2 l'ho messo perchè in acccelerazione il consumo aumenta di suo
      Serial.println("limit acc reset chiudo stop");
      ferma_WARD(30);
      return;
    }
    if (abs(i) > 650 && abs(pos - pos_vecchio) <= 1) {// -- QUESTA POTREBBE ESSERE LA PESEUDO VELOCITA' PER CAPIRE CHE SE A 650 (lo possiamo anche alzare) NON CAMBIA IL POS ALLORA SIAMO BLOCCATI CONTRO IL FINECORSA
      Serial.println("pos invariato reset chiudo stop");
      ferma_WARD(30);
      return;
    }
    pos_vecchio = pos;
    if (crocera(1)) {
      Serial.print("\n RAGGIUNTA VELOCITà CROCERA , TENSIONE = ");
      Serial.print(tensione);
      break;
    }
    Ascolta_Master();
    if (str == 2221 || str == 2223) {
      Serial.print("azione stop");
      ferma_WARD(7);
      str = 0;
      return;
    }
    delay(2);
    v_attuale = i;
  }
  
  tensione = i;
  Stato_Anta[0] = 'V';
  int tempo_chiudi = 0;
  pos_vecchio = 0;
  int conteggio_aggiustamenti = 0;
  while (true) {  // STO CHIUDENDO
    delay(1);
    if (fai_media() < 50) {// SE NON HO CONSUMO ... QUALCOSA NON VA ESCO DAL SET_RESET
      Serial.print("no consumo ");
      ferma_WARD(30);
      break;
    }  
    velocita_misurata = Tachi_Metro();
    if (velocita_misurata < velocita_crocera * attrito ) {
      conteggio_aggiustamenti++;
      if (conteggio_aggiustamenti > 3) {
        Serial.print("SET RESET CHIUDO VEL BASSA stop");
        ferma_WARD(30);
        break;
      }
      v_attuale = (v_attuale + 15) * motore *_Dir;
      md.setM2Speed( v_attuale );
      Serial.print("v_attuale :");Serial.println(v_attuale);
    }
    if (limit_senza_curva(5)) {
      ferma_WARD(30);
      break;
    }
    if (tempo_chiudi > 9000) {
      Serial.println(" stop tempo_chiudi < 9000");
      ferma_WARD(30);
      break;
    }
    Serial.print("pos vecchio - pos = ");
    Serial.println(abs(pos - pos_vecchio));
    if (abs(pos - pos_vecchio) <= 1) {
      // -- QUESTA POTREBBE ESSERE LA PESEUDO VELOCITA' PER CAPIRE CHE SE A 500(lo possiamo anche alzare)
      // -- NON CAMBIA IL POS ALLORA SIAMO BLOCCATI CONTRO IL FINECORSA
      Serial.println("pos invariato reset chiudo stop");
      ferma_WARD(30);
      break;
    }
    pos_vecchio = pos;

    Ascolta_Master();
    if (str == 2221 || str == 2223) {
      Serial.print("PREMUTO PULSANTE stop set chiudo");
      ferma_WARD(7);
      str = 0;
      return;
    }
    delay(5);
    tempo_chiudi++;
  }
  // in teoria abbiamo chiuso
}

void set_reset_pos() {
  digitalWrite(4, HIGH);
  for (int i = 0; i > -300; i--) {
    md.setM2Speed(i * motore);
    delay(1);
  }
  ferma_WARD(7);
  digitalWrite(4, LOW);
  delay(200);  // FORSE QUI FUNZIONA MEGLIO
  pos = 0;
  digitalWrite(5, LOW); // ABBSSO IL DROP-BOLT
  Serial.print("TROVATA POSIZIONE ZERO");
  if (set == 0) {
    Stato_Anta[0] = 'O';
  }
  delay(1);  // DEVO VALUTARE SE SERVE
}



void set_reset_apro() {  // adesso tutto è fermo di nuovo
    // IMPOSTO TUTTE LE VARIABILI A 0
  digitalWrite(4, HIGH);  // ABILITA I MOTORI
  md.setM2Speed(0);
  Stato_Anta[0] = 'F';
  velocita_crocera = 0;
  v_attuale = 0;
  iCrocera = 0;
  Stato_Anta[0] = 'V';
  _Dir = 1;
  set = 0;
  //solopassaggio = false;
  porta_tutta_chiusa = false;
  porta_tutta_aperta = false;
  digitalWrite(4, HIGH);  // ABILITA I MOTORI
  md.setM2Speed(0);
  int i = 0;
  velocita_crocera = velocita_crocera_SET;    // POTREI METTERE velocita_crocera_SET UGUALE ALLA velocita_crocera_MIN COSI' RISPARMIO UNA VARIABILE E MEMORIZZO LO SFORZO ALLA VELICITA' PIU BASSA
  for (i = 70; i >= TopSpeed; i = i + 1) {  // ACCELERO
    md.setM2Speed(i * motore*_Dir);
    tensione = i + 1;
    if (limit_senza_curva(1)) { // il 2 l'ho messo perchè in acccelerazione il consumo aumenta di suo
      Serial.println("limit acc reset chiudo stop");
      ferma_WARD(30);
      return;
    }
    if (abs(i) > 650 && abs(pos - pos_vecchio) <= 1) {// -- QUESTA POTREBBE ESSERE LA PESEUDO VELOCITA' PER CAPIRE CHE SE A 650 (lo possiamo anche alzare) NON CAMBIA IL POS ALLORA SIAMO BLOCCATI CONTRO IL FINECORSA
      Serial.println("pos invariato reset chiudo stop");
      ferma_WARD(30);
      return;
    }
    pos_vecchio = pos;
    if (crocera(_Dir)) {
      Serial.print("\n RAGGIUNTA VELOCITà CROCERA , TENSIONE = ");
      Serial.print(tensione);
      break;
    }
    Ascolta_Master();
    if (str == 2221 || str == 2223) {
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
  int conteggio_aggiustamenti = 0;
  while (true) {  // STO CHIUDENDO
    delay(1);
    if (fai_media() < 50) {// SE NON HO CONSUMO ... QUALCOSA NON VA ESCO DAL SET_RESET
      Serial.print("no consumo ");
      ferma_WARD(30);
      break;
    }  
    velocita_misurata = Tachi_Metro();
    if (velocita_misurata < velocita_crocera * attrito * 0.6) {
      conteggio_aggiustamenti++;
      if (conteggio_aggiustamenti > 3) {
        Serial.print("SET RESET CHIUDO VEL BASSA stop");
        ferma_WARD(30);
        break;
      }
      md.setM2Speed(v_attuale + 15 * _Dir);
    }
    if (limit_senza_curva(5)) {
      ferma_WARD(30);
      break;
    }
    if (tempo_chiudi > 9000) {
      Serial.println(" stop tempo_chiudi < 9000");
      ferma_WARD(30);
      break;
    }
    Serial.print("pos vecchio - pos = ");
    Serial.println(abs(pos - pos_vecchio));
    if (abs(pos - pos_vecchio) <= 1) {
      // -- QUESTA POTREBBE ESSERE LA PESEUDO VELOCITA' PER CAPIRE CHE SE A 500(lo possiamo anche alzare)
      // -- NON CAMBIA IL POS ALLORA SIAMO BLOCCATI CONTRO IL FINECORSA
      Serial.println("pos invariato reset chiudo stop");
      ferma_WARD(30);
      break;
    }
    pos_vecchio = pos;

    Ascolta_Master();
    if (str == 2221 || str == 2223) {
      Serial.print("PREMUTO PULSANTE stop set chiudo");
      ferma_WARD(7);
      str = 0;
      return;
    }
    delay(5);
    tempo_chiudi++;
  }
  // FATTO, TROVATA POSIZIONE TUTTO APERTO
  //set = 1;
}
