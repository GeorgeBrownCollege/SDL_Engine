#pragma once
#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <optional>
#include "GameObject.h"


class Scene : public GameObject
{
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

	void AddChild(DisplayObject* child, uint32_t layer_index = 0, std::optional<uint32_t> order_index = std::nullopt);
	void RemoveChild(DisplayObject* child);

	void RemoveAllChildren();
	[[nodiscard]] int NumberOfChildren() const;

	void UpdateDisplayList();
	void DrawDisplayList();

	[[nodiscard]] std::vector<DisplayObject*> GetDisplayList() const;

private:
	uint32_t m_nextLayerIndex = 0;
	std::vector<DisplayObject*> m_displayList;

	static bool SortObjects(DisplayObject* left, DisplayObject* right);
};

#endif /* defined (__SCENE__) */
