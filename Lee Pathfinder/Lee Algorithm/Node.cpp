#include "Node.h"


Node::Node(void)
{
}


Node::~Node(void)
{
}

void Node::Initialise(int x_pos, int y_pos)
{
	distance = 0;
	passable = true;
	used = false;
	parent = 0;
	x = x_pos;
	y = y_pos;
	inPath = false;
}

void Node::SetParent(Node *p)
{
	parent = p;
}

void Node::SetDistance(int d)
{
	distance = d;
}