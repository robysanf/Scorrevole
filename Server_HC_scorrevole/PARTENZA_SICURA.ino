void Partenza_Sicura(int Direzione, int Except, int Prw) {
  //****************************
  //Execept= 1 uomo assente
  //Execept= 0 uomo presente
  if (apertura) {
    for (int i = 2 ; i <= Numero_Ante_Slave ; i++) {
      int c = 0;
      inVia(i, "2224", 36); delay(100); //****************************************************MOD
      while (Risposta_Comando[i] != "2224" && c < 10)
      {
        ricEvi(); delay(10);
        c++;
      }

    }
    return;
  }
  if (_Dir == 0) { // -- (siamo_fermi() == true)
    int i ;
    ///**************  APRI
    if ( Direzione == 1) {
      int curr = 0;
      Serial.println("9");
      Serial.print("Stato slave = "); Serial.println(Stato_Anta[1]);
      if (Stato_Anta[1] == "A" && Stato_Anta[2] == "A") {   //*********************************MOD
        return;
      }
      if (Stato_Anta[1] == "T" || Pos_Anta[1] < 100 || Stato_Anta[2] == "T"  || Pos_Anta[1] < 500  ) { //*********************************MOD
        Serial.println("tutto chiuso");
        inVia(1, "2224", 25626);
        int c = 0;
        while (Risposta_Comando[1] != comando && c < 10)
        {
          ricEvi(); delay(10); Serial.print("while rit "); Serial.println(c);
          c++;
        }
        apertura = true;
        apertura_time = millis();

      } else  {
        Serial.print("\n arrivato qui");

        for (int i = 1 ; i <= Numero_Ante_Slave ; i++) {
          int c = 0;
          inVia(i, "2223", 652); delay(100);
          while (Risposta_Comando[i] != "2223" && c < 10)
          {
            ricEvi(); delay(10);
            c++;
          }

        }
        writelog("Apri");
        _Dir = 1;
        Previus_Dir = _Dir;
      }
    }

    //**********************************  CHIUDI ******************************
    if ( Direzione == -1) {
      Serial.print("\n partenza");
      if (Stato_Anta[1] == "T" && Stato_Anta[2] == "T") {
        Serial.print("\n retttll");
        return;
      }

      for (int i = 1 ; i <= Numero_Ante_Slave ; i++) {
        inVia(i, "2222", 7642);
        int c = 0;
        while (Risposta_Comando[i] != "2222" && c < 10)
        {
          ricEvi(); delay(10); Serial.print("while rit "); Serial.println(c);
          c++;
        }
        delay(200);
      }
      writelog("Chiudi");
      _Dir = -1;
      Previus_Dir = _Dir;
    }
  }
  else {
    Serial.print("\n ncoll222");
    ferma_WARD();
  }
}

boolean check_dipendente(int contatore) {
  int cont = 0;

  while (digitalRead(CONSENSO_in_lettura) == LOW || digitalRead(CONSENSO_in_lettura_vento) == LOW) { // -- "LOW" qui vuol dire NO
    String s = comando_web;
    if ( s != "0000/" || digitalRead(STOP) == LOW || digitalRead(APRI) == LOW || digitalRead(CHIUDI) == LOW || cont >= contatore) {
      strweb = "";
      return true;
    }
    delay(50);
    cont++;
  }
  return false;
}


boolean evento_pulsanti() {
  if (digitalRead(APRI) == LOW || digitalRead(CHIUDI) == LOW ||  digitalRead(STOP) == LOW)
  {
    return true;
  }
  return false;
}
