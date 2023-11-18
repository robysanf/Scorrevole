String scanner() {
  delay(3000);
  int nDevices, naddress ;
  String myaddr = "";//metterla vuota"";//
  nDevices = 0;

       for (naddress = 61; naddress < 65; naddress++ )
    { Serial.print("\n Scanner invio a: "); Serial.println(naddress);
      String   msg = "0000" ;
      char list[255];
      for(int i=1;i<255;i++){
       list[i] ='\0';
       }
      msg = String(naddress)+ "," + msg + "," + millis()+"@";
      msg.toCharArray(list, 255);
      Serial.print("ip : "); Serial.println(naddress);
      Serial.println(msg);
      Serial1.write(list);
      delay(200);
      char str_scan[255];
      String result="";
      int lung = hc12_read(str_scan, 255);
      str_scan[lung - 1] = '\0';
      Serial.print("rsiposta****  ");Serial.println(str_scan); 
       if(lung>2){
          if(String(str_scan).substring(0,2)==String(naddress)){
              myaddr = myaddr + String(naddress) + ",";
            }
        }
    }
  if (myaddr.endsWith(","))
  {
    myaddr = myaddr.substring(0, myaddr.length() - 1);
  }
  Serial.println("Scanner invio terminato");
 
  if (myaddr.length() == 0) {
    myaddr = "";
    Serial.println("No IP devices found");
    writelog("No IP devices found");
    delay(2000);
  }
  else {
    Serial.print("myaddr = ");
    Serial.println(myaddr);
    delay(2000);
  }
  return myaddr;
}

String rx_scanner() {
  char myBuffer[255];
  String trovati[9];
  String myaddr = "";
  //int conto = 1;
  int packetSize = 0;
  for (int i = 0; i < 100; i++ )
  { delay(10);
    //packetSize = Udp.parsePacket();
    if (Serial1.available())
    {
      int i = 0;
      while (Serial1.available())
      { // If anything comes in Serial1 (pins 0 & 1)
        myBuffer[i] = Serial1.read(); // read it and send it out Serial (USB)
        i++;
        if (i == 254)
          break;
      }

      myBuffer[packetSize] = '\0';
      Serial.print(" myBuffer = "); Serial.println(myBuffer);
      char * pch;
      pch = strtok (myBuffer, ",");
      String sono_io = String(pch);
      pch = strtok (NULL, ",");
      //le schede devono essee già impostate con IP finale da 0 a 9 diverse tra loro
      int pos_trovati = sono_io.substring(sono_io.length() - 1).toInt();
      trovati[pos_trovati] = sono_io;

      //salva in array trovati solo una volta
      Serial.print(" sono io = "); Serial.println(sono_io);
      Serial.print(" pos_trovati = "); Serial.println(pos_trovati);
    }
  }
  for (int i = 0; i < 9; i++ )
  { // verifica se è presente

    String s = trovati[i];
    // Serial.print("s =" );Serial.print(s);
    // Serial.print("lung = ");Serial.println(s.length());
    if (s.length() != 0)
    {
      myaddr = myaddr + s + ",";
    }
  }
  if (myaddr.endsWith(","))
  {
    myaddr = myaddr.substring(0, myaddr.length() - 1);
  }
  // @-- Serial.print("myaddr = " ); Serial.println(myaddr);
  return myaddr;
}
/*String scanner(){
  delay(10000);
  int nDevices, naddress ;
  String myaddr = "";//metterla vuota"";//
  nDevices = 0;
  
  for(int i=0;i<3;i++){
  for(naddress = 61; naddress < 65; naddress++ ) 
  {Serial.print("\n Scanner invio a: ");Serial.println(naddress);
  String   msg = "0000" ;
  String ip_addr=ip_prefix+String(naddress);
  String port_addr=port_prefix+String(naddress);
     //192.168.81+X
     //port 23x
    char list[255];
    msg=msg+","+ millis();
    msg.toCharArray(list, 255);
    Serial.print("ip : ");Serial.println(ip_addr);
    char cl[16];
    ip_addr.toCharArray(cl,16);
    int port = port_addr.toInt();
    Serial.println(msg);
    Udp.beginPacket(cl,port);
    Udp.write(list);
    Udp.endPacket();
     delay(100);
  }
  }
  Serial.print("\n Scanner invio terminato");
  myaddr=rx_scanner();
  if (myaddr.length() == 0){
    Serial.print("\n No IP devices found");
    }
  else{
    Serial.print("\n myaddr = ");
    Serial.print(myaddr);
    delay(10);
     }
  return myaddr;
}

String rx_scanner(){
  char myBuffer[255];
  String trovati[9];
  String myaddr="";
  int conto = 1;
  int packetSize = 0;
 
       for(int i=0; i < 100; i++ ) 
      { delay(10);Serial.print("xxxxx: ");Serial.println(i);
        packetSize=Udp.parsePacket();
        if (packetSize > 0)
        {
        Serial.print(" RIC scann: ");Serial.println(i);
        Udp.read(myBuffer, 255);
        myBuffer[packetSize] = '\0';
       // Serial.print(" myBuffer = ");Serial.println(myBuffer);
        //leggo sono io
        char * pch;
         pch = strtok (myBuffer, ",");
         String sono_io=String(pch);
         pch = strtok (NULL, ",");
         //le schede devono essee già impostate con IP finale da 0 a 9 diverse tra loro
         int pos_trovati=sono_io.substring(sono_io.length()-1).toInt();
         trovati[pos_trovati]=sono_io;
         
        //salva in array trovati solo una volta
         Serial.print(" sono io = ");Serial.println(sono_io);  
        //Serial.print(" pos_trovati = ");Serial.println(pos_trovati);
       } 
    }
    for(int i=0; i < 9; i++ ) 
      {// verifica se è presente
        
        String s=trovati[i];
       // Serial.print("s =" );Serial.print(s);
       // Serial.print("lung = ");Serial.println(s.length());
        if(s.length()!=0)
         {
          myaddr=myaddr +s+ ",";
         }
       }
        if (myaddr.endsWith(","))
        {
           myaddr=myaddr.substring(0,myaddr.length()-1);
        }
    Serial.print("myaddr =" );Serial.print(myaddr);
    return myaddr;
  }*/
