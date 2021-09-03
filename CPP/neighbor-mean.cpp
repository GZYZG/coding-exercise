#include <iostream>
using namespace std;


int main(){
    // 二维前缀和
    int n, L, r, t;
    cin >> n >> L >> r >> t;
    int pixels[n+1][n+1] = {{0}};
    int tmp = 0;
    for(int i = 0; i <= n; i++){
        pixels[0][i] = 0;
        pixels[i][0] = 0;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> tmp;
            pixels[i][j] = tmp + pixels[i][j-1] + pixels[i-1][j] - pixels[i-1][j-1];  
        }
    }

    int left = 0, right = 0, top = 0, bottom = 0;
    int sum = 0, ret = 0;

    for(int i = 1; i <= n; i++){
        top = (i-r > 0? i-r: 1) - 1; // 计算上边界后要减1，因为上边界是包含在内的
        bottom = i+r <= n? i+r: n;
        for(int j = 1; j <= n; j++){
            left = (j-r > 0? j-r: 1) - 1; // 计算左边界后要减1，因为左边界是包含在内的
            right = j+r <= n? j+r: n;
            sum = pixels[bottom][right] - pixels[bottom][left] - pixels[top][right] + pixels[top][left];
            // cout << "(" << i << ", " << j << ") = " << sum << ", " << pixels[i][j] << " ";
            if(sum <= (bottom - top) * (right - left) * t){
                ret++;
            }
        }
    }

    cout << ret;
    return 0;
}

int _main(){
    int n, L, r, t;
    cin >> n >> L >> r >> t;
    int pixels[n][n];
    int tmp = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> tmp;
            pixels[i][j] = tmp;
        }
    }

    int sum = 0, size = 0, num = 0;
    bool flag = true;
    int j;
    for(int i = 0; i <= r && i < n; i++){
        for(int k = 0; k <= r && i < n; k++){
            sum += pixels[i][k];
            size++;
        }
    }
    if(sum <= size * t){
        num++;
    }

    int left = 0, right = 0, top = 0, bottom = 0;

    for(int i = 0; i < n; i++){
        top = i-r > 0? i-r: 0;
        bottom = i+r <= n-1? i+r: n-1;
        if(flag){
            // 从左到右
            j = 1;
            for(; j < n; j++){
                left = j-r > 0? j-r: 0;
                right = j+r <= n-1? j+r: n-1;

                if(j-r > 0){
                    for(int k = top; k <= bottom; k++){
                        sum -= pixels[k][j-r-1];
                        size--;
                    }
                }
                
                if(j+r <= n-1){
                    for(int k = top; k <= bottom; k++){
                        sum += pixels[k][j+r];
                        size++;
                    }
                }
                if(sum <= size*t){
                    num++;
                }
            }
        } else{
            // 从右到左
            j = n-2;
            for(; j >= 0; j--){
                left = j-r > 0? j-r: 0;
                right = j+r <= n-1? j+r: n-1;

                if(j-r >= 0){
                    for(int k = top; k <= bottom; k++){
                        sum += pixels[k][j-r];
                        size++;
                    }
                }
                
                if(j+r < n-1){
                    for(int k = top; k <= bottom; k++){
                        sum -= pixels[k][j+r+1];
                        size--;
                    }
                }
                if(sum <= size*t){
                    num++;
                }
            }
        }
        if(i == n-1)    break;
        
        if(i-r >= 0){
            for(int k = left; k <= right; k++){
                sum -= pixels[i-r][k];
                size--;
            }  
        }
        if(i+r < n-1){
            for(int k = left; k <= right; k++){
                sum += pixels[i+r+1][k];
                size++;
            } 
        }
        if(sum <= size*t){
            num++;
        }

        flag = !flag;
    }

    cout << num;
    return 0;
}