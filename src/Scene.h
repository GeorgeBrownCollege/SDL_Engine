#pragma once
#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <optional>
#include "GameObject.h"

/*
 *Scene Class inherits from GameObject and holds all the DisplayObject Class objects
 *in the child Scene like PlayScene. You can add and remove the objects using the functions
 *in this Class. This Class also calls draw and update for all the DisplayObject Class objects
 *in the child Scene.
 */
class Scene : public GameObject
{
public:
	friend class DisplayObject;
	Scene();
	virtual ~Scene();

	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;
	virtual void handleEvents() = 0;
	virtual void start() = 0;

	void addChild(DisplayObject* child, uint32_t layer_index = 0, std::optional<uint32_t> order_index = std::nullopt);
	void removeChild(DisplayObject* child);

	void removeAllChildren();
	int numberOfChildren() const;

	void updateDisplayList();
	void drawDisplayList();

	std::vector<DisplayObject*> getDisplayList() const;

private:
	uint32_t m_nextLayerIndex = 0; // keeps track of the last layer created
	std::vector<DisplayObject*> m_displayList;

	static bool sortObjects(DisplayObject* left, DisplayObject* right);
};

#endif /* defined (__SCENE__) */
