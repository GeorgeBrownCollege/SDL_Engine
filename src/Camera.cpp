#include "Camera.h"

Camera::Camera() { 

}


void Camera::Update() {


}

void Camera::Draw() { }
void Camera::Clean() { }

void Camera::SetGlobalPositions() {

	for (auto child : m_children) {

		if (child->IsEnabled()) { 
		
			child->GetTransform()->global_position
				= this->GetTransform()->local_position + child->GetTransform()->local_position;
		}
	
	}
}