#include "Globals.h"
#include "Application.h"
#include "ModuleIA.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "Timer.h"

/// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled) {
	// Character general declarations
	direction = RIGHT;
	state = NONE;
	camara_state = BLOCKED;

	/* CHARACTER ANIMATIONS */
	// idle animation
	//idle.frames.push_back({66, 1, 32, 14});
	idle_right.frames.push_back({400, 0, 80, 80 });

	idle_left.frames.push_back({ 480, 0, 80, 80 });

	/* CHARACTER MOVEMENT ANIMATIONS */
	// move upwards
	up_right.frames.push_back({ 320, 80, 80, 80 });
	up_right.frames.push_back({ 400, 80, 80, 80 });
	up_right.frames.push_back({ 480, 80, 80, 80 });
	up_right.frames.push_back({ 560, 80, 80, 80 });
	//up.loop = false;
	up_right.speed = 0.1f;

	up_left.frames.push_back({ 320, 160, 80, 80 });
	up_left.frames.push_back({ 400, 160, 80, 80 });
	up_left.frames.push_back({ 480, 160, 80, 80 });
	up_left.frames.push_back({ 560, 160, 80, 80 });
	up_left.speed = 0.1f;

	// Move right
	right.frames.push_back({ 0, 80, 80, 80 });
	right.frames.push_back({ 80, 80, 80, 80 });
	right.frames.push_back({ 160, 80, 80, 80 });
	right.frames.push_back({ 240, 80, 80, 80 });
	right.speed = 0.1f;

	// Move left 
	left.frames.push_back({ 0, 160, 80, 80 });
	left.frames.push_back({ 80, 160, 80, 80 });
	left.frames.push_back({ 160, 160, 80, 80 });
	left.frames.push_back({ 240, 160, 80, 80 });
	left.speed = 0.1f;

	//Running right
	running_right.frames.push_back({ 0, 240, 80, 80 });
	running_right.frames.push_back({ 80, 240, 80, 80 });
	running_right.frames.push_back({ 160, 240, 80, 80 });
	running_right.frames.push_back({ 240, 240, 80, 80 });
	running_right.speed = 0.1f;

	//Running left
	running_left.frames.push_back({ 0, 320, 80, 80 });
	running_left.frames.push_back({ 80, 320, 80, 80 });
	running_left.frames.push_back({ 160, 320, 80, 80 });
	running_left.frames.push_back({ 240, 320, 80, 80 });
	running_left.speed = 0.1f;

	//Jumping Right

	//Jumping Left

	/* CHARACTER ATACK ANIMATIONS */
	//Atacking right
	atacking_right.frames.push_back({ 0, 400, 80, 80 });
	atacking_right.frames.push_back({ 80, 400, 80, 80 });
	atacking_right.frames.push_back({ 160, 400, 80, 80 });
	atacking_right.speed = 0.1f;

	//Atacking left
}

ModulePlayer::~ModulePlayer() {
}

// Load assets
bool ModulePlayer::Start() {
	LOG("Loading player");

	//Character graphics
	switch (race) {
	case AMAZON:
		graphics = App->textures->Load("character\\character_amazone.png");
		break;
	case DWARF:
		graphics = App->textures->Load("character\\character_dwarf.png");
		break;
	case BARBARIAN:
		graphics = App->textures->Load("character\\character_barbarian.png");
		break;
	}
	
	//Start position
	position.x = 50;
	position.y = 200;

	//Magic graphics
	//SDL_Texture* particles = App->textures->Load("particles.png");

	//Player collider
	character_collider = App->collision->AddCollider({2000, 40, 30, 10}, COLLIDER_PLAYER, this);
	
	//Others
	finished = false;
	character_health = 48;
	character_lifes = 3;
	character_mana = 1;
	character_timer = new Timer();
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp() {
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update() {
	int speed = 1;
	preposition = position;

	if(finished == true)
		return UPDATE_CONTINUE;

	/* ATACKING*/
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN && state != ATTACK) {
		if (App->ia->active) App->ia->hurt(1);
		if (current_animation != &atacking_right) {
			atacking_right.Reset();
			current_animation = &atacking_right;
			state = ATTACK;
			character_timer->running = true;
			character_timer->started_at = SDL_GetTicks();
		}

	/* MAGIC */
	}
	else if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN  && state != ATTACK) {
		if (App->ia->active) App->ia->hurt_all(4);
		if (current_animation != &up_left) {
			up_left.Reset();
			current_animation = &up_left;
		}

	/* MOVEMENT */
	// JUMPING
	} else if (App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN  && state != ATTACK) {
	
	//Character goes up-left
	} else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT  && state != ATTACK) {
		position.x -= speed;
		position.y -= speed;
		direction = LEFT;
		state = NONE;
		
		if (current_animation != &up_left) {
			up_left.Reset();
			current_animation = &up_left;
		}
	
	//Character goes up-right
	} else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT  && state != ATTACK) {
		position.x += speed;
		position.y -= speed;
		direction = RIGHT;
		state = NONE;

		if (current_animation != &up_right) {
			up_right.Reset();
			current_animation = &up_right;
		}
	
	} else {
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN  && state != ATTACK) {
			if (state == NONE) state = PRERUNNINGRIGHT;
			else if (state == PRERUNNINGRIGHT) state = RUNNINGRIGHT;
		} else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN  && state != ATTACK) {
			if (state == NONE) state = PRERUNNINGLEFT;
			else if (state == PRERUNNINGLEFT) state = RUNNINGLEFT;
		}

		//Character goes left
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT  && state != ATTACK) {
			direction = LEFT;

			if (state == RUNNINGRIGHT) {
				//position.x -= speed * 2;
				if (current_animation != &running_left) {
					running_left.Reset();
					current_animation = &running_left;
				}
			} else {
				position.x -= speed;
				state = NONE;
				if (current_animation != &left) {
					left.Reset();
					current_animation = &left;
				}
			}
		}

		//Character goes right
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT  && state != ATTACK) {
			direction = RIGHT;
		
			if (state == RUNNINGRIGHT) {
				position.x += speed * 2;
				if (current_animation != &running_right) {
					running_right.Reset();
					current_animation = &running_right;
				}
			} else {
				position.x += speed;
				state = NONE;
				if (current_animation != &right) {
					right.Reset();
					current_animation = &right;
				}
			}
		}

		//Character goes down
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT  && state != ATTACK) {
			position.y += speed;

			switch (direction) {
			case RIGHT:
				if (current_animation != &right) {
					right.Reset();
					current_animation = &right;
				}
				break;
			case LEFT:
				if (current_animation != &left) {
					left.Reset();
					current_animation = &left;
				}
				break;
			}
		}

		//Character goes up
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT  && state != ATTACK) {
			position.y -= speed;

			switch (direction) {
			case RIGHT:
				if (current_animation != &up_right) {
					up_right.Reset();
					current_animation = &up_right;
				}
				break;
			case LEFT:
				if (current_animation != &up_left) {
					up_left.Reset();
					current_animation = &up_left;
				}
				break;
			}
		}
	}

	//If not moving
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE  && state != ATTACK) {
		camara_state = BLOCKED;
		switch (direction) {
		case RIGHT:
			current_animation = &idle_right;
			break;
		case LEFT:
			current_animation = &idle_left;
			break;
		}		
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		++character_lifes;
	}

	LOG("Timer es %d", character_timer->Read());
	if (state == ATTACK && character_timer->isRunning()) {
		LOG("Timer es %d", character_timer->Read());
		LOG("Timer actual %d", SDL_GetTicks());
		LOG("TIMER ON");
		if (character_timer->Compare(1000)) {
			LOG("JA HA COMPARAT");
			state = NONE;
			character_timer->Stop();
		}
		
	}
		

	character_collider->SetPos(position.x - (character_collider->rect.w / 2), position.y - character_collider->rect.h);

	App->renderer->Blit(graphics, position.x - 40, position.y - 80, &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	//LOG("Hi ha colisions");
	if (!finished) {
		switch (c1->type) {
		case COLLIDER_PLAYER:
			switch (c2->type) {
			case COLLIDER_WALL:
				//LOG("Player - WALL");
				position.y = preposition.y;
				character_collider->SetPos(position.x - (character_collider->rect.w / 2), position.y - character_collider->rect.h);
				App->renderer->Blit(graphics, position.x - 40, position.y - 80, &(current_animation->GetCurrentFrame()));
				break;
			case COLLIDER_EDGE:
				//LOG("Player - EDGE ");
				position.x = preposition.x;
				character_collider->SetPos(position.x - (character_collider->rect.w / 2), position.y - character_collider->rect.h);
				App->renderer->Blit(graphics, position.x - 40, position.y - 80, &(current_animation->GetCurrentFrame()));
				break;
			case COLLIDER_MIDDLE_EDGE:
				//LOG("Player - MIDDLE EDGE");
				position.x = preposition.x;
				character_collider->SetPos(position.x - (character_collider->rect.w / 2), position.y - character_collider->rect.h);
				App->renderer->Blit(graphics, position.x - 40, position.y - 80, &(current_animation->GetCurrentFrame()));
				camara_state = NON_BLOCKED;
				break;
			case COLLIDER_SPAWN:
				//LOG("Player - SPAWN");
				break;
			default:
				//camara_state = NON_BLOCKED;
				break;
			}
			break;
		case COLLIDER_MIDDLE_EDGE:
			switch (c2->type) {
			case COLLIDER_SPAWN:
				//LOG("Han colisionat el del mig i el spawn");
				camara_state = BLOCKED;
				break;
			default:
				break;
			}
			break;
		default:
				break;
		}
	}
}