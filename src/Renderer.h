#pragma once
#ifndef __RENDERER__
#define __RENDERER__
#include <SDL.h>
#include "Config.h"

/* Singleton */
class Renderer
{
public:
	static Renderer* Instance()
	{
		if(s_pInstance == nullptr)
		{
			s_pInstance = new Renderer();
		}
		return s_pInstance;
	}

	// getters and setters
	SDL_Renderer* getRenderer();
	void setRenderer(std::shared_ptr<SDL_Renderer> renderer);
	
private:
	Renderer();
	~Renderer();

	std::shared_ptr<SDL_Renderer> m_pRenderer;
	static Renderer* s_pInstance;
};

#endif /* defined (__RENDERER__) */