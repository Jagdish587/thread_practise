#include <iostream>
#include <future>
#include <string>

using namespace std;


void samplefunc()
{
    cout<<"samplefunc thread id = "<<std::this_thread::get_id()<<endl;
}


std::string helloFunction(const std::string& s){

   cout<<"aysnc function thread id = "<<std::this_thread::get_id()<<endl;
    samplefunc(); // executes in thread context
    return "Hello C++11 from " + s + ".";
}

void normalFunc()
{
    cout<<"normalFunc thread id = "<<std::this_thread::get_id()<<endl;
    samplefunc(); // executes in main thread context
}

void basicSTuff()
{
    cout<<"main thread id = "<<std::this_thread::get_id()<<endl;

    normalFunc();

    // std:.async feels like an asynchronous function call. Under the hood std::async is a task.
    //  std::async is a promise , it returns a std::future<T>
    auto futureFunction= std::async(std::launch::async, helloFunction,"function");

    // cout<<"from async programming = "<<futureFunction.get()<<endl;
}


void returnTime()
{
    auto timenow =
      chrono::system_clock::to_time_t(chrono::system_clock::now());

    cout << ctime(&timenow) << endl;
}
void lazyEarlyConcept()
{
    std::cout << std::endl;

    auto begin= std::chrono::system_clock::now();

    auto asyncLazy=std::async(std::launch::deferred,[]{ return  std::chrono::system_clock::now();});

    auto asyncEager=std::async( std::launch::async,[]{ return  std::chrono::system_clock::now();});

    std::this_thread::sleep_for(std::chrono::seconds(5));

    auto lazyStart= asyncLazy.get() - begin;
    auto eagerStart= asyncEager.get() - begin;

    auto lazyDuration= std::chrono::duration<double>(lazyStart).count();
    auto eagerDuration=  std::chrono::duration<double>(eagerStart).count();

    std::cout << "asyncLazy evaluated after : " << lazyDuration << " seconds." << std::endl;
    std::cout << "asyncEager evaluated after: " << eagerDuration << " seconds." << std::endl;

    std::cout << std::endl;
}


int mysleep()
{

        cout<<"aysnc function thread id = "<<std::this_thread::get_id()<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return 10;

}


void packaged_task_example()
{
    cout<<"main thread id = "<<std::this_thread::get_id()<<endl;



    std::packaged_task<int()> task(mysleep);

    auto f = task.get_future();

    task(); // invoke the function

    // You have to wait until task returns. Since task calls sleep
    // you will have to wait at least 1 second.
    std::cout << "You can see this after 1 second\n";

    // However, f.get() will be available, since task has already finished.
    std::cout << f.get() << std::endl;
}



int main()
{

  //  basicSTuff();

  // lazyEarlyConcept();

  packaged_task_example();




    return 0;
}

