#include <stdio.h>
#include <queue>
#include <vector>
#include <time.h>
#include <stdlib.h>
using std::queue;
using std::pair;
using std::vector;

#define BLOCKED 10000

struct node {
	int x,y,value=-1;
};

const int startX=4, startY=5, goalX=1, goalY=2;
const int row=5, col=7;
struct node arr[row][col];

pair<int, int> Point;

static vector<pair<int, int> > path;

void disp() {
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			printf("%d\t",arr[i][j].value);
		}
		printf("\n");
	}
	printf("\n");
}

void blocked(struct node* tmp, int x, int y, bool blocked=false) {
	tmp->x = x;
	tmp->y = y;
	if (blocked)
	tmp->value = BLOCKED;
}

bool check(int x, int y) {
	return ((x < 0 || x >= row || y < 0 || y >= col) || (arr[x][y].value != -1));
}

bool filled(int x, int y) {
	return ((x >= 0 && x < row && y >= 0 && y < col) && (arr[x][y].value != -1) && (arr[x][y].value != BLOCKED));
}

void fillPath(int x, int y, int num) {
	queue<pair<int, int> > q;
	q.push({x,y});
	arr[x][y].value = 0;
	while(!q.empty()) {
		pair<int, int> temp = q.front();
		int f = temp.first;
		int s = temp.second;
//		std::cout << f << " " << s << "\n";
		if (arr[startX][startY].value != -1) {
			return;
		}
		else {
			/* arr[temp.first][temp.second].value = num; */
			if (arr[f][s].value == -1 && filled(f-1,s)) {
				arr[f][s].value = arr[f-1][s].value + 1;
			}
			else if (arr[f][s].value == -1 && filled(f+1,s)) {
				arr[f][s].value = arr[f+1][s].value + 1;
			}
			else if (arr[f][s].value == -1 && filled(f,s+1)) {
				arr[f][s].value = arr[f][s+1].value + 1;
			}
			else if (arr[f][s].value == -1 && filled(f,s-1)) {
				arr[f][s].value = arr[f][s-1].value + 1;
			}
		}
		//1st
		if (!check(f+1,s)) 
			q.push({f+1, s});
		//2nd		
		if (!check(f-1,s)) 
			q.push({f-1, s});
		//3rd
		if (!check(f,s+1)) 
			q.push({f, s+1});
	
		//4th
		if (!check(f,s-1)) 
			q.push({f, s-1});
		q.pop();
	}
}

void pathFind(int startX, int startY) {
	if (startX == goalX && startY == goalY || !filled(startX, startY))
		return;
	int l = startX, m = startY;
	if (filled(l+1,m) && (arr[l+1][m].value == arr[l][m].value - 1)) {
		path.push_back({l+1,m});
		pathFind(l+1,m);
	}
	else if (filled(l-1,m) && (arr[l-1][m].value == arr[l][m].value - 1)) {
		path.push_back({l-1,m});
		pathFind(l-1,m);
	}
	else if (filled(l,m+1) && (arr[l][m+1].value == arr[l][m].value - 1)) {
		path.push_back({l,m+1});
		pathFind(l,m+1);
	}
	else if (filled(l,m-1) && (arr[l][m-1].value == arr[l][m].value - 1)) {
		path.push_back({l,m-1});
		pathFind(l,m-1);
	}	
}

void createObstacle(int n) {
	if (n > row*col) {
		printf("number of obstacles too large for the grid\n");
		return;
	}
	srand(time(0));
	int i = 0;
	while (i != n){
		int x = rand()%row;
		int y = rand()%col;
		if (x != startX && y != startY) {
		blocked(&arr[x][y],x,y,true);
		i++;
		}
	}
}

int main() 
{
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			blocked(&arr[i][j], i, j);

	
	createObstacle(10);
	fillPath(goalX,goalY,0);
	disp();
	pathFind(startX, startY);
	printf("(%d,%d)", startX, startY);
	for (int i = 0; i < path.size(); ++i) {
		printf("->(%d,%d)", path[i].first, path[i].second);
	}
	printf("\n");
	return 0;
}
