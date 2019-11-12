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
  thread t2(mythread_func,20,30,"Jagdish Tirumala");

  cout<<"thread id of main = "<<std::this_thread::get_id()<<endl;
  cout<<"thread id of  mythread_func = "<<t1.get_id()<<endl;

  t1.detach(); // detach t1 thread for fun

  if(t1.joinable()) {
    cout<<"t1 thread is  joinable "<<endl;
    t1.join();
  } else {
    cout<<"t1 thread is not joinable "<<endl;
  }


  if(t2.joinable()) {
    cout<<"t2 thread is  joinable "<<endl;
    t2.join();
  } else {
    cout<<"t2 thread is not  joinable "<<endl;
  }

  return 0;
}

