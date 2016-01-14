#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel1.h"
#include "ModuleSceneSelectPlayer.h"
#include "ModulePlayer.h"


ModuleSceneSelectPlayer::ModuleSceneSelectPlayer(bool start_enabled) : Module(start_enabled) {
	/* GRAPHICS */
	// Menu Select Player
	menu_select_player.x = 0;
	menu_select_player.y = 267;
	menu_select_player.w = 256;
	menu_select_player.h = 200;

	// Character amazon 
	menu_select_amazon.x = 160;
	menu_select_amazon.y = 0;
	menu_select_amazon.w = 80;
	menu_select_amazon.h = 80;

	// Character amazon semidark
	menu_select_amazon_semidark.x = 80;
	menu_select_amazon_semidark.y = 0;
	menu_select_amazon_semidark.w = 80;
	menu_select_amazon_semidark.h = 80;

	// Character amazon dark
	menu_select_amazon_dark.x = 0;
	menu_select_amazon_dark.y = 0;
	menu_select_amazon_dark.w = 80;
	menu_select_amazon_dark.h = 80;

	// Character barbarian  
	menu_select_barbarian_dark.x = 0;
	menu_select_barbarian_dark.y = 0;
	menu_select_barbarian_dark.w = 80;
	menu_select_barbarian_dark.h = 80;

	// Character dwarf  
	menu_select_dwarf_dark.x = 0;
	menu_select_dwarf_dark.y = 0;
	menu_select_dwarf_dark.w = 80;
	menu_select_dwarf_dark.h = 80;
}

ModuleSceneSelectPlayer::~ModuleSceneSelectPlayer() {
}

// Load assets
bool ModuleSceneSelectPlayer::Start() {
	LOG("Loading Select Player assets");
	bool ret = true;

	graphics_select_player = App->textures->Load("system\\menu.png");
	graphics_amazon = App->textures->Load("character\\character_amazone.png");
	graphics_barbarian = App->textures->Load("character\\character_barbarian.png");;
	graphics_dwarf = App->textures->Load("character\\character_dwarf.png");;

	//App->audio->PlayMusic("music\\The_Battle.ogg", 0.0f);
	fx = App->audio->LoadFx("sfx\\SceneSelectPlayer_PlayerSelected.wav");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneSelectPlayer::CleanUp() {
	LOG("Unloading Select Player Scene");

	App->textures->Unload(graphics_select_player);
	App->textures->Unload(graphics_amazon);
	App->textures->Unload(graphics_barbarian);
	App->textures->Unload(graphics_dwarf);

	return true;
}

// Update: draw background
update_status ModuleSceneSelectPlayer::Update() {
	// Draw everything --------------------------------------	

	
	App->renderer->Blit(graphics_select_player, SCREEN_WIDTH / 2 - menu_select_player.w / 2, SCREEN_HEIGHT / 2 - menu_select_player.h / 2, &menu_select_player, NULL);
	App->renderer->Blit(graphics_barbarian, 37, 76, &menu_select_barbarian_dark, NULL);
	App->renderer->Blit(graphics_dwarf, 77, 76, &menu_select_dwarf_dark, NULL);
	App->renderer->Blit(graphics_amazon, 52, 102, &menu_select_amazon, NULL);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP) {
		App->audio->PlayFx(fx);
		App->player->race = AMAZON;
		App->player->app_scene_level = SCENE_LEVEL_1;
		App->fade->FadeToBlack(App->scene_level1, this, 1.0f);
	}

	return UPDATE_CONTINUE;
}