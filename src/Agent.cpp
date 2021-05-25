#include "Agent.h"

#include "Util.h"

Agent::Agent()
{
}

Agent::~Agent()
= default;

/*
 * Returns the position of the Agent's target which could be where they
 * are headed in the case of an AI character for example.
 */
glm::vec2 Agent::getTargetPosition() const
{
	return m_targetPosition;
}

/*
 * Returns the current direction which can be used to set the the Rigidbody acceleration for example.
 * For instance the Rigidbody->acceleration = getCurrentDirection * (a float for acceleration);
 */
glm::vec2 Agent::getCurrentDirection() const
{
	return m_currentDirection;
}

 
// Returns distance the the Agent has Line Of Sight (LOS) over.
float Agent::getLOSDistance() const
{
	return m_LOSDistance;
}

// Returns a bool for Line Of Sight of the player for example. 
bool Agent::hasLOS() const
{
	return m_hasLOS;
}

// Returns the heading (angle the Agent is facing from starting position) 
float Agent::getCurrentHeading() const
{
	return m_currentHeading;
}

// Returns the colour of the LOS debugging line
glm::vec4 Agent::getLOSColour() const
{
	return m_LOSColour;
}

// Set the target position which for example an AI can use to head towards 
void Agent::setTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

/*
 * Sets the current direction which can be used to set the the Rigidbody acceleration for example.
 * For instance the Rigidbody->acceleration = getCurrentDirection * (a float for acceleration);
 */
void Agent::setCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

// Sets the distance the Agent has Line Of Sight over.
void Agent::setLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}


// Sets if the Agent has Line Of Sight and sets the colour of the Line appropriately for debugging.
void Agent::setHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1); // uses a ternary operator.
}

// Sets the heading (angle the Agent is facing from starting position) 
void Agent::setCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	m_changeDirection();
}

// Sets the colour of the LOS debugging line
void Agent::setLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

/* m_currentDirection is set using math from Util class that when multiplied by
* m_currentHeading angle creates a radian value which the cmath library takes
* as an argument to it's cos() or sin() functions.
* m_currentDirection is then set from the x and y determined by this math.
*/
void Agent::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
