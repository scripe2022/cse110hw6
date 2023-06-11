// compile: make data
// run: ./data < data.in
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef LOCAL
#include <debug/codeforces.h>
#define debug(x...) _debug_print(#x, x);
#else
#define debug(x...) {};
#endif
template<typename...Args> void print_(Args...args){((cout<<args<<" "),...)<<endl;}
#define rep(i,a,b) for(int i=(a);i<(int)(b);++i)
#define sz(v) ((int)(v).size())
#define print(...) print_(__VA_ARGS__);
#define cmin(x,...) x=min({(x), __VA_ARGS__})
#define cmax(x,...) x=max({(x), __VA_ARGS__})
#define INTMAX (int)(9223372036854775807)
#define INF (int)(1152921504606846976)
#define double long double
#define int long long
#define MAXN 200010

int n;
vector<int> a;

int dp1() {
    vector<int> dp(n+1);
    dp[0] = 0;
    rep(i, 1, n+1) {
        dp[i] = dp[i-1] + 2;
        rep(j, 0, i) {
            if (i == j + a[j]) cmin(dp[i], dp[j] + 1);
        }
    }
    return dp[n];
}

int dp2() {
    vector<int> dp(n+1);
    dp[n] = 0;
    for (int i = n-1; i >= 0; --i) {
        dp[i] = dp[i+1] + 2;
        if (i+a[i] <= n) cmin(dp[i], dp[i+a[i]] + 1);
    }
    return dp[0];
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> n; a.resize(n);
    rep(i, 0, n) cin >> a[i];
    cout << dp2() << endl;

    return 0;
}