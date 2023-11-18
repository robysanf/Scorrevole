/****************************************************************************************************************************
  WiFIUdpWebServer.ino
  For boards with WiFiNINA module/shield.

  created 25 Nov 2012
  by Roberto Seghetto e Roberto Sanfelici
  adapted to WiFi AP Example

  Version: 1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0
 *****************************************************************************************************************************/

#include "defines.h"
#include "arduino_secrets.h"
#include "Variabili.h"

//#include <SPI.h>
#include <WiFiWebServer.h>
#include <SD.h>
#define BUFFER_SIZE     5000
File root;
WiFiWebServer server(80);
File fsUploadFile;
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP), length must be 8+
unsigned int localPort = 2390;      // local port to listen on
int test_alzata = 0;
int cicli_test = 0;
long parti = 0;
boolean test_chiudi = true;
int led =  LED_BUILTIN;
char packetBuffer[256]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
String hold_packet[10];



int status = WL_IDLE_STATUS;

void setup()
{

  IPAddress ip(192, 168, 81, 90);
  Comando[1] = "0000";

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(9600);
  //while (!Serial);
  delay(2000);
  pinMode(APRI, INPUT_PULLUP);
  pinMode(CHIUDI, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Serial.println("\nStart AP_SimpleWebServer on " + String(BOARD_NAME));
  delay(2000);
  pinMode(led, OUTPUT);      // set the LED pin mode
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please upgrade the firmware");
  }
  Serial.print("Creating access point named: ");
  Serial.println(ssid);
  WiFi.config(ip); //commentare questa riga se si definisce l'IP nel route statico del Mango
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING)
  {
    Serial.println("Creating access point failed");
    while (true);
  }
  server.on(F("/"), handleRoot);
  server.on(F("/test.svg"), drawGraph);
  server.on(F("/inline"), []()
  {
    server.send(200, F("text/plain"), F("This works as well"));
  });
  server.on("/uploadf", HTTP_POST,                      // if the client posts to the upload page
  []() {},
  handleFileUpload                                    // Receive and save the file
           );
  server.on("/upload", HTTP_GET, []() {                 // if the client requests the upload page
    if (!handleFileRead("/upload.htm"))                // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  server.onNotFound(handleNotFound);
  server.begin();
  // you're connected now, so print out the status
  printWiFiStatus();
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:

  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  Serial.print(F("HTTP server started @ "));
  Serial.println(WiFi.localIP());
  root = SD.open("/");
  printDirectory(root, 0); digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  Distanza = Distanza * imp;                              // convertito in impulsi
  easy_pass = easy_pass * imp;                            // convertito in impulsi
  Spazio_Partenza = Spazio_Partenza * imp;                // convertito in impulsi
  //quasiChiuso = quasiChiuso * imp;                        // convertito in impulsi
  spazioRallenta = spazioRallenta * imp;                  // convertito in impulsi
  Spazio_Collisione = Spazio_Collisione * imp;            // convertito in impulsi
  Spazio_Collisione_hold = Spazio_Collisione;
  spazio_no_chk_vel = spazio_no_chk_vel * imp;
  collisione_anta_[1] = 3080 ; collisione_anta_[2] = 3080 ; collisione_anta_[3] = 2150 ; //
}

void loop() {
  if ( apertura && (millis() - apertura_time) > 300) {
    Partenza_Sicura(1, 0, 0);
    apertura = false;
  }
  server.handleClient();
  if ( chiedo_conf ) {
    Serial.println("CONFIGURAZIONE IN CORSO");
    chiedo_configurazioni();
    chiedo_conf = !chiedo_conf;
  }
  int conteggio = 1;
  // -- controllo i pulsanti
  Check_Pin();
  // -- controllo le ante e se il comando mi ritorna
  delay(1);
  for (int i = 1 ; i <= Numero_Ante_Slave ; i++) {
    inVia(i, Dime, 1);
    ricEvi();
    if (emergenza) {
      Emergenza(emergenza_chi, emergenza_dir, emergenza_buffer);
      Serial.println("emergenza");
      emergenza = false;
      emergenza_chi = 0;
      emergenza_dir = 0;
      emergenza_buffer = "";
    }
  }

  /* if (emergenza) {
     Emergenza(emergenza_chi, emergenza_dir);
     Serial.println("emergenza");
     emergenza = false;
     emergenza_chi = 0;
     emergenza_dir = 0;
    }*/

  // -- controllo il web
  ascolta_web();
  delay(10);
  conta++;
}
