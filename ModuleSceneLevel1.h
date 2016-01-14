//#pragma once

#ifndef __MODULESCENELEVEL1_H__
#define __MODULESCENELEVEL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct Collider;

class ModuleSceneLevel1 : public Module {
public:
	ModuleSceneLevel1(bool start_enabled = true);
	~ModuleSceneLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:
	Collider* left_collider = nullptr;
	Collider* middle_collider = nullptr;
	Collider* right_collider = nullptr;
	//std::list<Collider*> enemy_spawn;
	Collider* enemy_spawn1 = nullptr;
	Collider* enemy_spawn2 = nullptr;
	Collider* enemy_spawn3 = nullptr;
	Collider* enemy_spawn4 = nullptr;
	Collider* enemy_spawn5 = nullptr;
	
	std::list<Collider*>::iterator it;

	SDL_Rect pre_middle_collider;

	SDL_Texture* background1;
	SDL_Texture* background2;
};

#endif // __MODULESCENELEVEL1_H__