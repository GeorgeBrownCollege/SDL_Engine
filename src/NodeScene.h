#pragma once
#ifndef __NODE_SCENE__
#define __NODE_SCENE__

#include "Scene.h"
#include "Button.h"
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
};

#endif /* defined (__NODE_SCENE__) */