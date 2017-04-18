//
//  main.cpp
//  IntrospectiveQuickSort
//
//  Created by Erik Regla on 05/10/2015.
//  Copyright © 2015 Erik Regla. All rights reserved.
//

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>       /* time */
#include <chrono>

#include "IntrospectiveQuickSort.cpp"
using namespace std;

int main () {
    string path_sorted = "/Users/jvarred/Documents/Sources/2015/IntrospectiveQuickSort/sources/src/IntrospectiveQuickMedian/iiqs/test_cases/1000000.sorted";
    string path_desorted = "/Users/jvarred/Documents/Sources/2015/IntrospectiveQuickSort/sources/src/IntrospectiveQuickMedian/iiqs/test_cases/1000000.desorted";
    string path_random = "/Users/jvarred/Documents/Sources/2015/IntrospectiveQuickSort/sources/src/IntrospectiveQuickMedian/iiqs/test_cases/1000000.random";
    long long limit = 900000;
    printf("#queries: ");
    scanf("%lld", &limit);
    IncrementalQuickSelect introspective_random(path_random, limit);
    IncrementalQuickSelect standard_random(path_random, limit);
    IncrementalQuickSelect introspective_sorted(path_sorted,limit);
    IncrementalQuickSelect standard_sorted(path_sorted,limit);
    IncrementalQuickSelect introspective_desorted(path_desorted,limit);
    IncrementalQuickSelect standard_desorted(path_desorted,limit);
    
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    
    long long   time_iqs_random = 0, time_iiqs_random = 0,
                time_iqs_sorted = 0, time_iiqs_sorted = 0,
                time_iqs_desorted = 0, time_iiqs_desorted = 0;
    
    printf("idx\tt_iqs_random\tt_iiqs_random\tt_iqs_sorted\tt_iiqs_sorted\tt_iqs_desorted\tt_iiqs_desorted\n");
    for(long long i = 0; i < limit; i++){
        /*********** RANDOM INPUT *************/
        Clock::time_point test = Clock::now();
        standard_random.IQS(i);
        Clock::time_point test_2 = Clock::now();
        microseconds ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iqs_random += ms_iqs.count();
        
        test = Clock::now();
        introspective_random.IIQS(i);
        test_2 = Clock::now();
        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iiqs_random += ms_iqs.count();
        
        
        /*********** INCREMENTAL INPUT *************/
        test = Clock::now();
        standard_sorted.IQS(i);
        test_2 = Clock::now();
        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iqs_sorted += ms_iqs.count();
        
        test = Clock::now();
        introspective_sorted.IIQS(i);
        test_2 = Clock::now();
        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iiqs_sorted += ms_iqs.count();
        
        
        /*********** DECREMENTAL INPUT *************/
        test = Clock::now();
        standard_desorted.IQS(i);
        test_2 = Clock::now();
        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iqs_desorted += ms_iqs.count();
        
        test = Clock::now();
        introspective_desorted.IIQS(i);
        test_2 = Clock::now();
        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iiqs_desorted += ms_iqs.count();
        
        printf("%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t%lld\t\n",i,time_iqs_random,time_iiqs_random,time_iqs_sorted,time_iiqs_sorted,time_iqs_desorted,time_iiqs_desorted);
    }
    
    return 0;
}

/*
int main () {
    string path = "/Users/jvarred/Documents/Sources/2015/IntrospectiveQuickSort/sources/src/IntrospectiveQuickMedian/iiqs/test_cases/1000000.sorted";
    long long limit = 900000;
    IncrementalQuickSelect introspective(path,limit);
    IncrementalQuickSelect standard(path,limit);
    IncrementalQuickSelect quicksort(path,limit);
    IncrementalQuickSelect heapsort(path,limit);
    
    //introspective.print();
    
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::microseconds microseconds;
    bool heapified = false;
    long long quicksorted = 0;
    
    introspective.reset_counters();
    standard.reset_counters();
    quicksort.reset_counters();
    heapsort.reset_counters();
    
    long long   time_iqs = 0, comparisons_iqs = 0,
    time_iiqs = 0, comparisons_iiqs = 0;
    //    time_qs = 0, comparisons_qs = 0,
    //    time_hs = 0, comparisons_hs = 0;
    
    printf("idx\tt_iqs\tt_iiqs\tt_qs\t_hs\n");
    for(long long i = 0; i < limit; i++){
        
        Clock::time_point test = Clock::now();
        standard.IQS(i);
        Clock::time_point test_2 = Clock::now();
        microseconds ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iqs += ms_iqs.count();
        comparisons_iqs += standard.get_key_comparisons();
        //        printf("Time elapsed for IQS:  %lld\n", ms_iqs.count());
        //        printf("Comparisons  for IQS:  %lld\n", standard.comparisons);
        
        
        test = Clock::now();
        introspective.IIQS(i);
        test_2 = Clock::now();
        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        time_iiqs += ms_iqs.count();
        comparisons_iiqs += introspective.get_key_comparisons();
        //        printf("Time elapsed for IIQS: %lld\n", ms_iqs.count());
        //        printf("Comparisons  for IIQS: %lld\n", introspective.comparisons);
        //
        //        if(0 == time_qs){
        //            test = Clock::now();
        //            quicksort.data->quicksort(0,limit-1);
        //            test_2 = Clock::now();
        //
        //        }
        //        else{
        //            test = Clock::now();
        //            test_2 = Clock::now();
        //        }
        //        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        //        time_qs += ms_iqs.count();
        //        comparisons_qs += quicksort.get_key_comparisons();
        ////        printf("Time elapsed for   QS: %lld\n", ms_iqs.count());
        ////        printf("Comparisons  for   QS: %lld\n", introspective.comparisons);
        //
        //
        //        if(heapified){
        //            test = Clock::now();
        //            heapsort.extract_heap();
        //            test_2 = Clock::now();
        //        }
        //        else{
        //            heapified = true;
        //            test = Clock::now();
        //            heapsort.prepare_heap();
        //            heapsort.extract_heap();
        //            test_2 = Clock::now();
        //        }
        //        ms_iqs  = std::chrono::duration_cast<microseconds>(test_2-test);
        //        time_hs += ms_iqs.count();
        //        comparisons_hs += heapsort.get_key_comparisons();
        ////        printf("Time elapsed for   HS: %lld\n", ms_iqs.count());
        ////        printf("Comparisons  for   HS: %lld\n", heapsort.comparisons);
        printf("%lld\t%lld\t%lld\t\n",i,
               time_iqs,
               time_iiqs);
        //               time_qs,
        //               time_hs);
    }
    
    return 0;
}*/