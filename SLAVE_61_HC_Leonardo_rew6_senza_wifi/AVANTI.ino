void avanti_2() {
  if (giro == cadenza) {
    giro = 0;
    T2 = micros();          // -- fermo il tempo
    V_M = (imp_vel / (T2 - T1));  // -- calcolo la velocità
    T1 = T2;                     // -- salvo il tempo
  }
  giro++;
}

void avanti_3() {
  (digitalRead(3) == digitalRead(2)) ? pos = pos - encoder : pos = pos + encoder;
}
