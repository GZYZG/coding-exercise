// http://118.190.20.162/view.page?gpid=T122
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

bool mycmp(pair<int, int> p1, pair<int, int> p2){
    return p1.first < p2.first;
}

int main(){
    /*
    1. 读入数据，同时记录每个元素的数量（cnter）、标签为1的元素的数量（all）
    2. 根据元素值大小对数据进行排序
    3. 初始化：thresh = 第一个元素，num = 标签为1的元素的数量，zero = 0，one = all，p某个元素及其之后的元素中标签为1的样本数，q = 某个元素之前的标签为0的样本数
    4. 从小打到遍历去重后的元素，可以通过遍历排序后的数据来实现：
        a. p -= one, q += zero
        b. num = p+q >= num? p+q: num, 若num改变则thresh = 当前元素
        c. 记录该元素的集合中标签为1和0的数量，分别赋值给one和zero
    5. thresh即为答案
    */
    int m, y, r, all = 0;
    int thresh = 0, num = 0; // num为以某个元素为thresh时预测正确的样本数
    
    cin >> m;
    map<int, int> cnter; // 记录每个元素的数量
    int p = 0, q = 0;
    vector<pair<int, int>> data(m);
    for(int i = 0; i < m; i++){
        cin >> y >> r;
        data[i] = pair<int, int>(y, r);
        all += (r? 1: 0);
        if(cnter.find(y) != cnter.end()){
            cnter[y]++;
        } else{
            cnter[y] = 1;
        }
    }

    sort(data.begin(), data.end(), mycmp);

    p = all;  // 从小到大遍历元素时，该元素及其之后的元素中标签为1的数量
    q = 0;  // 从小到大遍历元素时，该元素之前的元素（不包含该元素）中标签为0的数量
    int one = 0, zero = 0;  // 该元素的标签集合（可能有重复的元素）中标签为1和0的数量

    thresh = data[0].first;
    num = p + q;  // 分类正确的数量

    for(int i = 0; i < m;){
        p -= one;
        q += zero;
        one = 0;
        zero = 0;

        if(p+q >= num){
            thresh = data[i].first;
            num = p + q;
        }

        if(cnter[data[i].first] > 1){
            int tmp = cnter[data[i].first];
            for(int j = i; j < i+tmp; j++){
                if(data[j].second == 1){
                    one++;
                } else{
                    zero++;
                }
            }
            i += tmp;
        } else{
            one = data[i].second;
            zero = 1 - data[i].second;
            i++;
        }
        
        // cout << data[i].first << " " << q[i] << " " << p[i] << endl;
    }

    cout << thresh;
    return 0;
}