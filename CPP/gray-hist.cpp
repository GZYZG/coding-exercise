#include <iostream>
#include <vector>

using namespace std;

// 保存输入数据的类别，包含输入的数据、如何读取输入
class InputData{
public:
    // 输入数据的字段
    int n, m, L;
    vector<vector<int>> pixels;

    InputData(){
        this->n = 0;
        this->m = 0;
    }

    // 读取输入数据相关代码
    void read(){
        // cout << "You are reading data from console ... \n";
        cin >> n;
        cin >> m;
        cin >> L;
        
        int p = 0;
        for(int i = 0; i < n; i++){
            vector<int> tmp;
            for(int j = 0; j < m; j++){
                cin >> p;
                tmp.push_back(p);
            }
            pixels.push_back(tmp);
        }
    }

};

// 保存输出数据，包含输出的数据，以及如何输出结果
class OutputData{
public: 
    // 输出数据的字段
    vector<int> result;

    // 输出数据
    void toConsole(){
        // cout << "You are writting result to console ... \n";
        for(auto num: result){
            cout << num << " ";
        }
    }
};

class Processor{
public:
    InputData *input;
    OutputData *output;

    Processor(InputData* in, OutputData* out){
        this->input = in;
        this->output = out;
    }

    // 根据输入数据处理，保存至输出 
    void process(){
        int ret[input->L] = {0};
        for(int i = 0; i < input->n; i++){
            for(int j = 0; j < input->m; j++){
                int t = input->pixels[i][j];
                ret[t]++;
            }
        }
        for(int i = 0; i < input->L; i++){
            output->result.push_back(ret[i]);
        }
        // output.toConsole();
    }
};


int main(){
    InputData in;
    OutputData out;
    
    InputData& inobj = in;
    OutputData& outobj = out;

    // 读取输入
    inobj.read();

    Processor pro(&inobj, &outobj);
    pro.process();

    outobj.toConsole();

    return 0;
}
