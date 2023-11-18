
void controlla_collisione() {//Serial.print("dentro collisione ");Serial.print(_Dir);
  if (_Dir == 1) {//apri
    int i ;
    //Serial.print("dentro collisione apri ");
    for ( i = 1; i < Numero_Ante_Slave  ; i = i + 1) {
      collisione_[i] = (collisione_anta_[i] - Pos_Anta[i] + Pos_Anta[i+1]);
     Serial.print("collisione i");Serial.println(collisione_[i]);
      if ( Stato_Anta[i] == "V" && collisione_[i] < Spazio_Collisione) {
           Serial.print("collisioneanta i");Serial.println(collisione_anta_[i]);
         Serial.print("posslave ");Serial.println(Pos_Anta[i]);
         Serial.print("posslave2 ");Serial.println(Pos_Anta[i+1]);
         Serial.print("spaziocol - ");Serial.println(Spazio_Collisione);
         //Serial.print("collisione i");Serial.println(collisione_[i]);
          fast_ward(); return;
      }
    }
  }
  if (_Dir == -1) {//chiudi
    int i ;//Serial.print("dentro collisione chiudi ");
   //Serial.print("collisione DIR chiuso");
    for ( i = 1; i < Numero_Ante_Slave  ; i = i + 1) {
      collisione_[i] = (Pos_Anta[i] - Pos_Anta[i+1]);
      Serial.print("collisione i");Serial.println(collisione_[i]);
      if ( Stato_Anta[i] == "V" && collisione_[i] < (Spazio_Collisione)) {
        Serial.print("collisioneanta i");Serial.println(collisione_anta_[i]);
         Serial.print("posslave ");Serial.println(Pos_Anta[i]);
         Serial.print("posslave2 ");Serial.println(Pos_Anta[i+1]);
         Serial.print("spaziocol - ");Serial.println(Spazio_Collisione);
        fast_ward(); return;
      }
    }
  }
}
