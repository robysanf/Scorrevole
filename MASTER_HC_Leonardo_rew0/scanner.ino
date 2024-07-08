String scanner() {
  delay(500);
  int naddress = 0;
  String myaddr = "";  // metterla vuota
  for (naddress = 61; naddress <= 69; naddress++) {
    Serial.print("\n Scanner invio a: ");
    Serial.println(naddress);
    String msg = "0000";
    char list[255];
    for (int i = 1; i < 255; i++) {
      list[i] = '\0';
    }
    msg = String(naddress) + "," + msg + "," + millis() + "@";
    msg.toCharArray(list, 255);
    Serial.print("ip : ");
    Serial.println(naddress);
    Serial.println(msg);
    for (int tentativi = 0; tentativi <= 3; tentativi++) {
      Serial1.write(list);
      int tempo = 0;
      while (!Serial1.available() && tempo < 30) {
        tempo++;
        delay(5);
      }
      Serial.print("TENTATIVO****  "); Serial.println(tentativi);
      if ( tempo < 30) {
        delay(35);
        char str_scan[255];
        int lung = hc12_read(str_scan, 255);
        str_scan[lung - 1] = '\0';
        Serial.print("rsiposta****  "); Serial.println(str_scan);
        if (lung > 2) {
          if (String(str_scan).substring(0, 2) == String(naddress)) {
            myaddr = myaddr + String(naddress) + ",";
            break;
          }
        }
      }
    }
  }
  if (myaddr.endsWith(",")) {
    myaddr = myaddr.substring(0, myaddr.length() - 1);
  }
  Serial.println("Scanner invio terminato");

  if (myaddr.length() == 0) {
    myaddr = "";
    Serial.println("No IP devices found");
    delay(2000);
  } else {
    Serial.print("myaddr = ");
    Serial.println(myaddr);
    delay(2000);
  }
  return myaddr;
}
