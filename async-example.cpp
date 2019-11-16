#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

std::string MyAsyncFunc(std::string myvalue)
{
  cout<<"thread id  = "<<std::this_thread::get_id()<<endl;
  cout<<"string value = "<<myvalue;

  return myvalue + "Hello ";
}

int main()
{
  cout<<"main id  = "<<std::this_thread::get_id()<<endl;
  std::future<std::string> resultFromThread = std::async(launch::async,MyAsyncFunc,"Value");


  cout<<"future value from thread = "<<resultFromThread.get()<<endl;

}

