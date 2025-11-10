#include <iostream>
#include <random>
#include <vector>
#include "LFU_Cache.h"
#include "Perfect_Cache.h"

int main() {
    int CAPACITY = 10;
    int number = 1000;
    
    LFU_Cache lfu_cache(CAPACITY);
    Perfect_Cache per_cache(CAPACITY);
    std::vector<int>& per_buffer = per_cache.get_buffer();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 50);

    for (int i = 0; i < number; i++) {
        int new_item = dist(gen);
        per_buffer.push_back(new_item);
    }

    int hits_number = 0;
    int per_hits_number = 0;

    for (int i = 0; i < number; i++) {
        int new_item = per_buffer[i];

        if (per_cache.get_item(new_item) == -1) {
            per_cache.push_item(new_item);
        } else {
            per_hits_number++;
        }

        if (lfu_cache.get_item(new_item) == -1) {
            lfu_cache.push_item(new_item);
        } else {
            hits_number++;
        }
    }

    std::cout<<"lfu_hits_number = "<<hits_number<<'\n';
    std::cout<<"per_hits_number = "<<per_hits_number<<'\n';
    
    return 0;
}
