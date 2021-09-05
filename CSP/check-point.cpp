// http://118.190.20.162/view.page?gpid=T113
#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, X, Y, i = 0;
    int x, y, dist = 0;
    cin >> n >> X >> Y;
    vector<pair<int, int>> ret;
    for(i = 0; i < n; i++){
        cin >> x >> y;
        dist = (X-x)*(X-x) + (Y-y)*(Y-y);
     
        int j = ret.size()-1;
        for(; j >= 0; j--){  // 找到当前检测点应该插入的位置：j+1
            if(ret[j].second <= dist){
                break;
            }
        }
        ret.insert(ret.begin()+j+1, pair<int, int>(i+1, dist));
        if(ret.size() > 3){
            ret.pop_back();
        }
        
    }
    for(auto e: ret){
        cout << e.first << endl;
    }
    return 0;
}