#include <iostream>
#include <thread>
using namespace std;

class DummyClass {
public:
    DummyClass()
    {}
    DummyClass(const DummyClass & obj)
    {}
    void sampleMemberFunction(int x)
    {
      std::cout<<"Inside sampleMemberFunction "<<x<<"thread id = "<<std::this_thread::get_id()<<std::endl;
    }
};

int main() {

    DummyClass dummyObj;
    int x = 10;
    std::thread threadObj(&DummyClass::sampleMemberFunction,&dummyObj, x);
    threadObj.join();

    std::cout<<"main thread id = "<<std::this_thread::get_id();
    return 0;
}

