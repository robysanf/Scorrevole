void ascolta_web() {
  if (Conta_Loop >= 3) {
    Conta_Loop = 0;
    delay(wait);
    if (strwebHost == strwebHostOld ) {
      delay(1);
      return;
    }
    strweb = strwebHost.substring(0, 4);
    strweb2 = strwebHost.substring(4);
    // -- comandi operativi apri-chiudi
    // -- comando per APRIRE
    if ( strweb == "apri") {
      Partenza_Sicura(1, 0, 0); Serial.println("APRI");
    }
    // -- comando per CHIUDERE
    if ( strweb == "chiu") {
      Partenza_Sicura(-1, 0, 0); Serial.println("CHIUDI");
    }
    // -- comando per FERMARE
    if ( strweb == "stop") {
      ferma_WARD(); Serial.println("STOP");
    }
    if ( strweb == "chch") {
      Serial.println("cambia canale");
      for (int i = 1 ; i <= Numero_Ante_Slave ; i++) {
        inVia(i, "5555" + strweb2, 45);
        attendi_risposta(i, 10, "5555");
        strwebHostOld = strwebHost;
      }
      digitalWrite(3, LOW );
      delay(150);
      String s = "AT+C" + strweb2;
      char lis[255];
      s.toCharArray(lis, 255);
      Serial1.write(lis);
      delay(150);
      digitalWrite(3, HIGH );
    }
    delay(1);
    strwebHostOld = strwebHost;
    delay(1);
  }
  Conta_Loop = Conta_Loop + 1;
}

void save(String s) { //solo per velocità max e lenta
  writelog("cambio velocita " + s);
  String val = s.substring(4);
  if (s.startsWith("3331")) {
    dataSave("velocita_crocera_MAX", val);
  }
  if (s.startsWith("3332")) {
    dataSave("velocita_crocera_LENTA", val);
  }
  if (s.startsWith("3333")) {
    dataSave("velocita_crocera_COL", val);
  }
  if (s.startsWith("4333")) {
    writelog("ricevo " + s);
    String str = s.substring(4);
    writelog("prendo solo " + str);
    char list[32];
    str.toCharArray(list, 32);
    int pos_num = 0;
    char * pch;
    String toret[6] = {"", "", "", "", "", ""};
    pch = strtok (list, ",");
    int cont = 0;
    while (pch != NULL)
    {
      toret[cont] = pch;
      cont++;

      pch = strtok (NULL, ",");
    }
    writelog("aray " + toret[0] + " " + toret[1] + " " + toret[2] + " " + toret[3] + " " + toret[4]);
    char d[6];
    toret[0].toCharArray(d, 6);
    int pos_n = atoi(d);
    writelog("door " + String(pos_n));
    aggiornaVar("attrito", toret[1], pos_n);
    aggiornaVar("inerzia", toret[2], pos_n);
    aggiornaVar("peso", toret[3], pos_n);
    aggiornaVar("ritardo", toret[4], pos_n);
    writelog(toret[1] + "-" + toret[2] + "-" + toret[3] + "-" + toret[4]);

  }

}

void aggiornaVar(String nome_var , String nuovo_val, int pos_num) {
  String att = dataFiller(nome_var);
  if (att.indexOf(",") == -1) {
    dataSave(nome_var, nuovo_val + "/");
  }
  char list[30];
  char nuovo_valore[5];
  att.toCharArray(list, 30);
  nuovo_val.toCharArray(nuovo_valore, 70);
  char * pch;
  String var_to_return;
  char toret[40] = "";
  pch = strtok (list, ",");
  int cont = 0;
  while (pch != NULL)
  {
    if (cont == pos_num)
    {
      strcat(toret, nuovo_valore);
    }
    else {
      strcat(toret, pch);
    }
    strcat(toret, ",");
    cont++;

    pch = strtok (NULL, ",");
  }
  String tosave = String(toret);
  tosave = tosave.substring(0, tosave.length() - 1); //tolgo ultima virgola
  tosave.replace("/", "");
  tosave.replace("\r", "");
  tosave.replace("\n", "");
  writelog("tosave " + tosave);
  dataSave(nome_var, tosave);
}
