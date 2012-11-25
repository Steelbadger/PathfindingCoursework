#pragma once
class Node
{
public:
	Node(void);
	~Node(void);

	void Initialise(int x, int y);
	bool IsPassable(){return passable;}
	bool IsUsed(){return used;}
	int GetDistance(){return distance;}
	int GetX(){return x;}
	int GetY(){return y;}

	void SetUsed() {used = true;}
	void SetParent(Node *parent);
	Node* GetParent(){return parent;}
	void SetDistance(int distance);
	void SetImpassable(){passable = false;}
	bool IsInPath(){return inPath;}
	void SetInPath(){inPath = true;}

private:

	Node* parent;
	int distance;
	bool passable;
	bool used;
	bool inPath;
	int x, y;
};

