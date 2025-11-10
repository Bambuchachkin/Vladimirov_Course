#include "Perfect_Cache.h"
#include <iostream>


Perfect_Cache::Perfect_Cache(int CAPACITY) : capacity{CAPACITY}, /*min_frequency{0},*/ current_position{0}{
    // std::cout << "PER_Cache()\n";
}

Perfect_Cache::~Perfect_Cache() {
    for (auto it = search_map.begin(); it!=search_map.end(); it++) {
        delete it->second;
    }
    search_map.clear();
	predictor_buffer.clear();
    // std::cout << "~PER_Cache()\n";
}

int Perfect_Cache::get_item(int key) {
    current_position++;
    auto it = search_map.find(key);
    if (it==search_map.end()) return -1;
    Node* node = it->second;
    return node->value;
}

void Perfect_Cache::destroy_by_key(int key) {
    Node* trash_node = search_map.find(key)->second;
    search_map.erase(key);
    delete trash_node;
}

int Perfect_Cache::find_trash_value(int new_item) {
    int current_value = -1;
    int trash_value = new_item;
    int current_distance = 0;
    int max_distance = 0;
    for (int i = current_position; i<predictor_buffer.size(); i++) {
        max_distance++;
        if (predictor_buffer[i] == new_item) {
            break;
        }
    }
    // std::cout<<trash_value<<"("<<max_distance<<") ";
    for (auto it = search_map.begin(); it!=search_map.end(); it++) {
        current_value = it->second->value;
        for (int i = current_position; i<predictor_buffer.size(); i++) {
            current_distance++;
            if (predictor_buffer[i] == current_value) {
                if (max_distance < current_distance) {
                    max_distance = current_distance;
                    trash_value = current_value;
                    // std::cout<<"maybe is: "<<trash_value<<"\n";
                    // std::cout<<"maybe Distance is: "<<max_distance<<"\n";
                }
                break;
            }
        }
        // std::cout<<current_value<<"("<<current_distance<<") ";
        if (current_distance>max_distance) {
            max_distance = current_distance;
            trash_value = current_value;
        }
        current_distance = 0;
        current_value = -1;
    }
    // std::cout<<"max_distance is:"<<max_distance<<"\n";
    // std::cout<<"Trash_value is: "<<trash_value<<"\n";
    // std::cout<<"Distance is: "<<max_distance<<"\n";
    return trash_value;
}


void Perfect_Cache::push_item(int item) {
    if (search_map.size() == capacity) {
        int trash_value = find_trash_value(item);
        if (trash_value == item) {
            // std::cout<<"No need to memorize\n";
            return;
        }
        destroy_by_key(trash_value);
    }
    Node* new_node = new Node(item);
    search_map[new_node->key] = new_node;
}

void Perfect_Cache::push_predictive_item(int item){
	predictor_buffer.push_back(item);
}

void Perfect_Cache::clear_predictor_buffer(){
    predictor_buffer.clear();
}

void Perfect_Cache::print_buffer() const {
    std::cout<<"cache: ";
    for (auto it = search_map.begin(); it!=search_map.end(); it++) {
        std::cout<<it->second->value<<" ";
    }
    std::cout<<"\n                                               ";
}

std::vector<int>& Perfect_Cache::get_buffer(){
    return predictor_buffer;
}