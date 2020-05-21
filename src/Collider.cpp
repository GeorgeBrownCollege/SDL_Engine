#include "Collider.h"

Collider::Collider(Transform* const ownerTransform, glm::vec2 anchor) :m_pTransform(ownerTransform), m_anchor(anchor)
{
}
