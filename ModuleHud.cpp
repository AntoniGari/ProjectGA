#include <math.h>
#include "ModuleHud.h"
#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"


ModuleHud::ModuleHud(bool start_enabled) : Module(start_enabled) {
	/* MAGIC */
	magic_title.x = 0;
	magic_title.y = 31;
	magic_title.w = 37;
	magic_title.h = 8;
	
	magic_level_1.x = 0;
	magic_level_1.y = 39;
	magic_level_1.w = 73;
	magic_level_1.h = 16;

	magic_level_2.x = 0;
	magic_level_2.y = 55;
	magic_level_2.w = 73;
	magic_level_2.h = 16;

	magic_level_3.x = 0;
	magic_level_3.y = 71;
	magic_level_3.w = 73;
	magic_level_3.h = 16;

	magic_level_4.x = 0;
	magic_level_4.y = 87;
	magic_level_4.w = 73;
	magic_level_4.h = 16;

	magic_level_5.x = 0;
	magic_level_5.y = 103;
	magic_level_5.w = 73;
	magic_level_5.h = 16;

	magic_level_6.x = 0;
	magic_level_6.y = 119;
	magic_level_6.w = 73;
	magic_level_6.h = 16;

	magic_bottle.x = 37;
	magic_bottle.y = 31;
	magic_bottle.w = 8;
	magic_bottle.h = 8;

	/* HEALTH */
	health_bar.x = 51;
	health_bar.y = 31;
	health_bar.w = 22;
	health_bar.h = 8;
	
	/* LIVES */
	lives_1.x = 0;
	lives_1.y = 16;
	lives_1.w = 16;
	lives_1.h = 15;

	lives_2.x = 16;
	lives_2.y = 16;
	lives_2.w = 16;
	lives_2.h = 15;

	lives_3.x = 32;
	lives_3.y = 16;
	lives_3.w = 16;
	lives_3.h = 15;

	/* PLAYER FACE */
	player_face.x = 0;
	player_face.y = 0;
	player_face.w = 16;
	player_face.h = 16;

	
}


ModuleHud::~ModuleHud() {

}

bool ModuleHud::Start() {
	LOG("Loading Hud assets");
	bool ret = true;

	hud_graphics = App->textures->Load("system\\hud.png");

	return ret;
}

update_status ModuleHud::Update() {
	int i;

	//Painting magic
	if (App->player->character_mana > 0)
		App->renderer->Blit(hud_graphics, 82, 2, &magic_title, NULL);

	switch (App->player->character_mana) {
	case 1:
	case 2:
	case 3:
	case 4:
		App->renderer->Blit(hud_graphics, 80, 10, &magic_level_1, NULL);
		break;
	case 5:
		App->renderer->Blit(hud_graphics, 80, 10, &magic_level_2, NULL);
		break;
	case 6:
		App->renderer->Blit(hud_graphics, 80, 10, &magic_level_3, NULL);
		break;
	case 7:
		App->renderer->Blit(hud_graphics, 80, 10, &magic_level_4, NULL);
		break;
	case 8:
		App->renderer->Blit(hud_graphics, 80, 10, &magic_level_5, NULL);
		break;
	case 9:
		App->renderer->Blit(hud_graphics, 80, 10, & magic_level_6, NULL);
		break;
	default:
		break;
	}

	for (i = 0; i < App->player->character_mana; ++i) {
		App->renderer->Blit(hud_graphics, 80 + i*8, 17, &magic_bottle, NULL);
	}

	//Painting Health
	if (App->player->character_health > 32)
		App->renderer->Blit(hud_graphics, 55, 200, &health_bar, NULL);
	if (App->player->character_health > 16)
		App->renderer->Blit(hud_graphics, 80, 200, &health_bar, NULL);
	if (App->player->character_health > 0)
		App->renderer->Blit(hud_graphics, 105, 200, &health_bar, NULL);

	//Painting Life
	switch (App->player->character_lifes) {
	case 1:
		App->renderer->Blit(hud_graphics, 128, 200, &lives_1, NULL);
		break;
	case 2:
		App->renderer->Blit(hud_graphics, 128, 200, &lives_2, NULL);
		break;
	case 3:
		App->renderer->Blit(hud_graphics, 128, 200, &lives_3, NULL);
		break;
	default:
		break;
	}

	App->renderer->Blit(hud_graphics, 144, 199, &player_face, NULL);

	return UPDATE_CONTINUE;
}

bool ModuleHud::CleanUp() {
	LOG("Unloading Hud");

	App->textures->Unload(hud_graphics);

	return true;
}
