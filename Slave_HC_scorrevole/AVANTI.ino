// ***************************************************
// da mettere nel loop:
//
// if (micros() - T1 > 1 / imp * 200000) V_M = 0;
//
// da mettrere prima di iniziare a muovere:
//
// V_M = 0;
//
// AGGIUNGERE IN VARIABILI.h     volatile volatile float imp_vel = ((1 / (imp / 2)) * 1000000);
//
// AGGIUNGERE IN CHE_FACCIO case 3311:    imp_vel = ((1 / (imp / 2)) * 1000000);
//
// ***************************************************

void avanti_2()  {
  if (giro == 4) {
    giro = 0;
    long t = micros();                                     // -- fermo il tempo
    int t_delta = t - T1;                                  // -- calcolo il tempo trascorso
    V_M = (imp_vel / t_delta);                             // -- calcolo la velocità
    T1 = t;                                                // -- salvo il tempo
  }
  giro++;
}

void avanti_3()  {
  (digitalRead(3) == digitalRead(2)) ? pos = pos - encoder : pos = pos + encoder ;
}
