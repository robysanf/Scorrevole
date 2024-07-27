//***************************************************

#include "arduino_secrets.h"
#include <SPI.h>



//*************************************************

#include "DualMC33926MotorShield.h"
#include "VARIABILI.h"


DualMC33926MotorShield md;


//************************************************************************
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8+
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
//int status = WL_IDLE_STATUS;
unsigned int localPort = 2300 + atoi(sonoio); //61;      // local port to listen on
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[255];       // a string to send back
char hold_packet[255];
IPAddress ip(192, 168, 81, atoi(sonoio)); //si usa se non ho il router che gli assegna lui IP
IPAddress ipdns(192, 168, 8, 1);
IPAddress ipgate(192, 168, 8, 1);
IPAddress ipmask(255, 255, 255, 0);

//**********************************************************************

int led =  LED_BUILTIN;//pin 13 su 33 IOT

void setup() {
  pinMode(5, OUTPUT); // PIN PER DROP-BOLT
  pinMode(11, OUTPUT); // PIN PER HC
  pinMode(led, OUTPUT);       // set the LED pin mode
  pinMode(A2, INPUT);         // VALORE DEL PIN PER CONTROLLO TENSIONE
  pinMode(A7, INPUT_PULLUP);  // VALORE DEL PIN PER ANTA FINE CORSA BASSO
  pinMode(A6, INPUT_PULLUP);  // VALORE DEL PIN PER ANTA FINE CORSA BASSO
  pinMode(2, INPUT_PULLUP);  //PIN ENCODER
  pinMode(3, INPUT_PULLUP);  //PIN ENCODER
  digitalWrite(5, LOW);
  digitalWrite(11, HIGH);
  attachInterrupt(digitalPinToInterrupt(3), avanti_3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), avanti_2, RISING);
  //***************************** INIZIALIZZO MOTORI
  md.init();
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(2000);
  Serial.println("Init Motore");
  digitalWrite(4, HIGH);
  delay(2);
  md.setM2Speed(0);
  digitalWrite(4, LOW);
  //***********
  //*********** moltiplico per imp perchè la variabile in variabili.h indica i millimetri e check pos controlla il pos cioè il numero di impulsi
  //***********
  spazioRallenta = spazioRallenta * imp;
  quasiChiuso = quasiChiuso * imp;
  spazio_no_chk_vel = spazio_no_chk_vel * imp;
  Stato_Alzata[0] = 'I';
  //************ IMPOSTAZIONI WIFI
  //************ SE SI USA ROUTING STATICO SUL ROUTER TOGLIERE COMMENTARE WIFI.CONFIG
}

void loop() {
  //long tempo = micros();

  //********* RICEVE I DATI DAL MASTER E INVIA LA STRINGA DI RISPOSTA CON LO STATO ALZATA, IL DIR, IL POS, E EVENTUALE EMERGENZA
  Ascolta_Master();
  delay(7);
  //********** INTERPRETA LA STRINGA RICEVUTA ED ESEGUE IL RELATIVO COMANDO
  che_faccio();
  delay(7);
  fai_media();
  delay(7);
  if (_Dir != 0) {
    controlla_velocita_WARD();
    // -----------------------------------------------
    // PASSO DA qua  e guardo il tempo
    // se il tempo salvato in passato è piu vecchio di un secondo
    if ( (millis() - check_time) > 1000 ) {
      //   entro  controllo il movimento e salvo il tempo e il pos
      check_time = millis();
      int pos_dif = abs(check_pos_old - pos);
      if ( pos_dif < 2.5 * imp ) { //  vuol dire 0,5 cm/sec
        Serial.println("fermo per niente");
        //Serial.print(" check_pos_old = "); Serial.println(check_pos_old);
        Serial.print(" pos_dif = "); Serial.println(pos_dif);
        ferma_WARD(30);
        //devo avvisare il master che ho fermato qui
        Stato_Anta[0] = 'S';
        // fatto
      }
      check_pos_old = pos;
    }
    // -----------------------------------------------
  }
  delay(7);
  if (_Dir == 0) {
    for (int ic = 0; ic < 20; ic++) {
      corrente[ic] = 0;
    }
  }
  delay(7);
  if (set == 1)
  {
    check_pos();
  }
  delay(7);
  if (  _Dir != 0 && limit_senza_curva(5)) {
    emergenza(66);
  }
  delay(7);
  tensione_batteria = map(analogRead(A2), 0, 4095, 0, 3300);
  contatore = contatore + 1 ;
 // Serial.print("Tempo = ");Serial.println(micros()-tempo);
}
