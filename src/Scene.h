#pragma once
#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <optional>
#include "GameObject.h"


class Scene : public GameObject {

	public:
	friend class DisplayObject;

	Scene();
	virtual ~Scene();

	// Inherited via GameObject
	virtual void Draw() override = 0;
	virtual void Update() override = 0;
	virtual void Clean() override = 0;
	virtual void HandleEvents() = 0;
	virtual void Start() = 0;

	void AddChild(DisplayObject *_child, uint32_t _layerIndex = 0, std::optional<uint32_t> _orderIndex = std::nullopt);
	void RemoveChild(DisplayObject *_child);

	void RemoveAllChildren();
	int NumberOfChildren() const;

	void UpdateDisplayList();
	void DrawDisplayList();

	private:

	uint32_t m_nextLayerIndex = 0;
	std::vector<DisplayObject *> m_displayList;

	static bool sortObjects(DisplayObject *left, DisplayObject *right);
};

#endif /* defined (__SCENE__) */
