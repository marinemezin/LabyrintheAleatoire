#include<iostream>
#include<cstdlib>
#include<stack>
#include<ctime>

#define NORTH   0
#define SOUTH   1
#define EAST    2
#define WEST    3
#define SIZEX   20
#define SIZEY   20

using namespace std;

int nGood = 0;
int locX = 1;
int locY = 1;

void printGrid(char grid[SIZEY][SIZEX]) {
	system("clear");
	for (int i = 0; i < SIZEY; i++) {
		for (int j = 0; j < SIZEX; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
}

int moveEW(int direction, int x) {
	if (direction == EAST)
		return x + 1;
	else if (direction == WEST)
		return x - 1;
	else
		return x;
}

int moveNS(int direction, int y) {
	if (direction == NORTH)
		return y - 1;
	else if (direction == SOUTH)
		return y + 1;
	else
		return y;
}

bool isGood(int x, int y, int direction, char grid[SIZEY][SIZEX]) {
	x = moveEW(direction, x);
	y = moveNS(direction, y);

	if (grid[y][x] == '.' || x >= (SIZEX - 1) || x <= 0 || y <= 0 || y >= (SIZEY - 1)) {
		return false;
	}

	// check cardinal directions
	if (direction == NORTH) {
		if (grid[y][x - 1] != '.' &&  grid[y - 1][x] != '.' && grid[y][x + 1] != '.' &&  grid[y - 1][x - 1] != '.' && grid[y - 1][x + 1] != '.') {
			return true;
		}
	}
	if (direction == SOUTH) {
		if (grid[y][x - 1] != '.' &&  grid[y + 1][x] != '.' && grid[y][x + 1] != '.' && grid[y + 1][x - 1] != '.' && grid[y + 1][x + 1] != '.') {
			return true;
		}
	}
	if (direction == EAST) {
		if (grid[y][x + 1] != '.' &&  grid[y - 1][x] != '.' && grid[y + 1][x] != '.' && grid[y - 1][x + 1] != '.' && grid[y + 1][x + 1] != '.') {
			return true;
		}
	}
	if (direction == WEST) {
		if (grid[y][x - 1] != '.' &&  grid[y - 1][x] != '.' && grid[y + 1][x] != '.' && grid[y - 1][x - 1] != '.' && grid[y + 1][x - 1] != '.') {
			return true;
		}
	}
	return false;
}



int main()
{
		char grid[SIZEY][SIZEX];

		// init grid
		for (int i = 0; i < SIZEY; i++) {
			for (int j = 0; j < SIZEX; j++) {
				grid[i][j] = '#';
			}
		}

		//init rand
		srand(time(0));

		//init stacks for xy coords
		stack<int> xValues;
		stack<int> yValues;

		nGood = 0;
		int direction = 0;

		do {
			//find n good moves
			for (int i = 0; i < 4; i++) {
				if (isGood(locX, locY, i, grid))
					nGood++;
			}

			// if only 1 good move, move there
			if (nGood == 1) {
				if (isGood(locX, locY, NORTH, grid))
					locY = moveNS(NORTH, locY);
				else if (isGood(locX, locY, SOUTH, grid))
					locY = moveNS(SOUTH, locY);
				else if (isGood(locX, locY, EAST, grid))
					locX = moveEW(EAST, locX);
				else if (isGood(locX, locY, WEST, grid))
					locX = moveEW(WEST, locX);
			}

			// if no good moves, move back in stack
			else if (nGood == 0) {
				locX = xValues.top();
				locY = yValues.top();
				xValues.pop();
				yValues.pop();
			}

			//if more than 1 good move, push stack
			else if (nGood > 1) {
				xValues.push(locX);
				yValues.push(locY);

				//direction to move randomly chosen
				do {
					direction = rand() % 4;
				} while (!isGood(locX, locY, direction, grid));

				locX = moveEW(direction, locX);
				locY = moveNS(direction, locY);
			}

			// set grid
			grid[locY][locX] = '.';
			//output grid to show creation
			printGrid(grid);
			//reset nGood value
			nGood = 0;

		} while (!xValues.empty());

		//final maze output
		printGrid(grid);
		return 0;	
}