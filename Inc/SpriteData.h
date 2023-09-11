// SpriteData.h
// Runs on TM4C123
// 04/28/23

#include "stdint.h"
#include "ADC.h"
#include "Nokia5110.h"

/* Define variables */
#define ENEMY_WIDTH 	18
#define ENEMY_HEIGHT 	10
#define MAX_ENEMYX 		MAX_X-ENEMY_WIDTH
#define NUM_ENEMY 		3
#define PLAYERW     	((unsigned char)PlayerShip0[18])
#define PLAYERH 			((unsigned char)PlayerShip0[22])
#define LASERW      	2
#define LASERH      	9
#define FAST					3
#define MEDIUM				2
#define SLOW					1

/* Struct(s) */
typedef struct {
  uint8_t x;               // x coordinate
  uint8_t y;               // y coordinate
  const uint8_t *image;    // ptr->image
  uint8_t life;            // 0=dead, 1=alive
} STyp;

/* Objects */
extern STyp Enemy[NUM_ENEMY]; 			// 3 enemy objects
extern STyp PlayerShip;							// 1 player spacechip object
extern STyp Laser;									// Laser object

/* Global values */
extern volatile uint8_t d_enemies, score;

/* Functions */
void Laser_Init(void);
void Enemy_Init(void);
void Player_Init(void);
void Laser_Draw(void);
uint8_t Obj_Coll(STyp Obj0, STyp Obj1);
void Enemy_Draw(void);
void Player_Draw(void);
void Laser_Move(uint8_t speed);
void Enemy_Move(uint8_t speed);
void Player_Move(void);
void Draw(void);
void beginMenu(void);
void gameOver(void);
