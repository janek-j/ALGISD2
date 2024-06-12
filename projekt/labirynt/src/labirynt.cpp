#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <random>

class Maze {
protected:
    int m; // rows
    int n; // cols
    std::vector<std::vector<int>> maze; // rectangle mesh
    std::vector<std::vector<bool>> visited; // visited cells
    std::vector<std::vector<int>> solution; // solution path

    const int WALL = 1;
    const int PATH = 0;
    const int START = 2;
    const int END = 3;

public:
    Maze(int _m, int _n) : m(_m), n(_n) {
        maze.resize(m, std::vector<int>(n, WALL)); // initialize maze with walls
        visited.resize(m, std::vector<bool>(n, false)); // initialize visited with false
        generateMaze(0, 0); // start generating maze from the top-left corner
        maze[0][0] = START; // start point
        maze[m-1][n-1] = END; // end point
    }

    void generateMaze(int x, int y) {
        std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        // Random engine
        std::random_device rd; //random ints generator
        std::mt19937 g(rd());
        
        // Shuffle directions
        std::shuffle(directions.begin(), directions.end(), g);

        visited[x][y] = true;
        maze[x][y] = PATH;
		
        for (auto dir : directions) {
            int nx = x + dir.first * 2;
            int ny = y + dir.second * 2; //przesuwam sie o dwie jednostki, bo prowadzi to do tworzenia szerszych sciezek w labiryncie
            if (nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx][ny]) {
                maze[x + dir.first][y + dir.second] = PATH;
                generateMaze(nx, ny);
            }
        }
    }

    bool solveMaze(int x, int y) {
        if (x < 0 || y < 0 || x >= m || y >= n || maze[x][y] == WALL || visited[x][y]) return false;
        solution.push_back({x, y});
        visited[x][y] = true;
        if (x == m-1 && y == n-1) return true;
        if (solveMaze(x+1, y) || solveMaze(x, y+1) || solveMaze(x-1, y) || solveMaze(x, y-1)) return true;
        solution.pop_back();
        return false;
    }

    void printMaze() {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << std::setw(2) << maze[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void printSolution() {
        if (solution.empty()) {
            std::cout << "No solution found." << std::endl;
        } else {
            std::cout << "Solution Path:" << std::endl;
            for (auto cell : solution) {
                std::cout << "(" << cell[0] << ", " << cell[1] << ") ";
            }
            std::cout << std::endl;
        }
    }

    void resetVisited() {
        visited = std::vector<std::vector<bool>>(m, std::vector<bool>(n, false));
    }
};

int main() {
    srand(time(0));

    int rows, cols;
    std::cout << "Enter the number of rows for the maze: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns for the maze: ";
    std::cin >> cols;

    if (rows < 5 || cols < 5) {
        std::cout << "Minimum size for the maze is 5x5." << std::endl;
        return 1;
    }

    Maze maze(rows, cols);
    std::cout << "Generated Maze:" << std::endl;
    maze.printMaze();

    maze.resetVisited();
    maze.solveMaze(0, 0);
    maze.printSolution();

    return 0;
}

