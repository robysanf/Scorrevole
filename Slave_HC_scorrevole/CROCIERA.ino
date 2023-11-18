boolean crocera(int verso) {
  velocita_misurata = Tachi_Metro();
  if ( (verso == 1 && velocita_misurata > (velocita_crocera * (1 - V_Range_UP))) || (verso == -1 && velocita_misurata < (velocita_crocera * (1 + V_Range_Down )))) {
    return true;
  }
  else {
    return false;
  }
}
