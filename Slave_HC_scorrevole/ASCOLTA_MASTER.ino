void Ascolta_Master() {
  String risposta = "";
  String str_in_arrivo = "0000";
  //Serial.println("aspetto master");
  if (Serial1.available())
  { //Serial.print("ci sono dati");
    int lung = hc12_read(packetBuffer, 255);
    packetBuffer[lung - 1] = '\0';
    //Serial.println(packetBuffer);
    if (!costruisci_mesg(packetBuffer)) {
      return;
    }
    char * pch;
    pch = strtok (packetBuffer, ",");
    String chi = String(pch);
    if (String(sonoio) == chi) {
      pch = strtok (NULL, ",");
      String mystr = String(pch);
      str_in_arrivo = mystr.substring(0, 4);
      if (str_in_arrivo != str_old)
      {
        str = str_in_arrivo.toInt();
        str2 = mystr.substring(4);
        str_old = String(str);
      }
      invia(mystr);
    }
    for (int i = 1; i < 255; i++) {
      hold_packet[i] = '\0';
      packetBuffer[i] = '\0';
    }
    hold_packet[0] = '\0';
  }
}

void invia(String str_ricevuta) {
  ReplyBuffer[0] = '\0';
  String risposta = String(sonoio) + "," + Stato_Anta[0] + "," + _Dir + "," + Stato_Alzata[0] + "," + pos + "," + str_ricevuta + "," + str_emergenza + "," +  String(millis()) + ", @" ;
  //Serial.print("risposta "); Serial.println(risposta);
  risposta.toCharArray(ReplyBuffer, 255);
  Serial1.write(ReplyBuffer);
  delay(1);
  ;
}
boolean costruisci_mesg(char msg_in[]) {
  int l = strlen(hold_packet);
  int l_in = strlen(msg_in);
  String s = String(hold_packet) + String(msg_in);
  if (String(s).endsWith("@"))
  {
    s.toCharArray(packetBuffer, 255);
    return true;
  } else
  {
    s.toCharArray(hold_packet, 255);
    return false;
  }
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
