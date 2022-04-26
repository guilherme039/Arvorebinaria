#include <stdio.h>
#include "btree.h"

void visita(No* no) {
  printf("%c ", no->info);
}

int main(void) {

  No *um = criaNo('+');
  No *dois = criaNo('*');
  No *tres = criaNo('*');
  No *quat = criaNo('a');
  No *cinc = criaNo('b');
  No *seis = criaNo('c');
  No *sete = criaNo('+');
  No *oito = criaNo('d');
  No *nove = criaNo('e');

  int err = insereEsq(dois, um);
  err = insereDir(tres, um);
  err = insereEsq(quat, dois);
  err = insereDir(cinc, dois);
  err = insereEsq(seis, tres);
  err = insereDir(sete, tres);
  err = insereEsq(oito, sete);
  err = insereDir(nove, sete);
  
  caminhaEmOrdem(um, &visita);
  printf("\n\n");

  caminhaPreOrdem(um, &visita);
  printf("\n\n");

  caminhaPosOrdem(um, &visita);
  printf("\n\n");

  buscaEmLargura(um, &visita);
  printf("\n\n");

  destroiArvore(um);
  
  return 0;
}