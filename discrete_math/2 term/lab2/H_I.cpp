#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* ML2. Если сможете исправить - удачи */
/* Не советую смотреть на этот код, ибо это то ещё говно */
/* Вместо того, чтобы пытаться сдать эту задачу, лучше выпей винишка */

/*
......................／＞　フ
.................... | _　 _l
..................／` ミ＿xノ
................/　　　　 |
............. / ヽ　　 ﾉ
.............│　　 |　|　|
..........／￣|　　 |　|　|
.......... | (￣ヽ＿_ヽ_)__)
...........＼二つ
*/



void isConnected(int n, vector<bool> &connected, vector<vector<int>> &moves, vector<bool> &visited) {
    if (visited[n]) {
        return;
    }
    visited[n] = connected[n] = true;
    for (int i = 0; i < 26; i++) {
        isConnected(moves[n][i], connected, moves, visited);
    }
}

void isGood(int n, vector<vector<vector<int>>> &reverse_moves, vector<bool> &terminal, vector<bool> &good,
            vector<bool> &visited, vector<bool> &connected) {
    if (visited[n]) {
        return;
    }
    visited[n] = true;
    if (!connected[n]) {
        good[n] = false;
        return;
    }
    good[n] = true;
    for (int i = 0; i < 26; i++) {
        for (int cur_n : reverse_moves[n][i]) {
            isGood(cur_n, reverse_moves, terminal, good, visited, connected);
        }
    }
}

int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    freopen("fastminimization.in", "r", stdin);
    freopen("fastminimization.out", "w", stdout);

    char sym;
    int t;
    int a, b;
    uint32_t n, m, k;
    cin >> n >> m >> k;

    int term = 0;
    int numbers_of_moves = 0;
    int component_number = 0;

    vector<bool> good(n + 1);
    vector<bool> visited(n + 1);
    vector<bool> terminal(n + 1);
    vector<bool> connected(n + 1);

    queue<pair<int, int>> cur_map;
    vector<vector<bool>> marked(n + 1, vector<bool>(n + 1, false));

    vector<int> component(n + 1, UINT32_MAX);
    vector<vector<int>> moves(n + 1, vector<int>(26));
    vector<vector<vector<int>>> reverse_moves(n + 1, vector<vector<int>>(26));

    for (int i = 0; i < k; i++) {
        cin >> t;
        terminal[t] = true;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> sym;
        moves[a][sym - 'a'] = b;
        reverse_moves[b][sym - 'a'].push_back(a);
    }

    isConnected(1, connected, moves, visited);

    visited = vector<bool>(n + 1);

    for (int i = 0; i < n + 1; i++) {
        if (terminal[i]) {
            isGood(i, reverse_moves, terminal, good, visited, connected);
        }
    }

    if (connected[0]) {
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < 26; j++) {
                if (moves[i][j] == 0 && connected[i])
                    reverse_moves[0][j].push_back(i);
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (!marked[i][j] && (terminal[i] != terminal[j])) {
                marked[i][j] = (marked[j][i] = true);
                cur_map.push(make_pair(i, j));
            }
        }
    }

    while (!cur_map.empty()) {
        pair<int, int> cur_pair = cur_map.front();
        cur_map.pop();
        for (int i = 0; i < 26; i++) {
            for (int cur_s : reverse_moves[cur_pair.first][i]) {
                for (int cur_t : reverse_moves[cur_pair.second][i]) {
                    if (!marked[cur_s][cur_t]) {
                        if (marked[cur_t][cur_s]) {
                            marked[cur_s][cur_t] = true;
                        } else {
                            marked[cur_s][cur_t] = false;
                        }
                        cur_map.push(make_pair(cur_s, cur_t));
                    }
                }
            }
        }
    }

    for (int i = 0; i < n + 1; ++i) {
        if (!marked[0][i]) {
            component[i] = 0;
        }
    }

    for (int i = 1; i < n + 1; i++) {
        if (!connected[i]) {
            continue;
        }
        if (component[i] == UINT32_MAX) {
            component_number += 1;
            component[i] = component_number;
            for (int j = i + 1; j < n + 1; j++) {
                if (!marked[i][j]) {
                    component[j] = component_number;
                }
            }
        }
    }

    vector<vector<int>> new_moves(component_number + 1, vector<int>(26));

    for (int i = 1; i < n + 1; i++) {
        for (int j = 0; j < 26; j++) {
            if (good[i] && moves[i][j] != 0 && component[i] >= 1 && component[i] <= component_number) {
                new_moves[component[i]][j] = component[moves[i][j]];
            }
        }
    }

    for (int i = 1; i < component_number + 1; i++) {
        for (int j = 0; j < 26; j++) {
            if (new_moves[i][j] != 0) {
                numbers_of_moves += 1;
            }
        }
    }

    vector<bool> new_terminal(component_number + 1);

    for (int i = 1; i < n + 1; i++) {
        if (terminal[i] && good[i]) {
            new_terminal[component[i]] = true;
        }
    }

    for (int i = 1; i < component_number + 1; i++) {
        if (new_terminal[i]) {
            term += 1;
        }
    }

    cout << component_number << " " << numbers_of_moves << " " << term << endl;

    for (int cur_number = 1; cur_number < component_number + 1; cur_number++) {
        if (new_terminal[cur_number]) {
            cout << cur_number << " ";
        }
    }

    cout << endl;

    for (int i = 1; i < component_number + 1; i++) {
        for (int j = 0; j < 26; j++) {
            if (new_moves[i][j]) {
                cout << i << " " << new_moves[i][j] << " " << (char) (j + 'a') << endl;
            }
        }
    }

    return 0;
}
