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



	
	marginX = 48 * 11;
	marginY = 48 * 7;




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
	else if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN || start_lvl1) // START LVL 1
	{
		level_man = LEVEL_01; 
		app->map->DeleteCol();
		app->map->CleanUp();
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
		start_lvl1 = false;
	}
	else if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN || start_lvl2)
	{
		level_man = LEVEL_02;
		app->map->DeleteCol();
		app->map->CleanUp();
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
		start_lvl2 = false;
	}
	else if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN || start_lvl3)
	{
		level_man = LEVEL_03;
		app->map->DeleteCol();
		app->map->CleanUp();
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
		Set_lvl_3_1();
		start_lvl3;
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
		}
		

		if (lvl1_3_done && !app->entityHandler->checkForEnemies())
		{
			start_lvl2 = true;
		}

	}
	
	if (level_man == LEVEL_02)
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

		if (lvl2_3_done && !app->entityHandler->checkForEnemies())
		{
			start_lvl3 = true;
		}
	}
	if (level_man == LEVEL_03)
	{

	int cameraSpeed = 10;


	if (sensor_01->type != TYPE_NULL)
	{
		if (sensor_01->body->GetContactList() != NULL)
		{
			if (lvl3_1_done && !inter3_2)
			{
				if (!app->entityHandler->players.getFirst()->data->interpolating &&
					!app->entityHandler->players.getFirst()->next->data->interpolating &&
					!app->entityHandler->players.getLast()->data->interpolating)
				{

					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{


						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);

						chicken_inter_3_2();
						
						// Spawn enemies!!!!

					}
				}
			}
			if (lvl3_2_done)
			{
				if (!app->entityHandler->players.getFirst()->data->interpolating &&
					!app->entityHandler->players.getFirst()->next->data->interpolating && 
					!app->entityHandler->players.getLast()->data->interpolating)
				{
					b2Body* playerB = sensor_01->body->GetContactList()->contact->GetFixtureA()->GetBody();
					if (playerB == app->entityHandler->players.getFirst()->data->GetPhysBody()->body)
					{

						app->entityHandler->players.getFirst()->data->moveType = STEP_TILES;

						app->physics->GetWorld()->DestroyBody(sensor_01->body);


						Set_lvl_3_3();
						// Spawn enemies!!!!

					}
				}
			}
		}
	}

	if (inter3_2&&
		!app->entityHandler->players.getFirst()->data->interpolating &&
		!app->entityHandler->players.getFirst()->next->data->interpolating &&
		!app->entityHandler->players.getLast()->data->interpolating)
	{
		Set_lvl_3_2();
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

	if (lvl3_3_done && !app->entityHandler->checkForEnemies())
	{
		return true;
	}
 }

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
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



	return true;

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
	lvl1_3_done = true;
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
	

	app->entityHandler->StartCombat();
	lvl2_3_done = true;
}

void Scene::Set_lvl_3_1()
{
	app->entityHandler->players.getFirst()->data->Interpolate(2 * 64 + 32, 28 * 64 + 32, 0.02);
	app->entityHandler->CreateEntity(ENTITY_PLAYER, 2 * 64, 29 * 64, 1);
	app->entityHandler->CreateEntity(ENTITY_PLAYER, 2 * 64, 27 * 64, 2);
	app->entityHandler->CreateEntity(ENTITY_MUMMY, 7 * 64, 27 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_MUMMY, 7 * 64, 28 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_MUMMY, 7 * 64, 29 * 64, 0);
	//app->entityHandler->CreateEntity(ENTITY_BAT, 8 * 64, 8 * 64, 0);

	//app->entityHandler->CreateEntity(ENTITY_SNAKE, 8 * 64, 2 * 64, 0);
	//app->entityHandler->CreateEntity(ENTITY_SNAKE, 12 * 64, 6 * 64, 0);

	app->physics->GetWorld()->DestroyBody(sensor_01->body);
	sensor_01 = app->physics->CreateSensorCircle(64 * 9 + 32, 28 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;

	app->entityHandler->StartCombat();
	lvl3_1_done = true;
}

void Scene::chicken_inter_3_2()
{
	app->entityHandler->players.getFirst()->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->next->data->state = STATE_TURN;
	app->entityHandler->players.getLast()->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->data->actual_mov = app->entityHandler->players.getFirst()->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->next->data->actual_mov = app->entityHandler->players.getFirst()->next->data->entity_stats.hp + 1;
	app->entityHandler->players.getLast()->data->actual_mov = app->entityHandler->players.getLast()->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->data->Interpolate(14 * 64 + 32, 27 * 64 + 32, 0.02);
	app->entityHandler->players.getFirst()->next->data->Interpolate(15 * 64 + 32, 28 * 64 + 32, 0.02);
	app->entityHandler->players.getLast()->data->Interpolate(14 * 64 + 32, 29 * 64 + 32, 0.02);
	inter3_2 = true;
}

void Scene::Set_lvl_3_2()
{	

	app->entityHandler->CreateEntity(ENTITY_MUMMY, 17 * 64, 27 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_MUMMY, 17 * 64, 28 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 20 * 64, 31 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 22 * 64, 33 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 15 * 64, 24 * 64, 0);

	app->entityHandler->CreateEntity(ENTITY_SNAKE, 14 * 64, 33 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 26 * 64, 23 * 64, 0);

	app->physics->GetWorld()->DestroyBody(sensor_01->body);
	sensor_01 = app->physics->CreateSensorCircle(64 * 28 + 32, 33 * 64 + 32, 24);
	sensor_01->type = TYPE_ENEMY;
	app->entityHandler->restoreHp();
	app->entityHandler->StartCombat();
	lvl3_2_done = true;
	inter3_2 = false;
}

void Scene::Set_lvl_3_3()
{
	app->entityHandler->players.getFirst()->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->next->data->state = STATE_TURN;
	app->entityHandler->players.getLast()->data->state = STATE_TURN;
	app->entityHandler->players.getFirst()->data->actual_mov = app->entityHandler->players.getFirst()->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->next->data->actual_mov = app->entityHandler->players.getFirst()->next->data->entity_stats.hp + 1;
	app->entityHandler->players.getLast()->data->actual_mov = app->entityHandler->players.getLast()->data->entity_stats.hp + 1;
	app->entityHandler->players.getFirst()->data->Interpolate(39 * 64 + 32, 28 * 64 + 32, 0.02);
	app->entityHandler->players.getFirst()->next->data->Interpolate(40 * 64 + 32, 28 * 64 + 32, 0.02);
	app->entityHandler->players.getLast()->data->Interpolate(41 * 64 + 32, 28 * 64 + 32, 0.02);


	app->entityHandler->CreateEntity(ENTITY_SOLDOR, 40 * 64, 4 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_MUMMY, 45 * 64, 10 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_BAT, 40 * 64, 20 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 48 * 64, 25 * 64, 0);

	app->entityHandler->CreateEntity(ENTITY_SNAKE, 32 * 64, 25 * 64, 0);
	app->entityHandler->CreateEntity(ENTITY_SNAKE, 32 * 64, 20 * 64, 0);

	app->physics->GetWorld()->DestroyBody(sensor_01->body);


	app->entityHandler->StartCombat();
	lvl3_3_done = true;

}
