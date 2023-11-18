/*
void ricEvi(){
  char myBuffer[255];
  int conto = 1;
  int packetSize = Udp.parsePacket();
  if (packetSize > 0)
    {
      while(packetSize > 0)
      {
        //Serial.print(" RIC: ");Serial.println(packetSize);
        Udp.read(myBuffer, 255);
        myBuffer[packetSize] = '\0';
        Serial.print(" myBuffer = ");Serial.println(myBuffer);
        Abbina_Pacchetto(String(myBuffer));
        if (Risposta_Comando[1]== Comando[1])
          {
            Serial.print(" Risposta_Comando = ");Serial.println(Comando[1]);
            break;
          }
        if (conto > 10)
          {
            break;
          }  
        packetSize = Udp.parsePacket();
        conto++; 
       }
    }
              
}

  void Abbina_Pacchetto(String varList){
  //Serial.print(" inizio Traduci: ");Serial.println(varList);
  
  char list[255];
  varList.toCharArray(list, 255);
  char * pch;
  int num_anta=0;
  pch = strtok (list, ",");
  int sono_io_slave = String(pch).toInt();
  for(int i=1;i<=MAX_ANTE;i++){
     if(Ante_Slave[i]==sono_io_slave){
        num_anta=i;
        break;
      }
    }
    if(num_anta==0){return;}
  //Serial.print(" sono_io_slave = ");Serial.println(sono_io_slave);
  pch = strtok (NULL, ",");
  
  Stato_Anta[num_anta] = String(pch);
  //Serial.print(" Stato_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch); 
  pch = strtok (NULL, ",");
   if(Stato_Anta[num_anta]=="S" && Stato_Anta[num_anta] != Stato_Anta_old[num_anta])
   {
    Serial.println("Emerg S"+num_anta);
    writelog("Anta emergenza : "+num_anta);
    emergenza_chi=num_anta;
    emergenza=true;
   }
   Stato_Anta_old[num_anta]=Stato_Anta[num_anta];
    
  Direzione_Anta[num_anta] = String(pch).toInt();
  //Serial.print(" Direzione_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");
  
  Stato_Alzata[num_anta] = String(pch);
  //Serial.print(" Stato_Alzata[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");

  Pos_Anta[num_anta] = String(pch).toInt();
  Serial.print(" Pos_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");

  Risposta_Comando[num_anta] = String(pch);
  //Serial.print(" Risposta_Comando_Anta[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  pch = strtok (NULL, ",");
  emerg[num_anta]= String(pch);
  Serial.print(" emerg[");Serial.print(num_anta); Serial.print("] = "); Serial.println(pch);
  impostaDir(emerg[num_anta]);
  pch = strtok (NULL, ",");
  String str_limit=String(pch);//curva consumo limit
  dataSaveLimit(num_anta,str_limit);
   pch = strtok (NULL, ",");//micros finale
   
  }

  void impostaDir(String str_emerg){
     char list[255];
     str_emerg.toCharArray(list, 255);
     char * pch;
    
     pch = strtok (list, "**");
     
      pch = strtok (NULL, "**");
      
      pch = strtok (NULL, "**");
     
     int dir = String(pch).toInt();
      pch = strtok (NULL, "**");
     //Serial.print(" emerg[DIR");Serial.println(dir);
    emergenza_dir=dir;
    }

     */
