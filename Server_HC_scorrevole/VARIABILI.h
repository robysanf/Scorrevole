int Conta_Loop = 0;
int Conta_Loop2 = 0;
int wait = 10;
int set =0;                              // SET_UP FATTO OPPURE NO
int _Dir = 0;                             // INDICA LA DIREZIONE
int emergenza_dir=0;
String emerg[10];
int emergenza_chi=0;
String limiti[12];
int Previus_Dir = 0;                      // USATO PER IL LETTORE DI CARTE
const int MAX_ANTE=9;
String comando_web="0000";
String ip_prefix="192.168.81.";
String port_prefix="23";
int conta = 1;                           // -- per rallentare il dime nel loop

boolean chiedo_conf = true;
const int RELAY1 = 2;                     // VALORE DEL PIN PER COMANDARE IL DROP-BOLT    
const int STOP = 6;                      // VALORE DEL PIN PER STOP   
const int APRI = 7;                      // VALORE DEL PIN PER APRI  
const int CHIUDI = 8;                    // VALORE DEL PIN PER CHIUDI
volatile int stato_APRI = 0;              // INDICA SE IL PIN APRI E PREMUNTO
volatile int stato_CHIUDI = 0;            // INDICA SE IL PIN CHIUDI E PREMUNTO
volatile int stato_STOP = 0;              // INDICA SE IL PIN STOP E PREMUNTO
volatile String str="";

volatile long tempo_pulsante_1 = 0 ;      // PER TEMPORIZZARE I PULSANTI
volatile long tempo_pulsante_2 = 0 ;      // PER TEMPORIZZARE I PULSANTI
volatile long tempo_pulsante_3 = 0 ;      // PER TEMPORIZZARE I PULSANTI
volatile long T_scemo_1 = 0 ;             // PER TEMPORIZZARE I PULSANTI
volatile long T_scemo_2 = 0 ;             // PER TEMPORIZZARE I PULSANTI
volatile long Tempo_C_U_P = 0 ;           // PER TEMPORIZZARE I PULSANTI

int _Pulsanti ;                           // PER TEMPORIZZARE I PULSANTI
volatile boolean U_P = false;              // UOMO PRESENTE

//String Stato_Slave_[10] ;                 // indica il movimento F> fermo V> veloce L> lento C> collisione S> emergenza dello slave
//String Stato_Anta ;                     // indica il movimento F> fermo V> veloce L> lento C> collisione S> emergenza del master
int Numero_Ante_Slave = 2;                // -- NUMERO DI DEFAULT DELLE ANTE SLAVE
int Ante_Slave[10];                       // -- VARIABILE DOVE SCRIVERE IL NR i2c CORRISPONDENTE
int addr[10];
String My_Buffer[10];

float ritardo[10]; // -- MI SERVE PER MODIFICARE MANUALMENTE LA VELOCITA' DI OGNI SINGOLA ANTA
String encoder[10];   // -- può errere 1 o -1 a seconda di come si muove durante il test di apertura
String motore[10];    // -- può errere 1 o -1 a seconda di come si muove durante il test di apertura
String attrito[10];// {1.00, 1.02, 0.00, 0.00,0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
int peso[10];
int inerzia[10];
String mm_apri_fisso="100";  // espresso in mm
float velocita_crocera_COL = 60;                // VELOCITA IN CASO DI COLLISIONE 
volatile float velocita_crocera_MAX = 70;       // VELOCITA' MASSIMA IN cm/sec
volatile float velocita_crocera_MIN = 30;       // VELOCITA' LENTO IN cm/sec
float velocita_crocera_LENTA = 5;         // -- VELOCITA' DELL'ANTA PIU' LENTA
float velocita_crocera_MAX_slave_[10];  

volatile int conteggio = 0;               // per il spingi e vai
boolean solopassaggio = false;            // per l'apertura parziale
boolean porta_tutta_aperta = false;       // stato porta aperta
boolean porta_tutta_chiusa = false;       // stato porta chiusa

String comando = "0000";                      //comando di stop
String str2 = "";
String str_hold = "";
String addrg="";

String vars = "";

String strweb = "";
String strweb2 = "";
String encoderg = "";

//volatile long pos_slave_[10];             // pos di tutte le ante 0> marter 1> slave1 2> slave2 ....
long pos_aperto[10];                      // VALORE DELLA POSIZIONE TUTTO APERTO

String pos1 ="";
String BARRA ="";
String strwebHost = "";
String strwebHostOld = "";
String error ="";

String Stato_Anta[10];
String Stato_Anta_old[10];
int Direzione_Anta[10];
String Stato_Alzata[10];
long Pos_Anta[10];
int portaRemota[10]; 
String cliEnt[10];
String Comando[10];
String Risposta_Comando[10];
boolean emergenza=false;

enum nomeVar { ADDR, NUMERO_ANTE_SLAVE, ANTE_SLAVE, VELOCITA_CROCERA_MAX,
               VELOCITA_CROCERA_LENTA,VELOCITA_CROCERA_COL, RITARDO,ATTRITO, MOTORE, ENCODER, 
               INERZIA, PESO, POS_APERTO, DIPENDENTE};
               
//*******************************************************************************************************************
boolean dipendente=true;                  // -- INDICA CHE è DIPENDENTE IN APERTURA CENTRALE O AD ANGOLO
boolean apertura=false; 
long apertura_time = 0;
long collisione_[10];
long collisione_anta_[10];
int Spazio_Partenza = 0;                 // espresso in mm
int Spazio_Partenza_init = 100; 
float Spazio_Collisione = 0.00;             // espresso in mm
float Spazio_Collisione_init = 100.00;
float Spazio_Collisione_hold ;            // serve per salvare il valore iniziale
int spazioRallenta= 0;                   // espresso in mm
int spazioRallenta_init= 60;    
int spazio_no_chk_vel = 0;               // espresso in mm
int spazio_no_chk_vel_init = 35;
int Distanza = 0;                        // SPAZIO TRA FINE CORSA "A" E LA COLLISIONE CONTRO "IL MURO" espresso in mm
int Distanza_init = 10;  
int ritardo_collisione = 200;
volatile long Anta_Coll[10];
int Nr_Coll = 0;
float imp = 34.26;
const int CONSENSO_in_lettura = 16;           // -- VALORE DEL PIN PER RICEVERE VIA LIBERA AD APRIRE 
const int CONSENSO_in_scrittura = 17;           // -- VALORE DEL PIN PER RICEVERE VIA LIBERA A CHIUDERE
const int CONSENSO_in_lettura_vento = 46;           // -- VALORE DEL PIN PER RICEVERE VIA LIBERA AL
const int CONSENSO_in_scrittura_vento = 48;           // -- VALORE DEL PIN PER RICEVERE VIA LIBERA A CHIUDERE
int easy_pass = 0;                      // espresso in mm
int easy_pass_init = 750; 
long _percentuale = 0;                    // usato per l'apertura parziale
long Per_Centuale = 2000;              // è un centesimo della apertura totale
boolean test=false;
long tempo_invia = 0;

String emergenza_buffer = "";
boolean riavvio_slave_avvenuto = false;
String Dime = "0000";
