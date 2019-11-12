#include <iostream>
#include <thread>
using namespace std;


void mythread_func(int vala, int valb,string mystr)
{

  cout<<"inside thread func vala = "<<vala<<" valb = "<<valb<<" mystr = "<<mystr<<endl;

  cout<<"thread id = "<<std::this_thread::get_id()<<endl;
}

int main()
{

  thread t1(mythread_func,20,30,"Jagdish Tirumala");

  cout<<"thread id of main = "<<std::this_thread::get_id()<<endl;
  cout<<"thread id of  mythread_func = "<<t1.get_id()<<endl;
  t1.join();

  return 0;
}

