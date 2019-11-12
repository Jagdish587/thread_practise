#include <iostream>
#include <thread>
using namespace std;
#include <chrono>

void mythread_func(int vala, int valb,string mystr,int *ptr)
{
  std::chrono::milliseconds dura( 1000 );
  std::this_thread::sleep_for( dura );
  cout<<"inside thread func vala = "<<vala<<" valb = "<<valb<<" mystr = "<<mystr<<endl;

  cout<<"thread id = "<<std::this_thread::get_id()<<endl;

  cout<<"ptr value = "<<*ptr<<endl;

  *ptr = 48;

  cout<<"ptr value = "<<*ptr<<endl;
}


void startnewthread()
{
  int myvalue = 24;

  thread t1(mythread_func,20,30,"Jagdish Tirumala",&myvalue);

  t1.detach();
}
int main()
{

  startnewthread();

  cout<<"main executed ";

  std::chrono::milliseconds dura( 3000 );
  std::this_thread::sleep_for( dura );
  cout<<"main exited ";
  return 0;
}

