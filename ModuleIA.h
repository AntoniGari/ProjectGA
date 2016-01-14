#ifndef __MODULEIA_H__
#define __MODULEIA_H__

#include<list>
#include "Application.h"
#include "Animation.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "Module.h"
#include "Timer.h"
#include "Globals.h"

enum actual_wave {
	WAVE_1,
	WAVE_2,
	WAVE_3,
	WAVE_4,
	WAVE_5,
	WAVE_6,
	WAVE_7,

	WAVE_MAX
};


class ModuleIA : public Module {
public:
	ModuleIA(bool start_enabled = true);
	~ModuleIA();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void nextWave();
	void nextLevel();
	void startWave();

	void hurt(int);
	void hurt_all(int);

	void animationsForEnemy1();
	void animationsForEnemy2();
	void animationsForEnemy3();
	void animationsForEnemy4();

	Timer* timer1;
	Timer* timer2;
	Timer* timer3;
	Timer* timer4;

	bool active;
	actual_wave wave;

private:
	std::list<Enemy> **all_waves;
	std::list<Enemy> actual_enemies;
	
	std::list<Enemy> wave_amazones_2;
	std::list<Enemy> wave_amazones_3;

	Enemy* left_enemy;
	Enemy* right_enemy;

	SDL_Texture* enemy_graphics = nullptr;

	//Enemy 1 Animations
	Animation* current_animation1 = nullptr;
	Animation enemy1_idle_right;
	Animation enemy1_idle_left;
	Animation enemy1_up_right;
	Animation enemy1_up_left;
	Animation enemy1_left;
	Animation enemy1_right;
	Animation enemy1_running_right;
	Animation enemy1_running_left;
	Animation enemy1_atacking_right;
	Animation enemy1_atacking_left;
	Animation enemy1_hurted_right;
	Animation enemy1_hurted_left;
	Animation enemy1_dead;

	//Enemy 2 Animations
	Animation* current_animation2 = nullptr;
	Animation enemy2_idle_right;
	Animation enemy2_idle_left;
	Animation enemy2_up_right;
	Animation enemy2_up_left;
	Animation enemy2_left;
	Animation enemy2_right;
	Animation enemy2_running_right;
	Animation enemy2_running_left;
	Animation enemy2_atacking_right;
	Animation enemy2_atacking_left;
	Animation enemy2_hurted_right;
	Animation enemy2_hurted_left;
	Animation enemy2_dead;

	//Enemy 3 Animations
	Animation* current_animation3 = nullptr;
	Animation enemy3_idle_right;
	Animation enemy3_idle_left;
	Animation enemy3_up_right;
	Animation enemy3_up_left;
	Animation enemy3_left;
	Animation enemy3_right;
	Animation enemy3_running_right;
	Animation enemy3_running_left;
	Animation enemy3_atacking_right;
	Animation enemy3_atacking_left;
	Animation enemy3_hurted_right;
	Animation enemy3_hurted_left;
	Animation enemy3_dead;

	//Enemy 4 Animations
	Animation* current_animation4 = nullptr;
	Animation enemy4_idle_right;
	Animation enemy4_idle_left;
	Animation enemy4_up_right;
	Animation enemy4_up_left;
	Animation enemy4_left;
	Animation enemy4_right;
	Animation enemy4_running_right;
	Animation enemy4_running_left;
	Animation enemy4_atacking_right;
	Animation enemy4_atacking_left;
	Animation enemy4_hurted_right;
	Animation enemy4_hurted_left;
	Animation enemy4_dead;
};


#endif //__MODULEIA_H__

