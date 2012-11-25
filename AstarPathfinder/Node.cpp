#include "Node.h"
#include <stdlib.h>
#include <math.h>
#include <algorithm>

Node::Node(int x_pos, int y_pos)
{
	Initialise(x_pos, y_pos);
}

Node::Node(int x_pos, int y_pos, int px, int py, int tx, int ty, int gDist)
{
	Initialise(x_pos, y_pos);
	p_x = px;
	p_y = py;
	SetGDistance(gDist);
}

Node::Node()
{
}


Node::~Node(void)
{
}

void Node::Initialise(int x_pos, int y_pos)
{
	gDistance = 0;
	fDistance = 0;
	hDistance = 0;
	x = x_pos;
	y = y_pos;
}

void Node::SetGDistance(int d)
{
	gDistance = d;
	fDistance = gDistance + hDistance;
}

void Node::SetHDistanceManhatten(int xTarget, int yTarget)
{
	hDistance = (abs(xTarget - x) + abs(yTarget - y))*10;
	fDistance = hDistance + gDistance;
}

void Node::SetHDistanceDiagonal(int xTarget, int yTarget)
{
	hDistance = std::max(abs(xTarget - x), abs(yTarget - y))*10;
	fDistance = hDistance + gDistance;
}

bool Node::operator<(Node rhs) const
{
	if (fDistance == rhs.fDistance)
		return (hDistance > rhs.hDistance);
	else
		return (fDistance > rhs.fDistance);
}

bool Node::operator>(Node rhs) const
{
	if (fDistance == rhs.fDistance)
		return (hDistance < rhs.hDistance);
	else
		return (fDistance < rhs.fDistance);
}

bool Node::operator==(Node rhs) const
{
	return (x == rhs.GetX() && y == rhs.GetY());
}

bool Node::operator!=(Node rhs) const
{
	return (x != rhs.GetX() || y != rhs.GetY());
}