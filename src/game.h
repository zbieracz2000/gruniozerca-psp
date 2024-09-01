#ifndef GAME_H_INCLUDE
#define GAME_INCLUDE
extern int screen;
extern int score;
extern int life;
extern int hiscore;
extern int speed;
extern struct carrot {
	int is; //stan
	int color; //kolor
	int h; //wysokosc
	int x; //pozycja
	int col; //kolizja
};
extern struct carrot c1;
extern struct carrot c2;
extern struct carrot c3;
void resetcarrots();
#endif //GAME_H_INCLUDE
