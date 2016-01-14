// ----------------------------------------------------
// Enemy class    -----------
// ----------------------------------------------------

#ifndef __ENEMY_H__
#define __ENEMY_H__

//#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

enum enemy_race {
	HENINGER,
	LONGMOAN,
	STORCHINAYA,
	SKELETON,
	BAD_BROTHER,
	KNIGHT,
	DEATH_ADDER,
	DEATH_BRINGER
};

enum enemy_attack_strenght {
	ATTACK_A,
	ATTACK_B,
	ATTACK_C,
	ATTACK_D
};

enum enemy_direction {
	ENEMY_RIGHT,
	ENEMY_LEFT
};

enum enemy_state {
	ENEMY_WAIT,
	ENEMY_TRACK,
	ENEMY_ATTACK,
	ENEMY_HURT,
	ENEMY_RECOVER,
	ENEMY_DEAD,
	ENEMY_MOCKERY,
};

class Enemy {
public:

	// Constructor
	Enemy(enemy_race, enemy_attack_strenght);
	~Enemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void change_position(float, float);

public:
	//SDL_Texture* graphics = nullptr;

	//Collider* character_collider = nullptr;

	enemy_direction direction;
	enemy_race race;
	enemy_attack_strenght attack_strenght;
	enemy_state state;
	unsigned short enemy_health;
	float enemy_speed_attack;
	
	bool alive = true;
	iPoint position;
};

#endif //__ENEMY_H__