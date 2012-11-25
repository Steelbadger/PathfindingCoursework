#pragma once
class Node
{
public:
	Node(int x, int y);
	Node(int x, int y, int p_x, int p_y, int t_x, int t_y, int gDist);
	Node();
	~Node(void);

	void Initialise(int x, int y);
	int GetFDistance(){return fDistance;}
	int GetGDistance(){return gDistance;}
	int GetX(){return x;}
	int GetY(){return y;}

	void SetGDistance(int gDistance);
	void SetHDistanceManhatten(int xTarget, int yTarget);
	void SetHDistanceDiagonal(int xTarget, int yTarget);
	int ParentX() {return p_x;}
	int ParentY() {return p_y;}
	void SetParent(int x, int y) {p_x = x; p_y = y;}
	void SetParent(Node n) {p_x = n.GetX(); p_y = n.GetY();}

	bool operator<(const Node node) const;
	bool operator>(const Node node) const;
	bool operator==(const Node node) const;
	bool operator!=(const Node node) const;
	int fDistance;

private:

	int gDistance, hDistance;
	int x, y;
	int p_x, p_y;
	int t_x, t_y;
};