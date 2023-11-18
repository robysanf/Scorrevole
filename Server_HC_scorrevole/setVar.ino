void setVar() {
  /* tabella parametri sullo slave
    3331: // -- PER CAMBIARE LA VELOCITA' MASSIMA
    3332: // -- PER CAMBIARE LA VELOCITA' MINIMA
    3333: // -- PER CAMBIARE LA VELOCITA' IN COLLISIONE  OPEEN CLOSE FAAST SETT1
    3334: // -- PER CAMBIARE LA DIREZIONE DEL MOTORE
    3336: // -- PER CAMBIARE IL VALORE DI ATTRITO
    3337: // -- E' LIBERO
    3338: // -- PER CAMBIARE IL VALORE DI INERZIA
    3339: // -- PER CAMBIARE IL VALORE DI PESO
    3310: // -- PER SETTARE IL VALORE DI POS_APERTO
  */
  int temporaneo = 0;
  String temporaneo2 = "";
  inviaTutti("3311", String(imp * 100));
  delay(10);
  velocita_crocera_MAX = dataRead("velocita_crocera_MAX").toInt() * 1.00;
  delay(10);
  Serial.print("\n Velocita max da file = " + String(velocita_crocera_MAX));
  velocita_crocera_LENTA = dataRead("velocita_crocera_LENTA").toInt() * 1.00;
  Serial.print("\n Velocita crocere lenta da file = " + String(velocita_crocera_LENTA));
  delay(10);
  String velocita_crocera_COL = dataRead("velocita_crocera_COL");
  delay(10);
  inviaTutti("3333", String(velocita_crocera_COL.toInt() * 100));
  delay(10);
  String attrito_arr = dataRead("attrito");
  Serial.print("\n attrito letto  = " + attrito_arr);
  delay(10);
  parseVar2( ATTRITO , attrito_arr);
  inviaOgnunoString("3336", attrito);
  delay(10);
  temporaneo = 0;
  Serial.print("\n Numero_Ante_Slave  = " ); Serial.println(Numero_Ante_Slave);
  delay(10);
  String motore_arr = dataRead("motore");
  delay(10);
  parseVar2( MOTORE , motore_arr);
  inviaOgnunoString("3334", motore);
  String encoder_arr = dataRead("encoder");
  delay(10);
  parseVar2( ENCODER , encoder_arr);
  inviaOgnunoString("3335", encoder);
  delay(10);
  String ritardo_arr = dataRead("ritardo");
  delay(10);
  parseVar2( RITARDO , ritardo_arr);
  String inerzia_arr = dataRead("inerzia");
  delay(10);
  parseVar2( INERZIA , inerzia_arr);
  inviaOgnunoInt("3338", inerzia);
  delay(10);
  String peso_arr = dataRead("peso");
  parseVar2( PESO , peso_arr);
  inviaOgnunoInt("3339", peso);
  delay(10);
  String pos_aperto_arr = dataRead("pos_aperto");
  parseVar2( POS_APERTO , pos_aperto_arr);
  inviaOgnunoLong("3310", pos_aperto);
  Per_Centuale = (pos_aperto[1] - (Distanza * ((Numero_Ante_Slave + 1) - 1))) / 100;
  delay(10);
  // -- ORA POSSO PASSARE AGLI SLAVE LA VELOCITA
  calcola_velocita();

}
