void Emergenza(int rh, int dir, String perche) { //  dir USATO DA NESSUNO
  // @-- Serial.print("rh "); Serial.println(rh);
  for (int i = 1 ; i <= Numero_Ante_Slave ; i++) {
    if (rh == i) {
      // @-- scrivi_sul_libretto("emergenza"); // io sriverei l'ora seguita dal My_Buffer[] in questo momento
      inVia(i, "7777", 19);
      attendi_risposta(i, 5, "7777");
    } else {
      inVia(i, "2221", 18);
      attendi_risposta(i, 5, "2221");
    }
    delay(10);
   // inVia(i, "0000", 17);
  }
  String da_scrivere = "Emergenza " ;
  da_scrivere = da_scrivere + String(rh) + " MYbuffer = " + perche + " ** " + String(millis()/60000);
  writelog(da_scrivere);
  // @-- Serial.println("emergenza ho aperto");
}

void Emergenza9(int rh, int dir) {
  //Serial.print("rh "); Serial.println(rh);
  for (int i = 1 ; i <= Numero_Ante_Slave ; i++) {

    if (rh == i) {
      inVia(i, "7777",876);
    } else {
      inVia(i, "2221",765);
    }
    delay(10);
    inVia(i, "0000",8768);
  }
  //Serial.println("emergenza ho aperto");
}

/*  //Serial.println("emergenza ho fermato");
  delay(50);
  int i = 0;
  if (dir == 1) {
   // WARD(-1, 0, 25);
    //

    for (int i = 1 ; i <= Numero_Ante_Slave ; i++){
            inVia(i,"2222"); delay(10);
            }
    Serial.println("emergenza ho chiuso");
  } else {
   // WARD(1, 0, 25);

  for (int i = 1 ; i <= Numero_Ante_Slave ; i++){
            inVia(i,"2223"); delay(10);
            }
    //Serial.println("emergenza ho aperto");
  }

  delay(1500);
  ricEvi();
  ferma_WARD();
  //Serial.println("emergenza ho fermato fine emergenza");
  delay(500);
}*/
