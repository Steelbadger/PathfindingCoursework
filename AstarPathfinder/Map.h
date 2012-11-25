#pragma once
#include <queue>
#include <vector>
#include <stack>
#include "Node.h"

class Map
{
public:
	Map(void);
	Map(int width, int height);
	~Map(void);

	bool CheckDuplicates(int x, int y);
	void SetStart(int x, int y);
	void SetEnd(int x, int y);

	int FindPath();
	int FindPathUseDiagonals();
	void ReturnPath();
	void SetImpassable(int x, int y);
	void Draw(int size);
	double GetTime(){return seconds;}

private:
	void Initialise(int width, int height);

	int mWidth, mHeight;
	std::vector<std::vector<bool> > passable;
	std::vector<std::vector<bool> > duplicates;
	std::vector<std::vector<bool> > pathnodes;
	std::vector<std::vector<Node> > nodes;
	Node eNode;
	Node sNode;
	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type> > workinglist;
	std::stack<Node> path;

	double seconds;

	void AddToWListM(Node node, Node parent);
	void AddToWListD(Node node, Node parent);

	static const int DEFAULT_SIZE = 10;
};