#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using pi = pair<int, int>;
#define f first
#define s second
#define mp make_pair

const int MOD = (int)1e9 + 7;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a=173;
    int b=1;
    int d=216;
    while (true )
    {
       if(a%d ==1) {cout<<b;break;}
       a+=173;
       b++;
       
    }
    cout<<endl;
    ll ans= (125*125) % 247;
    cout<<ans;
    
    return 0;
}