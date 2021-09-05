# CCF CSP考试注意
1. 边读取输入边处理时，小心用 `break` 语句，以防输入数据没有读完
2. 注意数据类型，数值范围
3. CPP设置小数位数：包含头文件`#include <iomanip>`, `std::setprecision(n)`用来设置有效位数，`cout << fixed << setprecision(n) << ...` 用来设置小数位数。
    关闭`fixed`：`cout.unsetf(ios::fixed)`
4. 