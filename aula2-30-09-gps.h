#ifndef _GPS_H_
#define _GPS_H_


#define PONTEIRO '@'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define ANUNCIO 'F'
#define ADBLOCKER 'P'

struct gps {
	char** matriz;
	int linhas;
	int colunas; 
};

typedef struct gps GPS;

void alocagps(GPS* m);
void legps(GPS* m);
void liberagps(GPS* m);

struct posicao {
	int x;
	int y;
};

typedef struct posicao POSICAO;

int encontragps(GPS* m, POSICAO* p, char c);

int ehvalida(GPS* m, int x, int y);
int ehparede(GPS* m, int x, int y);
int ehpersonagem(GPS* m, char personagem, int x, int y);

void andanogps(GPS* m, int xorigem, int yorigem, 
	int xdestino, int ydestino);

void copiagps(GPS* destino, GPS* origem);

int podeandar(GPS* m, char personagem, int x, int y);

#endif
