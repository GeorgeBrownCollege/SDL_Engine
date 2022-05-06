#include "EventManager.h"
#include <iostream>
#include "Game.h"
#include "WindowName.h"

void EventManager::Reset()
{
    m_isActive = false;
    SDL_Delay(300);
    m_isActive = true;
}

void EventManager::Update()
{
    if (m_isActive)
    {
        m_io = ImGui::GetIO();
        m_mouseWheel = 0;


        for (const auto controller : m_pGameControllers)
        {
            if (SDL_GameControllerGetAttached(controller->handle))
            {
                controller->Update();
            }
        }

        SDL_Event event;

        std::memcpy(m_keysLast, m_keysCurr, m_numKeys);
        m_mouseLast = m_mouseCurrent;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                Game::Instance().Quit();
                break;

            case SDL_MOUSEMOTION:
                OnMouseMove(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(m_mainWindowHasFocus)
                {
                    OnMouseButtonDown(event);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (m_mainWindowHasFocus)
                {
                    OnMouseButtonUp(event);
                }
                break;

            case SDL_MOUSEWHEEL:
                m_mouseWheel = event.wheel.y;
                break;

            case SDL_TEXTINPUT:
                m_io.AddInputCharactersUTF8(event.text.text);
                break;

            case SDL_KEYDOWN:
                OnKeyDown();

                if (event.key.keysym.sym == SDLK_BACKQUOTE)
                {
                    m_isIMGUIActive = (m_isIMGUIActive) ? false : true;


                    if (m_isIMGUIActive)
                    {
                        SDL_ShowWindow(ImGuiWindowFrame::Instance().GetWindow());
                    }
                    else
                    {
                        SDL_HideWindow(ImGuiWindowFrame::Instance().GetWindow());
                    }
                }
                {
                    int key = event.key.keysym.scancode;
                    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(m_io.KeysDown));
                    m_io.KeysDown[key] = (event.type == SDL_KEYDOWN);
                    m_io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
                    m_io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
                    m_io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
                    m_io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
                }
                break;

            case SDL_KEYUP:
                OnKeyUp();
                {
                    int key = event.key.keysym.scancode;
                    IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(m_io.KeysDown));
                    m_io.KeysDown[key] = (event.type == SDL_KEYDOWN);
                    m_io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
                    m_io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
                    m_io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
                    m_io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
                }
                break;

            case SDL_CONTROLLERDEVICEADDED:
                std::cout << "Controller Added " << std::endl;
                InitializeControllers();
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                std::cout << "Controller Removed " << std::endl;
                InitializeControllers();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    if (ImGuiWindowFrame::Instance().GetWindowId() == event.window.windowID)
                    {
                        SDL_HideWindow(ImGuiWindowFrame::Instance().GetWindow());
                        m_isIMGUIActive = false;
                    }
                    else
                    {
                        Game::Instance().Quit();
                    }
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:

                    m_mainWindowHasFocus = (ImGuiWindowFrame::Instance().GetWindowId() == event.window.windowID) ? false : true;

                    break;

	            case SDL_WINDOWEVENT_ENTER:
            		SDL_RaiseWindow((event.window.windowID == static_cast<int>(WindowName::MAIN)) ? Game::Instance().GetWindow() : ImGuiWindowFrame::Instance().GetWindow());
	                    break;
	                }
                break;


            default:
                break;
            }
        }

        m_keysCurr = SDL_GetKeyboardState(&m_numKeys);
        SDL_Point mouse_pos = { static_cast<int>(m_mousePosition.x), static_cast<int>(m_mousePosition.y) };
        m_mouseCurrent = SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        m_io.DeltaTime = 1.0f / 60.0f;
        int mouse_x;
        int mouse_y;
        const int buttons = static_cast<int>(SDL_GetMouseState(&mouse_x, &mouse_y));
        if(!m_mainWindowHasFocus)
        {
            m_io.MousePos = ImVec2(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
            m_io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
            m_io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
            m_io.MouseWheel = static_cast<float>(m_mouseWheel);

            m_io.DisplaySize.x = Config::SCREEN_WIDTH;
            m_io.DisplaySize.y = Config::SCREEN_HEIGHT;
        }
        
    }
}

void EventManager::Clean()
{
    for (const auto& game_controller : m_pGameControllers)
    {
        if (game_controller != nullptr)
        {
            SDL_GameControllerClose(game_controller->handle);
        }
    }

    m_pGameControllers.clear();
}

bool EventManager::IsKeyDown(const SDL_Scancode key) const
{
    if (m_keyStates != nullptr)
    {
        if (m_keyStates[key] == 1) return true;
    }
    return false;
}

bool EventManager::IsKeyUp(const SDL_Scancode key) const
{
    if (m_keyStates != nullptr)
    {
        if (m_keyStates[key] == 0) return true;
    }
    return false;
}

void EventManager::OnKeyDown()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void EventManager::OnKeyUp()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

bool EventManager::KeyPressed(const SDL_Scancode c) const
{
    return (m_keysCurr[c] > m_keysLast[c]);
}

bool EventManager::KeyReleased(const SDL_Scancode c) const
{
    return (m_keysCurr[c] < m_keysLast[c]);
}

void EventManager::OnMouseMove(const SDL_Event& event)
{
    m_mousePosition.x = static_cast<float>(event.motion.x);
    m_mousePosition.y = static_cast<float>(event.motion.y);
}

void EventManager::OnMouseButtonDown(const SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtons[static_cast<int>(MouseButtons::LEFT)] = true;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtons[static_cast<int>(MouseButtons::MIDDLE)] = true;
    }

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtons[static_cast<int>(MouseButtons::RIGHT)] = true;
    }
}

void EventManager::OnMouseButtonUp(const SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtons[static_cast<int>(MouseButtons::LEFT)] = false;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtons[static_cast<int>(MouseButtons::MIDDLE)] = false;
    }

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtons[static_cast<int>(MouseButtons::RIGHT)] = false;
    }
}

void EventManager::OnMouseWheel(const SDL_Event& event)
{
    m_mouseWheel = event.wheel.y;
}

bool EventManager::MousePressed(const int b) const
{
    return ((m_mouseCurrent & SDL_BUTTON(b)) > (m_mouseLast & SDL_BUTTON(b)));
}

bool EventManager::MouseReleased(const int b) const
{
    return ((m_mouseCurrent & SDL_BUTTON(b)) < (m_mouseLast & SDL_BUTTON(b)));
}

void EventManager::InitializeControllers()
{
    m_pGameControllers.clear();

    for (auto count = 0; count < SDL_NumJoysticks(); ++count)
    {
        auto controller = new GameController(SDL_GameControllerOpen(count));
        m_pGameControllers.push_back(controller);
    }
}

void EventManager::IMGUIKeymap() const
{
    // Keyboard mapping. ImGui will use those indices to peek into the m_io.KeysDown[] array.
    m_io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
    m_io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
    m_io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
    m_io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
    m_io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
    m_io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
    m_io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
    m_io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
    m_io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
    m_io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
    m_io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
    m_io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
    m_io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
    m_io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
    m_io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;

    m_io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
    m_io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
    m_io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
    m_io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
    m_io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
    m_io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;
}

bool EventManager::GetMouseButton(const int button_number) const
{
    return m_mouseButtons[button_number];
}

glm::vec2 EventManager::GetMousePosition() const
{
    return m_mousePosition;
}

int EventManager::GetMouseWheel() const
{
    return m_mouseWheel;
}

GameController* EventManager::GetGameController(const int controller_number) const
{
    if (SDL_GameControllerGetAttached(m_pGameControllers[controller_number]->handle))
    {
        return m_pGameControllers[controller_number];
    }

    return nullptr;
}

bool EventManager::IsIMGUIActive() const
{
    return m_isIMGUIActive;
}

bool EventManager::IsMainWindowInFocus() const
{
    return m_mainWindowHasFocus;
}

EventManager::EventManager() :
    m_io(ImGui::GetIO()), m_isIMGUIActive(false), m_keyStates(nullptr), m_mouseWheel(0), m_isActive(true), m_mainWindowHasFocus(true)
{
    // initialize mouse position
    m_mousePosition = glm::vec2(0.0f, 0.0f);

    // initialize button states for the mouse
    for (auto& mouse_button_state : m_mouseButtons)
    {
        mouse_button_state = false;
    }

    m_keysCurr = SDL_GetKeyboardState(&m_numKeys);
    m_keysLast = new Uint8[m_numKeys];
    std::memcpy(m_keysLast, m_keysCurr, m_numKeys);
    SDL_Point mouse_pos = { static_cast<int>(m_mousePosition.x), static_cast<int>(m_mousePosition.y) };
    m_mouseCurrent = SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    m_mouseLast = m_mouseCurrent;

    InitializeControllers();

    // initialize IMGUI Key Map
    IMGUIKeymap();
}

EventManager::~EventManager()
= default;
