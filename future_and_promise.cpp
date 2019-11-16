// thread_stuff.cpp : Jagdish Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <thread>
#include <string>
#include <future>
using namespace std;


void div_func(promise<int> promise_obj_div, int a, int b)
{
	promise_obj_div.set_value(b/a);
}

void product_func(promise<int> promise_obj_prod, int a, int b)
{
	promise_obj_prod.set_value(a*b);
}

int main()
{
	cout << "This is main function \n";
	int a = 2;
	int b = 4;

// declare promise obj 
	promise<int> promise_obj_prod;
	promise<int> promise_obj_div;

	future<int> future_obj_prod = promise_obj_prod.get_future();
	future<int> future_obj_div = promise_obj_div.get_future();

	thread thread_1(product_func, move(promise_obj_prod), a, b);
	thread thread_2(div_func, move(promise_obj_div), a, b);

	cout << "product value = " << future_obj_prod.get()<<endl;
	cout << "div value " << future_obj_div.get()<<endl;

	thread_1.join();
	thread_2.join();


    return 0;
}


