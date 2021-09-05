// http://118.190.20.162/view.page?gpid=T112
#include <iostream>

using namespace std;

int n, k, t, xl, yd, xr, yu;

int judge(int x, int y){
    if(xl <= x && x <= xr && yd <= y && y <= yu){
        return 1;
    }
    return 0;
}

int main(){
    cin >> n >> k >> t >> xl >> yd >> xr >> yu;
    int passby = 0, stay = 0;
    int x, y;
    int tmpLen = 0, passRisk = 0;

    while(n-- > 0){
        passRisk = 0;
        tmpLen = 0;
        for(int i = 0; i < t; i++){
            cin >> x >> y;
            if(judge(x, y)){
                passRisk++;
                tmpLen++;
            } else{
                if(tmpLen >= k){
                    // break; // 不能跳过，还要把剩下的数据读完
                } else{
                    tmpLen = 0;
                }
            }
        }
        passby += (passRisk > 0? 1: 0); 
        if(tmpLen >= k) {
            stay++;
        }
    }

    cout << passby << endl << stay;

    return 0;
}