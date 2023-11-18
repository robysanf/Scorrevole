String dataFiller(String toFind){
    String pathini="/data.ini";
   
  if (SD.exists(pathini)) { // If the file exists, either as a compressed archive, or normal
                                         
    File file = SD.open(pathini, FILE_READ);                    // Open the file
    while(file.available()) {
      //Lets read line by line from the file
      String line = file.readStringUntil('\n');
      //writelog(line);
      int p=line.indexOf("=");
      String var=line.substring(0,p);
      String value=line.substring(p+1);
      if(toFind==var){
        file.close(); 
        //writelog("trovata "+value);  
        return value;
        }
    }
    file.close();                                          // Close the file again
    //Serial.println(String("\tSent file: ") + path);
  return "";
  }
  }

String allDataFiller(){//********costruisce il JSON
   String result="{";
    String path="/data.ini";
   
  if ( SD.exists(path)) { // If the file exists, either as a compressed archive, or normal                                    
    File file = SD.open(path, FILE_READ);                    // Open the file
    while(file.available()) {
      //Lets read line by line from the file
      String line = file.readStringUntil('\n');
      //writelog(line);
      int p=line.indexOf("=");
      String var=line.substring(0,p);
      if(var!=""){
          String value=line.substring(p+1);
          value=value.substring(0,value.length()-1);
          value.replace("/","");
          result=result+"\""+var+"\":\""+value+"\",";
           //writelog(result);
      }
     
    }
    file.close();
    result=result.substring(0,result.length()-1)+"}";
    writelog("ALLDATAFILLER "+result);                                       
    //Serial.println(String("\tSent file: ") + path);
  return result;
  }
  }
  
String dataRead(String toFind){
    String path="data.ini";
     File file = SD.open(path, FILE_READ); 
   String line="";     
  if (file) {
   // Serial.println("data.ini:");
    // read from the file until there's nothing else in it:
    while (file.available()) {
     line = file.readStringUntil('\r');
   // Serial.println(line); //Printing for debugging purpose         
    int p=line.indexOf("=");
      String var=line.substring(1,p);
  //    Serial.println("var "+var);  
   //   Serial.println("tofind "+toFind); 
      String value=line.substring(p+1);
      if(toFind==var){
        file.close(); 
        Serial.println("trovata "+value);  
        return value;
        }
    }
    // close the file:
    file.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.ini");
  }
}

boolean dataSave(String key,String value){
   String path="/data.ini";
   String pathw="/data.tmp";
   Serial.println("copy");
   writelog("datasave "+path);
  if (SD.exists(path)) {  
       Serial.println("saveexist"); 
       File filew = SD.open(pathw, FILE_WRITE);
       File file = SD.open(path, FILE_READ);                    // Open the file
      //size_t sent = server.streamFile(file, contentType);    // Send it to the client
       while(file.available()) {
        //Lets read line by line from the file
        String line = file.readStringUntil('\n');
        line=line.substring(0,line.length()-1);
        if(line.startsWith(key)){
            String s=key+"="+value+"/"; 
           filew.println(s); 
          // writelog("datasave3 "+s);
          }else{
             filew.println(line);
            }
              //writelog("datasave2 "+line+"*");
       }
   
       file.close();
       filew.close();// Close the file again
       //pathw contiene i dati modificati adesso posso riscriverli nel file di partenza 
       if(SD.exists(pathw))
       {
         SD.remove(path);
         copyfile(path, pathw);
       }
       
       return true;
     }
  return false;
  
  }

boolean dataSaveLimit(int num_anta,String value){
   String path="/limit.ini";
   String pathw="/limit.tmp";
   Serial.println("copy");
   String key=""+num_anta;
   writelog("datasave "+path);
  if (SD.exists(path)) {  
       Serial.println("saveexist"); 
       File filew = SD.open(pathw, FILE_WRITE);
       File file = SD.open(path, FILE_READ);                    // Open the file
      //size_t sent = server.streamFile(file, contentType);    // Send it to the client
       while(file.available()) {
        //Lets read line by line from the file
        String line = file.readStringUntil('\n');
        line=line.substring(0,line.length()-1);
        if(line.startsWith(key)){
            String s=key+"="+value+"/"; 
           filew.println(s); 
          // writelog("datasave3 "+s);
          }else{
             filew.println(line);
            }
              //writelog("datasave2 "+line+"*");
       }
   
       file.close();
       filew.close();// Close the file again
       //pathw contiene i dati modificati adesso posso riscriverli nel file di partenza 
       if(SD.exists(pathw))
       {
         SD.remove(path);
         copyfile(path, pathw);
       }
       
       return true;
     }
  return false;
  
  }
 
 
 
 boolean copyfile(String pathfinale,String pathtemp){//usato per rinominare il file 
     Serial.println("copy");                                                 // il file pathtemp viene eliminato e pathfinale sovrascritto se eiste  
   writelog("path finale "+pathfinale+"pathtemp "+pathtemp);
  if (SD.exists(pathtemp)) {  
       File filew = SD.open(pathfinale, FILE_WRITE | O_TRUNC);
       File file = SD.open(pathtemp, FILE_READ);                    // Open the file
       while(file.available()) {
        //Lets read line by line from the file
        String line = file.readStringUntil('\n');
        line=line.substring(0,line.length()-1);
        filew.println(line);
         writelog("copy "+line);
       }
        file.close();
       filew.close();// Close the file again
       //pathw contiene i dati modificati adesso posso riscriverli nel file di partenza 
       SD.remove(pathtemp);
       return true;
     }
  return false;
  }

  void writelog(String tolog){
  //  Serial.println("log"); 
    String pathlog="/log.htm";
  if (SD.exists(pathlog)) { 
     File file = SD.open(pathlog, FILE_WRITE);                    // Open the file
     file.print(tolog+"<br>");
    file.close();                                          // Close the file again
  // Serial.println("endlog"); 
  }
  }

  void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
