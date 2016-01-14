#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleHud.h"
#include "ModuleSceneLevel1.h"
#include "ModuleIA.h"
#include "SDL/include/SDL.h"

ModuleSceneLevel1::ModuleSceneLevel1(bool start_enabled) : Module(start_enabled) {
	background1 = NULL;
	background2 = NULL;
}

ModuleSceneLevel1::~ModuleSceneLevel1() {
}

// Load assets
bool ModuleSceneLevel1::Start() {
	LOG("Loading space scene");
	
	background1 = App->textures->Load("backgrounds\\level1A.png");
	background2 = App->textures->Load("backgrounds\\level1B.png");

	App->collision->Enable(); // enable before player
	App->ia->Enable();
	App->player->Enable();
	App->hud->Enable(); //Activate Hud
	App->audio->PlayMusic("music\\Lvl1_Wilderness.ogg", 1.0f);

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//Colliders in Y coordinate
	App->collision->AddCollider({ 0, 120, 3000, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 224, 3000, 16 }, COLLIDER_WALL);
	left_collider = App->collision->AddCollider({ 0, 120, 20, 124 }, COLLIDER_EDGE,this);
	right_collider = App->collision->AddCollider({ 300, 120, 20, 124 }, COLLIDER_EDGE, this);
	middle_collider = App->collision->AddCollider({ 160, 120, 160, 124 }, COLLIDER_MIDDLE_EDGE, this);

	//Colliders 
	//enemy_spawn.push_back(App->collision->AddCollider({ 400, 0, 20, SCREEN_HEIGHT }, COLLIDER_SPAWN, this));
	//enemy_spawn.push_back(App->collision->AddCollider({ 600, 0, 20, SCREEN_HEIGHT }, COLLIDER_SPAWN, this));
	//it = enemy_spawn.begin();
	enemy_spawn1 = App->collision->AddCollider({ 400, 0, 20, SCREEN_HEIGHT }, COLLIDER_SPAWN, this);
	enemy_spawn2 = App->collision->AddCollider({ 600, 0, 20, SCREEN_HEIGHT }, COLLIDER_SPAWN, this);
	enemy_spawn3 = App->collision->AddCollider({ 800, 0, 20, SCREEN_HEIGHT }, COLLIDER_SPAWN, this);
	enemy_spawn4 = App->collision->AddCollider({ 1200, 0, 20, SCREEN_HEIGHT }, COLLIDER_SPAWN, this);

	return true;
}

// UnLoad assets
bool ModuleSceneLevel1::CleanUp() {
	LOG("Unloading space scene");

	App->textures->Unload(background1);
	App->textures->Unload(background2);
	App->player->Disable();
	App->collision->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneLevel1::Update() {
	if (App->player->finished_wave) {
		switch (App->ia->wave) {
		case WAVE_1:
			enemy_spawn1->SetPos(enemy_spawn1->rect.x, enemy_spawn1->rect.y - SCREEN_HEIGHT * 2);
			break;
		case WAVE_2:
			enemy_spawn2->SetPos(enemy_spawn2->rect.x, enemy_spawn2->rect.y - SCREEN_HEIGHT * 2);
			break;
		case WAVE_3:
			enemy_spawn3->SetPos(enemy_spawn3->rect.x, enemy_spawn3->rect.y - SCREEN_HEIGHT * 2);
			break;
		case WAVE_4:
			enemy_spawn4->SetPos(enemy_spawn4->rect.x, enemy_spawn4->rect.y - SCREEN_HEIGHT * 2);
			break;
		}
		App->ia->nextWave();
		middle_collider->SetPos(middle_collider->rect.x, middle_collider->rect.y - SCREEN_HEIGHT);
		App->player->finished_wave = false;
		App->player->camara_state = NON_BLOCKED;
		
	}
		
	

	// Move camera forward -----------------------------
	int scroll_speed = 3;
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->player->camara_state == NON_BLOCKED) {
		App->renderer->camera.x += scroll_speed;
		left_collider->ChangePos(-1, 0);
		right_collider->ChangePos(-1, 0);
		middle_collider->ChangePos(-1, 0);
	}

	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->player->camara_state == NON_BLOCKED) {
		App->renderer->camera.x -= scroll_speed;
		left_collider->ChangePos(1, 0);
		right_collider->ChangePos(1, 0);
		middle_collider->ChangePos(1, 0);
	}

	// Draw everything --------------------------------------
	App->renderer->Blit(background1, 0, 0, NULL, 0.5f);
	App->renderer->Blit(background2, 0, 0, NULL, 1);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneLevel1::OnCollision(Collider* c1, Collider* c2) {
	switch (c1->type) {
	case COLLIDER_MIDDLE_EDGE:
		switch (c2->type) {
		case COLLIDER_SPAWN:
			LOG("Han colisionat el del mig i el spawn");
			App->player->camara_state = BLOCKED;
			middle_collider->SetPos(middle_collider->rect.x, middle_collider->rect.y + SCREEN_HEIGHT);
			App->ia->startWave();
			break;
		default:
			//camara_state = NON_BLOCKED;
			break;
		}
		break;
	case COLLIDER_EDGE:
		switch (c2->type) {
		case COLLIDER_PLAYER:
			LOG("Han colisionat el Edge i el player");
			/*check = false;
			App->player->camara_state = NON_BLOCKED;
			middle_collider->SetPos(middle_collider->rect.x, middle_collider->rect.y - SCREEN_HEIGHT); */
			break;
		default:
			//camara_state = NON_BLOCKED;
			break;
		}
		break;
	}
}

