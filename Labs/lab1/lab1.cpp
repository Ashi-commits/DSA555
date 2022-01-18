/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Ayushi Sahu                             */
/*  Student number: 143789188                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

//this fucntion takes the input from the tester file and calculates
//the n's factorial value
unsigned int factorial (unsigned int n){
		//this variable will contain the result of factorial function
		unsigned int result=1;
		if(n>0){
			//this loop will calculate the exact factorial value
			//for n if it is greater than 0.
			for(int i=1;i<=n;i++){
			result*=i;
		  }
		}
		return result;
}

//this power function takes the two input from the tester file
//and calcultaes the the result of base raised to an exponent(n)
double power (double base, unsigned int n){
	//this variable will contain calculation of power function
	double result=1;
	if(n>0){
		//this loop will calculate the result of base raised to an
		//exponent(n) where the exponent is greater than 0.
		for(int i=1; i<=n;i++){
			result*=base;
		}
	}
	return result;
}

//this function takes the input from the tester file to calculate
//fibonacci value at n'th position
unsigned int fibonacci (unsigned int n){
	//these temporary variables hold the initial two values of the
	//fibonacci series and the result will contain the calculation
	//of fibonacci function
	unsigned int temp_variable1 = 0, temp_variable2 = 1, result = 0;
	//checking the base case of fibonacci function
	if (n==1){
		return result=1;
	}
	//this loop will calculate the fibonacci for n if is greater than 1.
	for (int i = 2; i <= n; i++) {
		result = temp_variable1 + temp_variable2;
		temp_variable1 = temp_variable2;
		temp_variable2 = result;
	}
	return result;
}
