#include "C:\Users\Nonce\Documents\VisualStudioCode\Lesson\Algorithms\lib.cpp"
typedef long long ll;
using namespace std;

const int N = 5e5 + 10;
ll f[N], w[N];
int n, m;

void add(int i, int v) {
    for(; i <= n; i += i & -i)
        f[i] += v;
}

ll get(int r) {
    ll ans = 0;
    while(r > 0) {
        ans += f[r];
        r -= r & -r;
    }
    return ans;
}

ll get(int l, int r) {
    return get(r) - get(l - 1);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
        add(i, w[i]);
    }

    int mode, l, r;
    for(int i = 1; i <= m; i++) {
        cin >> mode >> l >> r;
        if(mode == 1)
            add(l, r);
        else
            cout << get(l, r) << '\n';
    }

    return 0;

}