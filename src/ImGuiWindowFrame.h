#pragma once
#ifndef __IMGUI_WINDOW_FRAME__
#define __IMGUI_WINDOW_FRAME__
#include <SDL.h>
#include "Config.h"
#include <functional>

/* Singleton */
class ImGuiWindowFrame
{
public:
	static ImGuiWindowFrame& Instance()
	{
		static ImGuiWindowFrame instance;
		return instance;
	}

	void Init(const char* title = "ImGui Window", int x = 900, int y = 100, int width = 480, int height = 600, int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_UTILITY);
	void Render();
	void Start();
	void Clean();

	// getters and setters
	[[nodiscard]] SDL_Renderer* GetRenderer() const;
	[[nodiscard]] SDL_Window* GetWindow() const;
	[[nodiscard]] Uint32 GetWindowId() const;

	typedef std::function<void()> Callback;
	void SetGuiFunction(const Callback& callback);
	void SetDefaultGuiFunction();
	void ClearWindow() const;
	

private:
	ImGuiWindowFrame();
	~ImGuiWindowFrame();

	void DefaultGuiFunction();
	
	std::shared_ptr<SDL_Window> m_pWindow;
	std::shared_ptr<SDL_Renderer> m_pRenderer;

	Uint32 m_windowID;
	Callback m_callback;
};
#endif /* defined (__IMGUI_WINDOW_FRAME__) */
