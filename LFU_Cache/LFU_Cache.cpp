#include "LFU_Cache.h"
#include <iostream>


LFU_Cache::LFU_Cache(int CAPACITY) : capacity{CAPACITY}, min_frequency{0}{
    // std::cout << "LFU_Cache()\n";
}

LFU_Cache::~LFU_Cache() {
    for (auto it = search_map.begin(); it!=search_map.end(); it++) {
        delete it->second;
    }
    search_map.clear();
    sort_map.clear();
    // std::cout << "~LFU_Cache()\n";
}

void LFU_Cache::update_node(Node* node) {
    std::list<Node*>* old_frequency_list = &sort_map.find(node->frequency)->second;
    old_frequency_list->remove(node);
    if (old_frequency_list->empty() && node->frequency == min_frequency) {
        min_frequency++;
    }
    node->frequency++;
    sort_map[node->frequency].push_back(node);
}


int LFU_Cache::get_item(int key) {
    auto it = search_map.find(key);
    if (it==search_map.end()) return -1;
    Node* node = it->second;
    update_node(node);
    return node->value;
}

void LFU_Cache::push_item(int item) {
    if (search_map.size() == capacity) {
        std::list<Node*>* min_frequency_list = &sort_map.find(min_frequency)->second;
        Node* trash_node = min_frequency_list->front();
        int trash_key = trash_node->key;
        delete trash_node;
        min_frequency_list->pop_front();
        search_map.erase(trash_key);
    }
    Node* new_node = new Node(item);
    search_map[new_node->key] = new_node;
    sort_map[1].push_back(new_node);
    min_frequency = 1;
}

void LFU_Cache::print_buffer() const {
    std::cout<<"cache: ";
    for (auto it = search_map.begin(); it!=search_map.end(); it++) {
        std::cout<<it->second->value<<"("<<it->second->frequency<<")";
    }
    std::cout<<'\n';
}