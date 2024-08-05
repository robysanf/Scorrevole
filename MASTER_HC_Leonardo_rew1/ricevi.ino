void ricEvi() {
  long e = micros();
  while ( (micros() - tempo_invia) < 150000) {

  }

  char myBuffer[255];
  Serial.print(" ATTESA =========== "); Serial.println(String(micros() - e ));
  if (Serial1.available())
  { Serial.print(" inizio "); Serial.println(millis());
    long oldt = micros();
    int lung = hc12_read(myBuffer, 255);
    myBuffer[lung - 1] = '\0';
    Serial.print(" tempo fine "); Serial.println(String(micros() - oldt));
    Serial.print(" myBuffer = "); Serial.println(myBuffer);
    Abbina_Pacchetto(String(myBuffer));
  }


}


void Abbina_Pacchetto(String varList) {
  //Serial.print(" inizio Traduci: ");Serial.println(varList);

  char list[255];
  varList.toCharArray(list, 255);
  char * pch;
  int num_anta = 0;
  pch = strtok (list, ",");// SONO IO
  int sono_io_slave = String(pch).toInt();
  for (int i = 1; i <= MAX_ANTE; i++) {
    if (Ante_Slave[i] == sono_io_slave) {
      num_anta = i;
      if (My_Buffer[num_anta] == varList) {
        return;
      }

      My_Buffer[num_anta] = varList;
      break;
    }
  }
  Serial.print(" myBuffer = "); Serial.println(varList);
  if (num_anta == 0) {
    return;
  }
  
  //Serial.print(" sono_io_slave = ");Serial.println(sono_io_slave);
  pch = strtok (NULL, ","); // STATO ANTA

  Stato_Anta[num_anta] = String(pch);
  //Serial.print(" Stato_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  if (Stato_Anta[num_anta] == "S") //&& Stato_Anta[num_anta] != Stato_Anta_old[num_anta])
  {
    Serial.print("Emerg S " ); Serial.println(num_anta);
    emergenza_buffer = varList;
    emergenza_chi = num_anta;
    emergenza = true;

  }
  Stato_Anta_old[num_anta] = Stato_Anta[num_anta];
  pch = strtok (NULL, ",");



  Direzione_Anta[num_anta] = String(pch).toInt();
  _Dir = Direzione_Anta[1];
  //Serial.print(" Direzione_Anta[");
  //Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");

  Stato_Alzata[num_anta] = String(pch);
  //Serial.print(" ALZ_Anta = ");Serial.println(Stato_Alzata[num_anta]);
  //Serial.print(" SET = ");Serial.println(set);
  if (Stato_Alzata[num_anta] == "I" && set == 1) {
    riavvio_slave_avvenuto = true;
  }
  //Serial.print(" Stato_Alzata[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");

  Pos_Anta[num_anta] = String(pch).toInt();
  //Serial.print(" Pos_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");

  Risposta_Comando[num_anta] = String(pch);
  //Serial.print(" Risposta_Comando_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");
  emerg[num_anta] = String(pch);
  //Serial.print(" emerg[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  impostaDir(emerg[num_anta]);
  pch = strtok (NULL, ",");
  String str_limit = String(pch); //curva consumo limit
  pch = strtok (NULL, ",");
  Batteria_Tensione[num_anta] = String(pch); // -- valorizzo Batteria_Tensione
  pch = strtok (NULL, ",");

}

void impostaDir(String str_emerg) {
  int conta_valore = 0;
  int contapos = 0;
  String array_valori[200];
  while (str_emerg.length()) {
    array_valori[conta_valore] = str_emerg.substring(0, str_emerg.indexOf("*"));
    if (str_emerg.indexOf("*") > 0) {
      contapos = str_emerg.indexOf("*") + 2;
    } else {
      contapos = str_emerg.length();
    }
    str_emerg = str_emerg.substring(contapos);
    Serial.print("valore  "); Serial.print(conta_valore); Serial.print(" = "); Serial.println(array_valori[conta_valore]);
    conta_valore++;
  }
  int chi_emerg = array_valori[3].toInt();
  switch (chi_emerg) {

    case 6:
      cicli_6 ++;
      break;
          case 16:
      cicli_16 ++;
      break;
          case 55:
      cicli_55 ++;
      break;
          case 66:
      cicli_66 ++;
      break;
  }

  int dir = 0;
  emergenza_dir = dir;
}

int hc12_read(char packetBuffer[], int len) {
  int i = 0;
  while (Serial1.available())
  { // If anything comes in Serial1 (pins 0 & 1)
    packetBuffer[i] = Serial1.read(); // read it and send it out Serial (USB)
    i++;
    if (i == len - 1)
      break;
  }
  return i + 1;
}
