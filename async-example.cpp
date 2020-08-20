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

int addNumbers(int a, int b) {
      cout<<"addNumbers function thread id = "<<std::this_thread::get_id()<<endl;
    return a + b;
}

void packaged_task_example()
{
    std::cout << "Start of the program thread id = "<<std::this_thread::get_id()<<endl;
    std::packaged_task<int(int, int)> pt(addNumbers);
    std::cout << "Created the packaged_task\n";

    std::future<int> fut = pt.get_future();
    std::cout << "Got the future, but haven't executed the task\n";

    std::thread mythread(std::move(pt), 1, 2);
    mythread.join();
    std::cout << "Started the task in a thread\n";

    std::cout << "The result is: " << fut.get() << "\n";

    std::cout << "End of the program\n";
}



int main()
{

  //  basicSTuff();

  // lazyEarlyConcept();

  packaged_task_example();




    return 0;
}

