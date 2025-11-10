#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <unordered_map>
#include <list>

class LFU_Cache {
    struct Node {
        int key;
        int value;
        int frequency;
        Node (int v) : key{v}, value{v}, frequency{1} {}
    };
    int capacity;
    int min_frequency;
    std::unordered_map<int, Node*> search_map;
    std::unordered_map<int, std::list<Node*>> sort_map;
public:
    LFU_Cache(int CAPACITY);
    ~LFU_Cache();

    void update_node(Node* node);
    int get_item(int key);
    void push_item(int item);
    void print_buffer() const;
};



#endif //LFU_CACHE_H
