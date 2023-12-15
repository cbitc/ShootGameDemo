#pragma once

#include<vector>
#include"Common.hpp"
#include"PublicHeader.hpp"

struct Transform final
{
	Vec2<float> position;
	Vec2<float> scale;
	float rotation;
};



struct Texture final
{
	SDL_Texture* texture;

	int width,height;
	RGBA rgba;

	Texture() = default;
	Texture(SDL_Renderer* renderer,const std::string& path,const RGBA& rgba_):rgba(rgba_) {
		SDL_Surface* surface = IMG_Load(path.c_str());
		width = surface->w;
		height = surface->h;
		texture = SDL_CreateTextureFromSurface(renderer,surface);
		SDL_FreeSurface(surface);
	}
	Texture(SDL_Renderer* renderer,const std::string& path) {
		SDL_Surface* surface = IMG_Load(path.c_str());
		width = surface->w;
		height = surface->h;
		SDL_GetSurfaceColorMod(surface,&rgba.r,&rgba.g,&rgba.b);
		rgba.a = 255;
		texture = SDL_CreateTextureFromSurface(renderer,surface);
		SDL_FreeSurface(surface);
	}

	~Texture() {
		SDL_DestroyTexture(texture);
	}
};



struct Player final
{
	int hp;
};

struct Bullet final
{
	enum class Type
	{
		NORMAL,
	};
	Type type;
};


struct Healthy final
{
	float HP;
};

struct EnemySign final
{
	enum class Type
	{
		RED,
		GREEN,
		BLUE
	};
	Type type;
};


struct Velocity final
{
	Vec2<float> vel;
};