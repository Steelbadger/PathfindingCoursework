#include "Map.h"
#include "Node.h"
#include <iostream>
#include <time.h>

Map::Map(void)
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
	sNode = NULL;
	eNode = NULL;

	maparray = new Node **[width];
	for (int row = 0; row < height; row++)
		maparray[row] = new Node *[height];
	for (int row = 0; row < height; ++row){
		for (int col = 0; col < width; ++col){
			maparray[row][col] = new Node();
			maparray[row][col]->Initialise(col, row);
		}
	}
			
}

void Map::SetStart(int x, int y)
{
	sNode = maparray[y][x];
	std::cout << "Start at X: " << x << "\tY: " << y << std::endl;
}

void Map::SetEnd(int x, int y)
{
	eNode = maparray[y][x];
	std::cout << "End at X: " << x << "\tY: " << y << std::endl;
}

bool Map::CheckDuplicates(Node *n)
{
	if (!n->IsUsed() && n->IsPassable())
		return true;
	else
		return false;
}

void Map::AddToWList(Node *n, Node *p)
{
	if (CheckDuplicates(n)) {
		workinglist.push_back(n);
		n->SetUsed();
		n->SetParent(p);
		n->SetDistance(p->GetDistance()+1);
	}
}

int Map::FindPath()
{
	unsigned long t;
	t = clock();
	if (sNode == NULL || eNode == NULL)		//If start or end are unassigned then quit
		return -1;

	sNode->SetDistance(0);
	workinglist.push_back(sNode);			//Add start node to working set
	sNode->SetUsed();						//Set start Node as used (duplicates list alternative)

	int i = 0;
	bool foundEnd = false;
	Node *temp = NULL;						//temporary values for calculation


	while((i < (int)workinglist.size()) && !foundEnd)							//Move through working set checkin each node to see if
	{																			//it is the end node, if not then add it's neighbours to																		//the working set
		temp = workinglist.at(i++);												
		if (temp == eNode) {
			foundEnd = true;
		} else {
			if (temp->GetY() + 1 < mHeight)
				AddToWList(maparray[temp->GetY() + 1][temp->GetX()], temp);
			if (temp->GetY() > 0)
				AddToWList(maparray[temp->GetY() - 1][temp->GetX()], temp);
			if (temp->GetX() + 1 < mWidth)
				AddToWList(maparray[temp->GetY()][temp->GetX() + 1], temp);
			if (temp->GetX() > 0)
				AddToWList(maparray[temp->GetY()][temp->GetX() - 1], temp);
		}
	}
	if (foundEnd)																//Once a route is found track back through parent references
	{																			//and add to stack for retrieval later, return 0 to indicate success
		while(temp != sNode)													
		{
			path.push(temp);
			temp = temp->GetParent();
		}
		seconds = ((double)(clock() - t)*1000) / CLOCKS_PER_SEC;
		return 0;
	} else {																	//If no route is found return -2
		seconds = ((double)(clock() - t)*1000) / CLOCKS_PER_SEC;
		return -2;
	}
}

void Map::ReturnPath()
{
	Node* temp = NULL;
	while(!path.empty())
	{
		temp = path.top();
		temp->SetInPath();
		path.pop();
		std::cout << "X: " << temp->GetX() << "\tY: " << temp->GetY() << std::endl;
	}

}
void Map::SetImpassable(int x_pos, int y_pos)
{
	maparray[y_pos][x_pos]->SetImpassable();
}

void Map::Draw(int size)
{
	for (int i = 0; i < mHeight; i++){
		for (int q = 0; q < mWidth; q++){
			if (maparray[i][q] == sNode) {
				std::cout << "S";
			} else if (maparray[i][q] == eNode) {
				std::cout << "T";
			} else if (maparray[i][q]->IsInPath()) {
				std::cout << "P";
			} else if (maparray[i][q]->IsPassable()) {
				if (size < 11) {
					std::cout << maparray[i][q]->GetDistance();
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
		std::cout << std::endl;
	}
}