#include <vector>
#include <iostream>
using namespace std;


int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);

    char sym;
    int m, k;
    int t, a, b;
    int state = 0;
    unsigned int n;
    vector<char> cur_string;

    scanf("%c", &sym);
    while (sym != '\n') {
        cur_string.push_back(sym);
        scanf("%c", &sym);
    }

    cin >> n >> m >> k;

    vector<bool> terminal_state(n + 1, false);
    for (int i = 0; i < k; i++) {
        cin >> t;
        terminal_state[--t] = true;
    }

    vector<vector<int>> transitions(n);
    for (int i = 0; i < n; i++) {
        transitions[i].assign('z' - 'a' + 1, n);
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> sym;
        a -= 1;
        b -= 1;
        transitions[a][sym - 'a'] = b;
    }

    for (char cur_symbol : cur_string) {
        state = transitions[state][cur_symbol - 'a'];
        if (state == n) {
            terminal_state[state] = false;
            break;
        }
    }

    if (terminal_state[state]) {
        cout << "Accepts" << endl;
    }
    else {
        cout << "Rejects" << endl;
    }

    return 0;
}