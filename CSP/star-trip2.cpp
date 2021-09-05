// http://118.190.20.162/view.page?gpid=T110
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int n, m, r;

double squareDistance(int* p1, int* p2){
    double d = 0;
    for(int i = 0; i < n; i++){
        d += (p1[i] - p2[i]) * (p1[i] - p2[i]);
    }

    return d;
}

// 判断是否需要经过球面
bool judge(int c1, int c2, int c3, int r){
    double a = sqrt(c1), b = sqrt(c2), c = sqrt(c3);
    double p = (a + b + c) / 2;
    double sq = p * (p - c) * (p -b) * (p - a);
    if(sq * 4 / c3 > r*r || (c3 + (c2 > c1? c1: c2)) < (c2 > c1? c2: c1)){  // 当高大于半径时肯定不经过球面，或者当高小于等于半径时，三点形成的三角形中某个点的角度为钝角时也不会经过球面
        return false;
    } 
    return true;
}

int main(){
    std::setprecision(12);  // 设置输出的小数位数
    
    cin >> n >> m;
    cin >> r;  // 半径
    int O[n];
    int tmp = 0;
    // 输入球心坐标
    for(int i = 0; i < n; i++){
        cin >> tmp;
        O[i] =  tmp;
    }

    int points[m][n];
    // 读入点的坐标，所有的点均不在黑洞内部，可以位于边界上
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> tmp;
            points[i][j] = tmp;
        }
    }

    // 计算每个点到其他店的距离和
    double dist[m][m];
    double C1 = 0, C2 = 0, C3 = 0, L1 = 0, L2 = 0;
    double Cs[m] = {-1}, Ls[m] = {-1}, C3s[m][m];
    double theta = 0;
    for(int i = 0; i < m; i++){
        Cs[i] = -1;
        Ls[i] = -1;
        
        for(int j = 0; j < m; j++){
            C3s[i][j] = -1;
        }
    }
    int r2 = r*r;
    for(int i = 0; i < m; i++){
        dist[i][i] = 0;
        for(int j = i+1; j < m; j++){
            C1 = Cs[i] < 0? squareDistance(O, points[i]): Cs[i];  // 点到球心的距离平方
            C2 = Cs[j] < 0? squareDistance(O, points[j]): Cs[j];  
            Cs[i] = C1;
            Cs[j] = C2;
            L1 = Ls[i] < 0? sqrt(C1 - r2): Ls[i];
            L2 = Ls[j] < 0? sqrt(C2 - r2): Ls[j];
            C3 = C3s[i][j] < 0? squareDistance(points[i], points[j]): C3s[i][j];  // 两点间距离平方
            C3s[i][j] = C3;
            C3s[j][i] = C3;

            if(!judge(C1, C2, C3, r)){
                dist[i][j] = sqrt(C3);
                dist[j][i] = sqrt(C3);
                continue;
            }

            double alpha = acos((C1+C2-C3) / (2*sqrt(C1*C2) ) ), beta1 = acos(r / sqrt(C1)), beta2 = acos(r / sqrt(C2));
            //cout << (C1+C2-C3) / (2*sqrt(C1*C2)) << " " << r / sqrt(C1) << " " << r /  sqrt(C2) << endl;
            theta = alpha - beta1 - beta2; // acos((C1+C2-C3) / 2*sqrt(C1*C2)) - (acos(r / sqrt(C1)) + acos(r / sqrt(r / sqrt(C2))));  // 圆弧对应的夹角
            dist[j][i] = (L1 + L2 + r * theta) ; 
            dist[i][j] = (L1 + L2 + r * theta) ; 
        }
    }

    double ret = 0;
    for(int i = 0; i < m; i++){
        ret = 0;
        for(int j = 0; j < m; j++){
            ret += dist[i][j];
        }
        // cout << fixed << setprecision(14) <<  ret << endl;
        printf("%.12f\n", ret);
    }

    return 0;
}
