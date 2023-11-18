void testDurata(){
  
  if(!test){
    return;
  }
   
     //apri
     //Serial.println(parti);
     //Serial.println(test_chiudi);
   if(parti == 0){
     cicli_test=cicli_test+1; 
    Serial.print("\n Nuovo Ciclo*****"); // writelog("Nuovo Ciclo *********************  "+String(cicli_test));
        parti=millis(); 
      Partenza_Sicura(1,0,0);Serial.print("\n ALZA");  //writelog("test");   
    }
    
   long now=millis();
   //Serial.print("now-parti ");Serial.println(now-parti);
     if(now-parti < 15000 ){
          return;
      }
      if(test_alzata==0){
        Partenza_Sicura(1,0,0);Serial.print("\n APRI");  //writelog("apri_test");
        test_alzata=1;
      }
      if(now-parti < 45000 ){
          return;
      }
  if(test_chiudi){       
         Partenza_Sicura(-1,0,0);Serial.print("\n CHIUDI");  //writelog("Chiudi_test");
         test_chiudi=false;
     }
     else{
      if(now-parti > 90000) {
          parti=0;
          test_alzata=0;
          test_chiudi=true;
        }else{
           return;
        }
      }
    }
