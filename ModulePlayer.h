#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "Point.h"
#include "Timer.h"

struct SDL_Texture;
struct Collider;
struct Particle;


enum character_race {
	AMAZON,
	BARBARIAN,
	DWARF
};

enum character_direction {
	RIGHT,
	LEFT
};

enum character_camara_state {
	BLOCKED,
	NON_BLOCKED
};

enum character_state {
	NONE,
	PRERUNNINGLEFT,
	PRERUNNINGRIGHT,
	RUNNINGLEFT,
	RUNNINGRIGHT,
	ATTACK,
	MAGIC,
	JUMP
};

enum application_scene_level {
	SCENE_LEVEL_1,
	SCENE_LEVEL_MAX
};

class ModulePlayer : public Module {
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	
	Collider* character_collider = nullptr;
	
	Animation* current_animation = nullptr;
	Animation idle_right;
	Animation idle_left;
	Animation up_right;
	Animation up_left;
	Animation left;
	Animation right;
	Animation running_right;
	Animation running_left;
	Animation jumping_right;
	Animation jumping_left;
	Animation atacking_right;
	Animation atacking_left;
	Animation magic;

	character_direction direction;
	character_race race;
	character_state state;
	character_camara_state camara_state;
	application_scene_level app_scene_level;
	unsigned short character_health;
	unsigned short int character_lifes;
	unsigned short int character_coins;
	unsigned short int character_mana;

	Timer* character_timer;

	uint fx_attack = 0;
	uint fx_magic_level1 = 0;
	
	bool finished = false;
	bool finished_wave = false;
	iPoint position;
	iPoint preposition;
};

#endif // __MODULEPLAYER_H__