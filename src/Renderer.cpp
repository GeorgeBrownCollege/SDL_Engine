#include "Renderer.h"

#include <utility>

SDL_Renderer* Renderer::GetRenderer()
{
	return m_pRenderer.get();
}

void Renderer::SetRenderer(std::shared_ptr<SDL_Renderer> renderer)
{
	m_pRenderer = std::move(renderer);
}

Renderer::Renderer()
= default;

Renderer::~Renderer()
= default;
