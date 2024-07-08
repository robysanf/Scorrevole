void avanti_2() {
  if (giro == cadenza) {
    giro = 0;
    long t = micros();          // -- fermo il tempo
    t_delta = t - T1;           // -- calcolo il tempo trascorso
    V_M = (imp_vel / t_delta);  // -- calcolo la velocità
    T1 = t;                     // -- salvo il tempo
  }
  giro++;
}

void avanti_3() {
  (digitalRead(3) == digitalRead(2)) ? pos = pos - encoder : pos = pos + encoder;
}