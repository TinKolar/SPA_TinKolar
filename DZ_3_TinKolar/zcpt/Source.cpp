#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <thread>
#include <chrono>

const int ROWS = 20;
const int COLS = 40;
const int INF = 1e9;
using namespace std;
using pii = pair<int, int>;

const vector<pii> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void printGrid(const vector<vector<char>>& grid, const pii& current,pii start,pii end) {
    system("cls"); 
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (start == make_pair(i, j)) {
                cout << "S";
            }
            else if (end == make_pair(i, j)) {
                cout << "F";
            }
            else if (make_pair(i, j) == current)
                cout << "x"; 
            else
                cout << grid[i][j];
        }
        cout << endl;
    }
}


bool isValid(int x, int y, const vector<vector<char>>& grid) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != '#';
}

vector<pii> dijkstra(const pii& start, const pii& end, const vector<vector<char>>& grid) {
    vector<vector<int>> dist(ROWS, vector<int>(COLS, INF));
    vector<vector<pii>> prev(ROWS, vector<pii>(COLS, { -1, -1 }));
    priority_queue<pair<int, pii>, vector<pair<int, pii>>, greater<pair<int, pii>>> pq;

    dist[start.first][start.second] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        pair<int, pii> top = pq.top();
        int d = top.first;
        pii u = top.second; 
        pq.pop();

        if (u == end) break;

        for (const auto& dir : directions) {
            int nx = u.first + dir.first;
            int ny = u.second + dir.second;
            if (isValid(nx, ny, grid) && dist[nx][ny] > d + 1) {
                dist[nx][ny] = d + 1;
                prev[nx][ny] = u;
                pq.push({ dist[nx][ny], {nx, ny} });
            }
        }
    }

    vector<pii> path;
    for (pii at = end; at != make_pair(-1, -1); at = prev[at.first][at.second])
        path.push_back(at);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    vector<vector<char>> grid(ROWS, vector<char>(COLS, '.'));


    for (int i = 5; i <= 15; ++i) {
        grid[i][20] = '#';
        grid[10][i+5] = '#';
    }

    int startX, startY, endX, endY;
    cout << "Enter start coordinates (row and column): ";
    cin >> startX >> startY;  //try 9,12 & 19,39
    cout << "Enter end coordinates (row and column): ";
    cin >> endX >> endY;
    startX--; startY--; endX--; endY--;

    pii start = { startX, startY };
    pii end = { endX, endY };

    vector<pii> path = dijkstra(start, end, grid);

    for (const auto& pos : path) {
        printGrid(grid, pos,start,end);
        this_thread::sleep_for(chrono::milliseconds(230));
    }

    return 0;
}