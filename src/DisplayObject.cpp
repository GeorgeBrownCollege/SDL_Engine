#include "DisplayObject.h"

DisplayObject::DisplayObject()
= default;

DisplayObject::~DisplayObject()
= default;

Scene * DisplayObject::getParent() const
{
	return m_pParentScene;
}

void DisplayObject::setParent(Scene * parent)
{
	m_pParentScene = parent;
}
