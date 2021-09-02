#include <iostream>


// 保存输入数据的类别，包含输入的数据、如何读取输入
class InputData{
public:
    // 输入数据的字段
    int m, n;

    InputData(){
        this->m = 0;
        this->n = 0;
    }

    // 读取输入数据相关代码
    void read(){
        std::cout << "You are reading data from console ... \n";
    }

};

// 保存输出数据，包含输出的数据，以及如何输出结果
class OutputData{
public: 
    // 输出数据的字段
    
    // 输出数据
    void toConsole(){
        std::cout << "You are writting result to console ... \n";
    }
};

class Processor{
public:
    InputData input;
    OutputData output;

    Processor(InputData &in, OutputData &out){
        this->input = in;
        this->output = out;
    }

    void process(){

    }
};

void process(InputData& input, OutputData& output){

}

int main(){
    InputData in;
    OutputData out;
    
    InputData& inobj = in;
    OutputData& outobj = out;

    // 读取输入
    inobj.read();

    Processor pro(inobj, outobj);
    pro.process();

    outobj.toConsole();

    return 0;
}