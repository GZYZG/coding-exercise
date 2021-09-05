// http://118.190.20.162/view.page?gpid=T123
#include <iostream>

using namespace std;

int main(){
    int n = 0;
    cin >> n;

    int wi = 0, score = 0;
    int index = 0;
    for(; n > 0; n--){
        cin >> wi >> score;
        index += wi * score;
    }

    index = index > 0? index: 0;
    cout << index;

    return 0;
}