#ifndef PERFECT_CACHE_H
#define PERFECT_CACHE_H

#include <unordered_map>
#include <vector>

class Perfect_Cache {
    struct Node {
        int key;
        int value;
        int frequency;
        Node (int v) : key{v}, value{v}, frequency{1} {}
    };
    int capacity;
    // int min_frequency;
    int current_position;
    std::unordered_map<int, Node*> search_map;
    // std::unordered_map<int, std::list<Node*>> sort_map;
    std::vector<int> predictor_buffer;
public:
    Perfect_Cache(int CAPACITY);
    ~Perfect_Cache();

    void update_node(Node* node);
    int get_item(int key);
    int find_trash_value(int new_item);
    void destroy_by_key(int key);
    void push_item(int item);
    void push_predictive_item(int item);
    void clear_predictor_buffer();
    void print_buffer() const;

    std::vector<int>& get_buffer();
};



#endif //PERFECT_CACHE_H
