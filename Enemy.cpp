#include "Globals.h"
#include "Application.h"
#include "Enemy.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include <time.h>

Enemy::Enemy(enemy_race r, enemy_attack_strenght as) {
	LOG("Creating Enemy");
	
	/* initialize random seed: */
	srand(time(NULL));

	// Character general declarations
	int random_direction = rand() % 2;
	switch (random_direction) {
	case 0:
		direction = ENEMY_RIGHT;
		break;
	case 1:
		direction = ENEMY_LEFT;
		break;
	}

	race = r;
	attack_strenght = as;
	state = ENEMY_TRACK;
	

	//Enemy Characteristics
	switch (race) {
		case HENINGER:
		case LONGMOAN:
		case SKELETON:
		case BAD_BROTHER:
		case KNIGHT:
		case DEATH_ADDER:
		case DEATH_BRINGER:
		case STORCHINAYA:

		//graphics = App->textures->Load("enemy\\storchinaya.png");
		enemy_health = 4;
		switch (attack_strenght) {
		case ATTACK_A:
			enemy_speed_attack = 0.05f;
		case ATTACK_B:
			enemy_speed_attack = 0.1f;
		case ATTACK_C:
			enemy_speed_attack = 0.2f;
		default:
			break;
		}
		break;
	}

	//Others
	alive = true;
	
	
}

Enemy::~Enemy() {
}

// Load assets
bool Enemy::Start() {
	return true;
}

// Unload assets
bool Enemy::CleanUp() {
	LOG("Unloading enemy");

	return true;
}

void Enemy::change_position(float speed_x, float speed_y) {
	position.x += speed_x;
	position.y += speed_y;
}