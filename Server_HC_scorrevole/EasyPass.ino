void check_easyPass(){
       if (Pos_Anta[1] > easy_pass && Stato_Anta[1] != "F" ) { ferma_WARD(); solopassaggio = false; return;}
}

void reset(){
   ferma_WARD(); 
   return;
}

void check_posizione(){
         if(Pos_Anta[2]>=5276 && _Dir == 1){
          Serial.print("Pos_Anta2************  = ");Serial.println(Pos_Anta[2]);
           ferma_WARD();
          }
          if(Stato_Anta[1]=="F" || Stato_Anta[1]=="T"|| Stato_Anta[1]=="A"){Serial.print("cambia stato e DIR ");
            _Dir=0;
            }
    /*     Per_Centuale=pos_aperto[1]/100;
         if ( _percentuale != 0 && (Pos_Anta[1]/Per_Centuale) >_percentuale && _Dir == 1){ferma_WARD(); _percentuale = 0;}                    // -- PER APPLICAZIONE FUTURA CON SWIPE
         if ( _percentuale != 0 && (Pos_Anta[1]/Per_Centuale) <_percentuale && _Dir == -1){ferma_WARD(); _percentuale = 0;}                   // -- PER APPLICAZIONE FUTURA CON SWIPE         
        
         if (Stato_Anta[1] == "T" && dipendente == true ) {digitalWrite(CONSENSO_in_scrittura,HIGH);digitalWrite(CONSENSO_in_scrittura_vento,HIGH);}
         if (Stato_Anta[1] != "T" && dipendente == true ) {digitalWrite(CONSENSO_in_scrittura,LOW);digitalWrite(CONSENSO_in_scrittura_vento,LOW);}
         
         if (Stato_Anta[1] == "T" && dipendente == false ) {digitalWrite(CONSENSO_in_scrittura,LOW);}
         if (Pos_Anta[1] >= 3000 && _Dir == 1 && dipendente == false ) {digitalWrite(CONSENSO_in_scrittura, HIGH);} // -- DO IL CONSENSO AD APRIRE
          if (Stato_Anta[1] != "T" && dipendente == false ) {digitalWrite(CONSENSO_in_scrittura_vento,LOW);}
           if (Stato_Anta[1] == "A" && dipendente == false ) {digitalWrite(CONSENSO_in_scrittura_vento,HIGH);}

         if (Pos_Anta[1] <= 3000 && _Dir == -1 && digitalRead(CONSENSO_in_lettura) == LOW){   // -- NON HO IL CONSENSO A CHIUDRE E QUINDI FERMO E ASPETTO
            ferma_WARD();
            int cont=0;
            while(digitalRead(CONSENSO_in_lettura) == LOW){   // -- "LOW" qui vuol dire NO
                if (comando != "0000" || digitalRead(STOP)==LOW || digitalRead(APRI)==LOW || digitalRead(CHIUDI)==LOW || cont>3000 ) {
                    strweb="";
                    return;
                }
                 delay(50);
                 cont++;
            }
             Partenza_Sicura(-1, 0, 0); 
         } */
}
