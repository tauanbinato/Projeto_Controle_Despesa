//
//  fila-h.h
//  Fila Exercicio
//
//  Created by Tauan Flores on 6/5/16.
//  Copyright © 2016 Astral Chest. All rights reserved.
//

#ifndef fila_h_h
#define fila_h_h

//Estruturas
typedef struct Fila Fila;

//Relacionado a Colunas
Fila *fila_cria (void);           /* Cria uma fila */
void fila_destroi (Fila *);       /* Destroi uma fila */
int fila_vazia (Fila *);          /* Checa fila vazia , retorna 1 = True  ; 0 = False */
int fila_insere (Fila *, double); /* Insere um numero na fila */
int fila_pop (Fila *, double *);  /* Remove um numero da fila */
void fila_exibe (Fila *);         /* Exibe a lista sem altera-la */


//
#endif /* fila_h_h */
