#include <iostream>
#include <thread>
using namespace std;

void threadfunc(const int&  val)
{
  int &y = const_cast<int &>(val);
  y++;
  cout<<"my value in thread = "<<val<<endl;
}


int main(int argc, char *argv[])
{
  int x = 10;
  std::thread mythread(threadfunc,std::ref(x));

  mythread.join();

  cout<<"value of x in main = "<<x<<endl;

  return 0;
}

