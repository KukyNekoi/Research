//
//  FixedStack.cpp
//  IntrospectiveQuickSort
//
//  Created by Erik Regla on 05/10/2015.
//  Copyright © 2015 Erik Regla. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class FixedStack{
private:
    long length;
    long top_index;
    long *data;
    long long comparisons;
    
public:
    
    void print_data(long highlight = 0){
        printf("data: ");
        for(long i = 0; i < this->length; i++){
            if(highlight > 0 && highlight == i)
                printf("(%ld) ", this->data[i]);
            else
                printf("%ld ", this->data[i]);
        }
        printf("\n");
    }
    
    bool empty(){
        return top_index < 0;
    }
    
    bool full(){
        return top_index >= length;
    }
    
    long size(){
        return top_index + 1;
    }
    
    void push(long value){
        if(!this->full()){
            top_index++;
            this->data[top_index] = value;
        }
        
    }
    
    long pop(){
        return this->data[top_index--];
    }
    
    long peek(){
        return this->data[top_index];
    }
    
    void reset_counters(){
        this->comparisons = 0;
    }
    
    long get_comparisons(){
        return this->comparisons;
    }
    
    FixedStack(long size){
        this->data = (long *)malloc(sizeof(long) * size);
        this->length = size;
        this->top_index = -1;
        this->comparisons = 0;
    }
    
    ~FixedStack(){
        free(this->data);
    }
};