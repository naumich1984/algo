// L9, task: B, DS-12 Naumovskiy Alexey
/*
B. Неявный ключ
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Научитесь быстро делать две операции с массивом:  add i x — добавить после i-го элемента x (0 ≤ i ≤ n)  del i — удалить i-й элемент (1 ≤ i ≤ n)

Входные данные
На первой строке n0 и m (1 ≤ n0, m ≤ 105) — длина исходного массива и количество запросов. На второй строке n0 целых чисел от 0 до 109 - 1 — исходный массив. Далее m строк, содержащие запросы. Гарантируется, что запросы корректны: например, если просят удалить i-й элемент, он точно есть.

Выходные данные
Выведите конечное состояние массива. На первой строке количество элементов, на второй строке сам массив.
*/
#include <iostream>
#include <string>
#include <ctime>

struct NodeTreap {
    int tree_key, priority, size = 1;
    NodeTreap* left, * right;
    NodeTreap(int new_key) : tree_key(new_key), left(NULL), right(NULL) {
        priority = rand();
    }
};
//Декартово Дерево с неявным ключом
class TreapTree {
    NodeTreap* tree;
    void del_tree(NodeTreap* tree);
    NodeTreap* merge(NodeTreap* left_subtree, NodeTreap* right_subtree);
    void split(NodeTreap* t, int tree_key, NodeTreap*& left_subtree, NodeTreap*& right_subtree);
    NodeTreap* _delete_key(NodeTreap*, int tree_key);
    NodeTreap* _delete_position(NodeTreap* pointer_NodeTreap, int position);
    NodeTreap* print_tree(NodeTreap* pointer_NodeTreap, std::string space);
    NodeTreap* exists(NodeTreap* pointer_NodeTreap, int tree_key);

 public:
    TreapTree() : tree(NULL) {}
    ~TreapTree() { del_tree(tree); }
    void add_key(int position, int tree_key);
    void delete_key(int tree_key);
    void delete_position(int position);
    int size(NodeTreap* v) {
        { return v ? v->size : 0; }
    }
    int size_tree() {
        { return this->tree ? this->tree->size  : 0; }
    }
    void update_size(NodeTreap* v) { v->size = 1 + size(v->left) + size(v->right); }
    void print_tree(std::string space) {
        NodeTreap* temp_NodeTreap = print_tree(tree, space);
        temp_NodeTreap = nullptr;
        std::cout << std::endl;
    }
};

NodeTreap* TreapTree::exists(NodeTreap* pointer_NodeTreap, int tree_key) {
    if (pointer_NodeTreap == NULL)
        return NULL;
    else if (tree_key < pointer_NodeTreap->tree_key)
        return exists(pointer_NodeTreap->left, tree_key);
    else if (tree_key > pointer_NodeTreap->tree_key)
        return exists(pointer_NodeTreap->right, tree_key);
    else
        return pointer_NodeTreap;
}

void TreapTree::del_tree(NodeTreap* pointer_NodeTreap) {
    if (pointer_NodeTreap != NULL) {
        if (pointer_NodeTreap->left) del_tree(pointer_NodeTreap->left);
        if (pointer_NodeTreap->right) del_tree(pointer_NodeTreap->right);
        delete pointer_NodeTreap;
    }
}

NodeTreap* TreapTree::merge(NodeTreap* left_subtree, NodeTreap* right_subtree) {
    if (left_subtree == NULL) return right_subtree;
    if (right_subtree == NULL) return left_subtree;
    if (left_subtree->priority > right_subtree->priority) {
        left_subtree->right = merge(left_subtree->right, right_subtree);
        update_size(left_subtree);
        return left_subtree;
    } else {
        right_subtree->left = merge(left_subtree, right_subtree->left);
        update_size(right_subtree);
        return right_subtree;
    }
}

void TreapTree::split(NodeTreap* pointer_NodeTreap, int position, NodeTreap*& left_subtree, NodeTreap*& right_subtree) {
    if (!pointer_NodeTreap) left_subtree = right_subtree = NULL;
    int cur_size = 0;
    if (pointer_NodeTreap == NULL)
        return;
    cur_size = size(pointer_NodeTreap->left) + 1;
    if (cur_size <= position) {
        left_subtree = pointer_NodeTreap;
        if (pointer_NodeTreap->right == NULL)
            right_subtree = NULL;
        else
            split(pointer_NodeTreap->right, position - size(pointer_NodeTreap->left) - 1, left_subtree->right, right_subtree);
        update_size(pointer_NodeTreap);
    } else {
        right_subtree = pointer_NodeTreap;
        if (pointer_NodeTreap->left == NULL)
            left_subtree = NULL;
        else
            split(pointer_NodeTreap->left, position, left_subtree, right_subtree->left);
        update_size(pointer_NodeTreap);
    }
}

void TreapTree::add_key(int position, int tree_key) {
    NodeTreap* tmp_NodeTreap = exists(this->tree, tree_key);
    if (tmp_NodeTreap != nullptr) return;
    NodeTreap* new_NodeTreap = new NodeTreap(tree_key);
    if (tree == NULL) {
        tree = new_NodeTreap;
        return;
    }
    NodeTreap* left_subtree = NULL;
    NodeTreap* right_subtree = NULL;
    split(tree, position, left_subtree, right_subtree);
    tree = merge(merge(left_subtree, new_NodeTreap), right_subtree);
}

void TreapTree::delete_key(int tree_key) {
    tree = _delete_key(tree, tree_key);
}

void TreapTree::delete_position(int position) {
    tree = _delete_position(tree, position);
}

NodeTreap* TreapTree::_delete_key(NodeTreap* pointer_NodeTreap, int tree_key) {
    if (pointer_NodeTreap == NULL) return NULL;
    if (pointer_NodeTreap->tree_key == tree_key) {
        NodeTreap* tmp_node = pointer_NodeTreap;
        pointer_NodeTreap = merge(pointer_NodeTreap->left, pointer_NodeTreap->right);
        delete tmp_node;
        return pointer_NodeTreap;
    }
    if (tree_key < pointer_NodeTreap->tree_key)
        pointer_NodeTreap->left = _delete_key(pointer_NodeTreap->left, tree_key);
    else
        pointer_NodeTreap->right = _delete_key(pointer_NodeTreap->right, tree_key);
    return pointer_NodeTreap;
}

NodeTreap* TreapTree::_delete_position(NodeTreap* pointer_NodeTreap, int position) {
    NodeTreap* left_subtree = NULL;
    NodeTreap* right_subtree = NULL;
    NodeTreap* median_subtree = NULL;
    split(tree, position, left_subtree, right_subtree);
    split(right_subtree, 1, median_subtree, right_subtree);
    return merge(left_subtree, right_subtree);
}

NodeTreap* TreapTree::print_tree(NodeTreap* pointer_NodeTreap, std::string space) {
    if (pointer_NodeTreap != NULL) {
        print_tree(pointer_NodeTreap->left, space);
        std::cout << pointer_NodeTreap->tree_key << space;
        print_tree(pointer_NodeTreap->right, space);
    }
    return pointer_NodeTreap;
}

int main() {
    srand(time(0));
    TreapTree treap_tree;
    int value_command;
    int len_array;
    int count_requests;
    int element;
    int position_element;
    std::cin >> len_array >> count_requests;
    for (int i = 0; i < len_array; ++i) {
        std::cin >> element;
        treap_tree.add_key(i, element);
    }
    std::string current_command = "";
    for (int i = 0; i < count_requests; ++i) {
        std::cin >> current_command;
        if (current_command.compare("del") == 0) {
            std::cin >> position_element;
            treap_tree.delete_position(position_element - 1);
        } else if (current_command.compare("add") == 0) {
            std::cin >> position_element >> element;
            treap_tree.add_key(position_element , element);
        }
    }
    std::cout << treap_tree.size_tree() << std::endl;
    treap_tree.print_tree(" ");
    return 0;
}

