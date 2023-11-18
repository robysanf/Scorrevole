boolean button_pressed() {
  if ( (digitalRead(CHIUDI) == LOW || digitalRead(APRI) == LOW || digitalRead(STOP) == LOW) && set == 0 ) {
    return true;
  }
  return false;
}
//*******************************************
//   CALCOLA VELOCITA'
//*******************************************
void calcola_velocita() {
  int temporaneo;
  String temporaneo2;
  float costante;                            // -- RAPPRESENTA LA DIFFERENZA DI VELOCITA' TRA LE ANTE
  char _temporaneo[32];
  int i;
 
  costante = 0;
  Serial.print("\n costante = "); Serial.println(costante);
  for (i = 1; i <= Numero_Ante_Slave; i = i + 1) {
    Serial.print("\n costante i = "); Serial.println(i);
    if (ritardo[i] == NULL) {
      ritardo[i] = 1;
      Serial.print("\n costante i2 = ");
      Serial.println(i);
    }
    Serial.println("\n maxspeed = " + String(velocita_crocera_MAX));
    velocita_crocera_MAX_slave_[i] = velocita_crocera_MAX - ((i - 1) * costante) * ritardo[i] ;
    temporaneo = velocita_crocera_MAX_slave_[i] * 100; //gestico i decimali come ultime due cife senza scrivere la virgola  54,34 --> 5434
    temporaneo2 = "3331" + String(temporaneo);
    inVia(i, temporaneo2,87581);
    attendi_risposta(i, 10, temporaneo2);
    delay(10);
     //inVia(i, "0000",6235);
    Serial.print("\n velocita_crocera_MAX_slave_["); Serial.print(i); Serial.print("] = "); Serial.println(velocita_crocera_MAX_slave_[i]);
  }
  
  Serial.println("\n Ricevi9 = " + String(velocita_crocera_LENTA));
  Serial.print("\n Spazio_Collisione default = "); Serial.print(Spazio_Collisione_hold);
  Serial.println("\n maxspeed/40 = " + String(velocita_crocera_MAX / 40.00));
 // Serial.println("\n tot = " + String(Spazio_Collisione_hold * velocita_crocera_MAX / 40.00));
  // lo spazio collisione cambia in base alla velocità
 // Spazio_Collisione = Spazio_Collisione_hold * (1 + velocita_crocera_MAX / 70);
  Serial.print("\n Spazio_Collisione calcolo = "); Serial.print(Spazio_Collisione);
}

//*******************************************
//   SET_RESET_RIDOTTO
//*******************************************
void set_reset_ridotto() {
  // if(!dipendente && check_dipendente(3000)){ Serial.println("www");return; }
  boolean fatto = false;
  for ( int i = 1; i <= Numero_Ante_Slave   ; i = i + 1) {
    inVia(i, "1111",258);
    attendi_risposta(i,10,"1111");
    Serial.print("\n ORDINO ALLA ANTA "); Serial.print(i); Serial.print(" DI CHIUDERE");
    delay(200);
  }
  Serial.print("\n ASPETTO STATO ");
  int cont_r = 0;
  while (true) {                 // -- aspetto che chiudano tutte le ante
    delay(20);
    
    if (cont_r > 1500 ) {
      return;
    }
    Serial.print("\n aspetto ");  Serial.print(" DI CHIUDERE");
    for ( int i = 1; i <= Numero_Ante_Slave   ; i = i + 1) {
      inVia(i, "0000",78382);
      ricEvi();
      Serial.print(" stato anta"); Serial.print(i); Serial.println(" - "); Serial.println(Stato_Anta[i]);
      if (Stato_Anta[i] != "R") {
        // -- SE tutte le ante sono ferme esco
        break;
      }
      if (i == Numero_Ante_Slave) {
        fatto = true;
      }
    }
    cont_r++;
    delay(50);
    if (fatto == true) {
      fatto = false;
      break;
    }
  }
  // -- se arrivo qua ordino di fare il giochetto con la ginghia setp
  for ( int i = 1; i <= Numero_Ante_Slave   ; i = i + 1) {
    inVia(i, "1115",76584); //ordina("1115/",Ante_Slave[i],4);
    attendi_risposta(i,10,"1115");
    Serial.print( "memorizzo il pos_chiuso su anta "); Serial.println(i);
    int cont_O = 0;
    while (true) {
      if (cont_O > 100){
        fatto = false;
        return;
      }
      Serial.print( "Cerco O ");
      ricEvi();

      if (Stato_Anta[i] == "O") {
        Serial.print( "trovato O ");
        fatto = true;
        break;
      }
      cont_O++;
      delay(10);
      inVia(i, "0000",7615);
    }
    delay(150);
  }
  if (fatto == false){
    return;
  }

  // -- ORA DEVO CALCOLARE ANCHE IL VALORE DI COLLISIONE:
  // -- LE COLLISIONI SONO >> Numero_Ante_Slave - 1 ;
  // -- collisione_[i] = pos_aperto[1] - pos_aperto[i+1]

  
  for ( int i = 1; i <Numero_Ante_Slave   ; i = i + 1) {
    collisione_anta_[i] = pos_aperto[i] - pos_aperto[i + 1]; 
    Serial.print("\n collisione_anta_"); Serial.print(i); Serial.print(" = "); Serial.print(collisione_anta_[i]);
    delay(1);
  }
 

 

  for ( int i2 = 1; i2 <= Numero_Ante_Slave  ; i2 = i2 + 1) {
    inVia(i2, "1116",638);
    attendi_risposta(i2,10,"1116");
    delay(150);
  }
  for ( int i2 = 1; i2 <= Numero_Ante_Slave  ; i2 = i2 + 1) {
    inVia(i2, "2222",668);
    attendi_risposta(i2,10,"2222");
    delay(150);
  }
   delay(1000);
   set = 1 ;
  _Dir = 0 ;
}
