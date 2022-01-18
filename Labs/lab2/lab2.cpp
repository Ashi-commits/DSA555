/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Ayushi Sahu                             */
/*  Student number: 143789188                     */
/*                                                */
/**************************************************/

/* remember to code these in an recursive only manner*/

//this function takes the input from the tester file and calculate
//the n's factorial value using recursive programming.
unsigned int factorial (unsigned int n){
	//this is checking the base cases for factorial function
	if(n==0 || n==1){
		return 1;
	}
	return n*factorial(n-1);
}

//this function takes the input from the tester file and calculate
//the power of base raised to an exponent n using recursive programming.
double power (double base, unsigned int n){
	//this result variable will store the output of power function.
	double result = base;
	//this is checking the base cases for power function
	if(n==0){
		return 1;
	}
	if(n==1){
		return result;
	}
	return result = result*power(base,n-1);
}

//this function takes the input from the tester file and calculate
//the fibonacci value at n'th position using recursive programming.
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
