#include "Map.h"
#include "Node.h"
#include <iostream>
#include <time.h>
#include <queue>

Map::Map(void):
	eNode(),
	sNode()
{
	Initialise(DEFAULT_SIZE, DEFAULT_SIZE);
}

Map::Map(int width, int height)
{
	Initialise(width, height);
}

Map::~Map(void)
{
}

void Map::Initialise(int width, int height)
{
	mWidth = width;
	mHeight = height;
	passable.resize(mWidth);
	duplicates.resize(mWidth);
	pathnodes.resize(mWidth);
	nodes.resize(mWidth);
	for (int i = 0; i < passable.size(); i++) {
		passable[i].resize(mHeight);
		duplicates[i].resize(mHeight);
		nodes[i].resize(mHeight);
		pathnodes[i].resize(mHeight);
	}
	for (int row = 0; row < height; ++row){
		for (int col = 0; col < width; ++col){
			passable[row][col] = true;
			duplicates[row][col] = false;
			nodes[row][col].Initialise(row, col);
			pathnodes[row][col] = false;
		}
	}		
}

void Map::SetStart(int x, int y)
{
	workinglist.push(nodes[x][y]);
	sNode.Initialise(x, y);
	duplicates[x][y] = true;
	std::cout << "Start at X: " << x << "\tY: " << y << std::endl;
}

void Map::SetEnd(int x, int y)
{
	eNode.Initialise(x, y);
	std::cout << "End at X: " << x << "\tY: " << y << std::endl;
}

bool Map::CheckDuplicates(int x, int y)
{
	if (!duplicates[x][y] && passable[x][y])
		return true;
	else
		return false;
}

void Map::AddToWListM(Node n, Node p)
{
	if (CheckDuplicates(n.GetX(), n.GetY())) {
		n.SetParent(p);
		nodes[n.GetX()][n.GetY()].SetParent(p);
		nodes[n.GetX()][n.GetY()].SetGDistance(p.GetGDistance() + 10);	
		nodes[n.GetX()][n.GetY()].SetHDistanceManhatten(eNode.GetX(), eNode.GetY());
		workinglist.push(nodes[n.GetX()][n.GetY()]);
		duplicates[n.GetX()][n.GetY()] = true;
	}
}

void Map::AddToWListD(Node n, Node p)
{
	if (CheckDuplicates(n.GetX(), n.GetY())) {
		n.SetParent(p);
		nodes[n.GetX()][n.GetY()].SetParent(p);

		if (n.GetX() != p.GetX() && n.GetY() != p.GetY()) {
			nodes[n.GetX()][n.GetY()].SetGDistance(p.GetGDistance() + 14);
		} else {
			nodes[n.GetX()][n.GetY()].SetGDistance(p.GetGDistance() + 10);
		}

		nodes[n.GetX()][n.GetY()].SetHDistanceDiagonal(eNode.GetX(), eNode.GetY());
		workinglist.push(nodes[n.GetX()][n.GetY()]);
		duplicates[n.GetX()][n.GetY()] = true;
	}
}

int Map::FindPath()
{
	unsigned long t;
	t = clock();

	bool foundEnd = false;
	Node temp;								//temporary value for calculation

	if (!workinglist.empty()) {														//  Ensure the workinglist is not empty.
		workinglist.top().SetHDistanceManhatten(eNode.GetX(), eNode.GetY());		//  If it is empty then do not attempt to find
	} else {																		//  path and 
		return -3;
	}

	while(!workinglist.empty() && !foundEnd)							//Move through working set checkin each node to see if
	{																	//it is the end node, if not then add it's neighbours to																			
		temp = workinglist.top();										//the working set.
		workinglist.pop();
		if (temp == eNode) {
			foundEnd = true;
		} else {
			if (temp.GetX() + 1 < mWidth)
				AddToWListM(nodes[temp.GetX() + 1][temp.GetY()], temp);
			if (temp.GetX() > 0)
				AddToWListM(nodes[temp.GetX() - 1][temp.GetY()], temp);
			if (temp.GetY() + 1 < mHeight)
				AddToWListM(nodes[temp.GetX()][temp.GetY() + 1], temp);
			if (temp.GetY() > 0)
				AddToWListM(nodes[temp.GetX()][temp.GetY() - 1], temp);
		}
	}
	if (foundEnd)																//Once a route is found track back through parent references
	{																			//and add to stack for retrieval later, return 0 to indicate success.
		while(temp != sNode)													
		{
			path.push(temp);
			temp = nodes[temp.ParentX()][temp.ParentY()];
		}
		seconds = ((double)(clock() - t) * 1000) / CLOCKS_PER_SEC;
		return 0;
	} else {																	//If no route is found return -2.
		seconds = ((double)(clock() - t) * 1000) / CLOCKS_PER_SEC;
		return -2;
	}
}

int Map::FindPathUseDiagonals()
{
	unsigned long t;
	t = clock();						//  Start timing the algorithm.

	bool foundEnd = false;
	Node temp;							//  Temporary value for calculation.

	if (!workinglist.empty()) {														//  Ensure the workinglist is not empty.
		workinglist.top().SetHDistanceDiagonal(eNode.GetX(), eNode.GetY());			//  If it is empty then do not attempt to find
	} else {																		//  path and 
		return -3;
	}

	while(!workinglist.empty() && !foundEnd)							//  Move through working set checkin each node to see if
	{																	//  it is the end node, if not then add it's neighbours to																
		temp = workinglist.top();										//  the working set.
		workinglist.pop();
		if (temp == eNode) {
			foundEnd = true;
		} else {
			if (temp.GetX() + 1 < mHeight)
				AddToWListD(nodes[temp.GetX() + 1][temp.GetY()], temp);
			if (temp.GetX() > 0)
				AddToWListD(nodes[temp.GetX() - 1][temp.GetY()], temp);
			if (temp.GetY() + 1 < mWidth)
				AddToWListD(nodes[temp.GetX()][temp.GetY() + 1], temp);
			if (temp.GetY() > 0)
				AddToWListD(nodes[temp.GetX()][temp.GetY() - 1], temp);
			if (temp.GetX() > 0 && temp.GetY() > 0)
				AddToWListD(nodes[temp.GetX() - 1][temp.GetY() - 1], temp);
			if (temp.GetX() + 1 < mHeight && temp.GetY() > 0)
				AddToWListD(nodes[temp.GetX() + 1][temp.GetY() - 1], temp);
			if (temp.GetX() + 1 < mHeight && temp.GetY() + 1 < mWidth)
				AddToWListD(nodes[temp.GetX() + 1][temp.GetY() + 1], temp);
			if (temp.GetX() > 0 && temp.GetY() + 1 < mWidth)
				AddToWListD(nodes[temp.GetX() - 1][temp.GetY() + 1], temp);
		}
	}
	if (foundEnd)																//  Once a route is found track back through parent references
	{																			//  and add to stack for retrieval later, return 0 to indicate success.
		while(temp != sNode)													
		{
			path.push(temp);
			temp = nodes[temp.ParentX()][temp.ParentY()];
		}
		seconds = ((double)(clock() - t)*1000) / CLOCKS_PER_SEC;
		return 0;
	} else {																	//  If no route is found return -2.
		seconds = ((double)(clock() - t)*1000) / CLOCKS_PER_SEC;
		return -2;
	}
}


void Map::ReturnPath()
{
	Node temp;
	while(!path.empty())
	{
		temp = path.top();
		pathnodes[temp.GetX()][temp.GetY()] = true;
		path.pop();
		std::cout << "X: " << temp.GetX() << "\tY: " << temp.GetY() << std::endl;
	}
}


void Map::SetImpassable(int x_pos, int y_pos)
{
	passable[y_pos][x_pos] = false;
}

void Map::Draw(int size)
{
	for (int i = 0; i < mHeight; i++){
		for (int q = 0; q < mWidth; q++){
			if (nodes[i][q] == sNode) {
				std::cout << "S";
			} else if (nodes[i][q] == eNode) {
				std::cout << "T";
			} else if (pathnodes[i][q]) {
				std::cout << "P";
			} else if (passable[i][q]) {
				if (duplicates[i][q] && size < 11) {
					std::cout << nodes[i][q].GetFDistance();
				} else {
					std::cout << " ";
				}
			} else {
				std::cout << "X";
			}
			if (size < 11) {
				std::cout << "\t";
			}
		}
		if (size < 80) {
			std::cout << std::endl;
		}
	}
}