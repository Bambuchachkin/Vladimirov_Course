#include <iostream>
#include "LFU_Cache.h"
#include "Perfect_Cache.h"

int main() {

    int CAPACITY, number;
    std::cout<<"Enter cache capacity and number of numbers\n";
    std::cin>>CAPACITY>>number;

    LFU_Cache lfu_cache(CAPACITY);
    Perfect_Cache per_cache(CAPACITY);
    std::vector<int>& per_buffer = per_cache.get_buffer();

    int new_item = 0;
    int hits_number = 0;
    int per_hits_number = 0;

    std::cout<<"Enter your numbers\n";

    for (int i =0; i<number; i++) {
        std::cin>>new_item;
        per_buffer.push_back(new_item);
    }
    for (int i =0; i<number; i++) {
        new_item = per_buffer[i];

        if (per_cache.get_item(new_item) == -1) {
            per_cache.push_item(new_item);
            std::cout<<i<<") ";
            std::cout<<"PER| miss to "<<new_item<<"|";
        } else {
            std::cout<<i<<") ";
            std::cout<<"PER| HIT to "<<new_item<<"|";
            per_hits_number++;
        }
        per_cache.print_buffer();

        if (lfu_cache.get_item(new_item) == -1) {
            lfu_cache.push_item(new_item);
            std::cout<<i<<") ";
            std::cout<<"miss to "<<new_item<<"|";
        } else {
            std::cout<<i<<") ";
            std::cout<<"HIT to "<<new_item<<"|";
            hits_number++;
        }
        lfu_cache.print_buffer();
    }

    std::cout<<"hits_number = "<<hits_number<<'\n';
    std::cout<<"per_hits_number = "<<per_hits_number<<'\n';
}