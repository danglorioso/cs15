// stirling.cpp
// Author: Dan Glorioso (dglori02)
// Date: 09/24/23
// Purpose: Calculate factorials, Stirling approximations, and relative error
//  

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const double PI = 3.14159;
const double E = 2.71828;

double approx_factorial(int n);
double fact_n(int n);
double relative_error(double fact_n, double approx_factorial);

int main()
{
    //take in a number for n from cin
    //run the functinos

    //go through numbers 10-50
    // increment by 10s
    for (int i = 10; i <= 50; i = i+10) {
        double factorial = fact_n(i);
        double approx = approx_factorial(i);
        double error = relative_error(factorial, approx);

        cout << "n = " << i << ": " << i << "!: " << factorial 
             << " -- Approximation: " << approx << " -- Relative Error: " 
             << (error * 100) << "%" << endl;
    }

    return 0;
}

double fact_n(int n) {
    //run the factorial function for n!
    if (n == 0)
        return 1;
    else  {
        return n * fact_n(n-1);
    }
}


double approx_factorial(int n) {
    //run the approximation formula for n!
    double new_num;
    new_num = (sqrt(2 * M_PI * n) * pow(n, n) * pow(M_E, -n));
    return new_num;
}

double relative_error(double fact_n, double approx_factorial) {
    return (approx_factorial - fact_n)/fact_n;
}


