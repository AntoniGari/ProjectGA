#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleIA;
class ModuleParticles;
class ModuleCollision;
class ModuleSceneIntro;
class ModuleSceneSelectPlayer;
class ModuleHud;
class ModuleSceneLevel1;

class Application {
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleCollision* collision;

	// Game logic --
	ModulePlayer* player;
	ModuleIA* ia;
	ModuleHud* hud;
	ModuleSceneIntro* scene_intro;
	ModuleSceneSelectPlayer* scene_select_player;
	ModuleSceneLevel1* scene_level1;

private:

	std::list<Module*> modules;
	Module* first_scene = nullptr;
};

extern Application* App;

#endif // __APPLICATION_CPP__

