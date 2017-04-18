//
//  FixedArray.cpp
//  IntrospectiveQuickSort
//
//  Created by Erik Regla on 05/10/2015.
//  Copyright © 2015 Erik Regla. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class FixedArray{
public:
    long get(long idx){
        return array[idx];
    }
    
    void swap(long target, long destination){
        long bubble = this->array[target];
        this->array[target] = this->array[destination];
        this->array[destination] = bubble;
    }
    
    //executes bfpr on [start,end] range, gives an aproximated median
    long bfprt(long start, long end){
        while(start < end){
            //do sweep
            long start_ptr = start;
            //swap_positions
            for(long i = start; i < this->min(end, i+this->bfprt_chunk); i+=bfprt_chunk){
                quicksort(i, this->min(end, i+this->bfprt_chunk));
                this->swap(start_ptr++, (i+this->min(end, i+this->bfprt_chunk))/2);
            }
            end = start_ptr-1;
        }
        return start;
    }
    
    long min(long a, long b){
        return (a<b) ? a : b;
    }
    
    long get_middle_pivot(long start, long end){
//        return (start+end)/2;
        //maybe changing it to end would balance things for heapsort
        return start;
    }
    
    void quicksort(long start, long end){
        if(start < end){
            long pivot = this->partition(get_middle_pivot(start, end), start, end);
            quicksort(start, pivot-1);
            quicksort(pivot+1, end);
        }
    }
    
    //returns the postition of the pivot on the array given a value
    long partition(long pivot_idx, long start, long end){
        //primer caso base
        if (start == end) return start;
        
        this->swap(pivot_idx, start);
        
        long pivot = this->array[start];
        
        long left_ptr_idx = start+1, right_ptr_idx = end;
        
        while(true){
            
            while(left_ptr_idx < right_ptr_idx &&
                  this->array[left_ptr_idx] < pivot){
                left_ptr_idx++;
            }
            while(left_ptr_idx < right_ptr_idx &&
                  this->array[right_ptr_idx] >= pivot){
                right_ptr_idx--;
            }
            
            if(left_ptr_idx < right_ptr_idx){
                this->swap(left_ptr_idx, right_ptr_idx);
                left_ptr_idx++;
                right_ptr_idx--;
            }
            else{
                break;
            }
        }
        if(this->array[left_ptr_idx] >= pivot) left_ptr_idx--;
        this->swap(start, left_ptr_idx);
        return left_ptr_idx;
    }
    
    
    void push_value(long value){
        if(this->filled_up_to < this->lenght){
            this->array[this->filled_up_to++] = value;
        }
    }
    
    void print_data(long highlight = 0){
        printf("data: ");
        for(long i = 0; i < this->lenght; i++){
            if(highlight > 0 && highlight == i)
                printf("(%ld) ", this->array[i]);
            else
                printf("%ld ", this->array[i]);
        }
        printf("\n");
    }
    
    long size(){
        return filled_up_to;
    }
    
    void reset_counters(){
        this->comparisons = 0;
    }
    
    long get_comparisons(){
        return this->comparisons;
    }
    
    FixedArray(long size, long bfprt_chunk = 5){
        this->array = (long *) malloc(size * sizeof(long));
        this->bfprt_chunk = bfprt_chunk;
        this->lenght = size;
        this->filled_up_to = 0;
    }
    
    ~FixedArray(){
        free(this->array);
    }
    
private:
    long *array;
    long lenght;
    long filled_up_to;
    
    long bfprt_chunk;
    long long comparisons;
};