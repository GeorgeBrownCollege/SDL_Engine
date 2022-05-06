#include "Renderer.h"

#include <utility>

/**
 * \brief Get Accessor function used to return a reference to the SDL_Renderer 
 * \return a pointer to the SDL Renderer
 */
SDL_Renderer* Renderer::GetRenderer() const
{
	return m_pRenderer.get();
}

/**
 * \brief Set Mutator function that sets the SDL_Renderer reference
 * \param renderer std::shared_ptr<SDL_Renderer>
 */
void Renderer::SetRenderer(std::shared_ptr<SDL_Renderer> renderer)
{
	m_pRenderer = std::move(renderer);
}

Renderer::Renderer()
= default;

Renderer::~Renderer()
= default;
