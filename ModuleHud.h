#ifndef __MODULEHUD_H__
#define __MODULEHUD_H__

#include "Application.h"
#include "Animation.h"
#include "Module.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModuleHud : public Module {
public:
	ModuleHud(bool start_enabled = false);
	~ModuleHud();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	SDL_Texture* hud_graphics = nullptr;
	
	SDL_Rect magic_title;
	SDL_Rect magic_level_1;
	SDL_Rect magic_level_2;
	SDL_Rect magic_level_3;
	SDL_Rect magic_level_4;
	SDL_Rect magic_level_5;
	SDL_Rect magic_level_6;
	SDL_Rect magic_bottle;

	SDL_Rect health_bar;

	SDL_Rect lives_1;
	SDL_Rect lives_2;
	SDL_Rect lives_3;
	
	SDL_Rect player_face;
};

#endif // __MODULEHUD_H__
