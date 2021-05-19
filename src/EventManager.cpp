#include "EventManager.h"
#include <iostream>
#include "Game.h"

void EventManager::reset()
{
    m_isActive = false;
    SDL_Delay(300);
    m_isActive = true;
}

void EventManager::update()
{
    if (m_isActive)
    {
        m_io = ImGui::GetIO();
        m_mouseWheel = 0;


        for (auto controller : m_pGameControllers)
        {
            if (SDL_GameControllerGetAttached(controller->handle))
            {
                controller->update();
            }
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                TheGame::Instance().quit();
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(m_mainWindowHasFocus)
                {
                    onMouseButtonDown(event);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (m_mainWindowHasFocus)
                {
                    onMouseButtonUp(event);
                }
                break;

            case SDL_MOUSEWHEEL:
                m_mouseWheel = event.wheel.y;
                break;

            case SDL_TEXTINPUT:
                m_io.AddInputCharactersUTF8(event.text.text);
                break;

            case SDL_KEYDOWN:
                onKeyDown();

                if (event.key.keysym.sym == SDLK_BACKQUOTE)
                {
                    m_isIMGUIActive = (m_isIMGUIActive) ? false : true;


                    if (m_isIMGUIActive)
                    {
                        SDL_ShowWindow(ImGuiWindowFrame::Instance().getWindow());
                    }
                    else
                    {
                        SDL_HideWindow(ImGuiWindowFrame::Instance().getWindow());
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
                onKeyUp();
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
                m_initializeControllers();
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                std::cout << "Controller Removed " << std::endl;
                m_initializeControllers();
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    if (ImGuiWindowFrame::Instance().getWindowID() == event.window.windowID)
                    {
                        SDL_HideWindow(ImGuiWindowFrame::Instance().getWindow());
                        m_isIMGUIActive = false;
                    }
                    else
                    {
                        TheGame::Instance().quit();
                    }
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:

                    m_mainWindowHasFocus = (ImGuiWindowFrame::Instance().getWindowID() == event.window.windowID) ? false : true;

                    break;
                }
                break;


            default:
                break;
            }
        }

        m_io.DeltaTime = 1.0f / 60.0f;
        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        m_io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
        m_io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        m_io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
        m_io.MouseWheel = static_cast<float>(m_mouseWheel);

        m_io.DisplaySize.x = Config::SCREEN_WIDTH;
        m_io.DisplaySize.y = Config::SCREEN_HEIGHT;
    }
}

void EventManager::clean()
{
    for (auto count = 0; count < m_pGameControllers.size(); ++count)
    {
        if (m_pGameControllers[count] != nullptr)
        {
            SDL_GameControllerClose(m_pGameControllers[count]->handle);
        }
    }

    m_pGameControllers.clear();
}

bool EventManager::isKeyDown(const SDL_Scancode key) const
{
    if (m_keyStates != nullptr)
    {
        if (m_keyStates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool EventManager::isKeyUp(const SDL_Scancode key) const
{
    if (m_keyStates != nullptr)
    {
        if (m_keyStates[key] == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void EventManager::onKeyDown()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void EventManager::onKeyUp()
{
    m_keyStates = SDL_GetKeyboardState(nullptr);
}

void EventManager::onMouseMove(SDL_Event& event)
{
    m_mousePosition.x = event.motion.x;
    m_mousePosition.y = event.motion.y;
}

void EventManager::onMouseButtonDown(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtons[LEFT] = true;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtons[MIDDLE] = true;
    }

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtons[RIGHT] = true;
    }
}

void EventManager::onMouseButtonUp(SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        m_mouseButtons[LEFT] = false;
    }

    if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        m_mouseButtons[MIDDLE] = false;
    }

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        m_mouseButtons[RIGHT] = false;
    }
}

void EventManager::onMouseWheel(SDL_Event& event)
{
    m_mouseWheel = event.wheel.y;
}

void EventManager::m_initializeControllers()
{
    m_pGameControllers.clear();

    for (auto count = 0; count < SDL_NumJoysticks(); ++count)
    {
        auto controller = new GameController(SDL_GameControllerOpen(count));
        m_pGameControllers.push_back(controller);
    }
}

void EventManager::m_IMGUI_Keymap()
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

bool EventManager::getMouseButton(const int button_number) const
{
    return m_mouseButtons[button_number];
}

glm::vec2 EventManager::getMousePosition() const
{
    return m_mousePosition;
}

int EventManager::getMouseWheel() const
{
    return m_mouseWheel;
}

GameController* EventManager::getGameController(const int controller_number)
{
    if (SDL_GameControllerGetAttached(m_pGameControllers[controller_number]->handle))
    {
        return m_pGameControllers[controller_number];
    }

    return nullptr;
}

bool EventManager::isIMGUIActive() const
{
    return m_isIMGUIActive;
}

bool EventManager::isMainWindowInFocus() const
{
    return m_mainWindowHasFocus;
}

EventManager::EventManager() :
    m_io(ImGui::GetIO()), m_isIMGUIActive(false), m_keyStates(nullptr), m_mouseWheel(0), m_isActive(true), m_mainWindowHasFocus(true)
{
    // initialize mouse position
    m_mousePosition = glm::vec2(0.0f, 0.0f);

    // initialize button states for the mouse
    for (auto& mouseButtonState : m_mouseButtons)
    {
        mouseButtonState = false;
    }

    m_initializeControllers();

    // initialize IMGUI Key Map
    m_IMGUI_Keymap();
}

EventManager::~EventManager()
= default;
