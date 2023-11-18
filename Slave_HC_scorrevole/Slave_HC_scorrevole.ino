//***************************************************
#include "defines.h"
#include "arduino_secrets.h"

#include <SPI.h>
#include <WiFiNINA.h>

#include <ArduinoOTA.h>

//*************************************************

#include "DualMC33926MotorShield.h"
#include "VARIABILI.h"
#define _Aprimi_DEBUG

DualMC33926MotorShield md;

//************************************************************************
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8+
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
unsigned int localPort = 2300 + atoi(sonoio); //61;      // local port to listen on
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[70];       // a string to send back
char hold_packet[255];
IPAddress ip(192, 168, 81, atoi(sonoio)); //si usa se non ho il router che gli assegna lui IP

//**********************************************************************

int led =  LED_BUILTIN;//pin 13 su 33 IOT

void setup() {

  pinMode(RELAY1, OUTPUT);
  pinMode(HC12, OUTPUT);
  pinMode(2, INPUT_PULLUP);  //PIN ENCODER
  pinMode(3, INPUT_PULLUP);  //PIN ENCODER
  attachInterrupt(digitalPinToInterrupt(3), avanti_3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), avanti_2, RISING);
  //***************************** INIZIALIZZO MOTORI
  md.init();
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);
  Serial.println("Init Motore");
  digitalWrite(RELAY1, LOW);//high
  md.setM1Speed(0);
  digitalWrite(HC12, HIGH);
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
  Stato_Alzata[0] = 'I';                    // -- SERVE PER FAR PARTIRE IL SET RESET RIDOTTO SUL MASTER
  //************ IMPOSTAZIONI WIFI
  //************ SE SI USA ROUTING STATICO SUL ROUTER TOGLIERE COMMENTARE WIFI.CONFIG
  Serial.println("\nStart Client WiFiUdpSendReceiveString on " + String(BOARD_NAME));
  if (WiFi.status() == WL_NO_MODULE)                                       // check for the WiFi module
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  WiFi.config(ip);//COMMENTARE SE ROUTING STATICO
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }
  while (status != WL_CONNECTED)                                            // attempt to connect to Wifi network:
  {
    Serial.print("setup Attempting to connect to SSID: "); Serial.println(ssid);
    status = WiFi.begin(ssid, pass);                                        // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    delay(500);                                                            // wait 5 seconds for connection
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
  Serial.println("\nStarting connection to server...");
                                                    // if you get a connection, report back via serial
  //*******************************************************************
  ArduinoOTA.begin(WiFi.localIP(), "Arduino", "password", InternalStorage);
}

void loop() {
  if (micros() - T1 > 1 / imp * 200000) V_M = 0;
  //**************************************************
  ArduinoOTA.poll();
  while (WiFi.status() != WL_CONNECTED) {
    //ferma_WARD(7);
    WiFi.config(ip);
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(500);
  }
  //********* RICEVE I DATI DAL MASTER E INVIA LA STRINGA DI RISPOSTA CON LO STATO ALZATA, IL DIR, IL POS, E EVENTUALE EMERGENZA
  Ascolta_Master();
  delay(7);
  //********** INTERPRETA LA STRINGA RICEVUTA ED ESEGUE IL RELATIVO COMANDO
  che_faccio();
  fai_media();
  //********** STAMPA LO STATO OGNI 50 GIRI
  if (contatore > 50) {
    Serial.print("velocita = "); Serial.println(V_M);
    contatore = 0;
  }
  delay(7);
  //********* CONTROLLA LA POSIZIONE E CAMBIA STATO_APERTO E STATO_CHIUSO E STATO ANTA A SECONDA DI DOVE SI TROVA
  //********* FERMA QUANDO IN APERTURA IL POS >=POS_APERTO E DIR=1
  //********* DECELERA QUANDO STATO_ANTA "V" O "C" DIR=1 (APRI)
  //********* DECELERA QUANDO STATO_ANTA "L" DIR=-1 (CHIUDI)

  //******** QUANDO IN MOVIMENTO CONTROLLA LA VELOCITA' AUMENTANDO O RIDUCENDO LA TENSIONE SUL MOTORE

  if (_Dir != 0) {
    controlla_velocita_WARD();
  }
  if (_Dir == 0) {
    for (int ic = 0; ic < 20; ic++) {
      corrente[ic] = 0;
    }
  }
  if (set == 1)
  {
    check_pos();
  }
  delay(7);

  //******** QUANDO IN MOVIMENTO CONTROLLA L'ASSORBIMENTO DI CORRENTE DEL MOTORE E LANCIA EMERGENZA SE SUPERA LA SOGLIA DEL METODO LIMIT
  if (  _Dir != 0 && limit()) {
    emergenza(66);
  }
  delay(7);

  contatore = contatore + 1 ;
}


void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  stampa("SSID: ");
  stampaACapo(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  stampa("IP Address: ");
  stampaACapo(String(ip));

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  stampa("signal strength (RSSI):");
  stampa(String(rssi));
  stampaACapo(" dBm");
}

void stampaACapo(String s) {
  stampa(s + "\n\r");
}
void stampa(String s)
{
#ifdef _Aprimi_DEBUG
  Serial.print(s);
#endif
}
