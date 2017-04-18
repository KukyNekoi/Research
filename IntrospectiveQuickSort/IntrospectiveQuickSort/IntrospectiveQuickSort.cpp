//
//  IntrospectiveQuickSort.cpp
//  IntrospectiveQuickSort
//
//  Created by Erik Regla on 05/10/2015.
//  Copyright © 2015 Erik Regla. All rights reserved.
//
/*  EXCEPTION LIST
    1: Array index out of bounds
 */
#include "FixedStack.cpp"
#include "FixedArray.cpp"
#include <string>
#include <iostream>
#include <fstream>

class IncrementalQuickSelect{
public:
    
    void print(){
        this->data->print_data();
        this->stack->print_data();
    }
    
    IncrementalQuickSelect(std::string path, long dimension){
        this->data = new FixedArray(dimension);
        this->stack = new FixedStack(dimension);
        std::string line;
        std::ifstream input(path);
        if (input.is_open()){
            while ( getline (input,line) ){
                data->push_value(stoi(line));
            }
            input.close();
        }
        else{
            std::cout << "Unable to open file\n";
        }
        input.close();
        this->stack->push(dimension);
        this->alpha = 0.3;
        this->stack->reset_counters();
        this->data->reset_counters();
        this->comparisons = 0;
    }
    
    
    void reset_counters(){
        this->stack->reset_counters();
        this->data->reset_counters();
        this->comparisons = 0;
    }
    
    long get_key_comparisons(){
        return this->stack->get_comparisons() + this->data->get_comparisons() + this->comparisons;
    }
    
    
    /************** Incremental Quick Sort code START *************************/
    long IQS(long k){
        if(k == this->stack->peek()){
            this->stack->pop();
            return this->data->get(k);
        }
        while(true){
            long pidx = this->data->get_middle_pivot(k, this->stack->peek());
            pidx = this->data->partition(pidx, k, this->stack->peek()-1);
            if(k == pidx){
                return this->data->get(k);
            }
            this->stack->push(pidx);
        }
    }
    /*************** Incremental Quick Sort code END **************************/
    
    
    /******** Introspective Incremental Quick Sort code START *****************/
    long IIQS(long k){
        if(k == this->stack->peek()){
            this->stack->pop();
            return this->data->get(k);
        }
        while(true){
            long pidx = this->data->get_middle_pivot(k, this->stack->peek());
            pidx = this->data->partition(pidx, k, this->stack->peek()-1);
            long remanent = -1;
            long m = this->stack->peek() - k;
            if(pidx < k + (long)(alpha * (double)m)){
                remanent = pidx;
                pidx = this->data->bfprt(remanent+1, this->stack->peek());
                pidx = this->data->partition(pidx, remanent, this->stack->peek()-1);
                this->stack->push(pidx);
                if(k == remanent){
                    return this->data->get(k);
                }
                this->stack->push(remanent);
            }
            else if(pidx > this->stack->peek() - (long)(alpha * (double)m)){
                remanent = pidx;
                pidx = this->data->bfprt(k, pidx-1);
                pidx = this->data->partition(pidx, k, remanent);
                remanent = -1;
                if(k == pidx){
                    return this->data->get(k);
                }
                this->stack->push(pidx);
            }
            this->stack->push(pidx);
            if(k == remanent){
                return this->data->get(k);
            }
            this->stack->push(remanent);
        }
        this->stack->pop();
        return this->data->get(k);
    }
    /********* Introspective Incremental Quick Sort code END ******************/
    
    /*********************** Heapsort code START ******************************/
    void shift_down(long i, long max) {
        long i_big, c1, c2;
        while(i < max) {
            i_big = i;
            c1 = (2*i) + 1;
            c2 = c1 + 1;
            if(c1<max && this->data->get(c1)>this->data->get(i_big) )
                i_big = c1;
            if(c2<max && this->data->get(c2)>this->data->get(i_big) )
                i_big = c2;
            if(i_big == i) return;
            this->data->swap(i,i_big);
            i = i_big;
        }
    }
    
    void to_heap() {
        long i = (this->data->size()/2) - 1;
        while(i >= 0) {
            shift_down(i, this->data->size());
            --i;
        }
    }
    
    void heap_sort() {
        to_heap();
        long end = this->data->size() - 1;
        while (end > 0) {
            this->data->swap(0, end);
            shift_down(0, end);
            --end;
        }
    }
    
    void prepare_heap(){
        to_heap();
        this->end = this->data->size() - 1;
    }
    
    void extract_heap(){
        this->data->swap(0, end);
        shift_down(0, end);
        --end;
    }
    /**********************  Heapsort code END   ******************************/
    
    ~IncrementalQuickSelect(){
        delete this->data;
        delete this->stack;
    }
    
//private:
    FixedArray *data;
    FixedStack *stack;
    double alpha;
    long long comparisons;
    long long end;
};