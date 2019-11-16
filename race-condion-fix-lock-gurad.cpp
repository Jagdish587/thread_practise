#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

/*
 * std::lock_guard is a class template, which implements the RAII for mutex.
 * It wraps the mutex inside it’s object and locks the attached mutex in its constructor.
 *  When it’s destructor is called it releases the mutex.
 *
*/

class Wallet
{
  int mMoney;
  std:: mutex mtx;
 public:
  Wallet() :mMoney(0){}
  int getMoney() { return mMoney; }
  void addMoney(int money)
  {
    lock_guard<mutex> lockgurad(mtx);

    for(int i = 0; i < money; ++i)
    {
      mMoney++;
    }

  }
};


int testMultithreadedWallet()
{
  Wallet walletObject;
  std::vector<std::thread> threads;
  for(int i = 0; i < 5; ++i){
    threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
  }
  for(int i = 0; i < threads.size() ; i++)
  {
    threads.at(i).join();
  }
  return walletObject.getMoney();
}

int main()
{
  int val = 0;

  // ideally 5000 , let's see what happens
  cout<<"money = "<<testMultithreadedWallet()<<endl ;

// let's test this over 1000 iterations , kind of regression testing

  for(int k = 0; k < 1000; k++)
  {
    if((val = testMultithreadedWallet()) != 5000)
    {
      std::cout << "Error at count = "<<k<<" Money in Wallet = "<<val << std::endl;
      break;
    }
    else {
      cout<<"sucess with iterator = "<<k<<endl;
    }
  }

  return 0;
}

