void Emergenza(int rh, int dir, String perche) {
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
  }

}
