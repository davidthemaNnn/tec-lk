#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define ADBLOCKER 'b'

int acabou();
void move(char direcao);
 
int ehdirecao(char direcao);
void anuncios();
void bloqueiaanuncio();
void bloqueiaanuncio2(int x, int y, int somax, int somay, int qtd);


#endif