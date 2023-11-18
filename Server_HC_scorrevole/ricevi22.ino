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
    Abbina_Pacchetto(String(myBuffer));
  } 
}
/*void ricEvi() {
  int e = 0;
  while ( (micros() - tempo_invia) < 70000 * Numero_Ante_Slave) {
    e++;
  }
  char myBuffer[255];
  int conto2 = 0;
  int conto = 0;
  int packetSize = Udp.parsePacket();
  if (packetSize > 0)
  { conto2 = 1;
    while (packetSize > 0)
    {
      Udp.read(myBuffer, 255);
      myBuffer[packetSize] = '\0';

      Abbina_Pacchetto(String(myBuffer));

      if (conto > 10)
      {
        break;
      }
      delay(25);
      packetSize = Udp.parsePacket();
      conto++;
    }
  }
  if (conto < Numero_Ante_Slave && conto2 > 0 )
  {
    Serial.println(" ********* QUALCUNO NON HA RISPOSTO ***********");
  }
  for (int i = 1; i <= Numero_Ante_Slave; i++) {
    not_packet[i]++;
  }
}
*/

void Abbina_Pacchetto(String varList) {
  //Serial.print(" inizio Traduci: ");Serial.println(varList);

  char list[255];
  varList.toCharArray(list, 255);
  char * pch;
  int num_anta = 0;
  pch = strtok (list, ",");
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
  pch = strtok (NULL, ",");

  Stato_Anta[num_anta] = String(pch);
  //Serial.print(" Stato_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");
  if (Stato_Anta[num_anta] == "S" && Stato_Anta[num_anta] != Stato_Anta_old[num_anta])
  {
    //Serial.println("Emerg S" + num_anta);
    emergenza_buffer = varList;
    emergenza_chi = num_anta;
    emergenza = true;
  }
  Stato_Anta_old[num_anta] = Stato_Anta[num_anta];

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
  impostaDir(emerg[num_anta]); // USATO DA NESSUNO
  pch = strtok (NULL, ",");
  String str_limit = String(pch); //curva consumo limit
  pch = strtok (NULL, ",");

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

void impostaDir(String str_emerg) {
  char list[255];
  str_emerg.toCharArray(list, 255);
  char * pch;

  pch = strtok (list, "**");

  pch = strtok (NULL, "**");

  pch = strtok (NULL, "**");

  int dir = String(pch).toInt();
  pch = strtok (NULL, "**");
  //Serial.print(" emerg[DIR");Serial.println(dir);
  emergenza_dir = dir;// USATO DA NESSUNO
}
