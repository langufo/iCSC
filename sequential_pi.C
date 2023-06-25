//---------------------------------------------------------------------
// This program is made to compute pi numerical value.
// It will numerically compute the integral of
//
//                   4/(1+x*x)
//
// from 0 to 1 using variable number of steps.
// The value of this integral is pi. The knowing of pi is quite 
// precise and the result can be compared to the "real" value.
//
// The is the basic sequential program.
// It uses a timer class defined in a separate header file.
//
// History: 
// Written by Gabriele Gaetano Fronzé, 01/18.
// Based on Tim Mattson implementation, 11/99.
//---------------------------------------------------------------------

#include "StopWatch.h"
#include <iostream>
#include "common.h"

int main()
{
    StopWatch stopWatch; //this object will be destroyed when out of scope

    double pi, sum = 0.0;
    double step = 1.0/(double) common::num_steps; //x-step
    double num_steps_2 = static_cast<double>(common::num_steps) * common::num_steps;
    int n_threads=1;

    for (unsigned long long i=1; i<common::num_steps*2+1; i+=2) {
        double x = i;
        sum += 16.0 / (num_steps_2 * 4.0 + x * x); //adding to the cumulus
    }

    pi = common::num_steps * sum;

    common::print_results(pi,n_threads);
    
    return 0;
}
