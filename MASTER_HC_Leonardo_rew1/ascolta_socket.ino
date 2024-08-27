
void ascolta_sock() {

  client = new WebsocketsClient;

  if (client)
  {
    *client = SocketsServer.accept();

    if (client->available())
    {
      WebsocketsMessage msg = client->readBlocking();

      // log
      Serial.print("Got Message: ");
      Serial.println(msg.data());
      String strwebHost = String(msg.data());
      Serial.print("strwebhost "); Serial.println(strwebHost);
      String strweb = strwebHost.substring(0, 4);
      String strweb2 = strwebHost.substring(4);
     
      if ( strweb == "apri") {
        Partenza_Sicura(1, 0, 0);
        Serial.println("APRI");
      }
      if ( strweb == "chiu") {
        Partenza_Sicura(-1, 0, 0);
        Serial.println("CHIUDI");
      }
      if ( strweb == "stop") {
        ferma_WARD();
        Serial.println("stop");
      }

      if ( strweb == "TEST") {                    // -- comando per CHIUDERE
        test = !test;
        Serial.println("TEST");
      }

       if ( strweb == "save") {                    // -- comando per salvare
           salva_dati(); 
  }
  
  if ( strweb == "load") {                    // -- comando per CARICARE LE VARIABILI DA STORAGE
    Storage_Load();
   
  }
  
  if ( strweb == "XXXX") {                    // -- comando per CARICARE MANUALMENTE LA STRINGA
    server.send(200, "text/html", "<!DOCTYPE html>"
                                  "<html>"
                                  "<body>"
                                  "<h2>RECUPERO DI EMERGENZA</h2>"
                                  "<p>Scrivere manualmente la stringa dello storage</p>"
                                  "<form action=\"SaVe\" id=\"form1\" method=\"get\" >"
                                  "<textarea name=\"message\" rows=\"3\" cols=\"40\"></textarea>"
                                  "<br>"
                                  "<input type=\"submit\">"
                                  "</form>"
                                  "</body>"
                                  "</html>");
  }
  if ( strweb == "SaVe") {                    // -- comando per CARICARE MANUALMENTE LA STRINGA
    salva_dati_emergenza();
    
  }
  if ( strweb == "setr") {                    // -- comando per CARICARE rifare il set-reset
    set = 0;
    chiedo_conf = true;
    Serial.println("***************************RIAVVIO 2********************************");
   
  }
  if ( strweb == "vars") {                    // -- comando per VEDERE LE VARIABILI
    //Stop(5);
    Serial.println("vars");
    //strwebHostOld = strwebHost;
    //time_strwebHostOld = millis();
    //String Da_Stampare = Storage_Read_Web();
    server.send(200, "text/html", Storage_Read_Web());
  }
      //qui devono essere passati i nomi delle variabili esatti perchè poi vengono rispediti cosi all'arduino
      String risposta = "";
// okkio agli array
     /* risposta = "IMP=" + String(imp) + "#POS_APERTO=" + longArrayToString(pos_aperto) + "#POS_CHIUSO=" + String(pos_chiuso)+ "#VELOCITA_BASSA=" + String(velocita_crocera_LENTA) +
                 + "#ENCODER=" + stringArrayToString(encoder) + "#MOTORE=" + stringArrayToString(motore) + "#CONFIGURAZIONE=" + String(configurazione) + "#pos=" + longArrayToString(Pos_Anta) + "#CADENZA=" + String(cadenza)
                 + "#CONSUMO_BASSA_MAX=" + String(consumo_Bassa_max) + "#CONSUMO_MEDIA_MAX=" + String(consumo_Media_max) + "#CONSUMO_ALTA_MAX=" + String(consumo_Alta_max);*/
   Numero_Ante_Slave=2;  // da eliminare serve solo per test
    risposta = "IMP=" + String(imp) + "#POS_APERTO=" + longArrayToString(pos_aperto,Numero_Ante_Slave) + "#POS_CHIUSO=" + String(pos_chiuso)+ "#VELOCITA_BASSA=" + String(velocita_crocera_LENTA) +
                 + "#ENCODER=" + stringArrayToString(encoder,Numero_Ante_Slave) + "#MOTORE=" + stringArrayToString(motore,Numero_Ante_Slave) + "#CONFIGURAZIONE=" + String(configurazione) ;
    Serial.print("risposta"); Serial.println(risposta);
     
      client->send(risposta);
      Serial.print("oooooooooooo "); Serial.println(strwebHost);
      // close the connection
      client->close();
      Storage_SaveAll(risposta);
      Storage_Load();

    }
    delete client;
  }
}

String longArrayToString(long var_array[],int size) {
  String s="";
  for(int i=1;i<=size;i++){
      String s_t=String(var_array[i]);
      Serial.print("s_t "); Serial.println(s_t);
      if(s_t!=NULL && s_t!="")
          s=s+String(var_array[i])+",";
    }
    return s.substring(0,s.length()-1);
}

String stringArrayToString(String var_array[], int size) {
  String s="";
  for(int i=1;i<=size;i++){
      String s_t=String(var_array[i]);
      Serial.print("s_t "); Serial.println(s_t);
      if(s_t!=NULL && s_t!="")
          s=s+String(var_array[i])+",";
    }
    return s.substring(0,s.length()-1);
}
