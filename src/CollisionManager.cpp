#include "CollisionManager.h"
#include "Util.h"
#include <algorithm>



int CollisionManager::SquaredDistance(const glm::vec2 p1, const glm::vec2 p2)
{
	const auto diff_of_xs = static_cast<int>(p2.x - p1.x);
	const auto diff_of_ys = static_cast<int>(p2.y - p1.y);

	return diff_of_xs * diff_of_xs + diff_of_ys * diff_of_ys;
}

bool CollisionManager::SquaredRadiusCheck(GameObject* object1, GameObject* object2)
{
	const glm::vec2 p1 = object1->GetTransform()->position;
	const glm::vec2 p2 = object2->GetTransform()->position;

	if (const int half_heights = static_cast<int>((object1->GetHeight() + object2->GetHeight()) * 0.5); 
		SquaredDistance(p1, p2) < (half_heights * half_heights)) 
	{
		if (!object2->GetRigidBody()->isColliding) 
		{
			object2->GetRigidBody()->isColliding = true;

			switch (object2->GetType()) {
			case GameObjectType::TARGET:
				std::cout << "Collision with Target!" << std::endl;
				SoundManager::Instance().PlaySound("yay", 0);

				break;
			default:

				break;
			}

			return true;
		}
		return false;
	}
	object2->GetRigidBody()->isColliding = false;
	return false;

}

bool CollisionManager::AABBCheck(GameObject* object1, GameObject* object2)
{
	// prepare relevant variables
	const auto p1 = object1->GetTransform()->position;
	const auto p2 = object2->GetTransform()->position;
	const auto p1_width = static_cast<float>(object1->GetWidth());
	const auto p1_height = static_cast<float>(object1->GetHeight());
	const auto p2_width = static_cast<float>(object2->GetWidth());
	const auto p2_height = static_cast<float>(object2->GetHeight());

	if (
		p1.x < p2.x + p2_width &&
		p1.x + p1_width > p2.x &&
		p1.y < p2.y + p2_height &&
		p1.y + p1_height > p2.y
		)
	{
		if (!object2->GetRigidBody()->isColliding) 
		{

			object2->GetRigidBody()->isColliding = true;

			switch (object2->GetType()) {
			case GameObjectType::TARGET:
				std::cout << "Collision with Target!" << std::endl;
				SoundManager::Instance().PlaySound("yay", 0);
				break;
			case GameObjectType::OBSTACLE:
				std::cout << "Collision with Obstacle!" << std::endl;
				SoundManager::Instance().PlaySound("yay", 0);
				break;
			default:

				break;
			}

			return true;
		}
		return false;
	}
	object2->GetRigidBody()->isColliding = false;
	return false;

}

bool CollisionManager::LineLineCheck(const glm::vec2 line1_start, const glm::vec2 line1_end, const glm::vec2 line2_start, const glm::vec2 line2_end)
{
	const auto x1 = line1_start.x;
	const auto x2 = line1_end.x;
	const auto x3 = line2_start.x;
	const auto x4 = line2_end.x;
	const auto y1 = line1_start.y;
	const auto y2 = line1_end.y;
	const auto y3 = line2_start.y;
	const auto y4 = line2_end.y;

	// calculate the distance to intersection point
	const auto u_a = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	const auto u_b = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (u_a >= 0 && u_a <= 1 && u_b >= 0 && u_b <= 1)
	{
		return true;
	}
	return false;
}

bool CollisionManager::LineRectCheck(const glm::vec2 line_start, const glm::vec2 line_end, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	const auto x1 = line_start.x;
	const auto x2 = line_end.x;
	const auto y1 = line_start.y;
	const auto y2 = line_end.y;
	const auto rx = rect_start.x;
	const auto ry = rect_start.y;
	const auto rw = rect_width;
	const auto rh = rect_height;

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	const auto left = LineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	const auto right = LineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	const auto top = LineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	const auto bottom = LineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) 
	{
		return true;
	}

	return false;
}

bool CollisionManager::LineRectEdgeCheck(const glm::vec2 line_start, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	bool state = false;

	const auto x1 = line_start.x;
	const auto y1 = line_start.y;

	const auto rx = rect_start.x;
	const auto ry = rect_start.y;
	const auto rw = rect_width;
	const auto rh = rect_height;

	// configure the left edge
	const auto left_edge_start = glm::vec2(rx, ry);
	const auto left_edge_end = glm::vec2(rx, ry + rh);
	const auto left_edge_mid_point = Util::Lerp(left_edge_start, left_edge_end, 0.5f);

	// configure the right edge
	const auto right_edge_start = glm::vec2(rx + rw, ry);
	const auto right_edge_end = glm::vec2(rx + rw, ry + rh);
	const auto right_edge_mid_point = Util::Lerp(right_edge_start, right_edge_end, 0.5f);

	// configure the top edge
	const auto top_edge_start = glm::vec2(rx, ry);
	const auto top_edge_end = glm::vec2(rx + rw, ry);
	const auto top_edge_mid_point = Util::Lerp(top_edge_start, top_edge_end, 0.5f);

	// configure the bottom edge
	const auto bottom_edge_start = glm::vec2(rx, ry + rh);
	const auto bottom_edge_end = glm::vec2(rx + rw, ry + rh);
	const auto bottom_edge_mid_point = Util::Lerp(bottom_edge_start, bottom_edge_end, 0.5f);

	// line / line comparisons
	const auto left = LineLineCheck(glm::vec2(x1, y1), left_edge_mid_point, left_edge_start, left_edge_end);
	const auto right = LineLineCheck(glm::vec2(x1, y1), right_edge_mid_point, right_edge_start, right_edge_end);
	const auto top = LineLineCheck(glm::vec2(x1, y1), top_edge_mid_point, top_edge_start, top_edge_end);
	const auto bottom = LineLineCheck(glm::vec2(x1, y1), bottom_edge_mid_point, bottom_edge_start, bottom_edge_end);

	// return true if any line collides with the edge
	if (left || right || top || bottom)
	{
		state = true;
	}
	return state;
}

int CollisionManager::MinSquaredDistanceLineLine(glm::vec2 line1_start, glm::vec2 line1_end, glm::vec2 line2_start, glm::vec2 line2_end)
{
	auto u = line1_end - line1_start;
	auto v = line2_end - line2_start;
	auto w = line1_start - line2_start;
	auto a = Util::Dot(u, u);         // always >= 0
	auto b = Util::Dot(u, v);
	auto c = Util::Dot(v, v);         // always >= 0
	auto d = Util::Dot(u, w);
	auto e = Util::Dot(v, w);
	auto D = a * c - b * b;					// always >= 0
	float sc, tc;

	// compute the line parameters of the two closest points
	if (D < Util::EPSILON) {					// the lines are almost parallel
		sc = 0.0;
		tc = (b > c ? d / b : e / c);			// use the largest denominator
	}
	else {
		sc = (b * e - c * d) / D;
		tc = (a * e - b * d) / D;
	}

	// get the difference of the two closest points
	auto d_p = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

	// return the normal
	return static_cast<int>(Util::Dot(d_p, d_p));
}

bool CollisionManager::LineAABBCheck(Ship* object1, GameObject* object2)
{
	const auto line_start = object1->GetTransform()->position;
	const auto line_end = object1->GetTransform()->position + object1->GetCurrentDirection() * 100.0f;
	// aabb
	const auto box_width = static_cast<float>(object2->GetWidth());
	const auto half_box_width = box_width * 0.5f;
	const auto box_height = static_cast<float>(object2->GetHeight());
	const auto half_box_height = box_height * 0.5f;
	const auto box_start = object2->GetTransform()->position - glm::vec2(half_box_width, half_box_height);

	if (LineRectCheck(line_start, line_end, box_start, box_width, box_height))
	{
		switch (object2->GetType())
		{
		case GameObjectType::TARGET:
			std::cout << "Collision with Obstacle!" << std::endl;
			SoundManager::Instance().PlaySound("yay", 0);

			break;
		default:

			break;
		}
		return true;
	}
	return false;
}

int CollisionManager::CircleAABBSquaredDistance(const glm::vec2 circle_centre, int circle_radius, const glm::vec2 box_start, const int box_width, const int box_height)
{
	auto dx = std::max(box_start.x - circle_centre.x, 0.0f);
	dx = std::max(dx, circle_centre.x - (box_start.x + static_cast<float>(box_width)));
	auto dy = std::max(box_start.y - circle_centre.y, 0.0f);
	dy = std::max(dy, circle_centre.y - (box_start.y + static_cast<float>(box_height)));

	return static_cast<int>((dx * dx) + (dy * dy));
}

bool CollisionManager::CircleAABBCheck(GameObject* object1, GameObject* object2)
{
	// common properties
	const auto box_width = static_cast<float>(object2->GetWidth());
	const auto box_height = static_cast<float>(object2->GetHeight());
	const auto half_box_width = box_width * 0.5f;
	const auto half_box_height = box_height * 0.5f;

	// circle
	const auto circle_centre = object1->GetTransform()->position;
	const auto circle_radius = static_cast<int>(std::max(half_box_width, half_box_height));

	// aabb

	if (const auto box_start = object2->GetTransform()->position - glm::vec2(half_box_width, half_box_height); 
		CircleAABBSquaredDistance(circle_centre, circle_radius, box_start, object2->GetWidth(), object2->GetHeight()) <= (circle_radius * circle_radius))
	{
		if (!object2->GetRigidBody()->isColliding) 
		{
			object2->GetRigidBody()->isColliding = true;

			const auto attack_vector = object1->GetTransform()->position - object2->GetTransform()->position;
			constexpr auto normal = glm::vec2(0.0f, -1.0f);

			const auto dot = Util::Dot(attack_vector, normal);
			const auto angle = acos(dot / Util::Magnitude(attack_vector)) * Util::Rad2Deg;

			switch (object2->GetType())
			{
			case GameObjectType::TARGET:
				std::cout << "Collision with Planet!" << std::endl;
				SoundManager::Instance().PlaySound("yay", 0);
				break;
			case GameObjectType::SHIP:
			{
				SoundManager::Instance().PlaySound("thunder", 0);
				const auto velocity_x = object1->GetRigidBody()->velocity.x;
				const auto velocity_y = object1->GetRigidBody()->velocity.y;

				if ((attack_vector.x > 0 && attack_vector.y < 0) || (attack_vector.x < 0 && attack_vector.y < 0))
					// top right or top left
				{
					if (angle <= 45)
					{
						object1->GetRigidBody()->velocity = glm::vec2(velocity_x, -velocity_y);
					}
					else
					{
						object1->GetRigidBody()->velocity = glm::vec2(-velocity_x, velocity_y);
					}
				}

				if ((attack_vector.x > 0 && attack_vector.y > 0) || (attack_vector.x < 0 && attack_vector.y > 0))
					// bottom right or bottom left
				{
					if (angle <= 135)
					{
						object1->GetRigidBody()->velocity = glm::vec2(-velocity_x, velocity_y);
					}
					else
					{
						object1->GetRigidBody()->velocity = glm::vec2(velocity_x, -velocity_y);
					}
				}
			}
			break;
			default:

				break;
			}

			return true;
		}
		return false;
	}
	object2->GetRigidBody()->isColliding = false;
	return false;

}

bool CollisionManager::PointRectCheck(const glm::vec2 point, const glm::vec2 rect_start, const float rect_width, const float rect_height)
{
	const float top_left_x = rect_start.x - rect_width * 0.5f;
	const float top_left_y = rect_start.y - rect_height * 0.5f;
	const auto width = rect_width;
	const auto height = rect_height;

	if (point.x > top_left_x &&
		point.x < top_left_x + width &&
		point.y > top_left_y &&
		point.y < top_left_y + height)
	{
		return true;
	}
	return false;
}

// assumptions - the list of objects are stored so that they are facing the target and the target is loaded last
bool CollisionManager::LOSCheck(Agent* agent, const glm::vec2 end_point, const std::vector<DisplayObject*>& objects, DisplayObject* target)
{
	const auto start_point = agent->GetTransform()->position;

	for (const auto object : objects)
	{
		const auto width = static_cast<float>(object->GetWidth());
		const auto height = static_cast<float>(object->GetHeight());
		auto object_offset = glm::vec2(width * 0.5f, height * 0.5f);
		const auto rect_start = object->GetTransform()->position - object_offset;
		

		switch (object->GetType())
		{
		case GameObjectType::OBSTACLE:
			if (LineRectCheck(start_point, end_point, rect_start, width, height))
			{
				return false;
			}
			break;
		case GameObjectType::TARGET:
		{
			switch (agent->GetType())
			{
			case GameObjectType::AGENT:
				if (LineRectCheck(start_point, end_point, rect_start, width, height))
				{
					return true;
				}
				break;
			case GameObjectType::PATH_NODE:
				if (LineRectEdgeCheck(start_point, rect_start, width, height))
				{
					return true;
				}
				break;
			default:
				//error
				std::cout << "ERROR: " << static_cast<int>(agent->GetType()) << std::endl;
				break;
			}
		}
		break;
		default:
			//error
			std::cout << "ERROR: " << static_cast<int>(object->GetType()) << std::endl;
			break;
		}

	}

	// if the line does not collide with an object that is the target then LOS is false
	return false;
}


CollisionManager::CollisionManager()
= default;


CollisionManager::~CollisionManager()
= default;
