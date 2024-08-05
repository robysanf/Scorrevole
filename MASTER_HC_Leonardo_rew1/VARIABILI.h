IPAddress ip(192, 168, 81, 90);
int wait = 10;
int set = 0;                              // SET_UP FATTO OPPURE NO
int _Dir = 0;                             // INDICA LA DIREZIONE
int emergenza_dir = 0;
String emerg[10];
int emergenza_chi = 0;
String limiti[12];                     
const int MAX_ANTE = 9;
int conta = 0;                            // -- per rallentare il dime nel loop

boolean chiedo_conf = true;
const int RELAY1 = 2;                     // VALORE DEL PIN PER COMANDARE IL DROP-BOLT
const int STOP = 6;                       // VALORE DEL PIN PER STOP
const int APRI = 7;                       // VALORE DEL PIN PER APRI
const int CHIUDI = 8;                     // VALORE DEL PIN PER CHIUDI
int stato_APRI = 0;                       // INDICA SE IL PIN APRI E PREMUNTO
int stato_CHIUDI = 0;                     // INDICA SE IL PIN CHIUDI E PREMUNTO
int stato_STOP = 0;                       // INDICA SE IL PIN STOP E PREMUNTO
String str = "";

long T_scemo_1 = 0 ;             // PER TEMPORIZZARE I PULSANTI
long T_scemo_2 = 0 ;             // PER TEMPORIZZARE I PULSANTI
int _Pulsanti = 1010;            // PER TEMPORIZZARE I PULSANTI
boolean U_P = false;              // UOMO PRESENTE di default

int Numero_Ante_Slave = 1;       // -- NUMERO DI DEFAULT DELLE ANTE SLAVE
int Ante_Slave[10];              // -- VARIABILE DOVE SCRIVERE IL NR i2c CORRISPONDENTE
int addr[10];
String My_Buffer[10];

float ritardo[10];    // -- MI SERVE PER MODIFICARE MANUALMENTE LA VELOCITA' DI OGNI SINGOLA ANTA
String encoder[10];   // -- può errere 1 o -1 a seconda di come si muove durante il test di apertura
String motore[10];    // -- può errere 1 o -1 a seconda di come si muove durante il test di apertura
String attrito[10];   // {1.00, 1.02, 0.00, 0.00,0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
int peso[10];
int inerzia[10];
int sensibilita = 1;
String mm_apri_fisso = "100";                   // espresso in mm
float velocita_crocera_COL = 60;                // VELOCITA IN CASO DI COLLISIONE
float velocita_crocera_MAX = 70;                // VELOCITA' MASSIMA IN cm/sec
float velocita_crocera_MIN = 30;                // VELOCITA' LENTO IN cm/sec
float velocita_crocera_LENTA = 50;              // -- VELOCITA' DELL'ANTA PIU' LENTA
float velocita_crocera_MAX_slave_[10];



int consumo_Bassa = 300;
int consumo_Media = 600;
int consumo_Alta = 900;
int consumo_max_crocera = 0;
int consumo_Bassa_max = 1200;
int consumo_Media_max = 1800;
int consumo_Alta_max = 2000;


//int conteggio = 0;                        // per il spingi e vai
boolean solopassaggio = false;            // per l'apertura parziale
boolean porta_tutta_aperta = false;       // stato porta aperta
boolean porta_tutta_chiusa = false;       // stato porta chiusa

String comando = "0000";
String str2 = "";
String str_hold = "";
String addrg = "";

String vars = "";

String strweb = "";
String strweb2 = "";
String encoderg = "";

long pos_aperto[10];                      // VALORE DELLA POSIZIONE TUTTO APERTO
int pos_chiuso = 0;
String segno = "";                       //valore del segno dopo move
String pos1 = "";
String BARRA = "";
String strwebHost = "0000";
String strwebHostOld = "";
String error = "";
int cadenza = 1;


String Stato_Anta[10];
String Stato_Anta_old[10];
int Direzione_Anta[10];
String Stato_Alzata[10];
long Pos_Anta[10];
String Comando[10] = {"0000", "0000", "0000", "0000", "0000", "0000", "0000", "0000", "0000", "0000"};
String Risposta_Comando[10];
boolean emergenza = false;

#define STORAGE_BUFFER 500
enum nomeVar1 { RAGGIO, IMP, POS_APERTO, POS_CHIUSO, VELOCITA_BASSA, VELOCITA_MEDIA, VELOCITA_ALTA, MOTORE, ENCODER, CONFIGURAZIONE,
                POS, CADENZA, CONSUMO_BASSA_MAX, CONSUMO_MEDIA_MAX, CONSUMO_ALTA_MAX, DIPENDENTE, NUMERO_ANTE_SLAVE, VELOCITA_CROCERA_MAX,
                VELOCITA_CROCERA_LENTA, VELOCITA_CROCERA_COL, ANTE_SLAVE, RITARDO, ATTRITO, INERZIA, PESO, ADDR , SENSIBILITA
              } ;
const static struct {
  nomeVar1     val;
  const char *str;
} conversion [] = {
  {SENSIBILITA, "SENSIBILITA"},
  {ADDR, "ADDR"},
  {PESO, "PESO"},
  {INERZIA, "INERZIA"},
  {ATTRITO, "ATTRITO"},
  {RITARDO, "RITARDO"},
  {ANTE_SLAVE, "ANTE_SLAVE"},
  {VELOCITA_CROCERA_LENTA, "VELOCITA_CROCERA_LENTA"},
  {VELOCITA_CROCERA_MAX, "VELOCITA_CROCERA_MAX"},
  {VELOCITA_CROCERA_COL, "VELOCITA_CROCERA_COL"},
  {NUMERO_ANTE_SLAVE, "NUMERO_ANTE_SLAVE"},
  {DIPENDENTE, "DIPENDENTE"},
  {RAGGIO, "RAGGIO"},
  {IMP, "IMP"},
  {POS_APERTO, "POS_APERTO"},
  {POS_CHIUSO, "POS_CHIUSO"},
  {VELOCITA_BASSA, "VELOCITA_BASSA"},
  {VELOCITA_MEDIA, "VELOCITA_MEDIA"},
  {VELOCITA_ALTA, "VELOCITA_ALTA"},
  {MOTORE, "MOTORE"},
  {ENCODER, "ENCODER"},
  {CONFIGURAZIONE, "CONFIGURAZIONE"},
  {POS, "POS"},
  {CADENZA, "CADENZA"},
  {CONSUMO_BASSA_MAX, "CONSUMO_BASSA_MAX"},
  {CONSUMO_MEDIA_MAX, "CONSUMO_MEDIA_MAX"},
  {CONSUMO_ALTA_MAX, "CONSUMO_ALTA_MAX"}

};
boolean dipendente = false;                 // -- INDICA CHE è DIPENDENTE IN APERTURA CENTRALE O AD ANGOLO false di default
const int CONSENSO_in_lettura = 4;          // -- VALORE DEL PIN PER RICEVERE VIA LIBERA AD APRIRE
const int CONSENSO_in_scrittura = 5;        // -- VALORE DEL PIN PER RICEVERE VIA LIBERA A CHIUDERE


//-------------------
boolean apertura = false;
int time_strwebHostOld = 0;                // -- per resettare il comando web vecchio


//---------------------
long collisione_[10];
long collisione_anta_[10];
int Spazio_Partenza = 0;                 // espresso in mm

int Spazio_Partenza_init = 50;
float Spazio_Collisione_init = 200.00;         // espresso in mm
float Spazio_Collisione = 0;
float Spazio_Collisione_hold ;            // serve per salvare il valore iniziale
int spazioRallenta = 0;                  // espresso in mm
int spazioRallenta_init = 60;
int spazio_no_chk_vel = 0;               // espresso in mm
int spazio_no_chk_vel_init = 35;
int Distanza = 0;                        // SPAZIO TRA FINE CORSA "A" E LA COLLISIONE CONTRO "IL MURO" espresso in mm
int Distanza_init = 10;
int ritardo_collisione = 100;
volatile long Anta_Coll[10];
int Nr_Coll = 0;
float imp = 6.6;
int easy_pass = 0;                      // espresso in mm
int easy_pass_init = 750;
long _percentuale = 0;                    // usato per l'apertura parziale
long Per_Centuale = 0;                    // è un centesimo della apertura totale
boolean test = false;
boolean log_time = true;
String Batteria_Tensione[10];
boolean riavvio_slave_avvenuto = false;   // -- se uno slave si riavvia per conto suo rifaccio il set_reset_ridotto();
long tempo_invia = 0;
String emergenza_buffer = "";
String Dime = "0000";
String configurazione = "false";
String init_param = "IMP=23.46#DIPENDENTE=false#NUMERO_ANTE_SLAVE=2#VELOCITA_CROCERA_LENTA=70#ENCODER=-1,-1#INERZIA=4,4#POS_APERTO=33000,10000#CONFIGURAZIONE=true#VELOCITA_CROCERA_MAX=250#VELOCITA_CROCERA_COL=80#ATTRITO=0.75,0.75#RITARDO=1.00,1.00#MOTORE=1,1#PESO=30,30#ANTE_SLAVE=61,62#SENSIBILITA=4€aperdere ";
