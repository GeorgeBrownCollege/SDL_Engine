#pragma once
#ifndef __RENDERER__
#define __RENDERER__
#include <SDL.h>
#include "Config.h"

/* Singleton */
class Renderer
{
public:
	static Renderer& Instance()
	{
		static Renderer instance;
		return instance;
	}

	// getters and setters
	SDL_Renderer* getRenderer();
	void setRenderer(std::shared_ptr<SDL_Renderer> renderer);

private:
	Renderer();
	~Renderer();

	std::shared_ptr<SDL_Renderer> m_pRenderer;
};

#endif /* defined (__RENDERER__) */