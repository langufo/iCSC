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
// This parallel version uses omp parallel for.
// It uses a timer class defined in a separate header file.
//
// History: 
// Written by Gabriele Gaetano Fronzé, 01/18.
// Based on Tim Mattson implementation, 11/99.
//---------------------------------------------------------------------

#include "StopWatch.h"
#include <omp.h>
#include <iostream>
#include "common.h"

int main()
{
    StopWatch stopWatch;

    double pi, sum = 0.0;
    double num_steps_2 = static_cast<double>(common::num_steps) * common::num_steps;
    int n_threads=1;

    #pragma omp parallel
    {
        n_threads = omp_get_num_threads();

        // OpenMP can handle for us for loop ranges!
        // TIP: you have to add something in the following line...
        #pragma omp for reduction(+:sum)
        for (unsigned long long i=1; i<=common::num_steps*2+1; i+=2) {
            double x = i;
            sum += 16.0 / (num_steps_2 * 4 + x * x); //adding to the cumulus
        }
    }

    pi = common::num_steps * sum;

    common::print_results(pi, n_threads);
    
    return 0;
    
}
