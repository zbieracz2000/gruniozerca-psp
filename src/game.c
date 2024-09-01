//#include "includes.h"
int screen = 1;
int score = 0;
int life = 3;
int speed = 1;
int hiscore;
struct carrot {
	int is; //stan
	int color; //kolor
	int h; //wysokosc
	int x; //pozycja
	int col; //kolizja
};
struct carrot c1;
struct carrot c2;
struct carrot c3;
void resetcarrots() { //funkcja resetująca marchewy do początkowego stanu
    c1.is=0;
    c1.color=5;
    c1.h=0;
    c1.x=0;
    c1.col=0;
    c2.is=0;
    c2.color=5;
    c2.h=0;
    c2.x=0;
    c2.col=0;
    c3.is=0;
    c3.color=5;
    c3.h=0;
    c3.x=0;
    c3.col=0;
}