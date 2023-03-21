#include "NodeScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"
#include "SDL_Nodes/imnodes.h"

NodeScene::NodeScene()
{
	NodeScene::Start();
}

NodeScene::~NodeScene()
= default;

void NodeScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void NodeScene::Update()
{
	UpdateDisplayList();
}

void NodeScene::Clean()
{
	RemoveAllChildren();
}


void NodeScene::HandleEvents()
{
	EventManager::Instance().Update();

	GetKeyboardInput();
}

void NodeScene::GetKeyboardInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_3))
	{
		Game::Instance().ChangeSceneState(SceneState::NODE);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_4))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void NodeScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Set Input Type
	m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);

	/* Scene Label */
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pSceneLabel = new Label("NODE SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pSceneLabel->GetTransform()->position = glm::vec2(400.0f, 40.0f);

	AddChild(m_pSceneLabel);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", GameObjectType::BACK_BUTTON);
	m_pBackButton->GetTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->AddEventListener(Event::CLICK, [&]()-> void
		{
			m_pBackButton->SetActive(false);
	Game::Instance().ChangeSceneState(SceneState::PLAY);
		});

	m_pBackButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
		{
			m_pBackButton->SetAlpha(128);
		});

	m_pBackButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
		{
			m_pBackButton->SetAlpha(255);
		});
	AddChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", GameObjectType::NEXT_BUTTON);
	m_pNextButton->GetTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->AddEventListener(Event::CLICK, [&]()-> void
		{
			m_pNextButton->SetActive(false);
	Game::Instance().ChangeSceneState(SceneState::END);
		});

	m_pNextButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
		{
			m_pNextButton->SetAlpha(128);
		});

	m_pNextButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
		{
			m_pNextButton->SetAlpha(255);
		});

	AddChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->GetTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	AddChild(m_pInstructionsLabel);

	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void NodeScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::SetNextWindowSize(ImVec2(800.0f, 800.0f));
	ImGui::SetNextWindowContentSize(ImVec2(800.0f, 740.0f));

	ImGui::Begin("Your Window Title Goes Here", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Decision Tree Node Graph");
	ImGui::Text("A -- add node");
	ImGui::Text("X -- delete selected node or link");

	ImGui::Separator();

	ImNodes::BeginNodeEditor();
	const bool open_popup = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
		ImNodes::IsEditorHovered() &&
		ImGui::IsKeyReleased(ImGuiKey_A);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
	if (!ImGui::IsAnyItemHovered() && open_popup)
	{
		ImGui::OpenPopup("add node");
	}

	if (ImGui::BeginPopup("add node"))
	{
		const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();
		if (ImGui::MenuItem("Root Node"))
		{
			const auto root = new EditorNode(EditorNodeType::ROOT);
			m_editorNodes.push_back(root);
			ImNodes::SetNodeScreenSpacePos(root->id, click_pos);
		}
		else if (ImGui::MenuItem("Condition Node"))
		{
			const auto condition = new EditorNode(EditorNodeType::CONDITION);
			m_editorNodes.push_back(condition);
			ImNodes::SetNodeScreenSpacePos(condition->id, click_pos);
		}
		else if (ImGui::MenuItem("Action Node"))
		{
			const auto action = new EditorNode(EditorNodeType::ACTION);
			m_editorNodes.push_back(action);
			ImNodes::SetNodeScreenSpacePos(action->id, click_pos);
		}
		ImGui::EndPopup();
	}
	ImGui::PopStyleVar();

	for (const auto node : m_editorNodes)
	{
		switch (node->type)
		{
		case EditorNodeType::ROOT:
		{
			ImNodes::BeginNode(node->id);

			ImNodes::BeginNodeTitleBar();
			ImGui::Text("Root Node");
			ImGui::SetNextItemWidth(100.0f);
			ImGui::InputText("", node->name, 64);
			ImNodes::EndNodeTitleBar();

			const int left_child_id = node->pins[1];
			const int right_child_id = node->pins[2];

			ImNodes::BeginOutputAttribute(left_child_id);
			ImGui::Indent(60.0f);
			ImGui::Text("True");
			ImNodes::EndOutputAttribute();

			ImGui::Spacing();

			ImNodes::BeginOutputAttribute(right_child_id);
			ImGui::Indent(60.0f);
			ImGui::Text("False");
			ImNodes::EndOutputAttribute();

			ImNodes::EndNode();
		}
		break;
		case EditorNodeType::CONDITION:
		{
			ImNodes::BeginNode(node->id);

			ImNodes::BeginNodeTitleBar();
			ImGui::Text("Condition Node");
			ImGui::SetNextItemWidth(100.0f);
			ImGui::InputText("", node->name, 64);

			ImNodes::EndNodeTitleBar();

			const int parent_id = node->pins[0];
			const int left_child_id = node->pins[1];
			const int right_child_id = node->pins[2];


			ImNodes::BeginOutputAttribute(left_child_id);
			ImGui::Indent(60.0f);
			ImGui::Text("True");
			ImNodes::EndOutputAttribute();

			ImGui::Spacing();

			ImNodes::BeginInputAttribute(parent_id);
			ImNodes::EndInputAttribute();
			ImGui::Spacing();


			ImNodes::BeginOutputAttribute(right_child_id);
			ImGui::Indent(60.0f);
			ImGui::Text("False");
			ImNodes::EndOutputAttribute();


			ImNodes::EndNode();
		}
		break;
		case EditorNodeType::ACTION:
		{
			ImNodes::BeginNode(node->id);

			ImNodes::BeginNodeTitleBar();
			ImGui::Text("Action Node");
			ImGui::SetNextItemWidth(100.0f);
			ImGui::InputText("", node->name, 64);
			ImNodes::EndNodeTitleBar();

			const int parent_id = node->pins[0];

			ImNodes::BeginInputAttribute(parent_id);
			ImNodes::EndInputAttribute();

			ImNodes::EndNode();
		}
		break;

		default:;
		}
	}

	ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);

	for (const auto link : m_nodeLinks)
	{
		ImNodes::Link(link.id, link.start, link.end);
	}

	ImNodes::EndNodeEditor();

	// Remove a link
	{
		const int num_links_selected = ImNodes::NumSelectedLinks();
		if (num_links_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X))
		{

			static std::vector<int> selected_links;
			selected_links.resize(static_cast<size_t>(num_links_selected));
			ImNodes::GetSelectedLinks(selected_links.data());
			for (auto selected_link : selected_links)
			{
				auto iter =
					std::find_if(m_nodeLinks.begin(), m_nodeLinks.end(), [selected_link](const NodeLink& link) -> bool
						{
							return link.id == selected_link;
						});
				m_nodeLinks.erase(iter);
			}
		}
	}

	// Remove a Node
	{
		const int num_nodes_selected = ImNodes::NumSelectedNodes();
		if (num_nodes_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X))
		{
			static std::vector<int> selected_nodes;
			selected_nodes.resize(static_cast<size_t>(num_nodes_selected));
			ImNodes::GetSelectedNodes(selected_nodes.data());
			for (int id : selected_nodes)
			{
				auto iter = std::find_if(
					m_editorNodes.begin(), m_editorNodes.end(), [id](const EditorNode* node) -> bool {
						return node->id == id;
					});

				// Erase any additional internal nodes
				switch ((*iter)->type)
				{
				case EditorNodeType::ROOT:
					break;
				case EditorNodeType::CONDITION:
					break;
				case EditorNodeType::ACTION:
					break;

				}

				for (const int pin : (*iter)->pins)
				{
					for (auto it = m_nodeLinks.begin(); it != m_nodeLinks.end(); ++it)
					{
						if (it->end == pin || it->start == pin)
						{
							m_nodeLinks.erase(it);
							break;
						}
					}
				}

				m_editorNodes.erase(iter);
			}
		}
	}

	// Check if Link is Created
	{
		NodeLink link{};
		if (ImNodes::IsLinkCreated(&link.start, &link.end))
		{
			link.id = m_currentID++;
			m_nodeLinks.push_back(link);
		}
	}

	// Check if Link is Destroyed
	{
		int link_id;
		if (ImNodes::IsLinkDestroyed(&link_id))
		{
			auto iter =
				std::find_if(m_nodeLinks.begin(), m_nodeLinks.end(), [link_id](const NodeLink& link) -> bool
					{
						return link.id == link_id;
					});
			assert(iter != m_nodeLinks.end());
			m_nodeLinks.erase(iter);
		}
	}


	ImGui::End();
}
