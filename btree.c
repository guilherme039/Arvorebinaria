#include "btree.h"
#include <stdio.h>

typedef struct _nof {
  No *no;
  struct _nof *next;
} NoF;

typedef struct _fila {
  NoF *head, *tail;
} Fila;

Fila *criaFila() {
  Fila *temp = (Fila*)malloc(sizeof(Fila));
  if(!temp) return NULL;
  temp->head = NULL;
  temp->tail = NULL;
  return temp;
}

void destroiFila(Fila *f) {
  if(!f->head && !f->tail){
    free(f);
    f = NULL;
    return;
  }
  if(f->head){
    while(f->tail){
      NoF *aux = f->head;
      f->head = aux->next;
      free(aux);
    }
  }
  free(f);
  f = NULL;
}

void push(No *no, Fila *f) {
  if(!f || !no) return;
  NoF *aux = (NoF*)malloc(sizeof(NoF));
  aux->no = no;
  aux->next = NULL;
  if(!f->head){
    f->head = aux;
    f->tail = aux;
    return;
  }
  f->tail->next = aux;
  f->tail = aux;
}

No *pop(Fila *f) {
  if(!f || !f->head) return NULL;
  
  No *temp = f->head->no;
  NoF *aux = f->head;
  f->head = f->head->next;
  if(!f->head){
    f->tail = f->head;
  }
  aux->no = NULL;
  free(aux);
  return temp;
}

No *criaNo(char info) {
  No *temp = (No*)malloc(sizeof(No));
  temp->esq = NULL;
  temp->dir = NULL;
  temp->pai = NULL;
  temp->info = info;

  return temp;
}

void destroiNo(No *no){
  no->esq = NULL;
  no->dir = NULL;
  no->pai = NULL;
  free(no);
  no = NULL;
}

void destroiArvore(No *no) {
  caminhaPosOrdem(no, &destroiNo);
}

int insereEsq(No *filho, No *pai){
  if(!filho && !pai)
    return 1;
  pai->esq = filho;
  filho->pai = pai;
  return 0;
}

int insereDir(No *filho, No *pai){
  if(!filho && !pai)
    return 1;
  pai->dir = filho;
  filho->pai = pai;
  return 0;
}

void caminhaEmOrdem(No *raiz, void(*fn)(No*)) {
  if(!raiz) return;
  
  caminhaEmOrdem(raiz->esq, fn);
  fn(raiz);
  caminhaEmOrdem(raiz->dir, fn);
}

void caminhaPreOrdem(No *raiz, void(*fn)(No*)) {
  if(!raiz) return;
  
  fn(raiz);
  caminhaPreOrdem(raiz->esq, fn);
  caminhaPreOrdem(raiz->dir, fn);
}

void caminhaPosOrdem(No *raiz, void(*fn)(No*)) {
  if(!raiz) return;
  
  caminhaPosOrdem(raiz->esq, fn);
  caminhaPosOrdem(raiz->dir, fn);
  fn(raiz);
}

void buscaEmLargura(No *raiz, void(*fn)(No*)){
  Fila *f = criaFila();

  push(raiz, f);
  while(f->head) {
    No *r = pop(f);
    fn(r);
    if(r->esq)
      push(r->esq, f);
    if(r->dir)
      push(r->dir, f);
  }
  destroiFila(f);
}