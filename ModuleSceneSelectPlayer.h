#ifndef __MODULESCENESELECTPLAYER_H__
#define __MODULESCENESELECTPLAYER_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneSelectPlayer : public Module {
public:
	ModuleSceneSelectPlayer(bool start_enabled = true);
	~ModuleSceneSelectPlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics_select_player = nullptr;
	SDL_Texture* graphics_amazon = nullptr;
	SDL_Texture* graphics_barbarian = nullptr;
	SDL_Texture* graphics_dwarf = nullptr;
	
	SDL_Rect menu_select_player;
	SDL_Rect menu_select_amazon;
	SDL_Rect menu_select_amazon_semidark;
	SDL_Rect menu_select_amazon_dark;
	SDL_Rect menu_select_barbarian;
	SDL_Rect menu_select_barbarian_semidark;
	SDL_Rect menu_select_barbarian_dark;
	SDL_Rect menu_select_dwarf;
	SDL_Rect menu_select_dwarf_semidark;
	SDL_Rect menu_select_dwarf_dark;

	uint fx = 0;
};

#endif //__MODULESCENESELECTPLAYER_H__