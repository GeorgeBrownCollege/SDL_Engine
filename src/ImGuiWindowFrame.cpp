#include "ImGuiWindowFrame.h"
#include <iostream>
#include "imgui.h"
#include "imgui_sdl.h"
#include "Util.h"

ImGuiWindowFrame::ImGuiWindowFrame()
= default;

ImGuiWindowFrame::~ImGuiWindowFrame()
= default;

void ImGuiWindowFrame::Init(const char* title, const int x, const int y, const int width, const int height, const int flags)
{
	std::cout << "SDL ImGUI Window Init success" << std::endl;

	// if succeeded create our window

	m_pWindow = (Config::make_resource(SDL_CreateWindow(title, x, y, width, height, flags)));
	m_windowID = SDL_GetWindowID(m_pWindow.get());

	// if window creation successful create our renderer
	if (m_pWindow != nullptr)
	{
		std::cout << "ImGui window creation success" << std::endl;

		// create a new SDL Renderer and store it in the Singleton
		m_pRenderer = (Config::make_resource(SDL_CreateRenderer(m_pWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)));

		if (getRenderer() != nullptr) // render init success
		{
			std::cout << "ImGui Renderer creation success" << std::endl;
			SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
		}
		else
		{
			std::cout << "ImGui Renderer init failure" << std::endl;
		}

		// IMGUI 
		ImGui::CreateContext();
		ImGuiSDL::Initialize(getRenderer(), width, height);

		setDefaultGUIFunction();

	}
	else
	{
		std::cout << "ImGUI window init failure" << std::endl;
	}
}

void ImGuiWindowFrame::Render()
{
	SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(getRenderer()); // clear the renderer to the draw colour

	Start();

	SDL_RenderPresent(getRenderer()); // draw to the screen
}

void ImGuiWindowFrame::setGUIFunction(const Callback& callback)
{
	SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(getRenderer());
	
	m_callback = callback;
}

void ImGuiWindowFrame::setDefaultGUIFunction()
{
	setGUIFunction(std::bind(&ImGuiWindowFrame::m_defaultGUIFunction, this));
}

void ImGuiWindowFrame::clearWindow() const
{
	SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(getRenderer());
}

void ImGuiWindowFrame::m_defaultGUIFunction()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	ImGui::ShowDemoWindow();

	ImGui::Begin("Default GUI Function", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Please add your own GUI Function to the scene");

	ImGui::End();
}

void ImGuiWindowFrame::Start()
{
	m_callback();

	// Don't Remove this
	
	ImGui::Render();
	SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(getRenderer());
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();

	// Hack to remove ghost window error - do not remove
	Util::DrawRect(glm::vec2(0, 0), 1, 1, glm::vec4(1, 1, 1, 1), getRenderer());
}

void ImGuiWindowFrame::Clean()
{
	// Clean Up for IMGUI
	ImGui::DestroyContext();
}

SDL_Renderer* ImGuiWindowFrame::getRenderer() const
{
	return m_pRenderer.get();
}

SDL_Window* ImGuiWindowFrame::getWindow() const
{
	return m_pWindow.get();
}

Uint32 ImGuiWindowFrame::getWindowID() const
{
	return m_windowID;
}
