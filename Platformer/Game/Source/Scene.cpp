#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Render.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Physics.h"
#include "Input.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include <stdio.h>

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{
}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	level_man = LEVEL_MENU;
	state = GAMEPLAY;
	app->SetPause(false);

	player = app->entityHandler->GetMainPlayer();

	
	sensor_01 = app->physics->CreateSensorCircle(64 * 13 + 32, 4 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;

	char lookupTable1[] = { "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[£]çç€!ççç%&'()*+,-.^0123456789:;<=>?/abcdefghijklmnopqrstuvwxyz ççççççç" };

	font1_gold_1 = app->fonts->Load("Assets/textures/UI/fonts/font1_gold_1.png", lookupTable1, 6);
	font1_black_1 = app->fonts->Load("Assets/textures/UI/fonts/font1_black_1.png", lookupTable1, 6);
	font1_white_1 = app->fonts->Load("Assets/textures/UI/fonts/font1_white_1.png", lookupTable1, 6);

	font1_black_2 = app->fonts->Load("Assets/textures/UI/fonts/font1_black_2.png", lookupTable1, 6);
	font1_gold_2 = app->fonts->Load("Assets/textures/UI/fonts/font1_gold_2.png", lookupTable1, 6);
	font1_white_2 = app->fonts->Load("Assets/textures/UI/fonts/font1_white_2.png", lookupTable1, 6);

	font1_gold_3 = app->fonts->Load("Assets/textures/UI/fonts/font1_gold_2.png", lookupTable1, 6);
	font1_black_3 = app->fonts->Load("Assets/textures/UI/fonts/font1_black_3.png", lookupTable1, 6);
	font1_white_3 = app->fonts->Load("Assets/textures/UI/fonts/font1_white_3.png", lookupTable1, 6);

	menu_ = app->tex->Load("Assets/textures/Menu/main_menu.png");
	//menu_ = app->tex->Load("Assets/textures/chickens/main_menu.png");
	menu.PushBack({ 1 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 2 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 3 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 4 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 5 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 6 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 7 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 8 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 9 * 540, 0 * 360, 540, 360 });
	menu.PushBack({ 10 *540, 0 * 360, 540, 360 });
	menu.PushBack({ 11 *540, 0 * 360, 540, 360 });
	menu.PushBack({ 12 *540, 0 * 360, 540, 360 });
	menu.PushBack({ 13 *540, 0 * 360, 540, 360 });
	menu.PushBack({ 14 *540, 0 * 360, 540, 360 });
	menu.PushBack({ 15 *540, 0 * 360, 540, 360 });
	menu.speed = 0.1f;
	menu.loop = true;
	//.pingpong = true;


	//state == INTRO;

	

// L03: DONE: Load map

	if (app->map->Load("mapConcept.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data))
			app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	//jungleMusic = app->audio->PlayMusic("Assets/audio/music/cyber.ogg");

	//Mix_Music* music = Mix_LoadMUS("Assets/audio/music/mission_1_repeat.ogg");
	//Mix_PlayMusic(music, -1);

	//app->audio->PlayMusic("Assets/audio/music/videoplayback.ogg");    Destroy ears
	//app->audio->PlayFx(jungleMusic, 0);


	//arcaic code
	/*for (int x = 0; x < app->map->data.layers.start->data->width; x++)
	{
		for (int y = 0; y < app->map->data.layers.start->data->height; y++)
		{

			int gid = app->map->data.layers.start->data->Get(x, y);

			iPoint screenPos = app->map->MapToWorld(x, y);
			PhysBody* temp;


			if (gid == 4)
			{
				LOG("found tile");
				temp = app->physics->CreateRectangle(screenPos.x + 24, screenPos.y + 24, 48, 48);
				temp->body->SetType(b2_staticBody);
			}


		}


	}*/

	
	

	/*app->entityHandler->CreateEntity(EntityType::ENEMY_BIRD, 48 * 10 - 24, 48 * 10 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_BIRD, 48 * 28 - 24, 48 * 7 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_BIRD, 48 * 43 - 24, 48 * 13 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_BIRD, 48 * 73 - 24, 48 * 25 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_BIRD, 48 * 74 - 24, 48 * 6 - 24);
	
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, 48 * 12 - 24, 48 * 22 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, 48 * 15 - 22, 48 * 2 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, 48 * 70 - 22, 48 * 20 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, 48 * 45 - 45, 48 * 22 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, 48 * 70 - 67, 48 * 27 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, 48 * 70 - 67, 48 * 7 - 24);
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, METERS_TO_PIXELS(25), METERS_TO_PIXELS(25));
	app->entityHandler->CreateEntity(EntityType::ENEMY_MUSHROOM, METERS_TO_PIXELS(53.6f), METERS_TO_PIXELS(9.5f));

	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, METERS_TO_PIXELS(39), METERS_TO_PIXELS(21.5f) + 8 );
	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, METERS_TO_PIXELS(54.f), METERS_TO_PIXELS(28.5f) + 8);
	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, METERS_TO_PIXELS(79.5f), METERS_TO_PIXELS(25.5f) + 8);
	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, METERS_TO_PIXELS(67.5f), METERS_TO_PIXELS(3.5f) + 8);
	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, METERS_TO_PIXELS(36.5f), METERS_TO_PIXELS(27.5f) + 8);

	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, 48 * 13 - 24, 48 * 22 - 24);
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(33.52f), METERS_TO_PIXELS(24.52f));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(3.52f), METERS_TO_PIXELS(3.52f));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(39.52f), METERS_TO_PIXELS(14.52f));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(37), METERS_TO_PIXELS(21.5f));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(37), METERS_TO_PIXELS(22.5f));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(47), METERS_TO_PIXELS(28));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(47), METERS_TO_PIXELS(28));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(71), METERS_TO_PIXELS(20));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(6), METERS_TO_PIXELS(28.11f));
	app->entityHandler->CreateEntity(EntityType::ITEM_BANANA, METERS_TO_PIXELS(15.7f), METERS_TO_PIXELS(28.4f));
	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, 48 * 20 + 25, 48 * 25 + 35);
	app->entityHandler->CreateEntity(EntityType::ENEMY_SNAKE, 48 * 30, 48 * 13 + 35);*/
	

	//app->entityHandler->CreateEntity(EntityType::ROCKET_BANANA, 48 * 10 - 24, 48 * 15 - 24);

	


	
	marginX = 48 * 11;
	marginY = 48 * 7;

	////player lifes
	//SDL_Rect rec_panel = { 0,188,340,124 };
	//UI_player_lifes = app->UI_handler->CreatePanel(app->UI_handler->spritesheet, 0, 5, 0, 0);
	//UI_player_lifes->sprite = app->UI_handler->spritesheet;
	//UI_player_lifes->rec_sprite = rec_panel;

	////skill icon
	//rec_panel = { 368, 200, 80, 80 };
	//UI_player_skill_icon = app->UI_handler->CreatePanel(app->UI_handler->spritesheet, 16, 150, 0, 0);
	//UI_player_skill_icon->sprite = app->UI_handler->spritesheet;
	//UI_player_skill_icon->rec_sprite = rec_panel;

	////player skill_bg
	//rec_panel = { 260, 60, 140, 24 };
	//UI_player_skill_bar_bg = app->UI_handler->CreatePanel(app->UI_handler->spritesheet, 100, 200, 0, 0);
	//UI_player_skill_bar_bg->sprite = app->UI_handler->spritesheet;
	//UI_player_skill_bar_bg->rec_sprite = rec_panel;

	////player skill fill
	//rec_panel = { 264, 92, 132, 20 };
	//UI_player_skill_bar_fill = app->UI_handler->CreatePanel(app->UI_handler->spritesheet, 100 + 4, 200 + 4, 0, 0);
	//UI_player_skill_bar_fill->sprite = app->UI_handler->spritesheet;
	//UI_player_skill_bar_fill->rec_sprite = rec_panel;

	//////panel pause
	////rec_panel = { 0, 312, 672, 432 };
	////UI_panel_pause_menu = app->UI_handler->CreatePanel(app->UI_handler->spritesheet, 1080/2 - 672 /2, 720/2 - 432/2, 672, 432);
	////UI_panel_pause_menu->sprite = app->UI_handler->spritesheet;
	////UI_panel_pause_menu->rec_sprite = rec_panel;

	//////panel exit game
	////rec_panel = { 692, 4, 268, 48 };
	////UI_panel_pause_menu_exit_game = app->UI_handler->CreatePanel(app->UI_handler->spritesheet, 1080 / 2 + 14, 720 / 2 + 432/4 + 128, 268, 48);
	////UI_panel_pause_menu_exit_game->sprite = app->UI_handler->spritesheet;
	////UI_panel_pause_menu_exit_game->rec_sprite = rec_panel;

	////pause open button
	//rec_panel = { 468, 4, 48, 48 };
	//UI_button_open_pause_menu = app->UI_handler->CreateButton(app->UI_handler->spritesheet, 1080 - 48 - 14, 14, 48, 48);
	//UI_button_open_pause_menu->sprite = app->UI_handler->spritesheet;
	//UI_button_open_pause_menu->rec_sprite = rec_panel;
	//UI_button_open_pause_menu->action = ACTION_PAUSE_OPEN;

	////pause close button
	//rec_panel = { 412, 60, 48, 48 };
	//UI_button_close_pause_menu = app->UI_handler->CreateButton(
	//	app->UI_handler->spritesheet,
	//	1080 / 2 + 584/2 -28,
	//	584/2 - 432/4,
	//	48,
	//	48);
	//UI_button_close_pause_menu->sprite = app->UI_handler->spritesheet;
	//UI_button_close_pause_menu->rec_sprite = rec_panel;
	//UI_button_close_pause_menu->action = ACTION_PAUSE_CLOSE;

	//
	//
	////exit button
	//rec_panel = { 468, 60, 48, 48 };
	//UI_button_exit_game = app->UI_handler->CreateButton(
	//	app->UI_handler->spritesheet,
	//	1080 / 2 + 584 / 2 - 28,
	//	720 / 2 + 432 / 2 - 64,
	//	48,
	//	48);
	//UI_button_exit_game->sprite = app->UI_handler->spritesheet;
	//UI_button_exit_game->rec_sprite = rec_panel;
	//UI_button_exit_game->action = ACTION_EXIT_GAME;

	////exit button confirm
	//rec_panel = { 412, 4, 48, 48 };
	//UI_button_exit_game_confirm = app->UI_handler->CreateButton(
	//	app->UI_handler->spritesheet,
	//	1080 / 2 - 584 / 2 + 584 + 4,
	//	720 / 2 + 432 / 4 + 128,
	//	48,
	//	48
	//);
	//UI_button_exit_game_confirm->sprite = app->UI_handler->spritesheet;
	//UI_button_exit_game_confirm->rec_sprite = rec_panel;
	//UI_button_exit_game_confirm->action = ACTION_EXIT_GAME_CONFIRM;

	////exit button deny
	//rec_panel = { 468, 60, 48, 48 };
	//UI_button_exit_game_deny = app->UI_handler->CreateButton(
	//	app->UI_handler->spritesheet,
	//	1080 / 2 - 584 / 2 + 584 + 48 + 16,
	//	720 / 2 + 432 / 4 + 128,
	//	48,
	//	48
	//);
	//UI_button_exit_game_deny->sprite = app->UI_handler->spritesheet;
	//UI_button_exit_game_deny->rec_sprite = rec_panel;
	//UI_button_exit_game_deny->action = ACTION_EXIT_GAME_DENY;

	////save button
	//rec_panel = { 320, 116, 132, 48 };
	//UI_button_save_game = app->UI_handler->CreateButton(
	//	app->UI_handler->spritesheet,
	//	 1080 / 2 - 584 / 2 + 584 / 4,
	//	720 / 2 + 432 / 4 + 24,
	//	132,
	//	48
	//);
	//UI_button_save_game->sprite = app->UI_handler->spritesheet;
	//UI_button_save_game->rec_sprite = rec_panel;
	//UI_button_save_game->rec_over = {468,112,140,56};
	//UI_button_save_game->rec_hold = { 472,172,132,48 };
	//UI_button_save_game->action = ACTION_SAVE_GAME;

	////load button
	//rec_panel = { 180, 116, 132, 48 };
	//UI_button_load_game = app->UI_handler->CreateButton(
	//	app->UI_handler->spritesheet,
	//	1080 / 2 + 584 / 2 - 584 / 4 - 132,
	//	720 / 2 + 432 / 4 + 24,
	//	132,
	//	48
	//);
	//UI_button_load_game->sprite = app->UI_handler->spritesheet;
	//UI_button_load_game->rec_sprite = rec_panel;
	//UI_button_load_game->rec_over = { 468,112,140,56 };
	//UI_button_load_game->rec_hold = { 472,172,132,48 };
	//UI_button_load_game->action = ACTION_LOAD_GAME;

	////sfx volume slider
	//rec_panel = { 0, 60, 256, 24 };
	//UI_slider_sfx_vol = app->UI_handler->CreateSlider(450, 420, 128, app->UI_handler->spritesheet, { 0 }, { 0 }, { 0 }, { 0 });
	//UI_slider_sfx_vol->rec_sprite = rec_panel;
	//rec_panel = { 4, 92, 244, 16 };
	//UI_slider_sfx_vol->rec_body_fill = rec_panel;
	//rec_panel = { 0, 0, 116, 60 };
	//UI_slider_sfx_vol->rec_slider_hold = rec_panel;
	//rec_panel = { 120, 0, 120, 60 };
	//UI_slider_sfx_vol->rec_slider = rec_panel;
	//UI_slider_sfx_vol->w = 256;
	//UI_slider_sfx_vol->h = 24;
	//UI_slider_sfx_vol->set = SET_SFX_VOLUME;

	////global audio slider
	//rec_panel = { 0, 60, 256, 24 };
	//UI_slider_global_audio = app->UI_handler->CreateSlider(450, 320, 100, app->UI_handler->spritesheet, { 0 }, { 0 }, { 0 }, { 0 });
	//UI_slider_global_audio->rec_sprite = rec_panel;
	//rec_panel = { 4, 92, 244, 16 };
	//UI_slider_global_audio->rec_body_fill = rec_panel;
	//rec_panel = { 0, 0, 116, 60 };
	//UI_slider_global_audio->rec_slider_hold = rec_panel;
	//rec_panel = { 120, 0, 120, 60 };
	//UI_slider_global_audio->rec_slider = rec_panel;
	//UI_slider_global_audio->w = 256;
	//UI_slider_global_audio->h = 24;
	//UI_slider_global_audio->set = SET_GLOBAL_VOLUME;


	////music volume slider
	//rec_panel = { 0, 60, 256, 24 };
	//UI_slider_music_vol = app->UI_handler->CreateSlider(450, 370, 128, app->UI_handler->spritesheet, { 0 }, { 0 }, { 0 }, { 0 });
	//UI_slider_music_vol->rec_sprite = rec_panel;
	//rec_panel = { 4, 92, 244, 16 };
	//UI_slider_music_vol->rec_body_fill = rec_panel;
	//rec_panel = { 0, 0, 116, 60 };
	//UI_slider_music_vol->rec_slider_hold = rec_panel;
	//rec_panel = { 120, 0, 120, 60 };
	//UI_slider_music_vol->rec_slider = rec_panel;
	//UI_slider_music_vol->w = 256;
	//UI_slider_music_vol->h = 24;
	//UI_slider_music_vol->set = SET_MUSIC_VOLUME;

	//176, 120, 140, 24
	//180, 124, 132, 20


app->render->camera_0 = true;
	
	
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		level_man = LEVEL_MENU;
		app->entityHandler->entities_active = false;
		app->render->cameraFollow = false;
		app->render->camera_0 = true;
	}
	else if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) // START LVL 1
	{
		level_man = LEVEL_01; 
		app->map->DeleteCol();
		app->entityHandler->entities_active = true;
		app->render->cameraFollow = true;
		app->render->camera_0 = false;
		if (app->map->Load("level_01.tmx") == true)
		{
			int w, h;
			uchar* data = NULL;

			if (app->map->CreateWalkabilityMap(w, h, &data))
				app->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);
		}
		
		app->map->LoadCol();
		Set_lvl_1_1();
	}
	else if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		level_man = LEVEL_02;
		app->map->DeleteCol();
		app->render->cameraFollow = true;
		app->render->camera_0 = false;
		app->entityHandler->entities_active = true;
		if (app->map->Load("level_02.tmx") == true)
		{
			int w, h;
			uchar* data = NULL;

			if (app->map->CreateWalkabilityMap(w, h, &data))
				app->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);
		}
		
		app->map->LoadCol();
		Set_lvl_2_1();
	}
	else if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
	{
		level_man = LEVEL_03;
		app->map->DeleteCol();
		app->render->cameraFollow = true;
		app->render->camera_0 = false;
		app->entityHandler->entities_active = true;
		if (app->map->Load("level_03.tmx") == true)
		{
			int w, h;	
			uchar* data = NULL;

			if (app->map->CreateWalkabilityMap(w, h, &data))
				app->pathfinding->SetMap(w, h, data);

			RELEASE_ARRAY(data);
		}
		
		app->map->LoadCol();
	}

	currentTime += 16;
	if (level_man == LEVEL_MENU)
	{
		menu.Update();
		app->render->DrawTexture(menu_, 0, 0, &menu.GetCurrentFrame(), SDL_FLIP_NONE, 2);
		
	}
	else if (level_man == LEVEL_01)
	{
		if (sensor_01->type != TYPE_NULL)
		{
			if (sensor_01->body->GetContactList() != NULL)
			{
				if (lvl1_1_done && !app->entityHandler->GetMainPlayer()->interpolating && !lvl1_2_done)
				{
					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{
						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_1_2();
						// Spawn enemies!!!!
					}
				}
				else if (lvl1_2_done && !app->entityHandler->GetMainPlayer()->interpolating)
				{
					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{
						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_1_3();
						// Spawn enemies!!!!
					}
				}
			}
		}

		if (!app->entityHandler->checkForEnemies())
		{
			// end of combat
			app->render->cameraFollow = false;
			//app->entityHandler->players.getFirst()->data->moveType = STEP_FREE;
			//Give chicken exp and check for lvl up;
		}

		switch (state)
		{
		case INTRO:
		{
			
		}break;
		case GAMEPLAY:
		{

			int cameraSpeed = 10;

			uint screnWidth, screenHeight;
			app->win->GetWindowSize(screnWidth, screenHeight);

			// L02: DONE 3: Request Load / Save when pressing L/S
			if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
				app->SaveGameRequest();

			if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
				app->LoadGameRequest();


			if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
			{
				if (!freeCam) freeCam = true;
				else freeCam = false;
			}

			if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
			{
				if (app->GetMaxFrames() == 30) app->SetMaxFrames(60);
				else if (app->GetMaxFrames() == 60) app->SetMaxFrames(30);
				//LOG("current: %i", app->GetMaxFrames());

			}




			if (freeCam)
			{
				app->render->cameraFollow = false;
				//move cam sith arrows
				if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))

					app->render->camera.y += cameraSpeed;



				if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)

					app->render->camera.y -= cameraSpeed;




				if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))

					app->render->camera.x += cameraSpeed;




				if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
					app->render->camera.x -= cameraSpeed;


			}
			else
			{
				app->render->cameraFollow = true;
			}




			app->map->Draw();
			app->entityHandler->DrawAllEntities();

		}break;
		case END:
		{


		}break;
		}

	}
	else if (level_man = LEVEL_02)
	{


	int cameraSpeed = 10;


	if (sensor_01->type != TYPE_NULL)
	{
		if (sensor_01->body->GetContactList() != NULL)
		{
			if (lvl2_1_done && !lvl2_2_done)
			{
				if (!app->entityHandler->players.getFirst()->data->interpolating &&
					!app->entityHandler->players.getFirst()->next->data->interpolating)
				{

					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{


						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_2_2();
						// Spawn enemies!!!!

					}
				}
			}
			if (lvl2_2_done)
			{
				if (!app->entityHandler->players.getFirst()->data->interpolating &&
					!app->entityHandler->players.getFirst()->next->data->interpolating)
				{
					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{

						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_2_3();
						// Spawn enemies!!!!

					}
				}
			}
		}
	}

		if (freeCam)
		{
			app->render->cameraFollow = false;
			//move cam sith arrows
			if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))

				app->render->camera.y += cameraSpeed;



			if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)

				app->render->camera.y -= cameraSpeed;




			if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))

				app->render->camera.x += cameraSpeed;




			if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
				app->render->camera.x -= cameraSpeed;


		}
		else
		{
			app->render->cameraFollow = true;
		}




		app->map->Draw();
		app->entityHandler->DrawAllEntities();
	}
	else if (level_man == LEVEL_03)
	{

	int cameraSpeed = 10;


	if (sensor_01->type != TYPE_NULL)
	{
		if (sensor_01->body->GetContactList() != NULL)
		{
			if (lvl2_1_done && !lvl2_2_done)
			{
				if (!app->entityHandler->players.getFirst()->data->interpolating &&
					!app->entityHandler->players.getFirst()->next->data->interpolating)
				{

					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{


						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_2_2();
						// Spawn enemies!!!!

					}
				}
			}
			if (lvl2_2_done)
			{
				if (!app->entityHandler->players.getFirst()->data->interpolating &&
					!app->entityHandler->players.getFirst()->next->data->interpolating)
				{
					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{

						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_2_3();
						// Spawn enemies!!!!

					}
				}
			}
		}
	}

	if (freeCam)
	{
		app->render->cameraFollow = false;
		//move cam sith arrows
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT))

			app->render->camera.y += cameraSpeed;



		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)

			app->render->camera.y -= cameraSpeed;




		if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))

			app->render->camera.x += cameraSpeed;




		if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
			app->render->camera.x -= cameraSpeed;


	}
	else
	{
		app->render->cameraFollow = true;
	}




	app->map->Draw();
	app->entityHandler->DrawAllEntities();
 }

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	switch (state)
	{
	case INTRO:
	{


		//if (!menuOpen)
		//{
		//	UI_panel_pause_menu->SetActive(false);
		//}

		//if (UI_panel_pause_menu->IsActive())
		//{
		//	app->fonts->DrawText(1080 / 3 + 50, 200 - 24, font1_gold_2, "Settings");


		//	char val[4];

		//	app->fonts->DrawText(310, 320 - 8, font1_black_1, "Global");
		//	app->fonts->DrawText(310, 320 + 8, font1_black_1, "Vol:");

		//	sprintf_s(val, "%i", UI_slider_global_audio->GetValue());

		//	app->fonts->DrawText(310 + 4 * 16, 320 + 8, font1_black_1, val);
		//	app->fonts->DrawText(310 + (4 + strlen(val)) * 16, 320 + 8, font1_black_1, "%");

		//	app->fonts->DrawText(310, 370 - 8, font1_black_1, "Music");
		//	app->fonts->DrawText(310, 370 + 8, font1_black_1, "Vol:");

		//	sprintf_s(val, "%i", (int)((float)UI_slider_music_vol->GetValue() / 128.f * 100));

		//	app->fonts->DrawText(310 + 4 * 16, 370 + 8, font1_black_1, val);
		//	app->fonts->DrawText(310 + (4 + strlen(val)) * 16, 370 + 8, font1_black_1, "%");

		//	app->fonts->DrawText(310, 420 - 8, font1_black_1, "SFX");
		//	app->fonts->DrawText(310, 420 + 8, font1_black_1, "Vol:");

		//	sprintf_s(val, "%i", (int)((float)UI_slider_sfx_vol->GetValue() / 128.f * 100));

		//	app->fonts->DrawText(310 + 4 * 16, 420 + 8, font1_black_1, val);
		//	app->fonts->DrawText(310 + (4 + strlen(val)) * 16, 420 + 8, font1_black_1, "%");



		//	UI_button_close_pause_menu->SetActive(true);
		//	//UI_button_exit_game->SetActive(true);
		//	//UI_button_load_game->SetActive(true);
		//	//UI_button_save_game->SetActive(true);
		//	UI_slider_global_audio->SetActive(true);
		//	UI_slider_music_vol->SetActive(true);
		//	UI_slider_sfx_vol->SetActive(true);

		//}
		//else
		//{
		//	UI_panel_pause_menu->SetActive(false);
		//	UI_button_close_pause_menu->SetActive(false);
		//	
		//	if (!loadingScreenActive)
		//		UI_button_settings->SetActive(true);
		//	else {
		//		UI_button_settings->SetActive(false);

		//	}

		//	UI_panel_pause_menu_exit_game->SetActive(false);
		//	UI_button_exit_game->SetActive(false);
		//	UI_button_exit_game_confirm->SetActive(false);
		//	UI_button_exit_game_deny->SetActive(false);
		//	UI_button_load_game->SetActive(false);
		//	UI_button_save_game->SetActive(false);
		//	UI_slider_global_audio->SetActive(false);
		//	UI_slider_music_vol->SetActive(false);
		//	UI_slider_sfx_vol->SetActive(false);



		//}
	}
		break;
	case GAMEPLAY:
	{




		/*if (app->GameIsPaused())
		{
			app->fonts->DrawText(1080 / 3, 200 - 24, font1_gold_2, "Game Paused");


			char val[4];

			app->fonts->DrawText(310, 320 - 8, font1_black_1, "Global");
			app->fonts->DrawText(310, 320 + 8, font1_black_1, "Vol:");
			
			sprintf_s(val, "%i", UI_slider_global_audio->GetValue());

			app->fonts->DrawText(310 + 4 * 16, 320 + 8, font1_black_1, val);
			app->fonts->DrawText(310 + (4 + strlen(val))*16, 320 + 8, font1_black_1, "%");

			app->fonts->DrawText(310, 370 - 8, font1_black_1, "Music");
			app->fonts->DrawText(310, 370 + 8, font1_black_1, "Vol:");

			sprintf_s(val, "%i", (int)((float)UI_slider_music_vol->GetValue() / 128.f * 100));

			app->fonts->DrawText(310 + 4 * 16, 370 + 8, font1_black_1, val);
			app->fonts->DrawText(310 + (4 + strlen(val)) * 16, 370 + 8, font1_black_1, "%");

			app->fonts->DrawText(310, 420 - 8, font1_black_1, "SFX");
			app->fonts->DrawText(310, 420 + 8, font1_black_1, "Vol:");
			
			sprintf_s(val, "%i", (int)((float)UI_slider_sfx_vol->GetValue() / 128.f * 100));

			app->fonts->DrawText(310 + 4 * 16, 420 + 8, font1_black_1, val);
			app->fonts->DrawText(310 + (4 + strlen(val)) * 16, 420 + 8, font1_black_1, "%");


			UI_panel_pause_menu->SetActive(true);
			UI_button_close_pause_menu->SetActive(true);
			UI_button_open_pause_menu->SetActive(false);
			UI_button_exit_game->SetActive(true);
			UI_button_load_game->SetActive(true);
			UI_button_save_game->SetActive(true);
			UI_slider_global_audio->SetActive(true);
			UI_slider_music_vol->SetActive(true);
			UI_slider_sfx_vol->SetActive(true);
			 
		}
		else
		{
			UI_panel_pause_menu->SetActive(false);
			UI_button_close_pause_menu->SetActive(false);
			UI_button_open_pause_menu->SetActive(true);
			UI_panel_pause_menu_exit_game->SetActive(false);
			UI_button_exit_game->SetActive(false);
			UI_button_exit_game_confirm->SetActive(false);
			UI_button_exit_game_deny->SetActive(false);
			UI_button_load_game->SetActive(false);
			UI_button_save_game->SetActive(false);
			UI_slider_global_audio->SetActive(false);
			UI_slider_music_vol->SetActive(false);
			UI_slider_sfx_vol->SetActive(false);


		}*/
	}
		break;
	case END:
		break;
	case NONE:
		break;
	default:
		break;
	}

	

	//
	//

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Scene::LoadState(pugi::xml_node& data)
{

	return true;
}

// L02: TODO 8: create a method to save the state of the renderer
// Save Game State
bool Scene::SaveState(pugi::xml_node& data) const
{
	//...

	return true;
}

void Scene::Set_lvl_1_1()
{
	app->entityHandler->players.getFirst()->data->Interpolate(2 * 64 + 32, 4 * 64 + 32, 0.02);
	app->entityHandler->CreateEntity(ENTITY_SOLDOR, 7 * 64, 6 * 64, 0);
	//app->entityHandler->CreateEntity(ENTITY_BAT, 7 * 64, 6 * 64, 0);
	//app->entityHandler->CreateEntity(ENTITY_BAT, 5 * 64, 5 * 64, 0);
	app->entityHandler->StartCombat();
	lvl1_1_done = true;
}

void Scene::Set_lvl_1_2()
{
	app->entityHandler->restoreHp();
	app->entityHandler->players.getFirst()->data->Interpolate(17 * 64 + 32, 4 * 64 + 32, 0.02);
	app->entityHandler->CreateEntity(ENTITY_BAT, 19 * 64, 2 * 64, 0);
	//app->entityHandler->CreateEntity(ENTITY_BAT, 18 * 64, 4 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 21 * 64, 6 * 64, 0);
	app->entityHandler->StartCombat();

	sensor_01 = app->physics->CreateSensorCircle(64 * 20 + 32, 8 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;
	lvl1_2_done = true;
}

void Scene::Set_lvl_1_3()
{
	app->entityHandler->restoreHp();
	app->entityHandler->players.getFirst()->data->Interpolate(20 * 64 + 32, 12 * 64 + 32, 0.02);
	app->entityHandler->CreateEntity(ENTITY_BAT, 19 * 64, 14 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 27 * 64, 15 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 19 * 64, 19 * 64, 0);

	
	app->entityHandler->StartCombat();
	lvl1_2_done = true;
}

void Scene::Set_lvl_2_1()
{
	app->entityHandler->players.getFirst()->data->Interpolate(2 * 64 + 32, 5 * 64 + 32, 0.02);
	app->entityHandler->CreateEntity(ENTITY_PLAYER, 2 * 64, 7 * 64, 1);
	app->entityHandler->CreateEntity(ENTITY_BAT, 7 * 64, 7 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 8 * 64, 6 * 64, 0);
	//app->entityHandler->CreateEntity(ENTITY_BAT, 8 * 64, 8 * 64, 0);

	app->entityHandler->CreateEntity(ENTITY_SNAKE,  8 * 64, 2* 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 12 * 64, 6 * 64, 0);
	
	app->physics->GetWorld()->DestroyBody(sensor_01->body);
	sensor_01 = app->physics->CreateSensorCircle(64 * 7 + 32, 9 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;

	app->entityHandler->StartCombat();
	lvl2_1_done = true;
}

void Scene::Set_lvl_2_2()
{
	app->entityHandler->players.getFirst()->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->next->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->data->actual_mov = app->entityHandler->players.getFirst()->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->next->data->actual_mov = app->entityHandler->players.getFirst()->next->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->data->Interpolate(7 * 64 + 32, 16 * 64 + 32, 0.02);
	app->entityHandler->players.getFirst()->next->data->Interpolate(7 * 64 + 32, 15 * 64 + 32, 0.02);


	app->entityHandler->CreateEntity(ENTITY_BAT, 5 * 64, 17 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 11 * 64, 15 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 12 * 64,18 * 64, 0);

	app->entityHandler->CreateEntity(ENTITY_SNAKE, 8 * 64, 23 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 7 * 64, 23 * 64, 0);

	app->physics->GetWorld()->DestroyBody(sensor_01->body);
	sensor_01 = app->physics->CreateSensorCircle(64 * 13 + 32, 16 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;
	app->entityHandler->restoreHp();
	app->entityHandler->StartCombat();
	lvl2_2_done = true;
}

void Scene::Set_lvl_2_3()
{
	app->entityHandler->players.getFirst()->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->next->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->data->actual_mov = app->entityHandler->players.getFirst()->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->next->data->actual_mov = app->entityHandler->players.getFirst()->next->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->data->Interpolate(19 * 64 + 32, 17 * 64 + 32, 0.02);
	app->entityHandler->players.getFirst()->next->data->Interpolate(19 * 64 + 32, 15 * 64 + 32, 0.02);


	app->entityHandler->CreateEntity(ENTITY_BAT, 20 * 64, 17 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 21 * 64, 15 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 17 * 64, 15 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 23 * 64, 14 * 64, 0);

	app->entityHandler->CreateEntity(ENTITY_SNAKE, 23 * 64, 16 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 23 * 64, 15 * 64, 0);

	app->physics->GetWorld()->DestroyBody(sensor_01->body);
	sensor_01 = app->physics->CreateSensorCircle(64 * 7 + 32, 9 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;

	app->entityHandler->StartCombat();
	lvl2_3_done = true;
}

void Scene::Set_lvl_3_1()
{
}

void Scene::Set_lvl_3_2()
{
}

void Scene::Set_lvl_3_3()
{
}
