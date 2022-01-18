/********************************************************************/
/*                                                                  */
/*   lab 2 timing file                                              */
/*                                                                  */
/*   To compile: g++ lab2.cpp lab2timing.cpp timer.cpp -std=c++0x   */
/*                                                                  */
/*                                                                  */
/********************************************************************/
#include "timer.h"
#include <iostream>
using namespace std;

unsigned int fibonacci (unsigned int n){
	//below I am checking the base cases for fibonacci function
	if(n==0){
		return 0;
	}
	if(n==1){
		return 1;
	}
	return fibonacci(n-1)+fibonacci(n-2);
}

int main(void){
	unsigned int n = 27;
	unsigned int rc;
	Timer t;
	t.start();
	rc=fibonacci(n);
	t.stop();
	cout << "fibonacci (" << n << ") = " << rc << endl;
	cout << "fibonacci (" << n << ") took " << t.currtime() << " s" << endl;
	return 0;
}
