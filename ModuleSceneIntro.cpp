#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel1.h"
#include "ModuleSceneSelectPlayer.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(bool start_enabled) : Module(start_enabled) {
	/* ANIMATIONS */
	// 108,37 + 1 pixel per borde
	//FADE
	sega_logo.frames.push_back({ 1, 1, 108, 37 });
	sega_logo.frames.push_back({ 1, 39, 108, 37 });
	sega_logo.frames.push_back({ 1, 77, 108, 37 });
	sega_logo.frames.push_back({ 1, 115, 108, 37 });
	sega_logo.frames.push_back({ 1, 153, 108, 37 });
	sega_logo.frames.push_back({ 1, 191, 108, 37 });
	sega_logo.frames.push_back({ 1, 229, 108, 37 });
	//LOGO WITHOUT BRIGHTNESS
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	//BRIGHTNESS
	sega_logo.frames.push_back({ 1, 267, 108, 37 });
	sega_logo.frames.push_back({ 1, 305, 108, 37 });
	sega_logo.frames.push_back({ 1, 343, 108, 37 });
	sega_logo.frames.push_back({ 1, 381, 108, 37 });
	sega_logo.frames.push_back({ 1, 419, 108, 37 });
	sega_logo.frames.push_back({ 1, 457, 108, 37 });
	sega_logo.frames.push_back({ 1, 495, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	//LOGO WITHOUT BRIGHTNESS
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	//BRIGHTNESS REPEAT
	sega_logo.frames.push_back({ 1, 267, 108, 37 });
	sega_logo.frames.push_back({ 1, 305, 108, 37 });
	sega_logo.frames.push_back({ 1, 343, 108, 37 });
	sega_logo.frames.push_back({ 1, 381, 108, 37 });
	sega_logo.frames.push_back({ 1, 419, 108, 37 });
	sega_logo.frames.push_back({ 1, 457, 108, 37 });
	sega_logo.frames.push_back({ 1, 495, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	//LOGO WITHOUT BRIGHTNESS
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	sega_logo.frames.push_back({ 1, 533, 108, 37 });
	//FADE
	sega_logo.frames.push_back({ 1, 571, 108, 37 });
	sega_logo.frames.push_back({ 1, 609, 108, 37 });
	sega_logo.frames.push_back({ 1, 647, 108, 37 });
	sega_logo.frames.push_back({ 1, 685, 108, 37 });
	sega_logo.frames.push_back({ 1, 723, 108, 37 });
	sega_logo.frames.push_back({ 1, 761, 108, 37 });
	sega_logo.frames.push_back({ 1, 799, 108, 37 });
	sega_logo.loop = false;
	sega_logo.speed = 0.15f;

	//Menu Sky Background
	int i, j;
	for (i = 0; i < 288; ++i) {
		menu_background.frames.push_back({ 256, i, 256, 224 });
	}
	for (j = 0; j < 100; ++j) {
		menu_background.frames.push_back({ 256, 288, 256, 224 });
	}
	for (; i > 0; --i) {
		menu_background.frames.push_back({ 256, i, 256, 224 });
	}
	for (j = 0; j < 100; ++j) {
		menu_background.frames.push_back({ 256, 0, 256, 224 });
	}
	menu_background.loop = true;
	menu_background.speed = 0.3f;

	//Menu 1 or 2 player start
	menu_player_start.frames.push_back({ 0, 210, 160, 10 });
	menu_player_start.frames.push_back({ 0, 220, 1, 1 });
	menu_player_start.loop = true;
	menu_player_start.speed = 0.04f;

	/* GRAPHICS */
	// Menu Blood  
	menu_blood.x = 206;
	menu_blood.y = 210;
	menu_blood.w = 50;
	menu_blood.h = 50;

	// Menu Golden Axe Kangi 
	menu_kangi.x = 0;
	menu_kangi.y = 0;
	menu_kangi.w = 256;
	menu_kangi.h = 160;

	// Menu Golden Axe Title 
	menu_title.x = 0;
	menu_title.y = 160;
	menu_title.w = 256 ;
	menu_title.h = 50;

	// Menu Sega
	menu_sega.x = 0;
	//menu_sega.y = 210;
	menu_sega.y = 220;
	menu_sega.w = 206;
	menu_sega.h = 45;
}

ModuleSceneIntro::~ModuleSceneIntro() {
}

// Load assets
bool ModuleSceneIntro::Start() {
	LOG("Loading Intro assets");
	bool ret = true;

	graphics_sega_logo = App->textures->Load("system\\sega_logo.png");
	graphics_menu = App->textures->Load("system\\menu.png");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	timer1 = new Timer();
	timer2 = new Timer();
	timer1->Start();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp() {
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics_sega_logo);
	App->textures->Unload(graphics_menu);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update() {
	// Draw everything --------------------------------------	
	if (timer1->CompareMin(5800)) {
		background_animation = &sega_logo;
		App->renderer->Blit(graphics_sega_logo, SCREEN_WIDTH / 2 - 54, SCREEN_HEIGHT / 2 - 19, &(background_animation->GetCurrentFrame()));

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP) {
			App->audio->PlayMusic("music\\The_Battle.ogg", 0.0f);
			timer1->Stop();
			timer2->Start();
		}
	} else {
		if (timer1->isRunning()) {
			App->audio->PlayMusic("music\\The_Battle.ogg", 0.0f);
			timer1->Stop();
			timer2->Start();
		}

		background_animation = &menu_background;
		App->renderer->Blit(graphics_menu, SCREEN_WIDTH / 2 - 128, 0, &(background_animation->GetCurrentFrame()));
		
		App->renderer->Blit(graphics_menu, SCREEN_WIDTH / 2 - menu_blood.w / 2, 4, &menu_blood, NULL);
		App->renderer->Blit(graphics_menu, SCREEN_WIDTH / 2 - menu_kangi.w / 2, 10, &menu_kangi, NULL);
		App->renderer->Blit(graphics_menu, SCREEN_WIDTH / 2 - menu_title.w / 2, 100, &menu_title, NULL);
		App->renderer->Blit(graphics_menu, 90, 173, &menu_sega, NULL);

		menu_animation = &menu_player_start;
		App->renderer->Blit(graphics_menu, 90, 163, &(menu_animation->GetCurrentFrame()));
		
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
			App->fade->FadeToBlack(App->scene_select_player, this, 1.0f);
	}
	
	return UPDATE_CONTINUE;
}