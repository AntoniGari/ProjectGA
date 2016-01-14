#include "Enemy.h"
#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleIA.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "Timer.h"
#include <time.h>
#include "SDL/include/SDL.h"
#include<list>


ModuleIA::ModuleIA(bool start_enabled) : Module(start_enabled) {
	all_waves = new std::list<Enemy> *[SCENE_LEVEL_MAX];
	for (int i = 0; i < SCENE_LEVEL_MAX; i++)
		all_waves[i] = new std::list<Enemy>[WAVE_MAX];
	
	wave = WAVE_1;
}

ModuleIA::~ModuleIA() {
}

bool ModuleIA::Start() {
	/* PREPARING WAVES */
	wave_amazones_2.push_back({ STORCHINAYA, ATTACK_A });
	wave_amazones_2.push_back({ STORCHINAYA, ATTACK_A });
	wave_amazones_3.push_back({ STORCHINAYA, ATTACK_A });
	wave_amazones_3.push_back({ STORCHINAYA, ATTACK_A });
	wave_amazones_3.push_back({ STORCHINAYA, ATTACK_A });
			
	/* LEVEL 1 */
	all_waves[SCENE_LEVEL_1][WAVE_1] = wave_amazones_2;
	all_waves[SCENE_LEVEL_1][WAVE_2] = wave_amazones_2;
	all_waves[SCENE_LEVEL_1][WAVE_3] = wave_amazones_2;
	all_waves[SCENE_LEVEL_1][WAVE_4] = wave_amazones_2;

	enemy_graphics = App->textures->Load("enemy\\storchinaya.png");

	timer1 = new Timer();
	timer2 = new Timer();
	timer3 = new Timer();
	timer4 = new Timer();

	/* initialize random seed: */
	srand(time(NULL));

	active = false;
	return true;
}

update_status ModuleIA::PreUpdate() {
	if (active) {
		if (left_enemy == NULL) {

		}
		if (right_enemy == NULL) {

		}
	}
	return UPDATE_CONTINUE;
}


update_status ModuleIA::Update() {
	if (active) {
		list<Enemy>::iterator it;
		int i = 0;

		for (it = actual_enemies.begin(); it != actual_enemies.end(); ++it) {
			if (App->player->state != MAGIC) {
				switch (it->state) {
				case ENEMY_WAIT:
					break;
				case ENEMY_TRACK:
					LOG("ENEMIC X %d - Y %d", it->position.x, it->position.y);
					LOG("JUGADOR X %d - Y %d", App->player->position.x, App->player->position.y);
					if (it->position.x < App->player->position.x) {
						LOG("POSICIO X MES PETITA");
						it->direction = ENEMY_LEFT;
						it->change_position(0.1, 0);
						//it->position.x += 0.1;
					}
					else if (it->position.x > App->player->position.x) {
						LOG("POSICIO X MES GRAN");
						it->direction = ENEMY_RIGHT;
						it->change_position(-0.1, 0);
						//it->position.x -= 0.1;
					}

					if (it->position.y < App->player->position.y) {
						LOG("POSICIO Y MES PETITA");
						it->change_position(0, 0.1);
						//it->position.y += 0.1;
					}
					else if (it->position.y > App->player->position.y) {
						LOG("POSICIO Y MES GRAN");
						it->change_position(0, -0.1);
						//it->position.y -= 0.1;
					}


					switch (i) {
					case 0:
						if (current_animation1 != &enemy1_right) {
							enemy1_right.Reset();
							current_animation1 = &enemy1_right;
						}
						break;
					case 1:
						if (current_animation2 != &enemy2_right) {
							enemy2_right.Reset();
							current_animation2 = &enemy2_right;
						}
						break;
					case 2:
						if (current_animation3 != &enemy3_right) {
							enemy3_right.Reset();
							current_animation3 = &enemy3_right;
						}
						break;
					case 3:
						if (current_animation4 != &enemy4_right) {
							enemy4_right.Reset();
							current_animation4 = &enemy4_right;
						}
						break;
					}

					break;
				case ENEMY_ATTACK:
					break;
				case ENEMY_HURT:
					switch (i) {
					case 0:
						if (timer1->Compare(1000)) {
							it->state = ENEMY_TRACK;
							timer1->Stop();
						}
						break;
					case 1:
						if (timer2->Compare(1000)) {
							it->state = ENEMY_TRACK;
							timer2->Stop();
						}
						break;
					case 2:
						if (timer3->Compare(1000)) {
							it->state = ENEMY_TRACK;
							timer3->Stop();
						}
						break;
					case 3:
						if (timer4->Compare(1000)) {
							it->state = ENEMY_TRACK;
							timer4->Stop();
						}
						break;
					}


					break;
				case ENEMY_RECOVER:
					break;
				case ENEMY_DEAD:
					switch (i) {
					case 0:
						current_animation1 = &enemy1_dead;
						break;
					case 1:
						current_animation2 = &enemy2_dead;
						break;
					case 2:
						current_animation3 = &enemy3_dead;
						break;
					case 3:
						current_animation4 = &enemy4_dead;
						break;
					}

					break;
				case ENEMY_MOCKERY:
					break;
				default:
					break;
				}
				//LOG("ANEM A PINTAR ENEMIC %d",i)
				LOG("PINTEM ENEMIC");
				LOG("ENEMIC X %d - Y %d", it->position.x, it->position.y);
				LOG("JUGADOR X %d - Y %d", App->player->position.x, App->player->position.y);
				if (it->position.y < App->player->position.y) {
					switch (i) {
					case 0:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation1->GetCurrentFrame()));
						break;
					case 1:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation2->GetCurrentFrame()));
						break;
					case 2:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation3->GetCurrentFrame()));
						break;
					case 3:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation4->GetCurrentFrame()));
						break;
					}
				}
			} else {
				if (it->position.y < App->player->position.y) {
					switch (i) {
					case 0:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation1->GetCurrentFrame()));
						break;
					case 1:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation2->GetCurrentFrame()));
						break;
					case 2:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation3->GetCurrentFrame()));
						break;
					case 3:
						App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation4->GetCurrentFrame()));
						break;
					}
				}
			}
										
			++i;
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleIA::PostUpdate() {
	if (active) {
		list<Enemy>::iterator it;
		//list<Animation>::iterator it2;
		int i = 0;

		for (it = actual_enemies.begin(); it != actual_enemies.end(); ++it) {
			if (it->position.y >= App->player->position.y) {
				switch (i) {
				case 0:
					App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation1->GetCurrentFrame()));
					break;
				case 1:
					App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation2->GetCurrentFrame()));
					break;
				case 2:
					App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation3->GetCurrentFrame()));
					break;
				case 3:
					App->renderer->Blit(enemy_graphics, it->position.x - 40, it->position.y - 80, &(current_animation4->GetCurrentFrame()));
					break;
				}
			}

			++i;
		}
	}
	return UPDATE_CONTINUE;
}


bool ModuleIA::CleanUp() {
	for (int i = 0; i < SCENE_LEVEL_MAX; i++)
		delete[] all_waves[i];
	delete[] all_waves;
	
	App->textures->Unload(enemy_graphics);

	return true;
}

void ModuleIA::nextLevel() {
	wave = WAVE_1;
}

void ModuleIA::nextWave() {
	switch (wave) {
	case WAVE_1:
		wave = WAVE_2;
		break;
	case WAVE_2:
		wave = WAVE_3;
		break;
	case WAVE_3:
		wave = WAVE_4;
		break;
	case WAVE_4:
		wave = WAVE_5;
		break;
	case WAVE_5:
		wave = WAVE_6;
		break;
	case WAVE_6:
		wave = WAVE_7;
		break;
	default:
		break;
	}
}

void ModuleIA::startWave() {
	LOG("START WAVE");
	actual_enemies = all_waves[App->player->app_scene_level][wave];
	int i = 0;
	list<Enemy>::iterator it;
	
	for (it = actual_enemies.begin(); it != actual_enemies.end(); ++it) {
		it->position.y = App->player->position.y + rand()%20;
		
		switch (it->direction) {
		case ENEMY_RIGHT:
			it->position.x = App->player->position.x + SCREEN_WIDTH / 2;
			break;
		case ENEMY_LEFT:
			it->position.x = App->player->position.x - SCREEN_WIDTH / 2;
			break;
		}
		

		switch (i) {
		case 0:
			animationsForEnemy1();
			switch (it->direction) {
			case ENEMY_RIGHT:
				current_animation1 = &enemy1_right;
				break;
			case ENEMY_LEFT:
				current_animation1 = &enemy1_left;
				break;
			}
			break;
		case 1:
			animationsForEnemy2();
			switch (it->direction) {
			case ENEMY_RIGHT:
				current_animation2 = &enemy2_right;
				break;
			case ENEMY_LEFT:
				current_animation2 = &enemy2_left;
				break;
			}
			break;
		case 2:
			animationsForEnemy3();
			switch (it->direction) {
			case ENEMY_RIGHT:
				current_animation3 = &enemy3_right;
				break;
			case ENEMY_LEFT:
				current_animation3 = &enemy3_left;
				break;
			}
			break;
		case 3:
			animationsForEnemy4();
			switch (it->direction) {
			case ENEMY_RIGHT:
				current_animation4 = &enemy4_right;
				break;
			case ENEMY_LEFT:
				current_animation4 = &enemy4_left;
				break;
			}
			break;
		default:
			break;
		}

		++i;
	}
	active = true;
}

void ModuleIA::hurt(int damage) {
	list<Enemy>::iterator it;
	int dead_counter = 0;
	int i = 0;
	bool hit;
	
	for (it = actual_enemies.begin(); it != actual_enemies.end(); ++it) {
		LOG("ENEMIC X %d - Y %d", it->position.x, it->position.y);
		LOG("JUGADOR X %d - Y %d", App->player->position.x, App->player->position.y);

		hit = false;
		switch (App->player->direction)	{
		case RIGHT:
			if (it->position.x < App->player->position.x + ATTACK_DISTANCE) {
				if (it->position.y > App->player->position.y) {
					if (App->player->position.y + 10 > it->position.y)
						hit = true;
				} else {
					if (App->player->position.y - 10 < it->position.y)
						hit = true;
				}
			}
			break;
		case LEFT:
			if (it->position.x < App->player->position.x - ATTACK_DISTANCE) {
				if (it->position.y > App->player->position.y) {
					if (App->player->position.y + 10 > it->position.y)
						hit = true;
				}
				else {
					if (App->player->position.y - 10 < it->position.y)
						hit = true;
				}
			}
			break;
		}
				
		if (hit) {
			it->enemy_health -= damage;
			LOG("impacte");
			if (it->state != ENEMY_HURT) {
				it->state = ENEMY_HURT;
				switch (it->direction) {
				case ENEMY_RIGHT:
					switch (i) {
					case 0:
						if (current_animation1 != &enemy1_hurted_right) {
							enemy1_hurted_right.Reset();
							current_animation1 = &enemy1_hurted_right;
							timer1->Start();
						}
						break;
					case 1:
						if (current_animation2 != &enemy2_hurted_right) {
							enemy2_hurted_right.Reset();
							current_animation2 = &enemy2_hurted_right;
							timer2->Start();
						}
						break;
					case 2:
						if (current_animation3 != &enemy3_hurted_right) {
							enemy3_hurted_right.Reset();
							current_animation3 = &enemy3_hurted_right;
							timer3->Start();
						}
						break;
					case 3:
						if (current_animation4 != &enemy4_hurted_right) {
							enemy4_hurted_right.Reset();
							current_animation4 = &enemy4_hurted_right;
							timer4->Start();
						}
						break;
					}
					break;
				case ENEMY_LEFT:
					switch (i) {
					case 0:
						if (current_animation1 != &enemy1_hurted_left) {
							enemy1_hurted_left.Reset();
							current_animation1 = &enemy1_hurted_left;
						}
						break;
					case 1:
						if (current_animation2 != &enemy2_hurted_left) {
							enemy2_hurted_left.Reset();
							current_animation2 = &enemy2_hurted_left;
						}
						break;
					case 2:
						if (current_animation3 != &enemy3_hurted_left) {
							enemy3_hurted_left.Reset();
							current_animation3 = &enemy3_hurted_left;
						}
						break;
					case 3:
						if (current_animation4 != &enemy4_hurted_left) {
							enemy4_hurted_left.Reset();
							current_animation4 = &enemy4_hurted_left;
						}
						break;
					}
					break;
				}
			}
			++i;
		}
		if (it->enemy_health <= 0) {
			it->alive = false;
			++dead_counter;
			it->state = ENEMY_DEAD;
		}
	}

	// COMPROVEM SI TOTS ESTAN MORTS
	LOG("DEAD COUNTER: %d", dead_counter);
	if (dead_counter == actual_enemies.size()) {
		active = false;
		App->player->finished_wave = true;
	}
}

void ModuleIA::hurt_all(int damage) {
	list<Enemy>::iterator it;
	int dead_counter = 0;
	int i = 0;

	for (it = actual_enemies.begin(); it != actual_enemies.end(); ++it) {
		it->enemy_health -= damage;
		if (it->state != ENEMY_HURT) {
			switch (it->direction) {
			case ENEMY_RIGHT:
				switch (i) {
				case 0:
					if (current_animation1 != &enemy1_hurted_right) {
						enemy1_hurted_right.Reset();
						current_animation1 = &enemy1_hurted_right;
					}
					break;
				case 1:
					if (current_animation2 != &enemy2_hurted_right) {
						enemy2_hurted_right.Reset();
						current_animation2 = &enemy2_hurted_right;
					}
					break;
				case 2:
					if (current_animation3 != &enemy3_hurted_right) {
						enemy3_hurted_right.Reset();
						current_animation3 = &enemy3_hurted_right;
					}
					break;
				case 3:
					if (current_animation4 != &enemy4_hurted_right) {
						enemy4_hurted_right.Reset();
						current_animation4 = &enemy4_hurted_right;
					}
					break;
				}
				break;
			case ENEMY_LEFT:
				switch (i) {
				case 0:
					if (current_animation1 != &enemy1_hurted_left) {
						enemy1_hurted_left.Reset();
						current_animation1 = &enemy1_hurted_left;
					}
					break;
				case 1:
					if (current_animation2 != &enemy2_hurted_left) {
						enemy2_hurted_left.Reset();
						current_animation2 = &enemy2_hurted_left;
					}
					break;
				case 2:
					if (current_animation3 != &enemy3_hurted_left) {
						enemy3_hurted_left.Reset();
						current_animation3 = &enemy3_hurted_left;
					}
					break;
				case 3:
					if (current_animation4 != &enemy4_hurted_left) {
						enemy4_hurted_left.Reset();
						current_animation4 = &enemy4_hurted_left;
					}
					break;
				}
				break;
			}
		}
				
		if (it->enemy_health <= 0) {
			it->alive = false;
			++dead_counter;
		}

		++i;
	}

	// COMPROVEM SI TOTS ESTAN MORTS
	if (dead_counter == actual_enemies.size()) {
		active = false;
		App->player->finished_wave = true;
	}

}

void ModuleIA::animationsForEnemy1() {
	/* ENEMY ANIMATIONS */
	// idle animation
	enemy1_idle_right.frames.push_back({ 240, 0, 80, 80 });
	enemy1_idle_left.frames.push_back({ 0, 0, 80, 80 });

	/* ENEMY MOVEMENT ANIMATIONS */
	// move upwards
	enemy1_up_right.frames.push_back({ 0, 80, 80, 80 });
	enemy1_up_right.frames.push_back({ 80, 80, 80, 80 });
	enemy1_up_right.frames.push_back({ 160, 80, 80, 80 });
	enemy1_up_right.frames.push_back({ 240, 80, 80, 80 });
	enemy1_up_right.speed = 0.1f;

	enemy1_up_left.frames.push_back({ 0, 160, 80, 80 });
	enemy1_up_left.frames.push_back({ 80, 160, 80, 80 });
	enemy1_up_left.frames.push_back({ 160, 160, 80, 80 });
	enemy1_up_left.frames.push_back({ 240, 160, 80, 80 });
	enemy1_up_left.speed = 0.1f;

	// Move right
	enemy1_right.frames.push_back({ 320, 80, 80, 80 });
	enemy1_right.frames.push_back({ 400, 80, 80, 80 });
	enemy1_right.frames.push_back({ 480, 80, 80, 80 });
	enemy1_right.frames.push_back({ 560, 80, 80, 80 });
	enemy1_right.speed = 0.1f;

	// Move left 
	enemy1_left.frames.push_back({ 320, 160, 80, 80 });
	enemy1_left.frames.push_back({ 400, 160, 80, 80 });
	enemy1_left.frames.push_back({ 480, 160, 80, 80 });
	enemy1_left.frames.push_back({ 560, 160, 80, 80 });
	enemy1_left.speed = 0.1f;

	/* ENEMY ATACKING ANIMATIONS */
	enemy1_atacking_right.frames.push_back({ 0, 320, 80, 80 });
	enemy1_atacking_right.frames.push_back({ 80, 320, 80, 80 });
	enemy1_atacking_right.frames.push_back({ 160, 320, 80, 80 });
	enemy1_atacking_right.frames.push_back({ 240, 320, 80, 80 });
	enemy1_atacking_right.frames.push_back({ 360, 320, 80, 80 });
	enemy1_atacking_right.speed = 0.1f;

	enemy1_atacking_left.frames.push_back({ 0, 400, 80, 80 });
	enemy1_atacking_left.frames.push_back({ 80, 400, 80, 80 });
	enemy1_atacking_left.frames.push_back({ 160, 400, 80, 80 });
	enemy1_atacking_left.frames.push_back({ 240, 400, 80, 80 });
	enemy1_atacking_left.frames.push_back({ 360, 400, 80, 80 });
	enemy1_atacking_left.speed = 0.1f;

	/* ENEMY HURT ANIMATIONS */
	enemy1_hurted_right.frames.push_back({ 0, 480, 80, 80 });
	enemy1_hurted_right.frames.push_back({ 80, 480, 80, 80 });
	enemy1_hurted_right.frames.push_back({ 160, 480, 80, 80 });
	enemy1_hurted_right.loop = false;
	enemy1_hurted_right.speed = 0.1f;

	enemy1_hurted_left.frames.push_back({ 0, 560, 80, 80 });
	enemy1_hurted_left.frames.push_back({ 80, 560, 80, 80 });
	enemy1_hurted_left.frames.push_back({ 160, 560, 80, 80 });
	enemy1_hurted_left.loop = false;
	enemy1_hurted_left.speed = 0.1f;

	enemy1_dead.frames.push_back({ 320, 560, 80, 80 });
	enemy1_dead.speed = 0.1f;
}

void ModuleIA::animationsForEnemy2() {
	/* ENEMY ANIMATIONS */
	// idle animation
	enemy2_idle_right.frames.push_back({ 240, 0, 80, 80 });
	enemy2_idle_left.frames.push_back({ 0, 0, 80, 80 });

	/* ENEMY MOVEMENT ANIMATIONS */
	// move upwards
	enemy2_up_right.frames.push_back({ 0, 80, 80, 80 });
	enemy2_up_right.frames.push_back({ 80, 80, 80, 80 });
	enemy2_up_right.frames.push_back({ 160, 80, 80, 80 });
	enemy2_up_right.frames.push_back({ 240, 80, 80, 80 });
	enemy2_up_right.speed = 0.1f;

	enemy2_up_left.frames.push_back({ 0, 160, 80, 80 });
	enemy2_up_left.frames.push_back({ 80, 160, 80, 80 });
	enemy2_up_left.frames.push_back({ 160, 160, 80, 80 });
	enemy2_up_left.frames.push_back({ 240, 160, 80, 80 });
	enemy2_up_left.speed = 0.1f;

	// Move right
	enemy2_right.frames.push_back({ 320, 80, 80, 80 });
	enemy2_right.frames.push_back({ 400, 80, 80, 80 });
	enemy2_right.frames.push_back({ 480, 80, 80, 80 });
	enemy2_right.frames.push_back({ 560, 80, 80, 80 });
	enemy2_right.speed = 0.1f;

	// Move left 
	enemy2_left.frames.push_back({ 320, 160, 80, 80 });
	enemy2_left.frames.push_back({ 400, 160, 80, 80 });
	enemy2_left.frames.push_back({ 480, 160, 80, 80 });
	enemy2_left.frames.push_back({ 560, 160, 80, 80 });
	enemy2_left.speed = 0.1f;

	/* ENEMY ATACKING ANIMATIONS */
	enemy2_atacking_right.frames.push_back({ 0, 320, 80, 80 });
	enemy2_atacking_right.frames.push_back({ 80, 320, 80, 80 });
	enemy2_atacking_right.frames.push_back({ 160, 320, 80, 80 });
	enemy2_atacking_right.frames.push_back({ 240, 320, 80, 80 });
	enemy2_atacking_right.frames.push_back({ 360, 320, 80, 80 });
	enemy2_atacking_right.speed = 0.1f;

	enemy2_atacking_left.frames.push_back({ 0, 400, 80, 80 });
	enemy2_atacking_left.frames.push_back({ 80, 400, 80, 80 });
	enemy2_atacking_left.frames.push_back({ 160, 400, 80, 80 });
	enemy2_atacking_left.frames.push_back({ 240, 400, 80, 80 });
	enemy2_atacking_right.frames.push_back({ 360, 400, 80, 80 });
	enemy2_atacking_left.speed = 0.1f;

	/* ENEMY HURT ANIMATIONS */
	enemy2_hurted_right.frames.push_back({ 0, 480, 80, 80 });
	enemy2_hurted_right.frames.push_back({ 80, 480, 80, 80 });
	enemy2_hurted_right.frames.push_back({ 160, 480, 80, 80 });
	enemy2_hurted_right.loop = false;
	enemy2_hurted_right.speed = 0.1f;

	enemy2_hurted_left.frames.push_back({ 0, 560, 80, 80 });
	enemy2_hurted_left.frames.push_back({ 80, 560, 80, 80 });
	enemy2_hurted_left.frames.push_back({ 160, 560, 80, 80 });
	enemy2_hurted_left.loop = false;
	enemy2_hurted_left.speed = 0.1f;

	enemy2_dead.frames.push_back({ 320, 560, 80, 80 });
	enemy2_dead.speed = 0.1f;
}

void ModuleIA::animationsForEnemy3() {
	/* ENEMY ANIMATIONS */
	// idle animation
	enemy3_idle_right.frames.push_back({ 240, 0, 80, 80 });
	enemy3_idle_left.frames.push_back({ 0, 0, 80, 80 });

	/* ENEMY MOVEMENT ANIMATIONS */
	// move upwards
	enemy3_up_right.frames.push_back({ 0, 80, 80, 80 });
	enemy3_up_right.frames.push_back({ 80, 80, 80, 80 });
	enemy3_up_right.frames.push_back({ 160, 80, 80, 80 });
	enemy3_up_right.frames.push_back({ 240, 80, 80, 80 });
	enemy3_up_right.speed = 0.1f;

	enemy3_up_left.frames.push_back({ 0, 160, 80, 80 });
	enemy3_up_left.frames.push_back({ 80, 160, 80, 80 });
	enemy3_up_left.frames.push_back({ 160, 160, 80, 80 });
	enemy3_up_left.frames.push_back({ 240, 160, 80, 80 });
	enemy3_up_left.speed = 0.1f;

	// Move right
	enemy3_right.frames.push_back({ 320, 80, 80, 80 });
	enemy3_right.frames.push_back({ 400, 80, 80, 80 });
	enemy3_right.frames.push_back({ 480, 80, 80, 80 });
	enemy3_right.frames.push_back({ 560, 80, 80, 80 });
	enemy3_right.speed = 0.1f;

	// Move left 
	enemy3_left.frames.push_back({ 320, 160, 80, 80 });
	enemy3_left.frames.push_back({ 400, 160, 80, 80 });
	enemy3_left.frames.push_back({ 480, 160, 80, 80 });
	enemy3_left.frames.push_back({ 560, 160, 80, 80 });
	enemy3_left.speed = 0.1f;

	/* ENEMY ATACKING ANIMATIONS */
	enemy3_atacking_right.frames.push_back({ 0, 320, 80, 80 });
	enemy3_atacking_right.frames.push_back({ 80, 320, 80, 80 });
	enemy3_atacking_right.frames.push_back({ 160, 320, 80, 80 });
	enemy3_atacking_right.frames.push_back({ 240, 320, 80, 80 });
	enemy3_atacking_right.frames.push_back({ 360, 320, 80, 80 });
	enemy3_atacking_right.speed = 0.1f;

	enemy3_atacking_left.frames.push_back({ 0, 400, 80, 80 });
	enemy3_atacking_left.frames.push_back({ 80, 400, 80, 80 });
	enemy3_atacking_left.frames.push_back({ 160, 400, 80, 80 });
	enemy3_atacking_left.frames.push_back({ 240, 400, 80, 80 });
	enemy3_atacking_right.frames.push_back({ 360, 400, 80, 80 });
	enemy3_atacking_left.speed = 0.1f;

	/* ENEMY HURT ANIMATIONS */
	enemy3_hurted_right.frames.push_back({ 0, 480, 80, 80 });
	enemy3_hurted_right.frames.push_back({ 80, 480, 80, 80 });
	enemy3_hurted_right.frames.push_back({ 160, 480, 80, 80 });
	enemy3_hurted_right.loop = false;
	enemy3_hurted_right.speed = 0.1f;

	enemy3_hurted_left.frames.push_back({ 0, 560, 80, 80 });
	enemy3_hurted_left.frames.push_back({ 80, 560, 80, 80 });
	enemy3_hurted_left.frames.push_back({ 160, 560, 80, 80 });
	enemy3_hurted_left.loop = false;
	enemy3_hurted_left.speed = 0.1f;

	enemy3_dead.frames.push_back({ 320, 560, 80, 80 });
	enemy3_dead.speed = 0.1f;
}

void ModuleIA::animationsForEnemy4() {
	/* ENEMY ANIMATIONS */
	// idle animation
	enemy4_idle_right.frames.push_back({ 240, 0, 80, 80 });
	enemy4_idle_left.frames.push_back({ 0, 0, 80, 80 });

	/* ENEMY MOVEMENT ANIMATIONS */
	// move upwards
	enemy4_up_right.frames.push_back({ 0, 80, 80, 80 });
	enemy4_up_right.frames.push_back({ 80, 80, 80, 80 });
	enemy4_up_right.frames.push_back({ 160, 80, 80, 80 });
	enemy4_up_right.frames.push_back({ 240, 80, 80, 80 });
	enemy4_up_right.speed = 0.1f;

	enemy4_up_left.frames.push_back({ 0, 160, 80, 80 });
	enemy4_up_left.frames.push_back({ 80, 160, 80, 80 });
	enemy4_up_left.frames.push_back({ 160, 160, 80, 80 });
	enemy4_up_left.frames.push_back({ 240, 160, 80, 80 });
	enemy4_up_left.speed = 0.1f;

	// Move right
	enemy4_right.frames.push_back({ 320, 80, 80, 80 });
	enemy4_right.frames.push_back({ 400, 80, 80, 80 });
	enemy4_right.frames.push_back({ 480, 80, 80, 80 });
	enemy4_right.frames.push_back({ 560, 80, 80, 80 });
	enemy4_right.speed = 0.1f;

	// Move left 
	enemy4_left.frames.push_back({ 320, 160, 80, 80 });
	enemy4_left.frames.push_back({ 400, 160, 80, 80 });
	enemy4_left.frames.push_back({ 480, 160, 80, 80 });
	enemy4_left.frames.push_back({ 560, 160, 80, 80 });
	enemy4_left.speed = 0.1f;

	/* ENEMY ATACKING ANIMATIONS */
	enemy4_atacking_right.frames.push_back({ 0, 320, 80, 80 });
	enemy4_atacking_right.frames.push_back({ 80, 320, 80, 80 });
	enemy4_atacking_right.frames.push_back({ 160, 320, 80, 80 });
	enemy4_atacking_right.frames.push_back({ 240, 320, 80, 80 });
	enemy4_atacking_right.frames.push_back({ 360, 320, 80, 80 });
	enemy4_atacking_right.speed = 0.1f;

	enemy4_atacking_left.frames.push_back({ 0, 400, 80, 80 });
	enemy4_atacking_left.frames.push_back({ 80, 400, 80, 80 });
	enemy4_atacking_left.frames.push_back({ 160, 400, 80, 80 });
	enemy4_atacking_left.frames.push_back({ 240, 400, 80, 80 });
	enemy4_atacking_right.frames.push_back({ 360, 400, 80, 80 });
	enemy4_atacking_left.speed = 0.1f;

	/* ENEMY HURT ANIMATIONS */
	enemy4_hurted_right.frames.push_back({ 0, 480, 80, 80 });
	enemy4_hurted_right.frames.push_back({ 80, 480, 80, 80 });
	enemy4_hurted_right.frames.push_back({ 160, 480, 80, 80 });
	enemy4_hurted_right.loop = false;
	enemy4_hurted_right.speed = 0.1f;

	enemy4_hurted_left.frames.push_back({ 0, 560, 80, 80 });
	enemy4_hurted_left.frames.push_back({ 80, 560, 80, 80 });
	enemy4_hurted_left.frames.push_back({ 160, 560, 80, 80 });
	enemy4_hurted_left.loop = false;
	enemy4_hurted_left.speed = 0.1f;

	enemy4_dead.frames.push_back({ 320, 560, 80, 80 });
	enemy4_dead.speed = 0.1f;
}


