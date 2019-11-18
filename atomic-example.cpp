#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <mutex>

using namespace std;

class Wallet
{
   std::atomic<int> atomicvalue ;
 // int atomicvalue ;
 public:
  Wallet() :atomicvalue(0){}
  int getMoney() { return atomicvalue; }

  void addMoney(int money)
  {
    for(int i = 0; i < money; ++i)
    {
        atomicvalue++;
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


