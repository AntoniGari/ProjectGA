#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Timer.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Animation* background_animation = nullptr;
	Animation* menu_animation = nullptr;
	Animation sega_logo;
	Animation menu_player_start;
	Animation menu_background;
	
	SDL_Rect menu_kangi;
	SDL_Rect menu_title;
	SDL_Rect menu_blood;
	SDL_Rect menu_sega;

	SDL_Texture* graphics_sega_logo = nullptr;
	SDL_Texture* graphics_menu = nullptr;

	Timer* timer1;
	Timer* timer2;
};

#endif //__MODULESCENEINTRO_H__