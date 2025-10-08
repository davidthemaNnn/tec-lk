#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "ponteiro.h"
#include "gps.h"
#include "ui.h"

GPS m;
POSICAO ponteiro;
int temcolor = 0;

int acabou() {
	POSICAO pos;

	int perdeu = !encontragps(&m, &pos, PONTEIRO);
	int ganhou = !encontragps(&m, &pos, ANUNCIO);

	return ganhou || perdeu;
		
}

int ehdirecao(char direcao) {
	return
		direcao == ESQUERDA || 
		direcao == CIMA ||
		direcao == BAIXO ||
		direcao == DIREITA;
}

void move(char direcao) {

	int proximox = ponteiro.x;
	int proximoy = ponteiro.y;

	switch(direcao) {
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}

	if(!podeandar(&m, PONTEIRO, proximox, proximoy))
		return;

	if(ehpersonagem(&m, ANUNCIO, proximox, proximoy)) {
		temcolor=1;
	}

	andanogps(&m, ponteiro.x, ponteiro.y, proximox, proximoy);
	ponteiro.x = proximox;
	ponteiro.y = proximoy;
}

int praondeanunciovai(int xatual, int yatual, 
	int* xdestino, int* ydestino) {

	int opcoes[4][2] = { 
		{ xatual   , yatual+1 }, 
		{ xatual+1 , yatual   },  
		{ xatual   , yatual-1 }, 
		{ xatual-1 , yatual   }
	};

	srand(time(0));
	for(int i = 0; i < 10; i++) {
		int posicao = rand() % 4;

		if(podeandar(&m, ANUNCIO, opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			return 1;
		}
	}

	return 0;
}

void anuncios() {
	GPS copia;

	copiagps(&copia, &m);

	for(int i = 0; i < copia.linhas; i++) {
		for(int j = 0; j < copia.colunas; j++) {
			if(copia.matriz[i][j] == ANUNCIO) {

				int xdestino;
				int ydestino;

				int encontrou = praondeanunciovai(i, j, &xdestino, &ydestino);

				if(encontrou) {
					andanogps(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}

	liberagps(&copia);
}

void bloqueiaanuncio2(int x, int y, int somax, int somay, int qtd) {

	if(qtd == 0) return;

	int novox = x+somax;
	int novoy = y+somay;

	if(!ehvalida(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;

	m.matriz[novox][novoy] = VAZIO;
	bloqueiaanuncio2(novox, novoy, somax, somay, qtd-1);
}

void bloqueiaanuncio() {
	if(!temcolor) return;
	
	bloqueiaanuncio2(ponteiro.x, ponteiro.y, 0, 1, 3);
	bloqueiaanuncio2(ponteiro.x, ponteiro.y, 0, -1, 3);
	bloqueiaanuncio2(ponteiro.x, ponteiro.y, 1, 0, 3);
	bloqueiaanuncio2(ponteiro.x, ponteiro.y, -1, 0, 3);
	
	temcolor = 0;
}

int main() {
	
	legps(&m);
	encontragps(&m, &ponteiro, PONTEIRO);

	do {
		printf("Anúncio: %s\n", (temcolor ? "SIM" : "NÃO"));
		imprimegps(&m);

		char comando;
		scanf(" %c", &comando);

		if(ehdirecao(comando)) move(comando);
		if(comando == BOMBA) bloqueiaanuncio();

		anuncios();

	} while (!acabou());

	liberagps(&m);
}
