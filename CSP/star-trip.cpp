// http://118.190.20.162/view.page?gpid=T119
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef unsigned long long int LL;
#define MOD LL(1e9+7)  // 1e+7默认是double类型，注意！！！

class Point{
public:
    LL x, y, z;
    Point(){
        x = 0;
        y = 0;
        z = 0;
    }
    Point(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void add(int a, int b, int c){
        this->x = (this->x + a) % MOD;
        this->y = (this->y + b) % MOD;
        this->z = (this->z + c) % MOD;
    }

    void boost(int k){
        this->x = (this->x * k) % MOD;
        this->y = (this->y * k) % MOD;
        this->z = (this->z * k) % MOD;
    }

    void shift(){
        int tmp = this->x;
        this->x = this->y;
        this->y = this->z;
        this->z = tmp;
    }
};

inline LL read(){
    int res, ch, f;
    res = 0, f = 1;
    ch = getchar();
    while(ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if(ch == '-'){
        f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        res *= 10;
        res += (ch - '0');
        ch = getchar();
    }

    return f*res;
}

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);
    LL n, m;
    LL type, L, R, a, b, c, k;
    LL dist = 0, xsum, ysum, zsum;
    LL i = 0;
    map<LL, Point> engines;
    cin >> n >> m;
    for(; m > 0; m--){
        cin >> type >> L >> R;
        // type = read(), L = read(), R = read();
        if(type == 1){
                // cin >> a >> b >> c;
                a = read(), b = read(), c = read();
                for(i = L; i <= R; i++){
                    if(engines.find(i) != engines.end()){
                        engines[i].add(a, b, c);
                    } else{
                        engines[i] = Point(a, b, c);
                    }
                }
        } else if(type == 2){
            cin >> k;
            // k = read();
            for(i = L; i <= R; i++){
                if(engines.find(i) != engines.end()){
                    engines[i].boost(k);
                } else{
                    engines[i] = Point(0, 0, 0);
                }
            }
        } else if(type == 3){
            for(i = L; i <= R; i++){
                if(engines.find(i) != engines.end()){
                    engines[i].shift();
                } else{
                    engines[i] = Point(0, 0, 0);
                }
            }
        } else{
            xsum = 0;
            ysum = 0;
            zsum = 0;
            for(i = L; i <= R; i++){
                if(engines.find(i) != engines.end()){
                    xsum = (xsum + engines[i].x) ;//% MOD;
                    ysum = (ysum + engines[i].y) ;//% MOD;
                    zsum = (zsum + engines[i].z) ;//% MOD;
                }
            }
            xsum %= MOD, ysum %= MOD, zsum %= MOD;
            // cout << xsum * xsum << " " << ysum * ysum << " " << zsum * zsum << endl;
            dist = (xsum * xsum + ysum * ysum + zsum * zsum) % MOD;
            cout << dist << endl;
        }

    }

    return 0;
}

