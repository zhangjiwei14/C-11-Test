/* 
 * author:  zhangjiwei
 * time:    2019/12/19
 */

// 用c++ 类中实现回调的简单实例
// 回调函数f_e()参数为可调用对象std::function<void(void)> f，在类中使用bind函数生成可调用对象传入。

#include <functional>
#include <iostream>
#include <memory>

class A
{
private:
    /* data */
    int data;

public:
    A(/* args */);
    ~A();
    void f();
    void f2(){
        std::cout << "f2\n";
        data = 4;
        std::cout << data << "\n";
    }
};

A::A(/* args */)
{
    data = 2;
}

A::~A()
{
}

void f_e(std::function<void(void)> f){
    std::cout << "callback.\n";
    f();
    std::cout << "callback.end\n";
}

void A::f(){
    std::function<void(void)> ff = std::bind(&A::f2, this);
    // auto a = [&]() { std::cout << data << std::endl; };
    f_e(ff);
}

int main(){

    A a;
    a.f();
    return 0;
}