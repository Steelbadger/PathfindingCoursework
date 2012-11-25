#pragma once
#include <deque>
#include <stack>
#include "Node.h"

class Map
{
public:
	Map(void);
	Map(int width, int height);
	~Map(void);

	bool CheckDuplicates(Node *node);
	void SetStart(int x, int y);
	void SetEnd(int x, int y);

	int FindPath();
	int APathFinding();
	void ReturnPath();
	void SetImpassable(int x, int y);
	void Draw(int size);
	double GetTime(){return seconds;}

private:
	void Initialise(int width, int height);


	int mWidth, mHeight;
	Node ***maparray;
	Node *sNode;
	Node *eNode;
	std::deque<Node*> workinglist;
	std::stack<Node*> path;

	double seconds;

	void AddToWList(Node *node, Node *parent);

	static const int DEFAULT_SIZE = 10;
};

