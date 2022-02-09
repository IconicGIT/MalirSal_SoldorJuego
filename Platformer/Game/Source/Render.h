#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"



#include "SDL/include/SDL.h"

class Render : public Module
{
public:

	Render();

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();

	// Drawing
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	void Interpolate(int x, int y, float speed)
	{
		cameraFollow = true;
		newX = (float)x;
		newY = (float)y;
		if (!interpolating)
		{
			h = 0;
			iSpeed = speed;
			if (speed > 1) iSpeed = 1;
			if (speed < 0) iSpeed = 0;
			oldX = this->camera.x;
			oldY = this->camera.y;
			interpolating = true;

			pos_dif_x = newX - oldX;
			pos_dif_y = newY - oldY;
		}
		else {
			h += iSpeed;

			if (1 - h < 0)
				h = 1;


			camera.x = oldX + pos_dif_x * h;
			camera.y = oldY + pos_dif_y * h;

			

			if (h == 1)
			{
				interpolating = false;
				h = 0;
			}

		}



	}
public:

	SDL_Renderer* renderer;
	SDL_Rect camera;
	SDL_Rect viewport;
	SDL_Color background;
	uint windowX, windowY;

	float iSpeed;
	bool interpolating = false;
	float oldX;
	float oldY;
	float newX;
	float newY;
	float pos_dif_x;
	float pos_dif_y;
	float h = 0;

	float inter_speed;	bool cameraFollow = false;
};

#endif // __RENDER_H__