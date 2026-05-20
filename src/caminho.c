#include <stdlib.h>
#include <math.h>
#include "caminho.h"

int ContarInstrucoes(Caminho* C) {
    
    if (C == NULL) return -1;

    return C->N;
}

Posicao* DeterminarFim(Caminho* C) {
        
    if(C == NULL) return NULL;

    return C->Fim;
}

Caminho* InicializarCaminho(const char* Sequencia, int xInicial, int yInicial) {
    
    if(Sequencia == NULL) return NULL;

    Caminho* C = (Caminho*) malloc(sizeof(Caminho));

    if (C == NULL) return NULL;

    C->Inicio = NULL;
    C->Fim = NULL;
    C->Historico = NULL;
    C->Instrucoes = NULL;
    C->N = 0;

    Posicao* primeiraPosicao = (Posicao*) malloc(sizeof(Posicao));

    if(primeiraPosicao == NULL) {
        free(C);
        return NULL;
    }

    primeiraPosicao->X = xInicial;
    primeiraPosicao->Y = yInicial;
    primeiraPosicao->Proximo = NULL;

    C->Inicio = primeiraPosicao;
    C->Fim = primeiraPosicao;
    C->Historico = primeiraPosicao;

    Comando* ultimoComando = NULL;
    Posicao* ultimaPosicao = primeiraPosicao;

    int xAtual = xInicial;
    int yAtual = yInicial;

    for(int i = 0; Sequencia[i] != '\0'; i++) {
       
        if(Sequencia[i] != 'N' && Sequencia[i] != 'S' && Sequencia[i] != 'L' && Sequencia[i] != 'O') {
            DestruirCaminho(C);
            return NULL;
        }
        
        Comando* novoComando = (Comando*) malloc(sizeof(Comando));

        if(novoComando == NULL) {
            DestruirCaminho(C);
            return NULL;
        }

        novoComando->Direcao = Sequencia[i];
        novoComando->Proximo = NULL;

        if(C->Instrucoes == NULL) {
            C->Instrucoes = novoComando;
        } else {
            ultimoComando->Proximo = novoComando;
        }

        ultimoComando = novoComando;  

        if (Sequencia[i] == 'N') {
            yAtual++;
        } else if (Sequencia[i] == 'S') {
            yAtual--;
        } else if (Sequencia[i] == 'L') {
            xAtual++;
        } else if (Sequencia[i] == 'O') {
            xAtual--;
        }

        Posicao* novaPosicao = (Posicao*) malloc(sizeof(Posicao));

        if(novaPosicao == NULL) {
            DestruirCaminho(C);
            return NULL;
        }

        novaPosicao->X = xAtual;
        novaPosicao->Y = yAtual;
        novaPosicao->Proximo = NULL;

        ultimaPosicao->Proximo = novaPosicao;
        ultimaPosicao = novaPosicao;
        C->Fim = novaPosicao;
        C->N++;
    }

    return C;
}

void DestruirCaminho(Caminho* C) {
    
    if(C == NULL) return;

    Posicao* atual = C->Historico;
    Posicao* Proximo;

    while (atual != NULL) {
        Proximo = atual->Proximo;
        free(atual);
        atual = Proximo;
    }

    Comando* instrucao = C->Instrucoes;
    Comando* proximoInstrucao;

    while (instrucao != NULL) {
        proximoInstrucao = instrucao->Proximo;
        free(instrucao);
        instrucao = proximoInstrucao;
    }

    free(C);
}

Posicao* HistoricoPosicoes(Caminho* C) {
    
    if(C == NULL) {
        return NULL;
    } else{
        return C->Historico;
    }
}

int CalcularDistanciaTotal(Caminho* C) {
    
    if(C == NULL) return -1;
    
    return C->N;
    
}

int CalcularDistanciaManhattan(Caminho* C) {
    
    if(C == NULL) return -1;

    if(C->Fim == NULL || C->Inicio == NULL) return -1;

    int distanciaX = C->Fim->X - C->Inicio->X;
    int distanciaY = C->Fim->Y - C->Inicio->Y;

    return abs(distanciaX) + abs(distanciaY);

}

double CalcularDistanciaGeometrica(Caminho* C) {
    
    if(C == NULL) return -1.0;

    if(C->Inicio == NULL || C->Fim == NULL) return -1.0;

    int distanciaX = C->Fim->X - C->Inicio->X;
    int distanciaY = C->Fim->Y - C->Inicio->Y;

    return sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
}