#include "DisplayObject.h"

DisplayObject::DisplayObject()
= default;

DisplayObject::~DisplayObject()
= default;

//Returns what Scene the DisplayObject has been previously added to.
Scene * DisplayObject::getParent() const
{
	return m_pParentScene;
}

//Sets what Scene the DisplayObject is added to.
void DisplayObject::setParent(Scene * parent)
{
	m_pParentScene = parent;
}
//Get layer the DisplayObject is in.
uint32_t DisplayObject::getLayerIndex() const
{
	return m_layerIndex;
}
//Get order in layer the DisplayObject is in.
uint32_t DisplayObject::getLayerOrderIndex() const
{
	return m_layerOrderIndex;
}
//Set layer and order in layer of the DisplayObject.
void DisplayObject::setLayerIndex(const uint32_t new_index, const uint32_t new_order)
{
	m_layerIndex = new_index;
	m_layerOrderIndex = new_order;
}
