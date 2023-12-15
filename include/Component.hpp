#pragma once

#include<vector>
#include<Common.hpp>

struct Transform final
{
	Vec2<float> position;
	Vec2<float> scale;
	float angle;
};



struct Texture final
{
	SDL_Texture* texture;
	int width,height;
	Texture() = default;
	Texture(SDL_Renderer* renderer,const std::string& path) {
		SDL_Surface* surface = IMG_Load(path.c_str());
		width = surface->w;
		height = surface->h;
		texture = SDL_CreateTextureFromSurface(renderer,surface);
		SDL_FreeSurface(surface);
	}
	~Texture() {
		SDL_DestroyTexture(texture);
	}
};




struct Graph final
{
	std::vector<std::vector<int>> neibs;
	std::vector<Vec2<float>> vertexs;
};


struct GraphInfo final
{
	enum class Type
	{
		TRIANGLE,
		ARROW,
		BULLET,
	};

	Type type;
	RGBA rgba;
};


struct Player final
{

};

struct Bullet final
{
	enum class Type
	{
		NORMAL,
	};
	Type type;
};


struct Velocity final
{
	Vec2<float> vel;
};