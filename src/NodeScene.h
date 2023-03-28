#pragma once
#ifndef __NODE_SCENE__
#define __NODE_SCENE__

#include "ActionType.h"
#include "Scene.h"
#include "Button.h"
#include "ConditionType.h"
#include "EditorNode.h"
#include "Label.h"
#include "NodeLink.h"

class NodeScene : public Scene
{
public:
	NodeScene();
	~NodeScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;

	// UI Items
	Button* m_pBackButton{};
	Button* m_pNextButton{};
	Label* m_pInstructionsLabel{};
	Label* m_pSceneLabel{};

	// Input Control
	int m_pCurrentInputType{};
	void GetKeyboardInput();

	// Editor Nodes
	std::vector<EditorNode*> m_editorNodes;
	std::vector<NodeLink> m_nodeLinks;
	int m_currentID = 0;

	// Decision Tree Stuff
	std::string m_conditions[static_cast<int>(ConditionType::NUM_OF_CONDITIONS)];
	std::string m_actions[static_cast<int>(ActionType::NUM_OF_ACTIONS)];
	void m_buildConditionArray();
	void m_buildActionArray();
};

#endif /* defined (__NODE_SCENE__) */