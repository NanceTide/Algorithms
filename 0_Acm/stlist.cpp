#include "C:\Users\Nonce\Documents\VisualStudioCode\Lesson\Algorithms\lib.cpp"
typedef long long ll;
using namespace std;

const int N = 1e5 + 10;
ll dp[N][20];
int n, m;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> dp[i][0];

    int l2n = log2(n) + 1;
    for(int i = 1; i <= l2n; i++)
        for(int j = 1; j + (1 << i) - 1 <= n; j++)
            dp[j][i] = max(dp[j][i - 1], dp[j + (1 << (i - 1))][i - 1]);

    int l, r;
    for(int i = 1; i <= m; i++) {
        cin >> l >> r;
        int len = log2(r - l + 1);
        cout << max(dp[l][len], dp[r - (1 << len) + 1][len]) << '\n';
    }
    return 0;

}