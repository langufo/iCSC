#include "StopWatch.h"
#include <omp.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;

int main(){
    
    const long maxIteration = 100000;
    bool debug_output=false;

    // This is needed to allow the presence of a parallel for nested in another parallel region
    /* replaced original function call as the compiler complained */
    omp_set_max_active_levels(2);

    int outputCounter = 0;
    bool done = false;

    /* reserve one thread (core) for monitoring */
    #pragma omp parallel
    #pragma omp master
    omp_set_num_threads(omp_get_num_threads() - 1);

#pragma omp parallel sections shared(outputCounter,done) num_threads(2)
{
    #pragma omp section
    {
        if ( omp_get_thread_num()==0 ){ 
            if(debug_output) printf("monitor th_id: %d, n_th: %d\n",omp_get_thread_num(), omp_get_num_threads());
            while(!done){
                printf("%d/%ld\r",outputCounter,maxIteration);
                std::this_thread::sleep_for (microseconds(50));
            }
            printf("%d/%ld\n",outputCounter,maxIteration);
        }
    }

    #pragma omp section
    {
        int section = 2;
        #pragma omp parallel
        {
            if(debug_output) printf("computing th_id: %d, n_th: %d\n",omp_get_thread_num(), omp_get_num_threads());
            #pragma omp for
            for( int i=0; i<maxIteration; i++){
                // This sleep emulates some heavy computation... Feel free to add yours!
                std::this_thread::sleep_for (microseconds(1000));

            #pragma omp atomic update
                    outputCounter++;
            }
        }
        done = true;
    }
}

    return 0;
}
