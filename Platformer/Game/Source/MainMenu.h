#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Physics.h"
#include "ModuleFonts.h"
#include "EntityHandler.h"
#include "EntityPlayer.h"
#include "SDL/include/SDL.h"

struct SDL_Texture;


enum GameState
{
	INTRO = 0,
	GAMEPLAY,
	END,
	NONE
};

class MainMenu : public Module
{
public:

	MainMenu();

	// Destructor
	virtual ~MainMenu();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	//int playerX = 0;
	//int playerY = 0;
	bool freeCam = false;


	GameState state;


	int font1_gold_1;
	int font1_black_1;
	int font1_white_1;

	int font1_black_2;
	int font1_gold_2;
	int font1_white_2;

	int font1_gold_3;
	int font1_black_3;
	int font1_white_3;

	//PhysBody* sensor_01;
	////start
	//UI_Panel* UI_panel_title;

	//UI_Button* UI_button_start_game;
	//UI_Button* UI_button_quit_game;

	//UI_Button* UI_button_settings;

	////gameplay
	//UI_Panel* UI_player_lifes;
	//UI_Panel* UI_player_skill_icon;
	//UI_Panel* UI_player_skill_bar_bg;
	//UI_Panel* UI_player_skill_bar_fill;

	//UI_Panel* UI_panel_pause_menu;
	//UI_Panel* UI_panel_pause_menu_exit_game;

	//UI_Button* UI_button_open_pause_menu;
	//UI_Button* UI_button_close_pause_menu;
	//UI_Button* UI_button_exit_game;
	//UI_Button* UI_button_exit_game_confirm;
	//UI_Button* UI_button_exit_game_deny;

	//UI_Button* UI_button_save_game;
	//UI_Button* UI_button_load_game;

	//UI_Slider* UI_slider_global_audio;
	//UI_Slider* UI_slider_music_vol;
	//UI_Slider* UI_slider_sfx_vol;

	int currentTime = 0;
	int lastTime = 0;


private:

	EntityPlayer* player;
	int marginX;
	int marginY;

	/*p2List<PhysBody*> trespasableElements;*/

};

#endif // __SCENE_H__