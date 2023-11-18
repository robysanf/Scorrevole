void Check_Pin(){                             // -- COSTRUISCO LA STRINGA DA SWITCIARE
  int i;
  int Pulsanti = 0;
  if (digitalRead(STOP) == LOW && _Dir != 0){ 
    ferma_WARD();
    return;
  }
  if (digitalRead(APRI) == LOW){Pulsanti = 2000;} else {Pulsanti = 1000;} 
  if (digitalRead(CHIUDI) == LOW){Pulsanti += 20;} else {Pulsanti += 10;}
  if (stato_APRI == 1){ Pulsanti += 100;} 
  if (stato_CHIUDI == 1 ){Pulsanti += 1;} 
  //Serial.print("\n inizio Pulsanti = ");Serial.println(Pulsanti);
  if (Pulsanti == _Pulsanti){return;}
  _Pulsanti = Pulsanti;
  Serial.print("\n dentro Pulsanti = ");Serial.println(Pulsanti);
  //I2c(1); // -- controllo gli slave prima di dare ordini

if (U_P == true && set == 1){
    switch (Pulsanti) {
      
      case 2010:  // -- APPENA PREMUTO APRI
      Serial.println("dentro apri");
        if (_Dir != 0){                                                                   //Serial.println("stop P_U1 2010");
        ferma_WARD();
        for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",543); delay(10); }              // -- > STOP
        Serial.println("dentro STOPoooooooooooooooooooooooooo");
        return;}                                                                          // -- SE SONO IN MOVIMENTO > FERMO
        
        delay(200); if(digitalRead(APRI)!=LOW){ return;}       // -- ALTRIMENTI ASPETTO 300
        T_scemo_2 = millis();                                                                            // -- > GUARDO IL TEMPO
        if ((T_scemo_2 - T_scemo_1) > 100 ){ //Serial.println("apro P_U1 2010");                           // -- ANTI SCEMO, SE IL TEMPO CHE PASSA DALL'ULTIMA VOLTA CHE HO RILASCIATO UN PULSANTE  E' SUPERIORE A 500..
           Partenza_Sicura(1,0,0);                                                                                  // -- > APRE
           /*
           for (int i = 1 ; i <= Numero_Ante_Slave ; i++){ 
            inVia(i,"2224"); delay(10); 
            }
           */
           Serial.println("dentro apri>>>>>>>>>>>>>>>>>>>>>>>>");
           stato_APRI = 1;                                                                                  // -- > IMPOSTA IL PULSANTE SU PREMUTO
        } 
        break;
//------------------------------------------------------------------------------------------------------------       
      case 2110 :  // -- PREMUTO STABILMENTE APRI
        // -- NON FACCIO NIENTE
        break;
//------------------------------------------------------------------------------------------------------------       
      case 1110 : { // -- APPENA RILASCIATO APRI
        //ferma_WARD();           // -- DEVO FERMARE IL MOVIMENTO
        for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",66433); delay(10); }
           Serial.println("dentro STOPooooooooooooooooooooooo");
        stato_APRI = 0;                                       // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
        T_scemo_1 = millis();}
        break; 
//------------------------------------------------------------------------------------------------------------     
      case 1020:  // -- APPENA PREMUTO CHIUDI
        if (_Dir != 0){ferma_WARD(); 
        for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",9865); delay(10); }               // -- > STOP
        
        Serial.println("dentro STOPoooooooooooooooooooooooooooooooooooooooo");
        return;}                        // -- SE SONO IN MOVIMENTO FERMO
        delay(200); if(digitalRead(CHIUDI)!=LOW){ return;}                                                  // -- ALTRIMENTI ASPETTO 300     Serial.println("sotto tempo 300 P_U1 1020");
        T_scemo_2 = millis();                                                                          // -- > GUARDO IL TEMPO
           if ((T_scemo_2 - T_scemo_1) > 100 ){//Serial.println("chiudo P_U1 1020");                     // -- ANTI SCEMO, SE IL TEMPO CHE PASSA DALL'ULTIMA VOLTA CHE HO RILASCIATO UN PULSANTE  E' SUPERIORE A 500.. 
              Partenza_Sicura(-1,0,0);
              /*for (int i = 1 ; i <= Numero_Ante_Slave ; i++){ 
              inVia(i,"2222");  
              }*/  // -- > CHIUDE
              
              Serial.println("dentro <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
              stato_CHIUDI = 1;                                                                             // -- > IMPOSTA IL PULSANTE SU PREMUTO
           }
        break;
//------------------------------------------------------------------------------------------------------------        
      case 1021 :  // -- PREMUTO STABILMENTE CHIUDI
        // -- NON FACCIO NIENTE
        break;
//------------------------------------------------------------------------------------------------------------        
      case 1011 :  {// -- APPENA RILASCIATO CHIUDI
          ferma_WARD();//Serial.println("stop P_U1 1011");                      // -- DEVO FERMARE IL MOVIMENTO 
          stato_CHIUDI = 0;                                                     // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
          for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",89632); delay(10); }  // -- > STOP
          char hello1[] = "2221";
         
          Serial.println("dentro STOPooooooooooooooooooooooooooooooooooooooooo");
          T_scemo_1 = millis();}
        break;

      case 2011 :  // -- APPENA FATTO SCAMBIO PULSANTE TRA APRI E CHIUDI
            {ferma_WARD();//Serial.println("stop P_U1 1011");                     // -- DEVO FERMARE IL MOVIMENTO 
            stato_CHIUDI = 0;                                                     // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
            for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",643);delay(10);  }  // -- > STOP
             
            Serial.println("dentro STOPooooooooooooooooooooooooooooooooooooooooooooooo");
            T_scemo_1 = millis();}
          break;  
  
        case 1120 :  // -- APPENA FATTO SCAMBIO PULSANTE TRA CHIUDI E APRI
            {ferma_WARD();//Serial.println("stop P_U1 1011");                                 // -- DEVO FERMARE IL MOVIMENTO 
            stato_APRI = 0;                                                                   // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
            for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",9654);delay(10);  }              // -- > STOP
            Serial.println("dentro STOPooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
            T_scemo_1 = millis();}
          break;   

        case 1010 :  // -- APPENA FATTO SCAMBIO PULSANTE TRA CHIUDI E APRI
            {ferma_WARD();//Serial.println("stop P_U1 1011");                      // -- DEVO FERMARE IL MOVIMENTO 
            stato_APRI = 0;                                                        // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
            for (int i = 1 ; i <= Numero_Ante_Slave ; i++){  inVia(i,"2221",8749); delay(10); }   // -- > STOP
            Serial.println("dentro STOPooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
            T_scemo_1 = millis();}
          break;         

             
  }
//------------------------------------------------------------------------------------------------------------  
 }
if (U_P == false && set == 1){
    switch (Pulsanti) {
      
      case 2010:  // -- APPENA PREMUTO APRI
        if (_Dir != 0){ ferma_WARD(); return;}                                                         // -- SE SONO IN MOVIMENTO > FERMO          Serial.println("stop U_P0 2010");
        delay(200); if(digitalRead(APRI)!=LOW){ return;}                                                   // -- ALTRIMENTI ASPETTO 300      Serial.println("sotto tempo 300 U_P0 2010");
        T_scemo_2 = millis();                                                                          // -- > GUARDO IL TEMPO
           if ((T_scemo_2 - T_scemo_1) > 100 ){                                                        // -- ANTI SCEMO, SE IL TEMPO CHE PASSA DALL'ULTIMA VOLTA CHE HO RILASCIATO UN PULSANTE  E' SUPERIORE A 500..
            if (Stato_Anta[1] == "T"){                                                           // -- SE LA PORTA E' TUTTA CHIUSA (PREPARO PER L'EASY_PASS)
             while(digitalRead(APRI) == LOW){//Serial.print("ci sono");                                    // -- MI METTO IN ATTESA
              T_scemo_1 = millis();
              if ((T_scemo_1 - T_scemo_2) > 1000 ){
                solopassaggio = true;                            //Serial.println("apro solopassaggio");   // -- SE SUPERO IL TEMPO APRO CON EASY_PASS
                Partenza_Sicura(1,2,0);
                _Dir = 1;
                delay(50);
                stato_APRI = 1;
                break;
               }
              }
              if (solopassaggio == false)
                   {
                    Partenza_Sicura(1,1,0);
                    break;                                                                             // -- APRO DA TUTTO CHIUSO SENZA EASY_PASS
                   }
            }else{
            Partenza_Sicura(1,1,0); //Serial.println("apro normale");                                               // -- APRO NORMALMENTE                                                                 
            break;
            }
           }
         stato_APRI = 1;                                                                                  // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
        break;
//------------------------------------------------------------------------------------------------------------    
       case 2110 :  // -- PREMUTO STABILMENTE APRI
          // -- NON FACCIO NIENTE
          break;


//------------------------------------------------------------------------------------------------------------    
       case 1021 :  // -- PREMUTO STABILMENTE CHIUDI
          // -- NON FACCIO NIENTE
          break;


//------------------------------------------------------------------------------------------------------------        
      case 1110 :   // -- APPENA RILASCIATO APRI
                                           
          stato_APRI = 0;      // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
          T_scemo_1 = millis();
           
         break;
//------------------------------------------------------------------------------------------------------------         
      case 1020 :   // -- APPENA PREMUTO CHIUDI
          if (_Dir != 0){ferma_WARD();  stato_CHIUDI = 1; return; }                                         // -- SE SONO IN MOVIMENTO > FERMO    Serial.println("stop U_P0 1020 ");
          delay(200); if(digitalRead(CHIUDI)!=LOW){ return;}                                                // -- ALTRIMENTI ASPETTO 300               Serial.println("sotto tempo 300 U_P0 1020");
          T_scemo_2 = millis();                                                                            // -- > GUARDO IL TEMPO
          if ((T_scemo_2 - T_scemo_1) > 300 ){                                                             // -- ANTI SCEMO, SE IL TEMPO CHE PASSA DALL'ULTIMA VOLTA CHE HO RILASCIATO UN PULSANTE  E' SUPERIORE A 500..
             Partenza_Sicura(-1,0,0); //Serial.println("CHIUDO U_P0 1020");                                             // -- > CHIUDE
             stato_CHIUDI = 1;                                                                                  // -- > IMPOSTA IL PULSANTE SU PREMUTO
          }
         break;
 //------------------------------------------------------------------------------------------------------------         
       case 1011 :   // -- APPENA RILASCIATO CHIUDI
         stato_CHIUDI = 0;                                      // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
         T_scemo_1 = millis();
         break; 

       /*default : 
             stato_APRI = 0; 
             stato_CHIUDI = 0; 
             T_scemo_1 = millis();
          break;*/
                    
    }
}


switch (Pulsanti) {

//------------------------------------------------------------------------------------------------------------        
      case 2120 :  // -- premuto 11 E APPENA premuto 13 
          ferma_WARD();//Serial.println("stop 2120");                        // -- DEVO FERMARE IL MOVIMENTO 
          stato_CHIUDI = 1;                                                      // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
        break;
//------------------------------------------------------------------------------------------------------------       
      case 2021 :  // -- premuto 13 E APPENA premuto 11 
          ferma_WARD();// Serial.println("stop 2021");                   // -- DEVO FERMARE IL MOVIMENTO 
          stato_APRI = 1;                                                      // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
         break;
//------------------------------------------------------------------------------------------------------------         
       case 2020 :  // -- APPENA premuto 11 & 13 
          ferma_WARD();// Serial.println("stop");                    // -- DEVO FERMARE IL MOVIMENTO
          stato_APRI = 1;                                        // -- > IMPOSTA IL PULSANTE SU PREMUTO
          stato_CHIUDI = 1;                                        // -- > IMPOSTA IL PULSANTE SU PREMUTO  
         break;
//------------------------------------------------------------------------------------------------------------         
       case 2121 :  // -- premuto E APPENA premuto 
          T_scemo_2 = millis();                                                 // -- > GUARDO IL TEMPO
          while(digitalRead(APRI)==LOW && digitalRead(CHIUDI)==LOW){ 1+1;}           // -- MI METTO IN ATTESA
          T_scemo_1 = millis();
              if ((T_scemo_1 - T_scemo_2) > 3500 && (T_scemo_1 - T_scemo_2) < 10000 ){
                   Commuta_Uomo_Presente();
                   Serial.println("commuta");                                // -- DEVO FERMARE IL MOVIMENTO 
               }
               if ((T_scemo_1 - T_scemo_2) > 15000 ){
                   //set_reset();
                                         
               }
            //Serial.print("U_P = ");Serial.println(U_P);
            stato_APRI = 0;                                                        // -- > IMPOSTA IL PULSANTE SU NON PREMUTO
            stato_CHIUDI = 0; 
            delay(500);
         break;

      
                
  } 
}
void Commuta_Uomo_Presente(){
   if ( Pos_Anta[1] > 2000   && set == 1 ){ // --  &&  (Pos_Anta[2] - Pos_Anta[1]) > 2000
       ferma_WARD();
       delay(200);
       ordina("2222",Ante_Slave[1],21);
       delay(300);
       ferma_WARD();
       delay(400);
       ordina("2223",Ante_Slave[1],21);
       delay(300);
       ferma_WARD();
       U_P = !U_P;
   }
}
