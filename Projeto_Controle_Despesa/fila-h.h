//
//  fila-h.h
//  Fila Exercicio
//
//  Created by Tauan Flores on 6/5/16.
//  Copyright © 2016 Astral Chest. All rights reserved.
//

#ifndef fila_h_h
#define fila_h_h

typedef struct Fila Fila;
Fila *fila_cria (void);
void fila_destroi (Fila *);
int fila_vazia (Fila *);
int fila_insere (Fila *, double); /* insere um numero na fila */
int fila_pop (Fila *, double *);    /* remove um numero da fila */
void fila_exibe (Fila *);         /* exibe a lista sem altera-la */

//Relacionado a Despesas
//int fila_vazia_despesa(Fila *);


#endif /* fila_h_h */
