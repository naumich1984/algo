// L9, task: A, DS-12 Naumovskiy Alexey
/*
A. Сбалансированное двоичное дерево поиска
ограничение по времени на тест2 секунды
ограничение по памяти на тест512 мегабайт
вводстандартный ввод
выводстандартный вывод
Реализуйте сбалансированное двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 105
. В каждой строке находится одна из следующих операций:

insert x
 — добавить в дерево ключ x
. Если ключ x
 есть в дереве, то ничего делать не надо;
delete x
 — удалить из дерева ключ x
. Если ключа x
 в дереве нет, то ничего делать не надо;
exists x
 — если ключ x
 есть в дереве выведите «true», если нет «false»;
next x
 — выведите минимальный элемент в дереве, строго больший x
, или «none» если такого нет;
prev x
 — выведите максимальный элемент в дереве, строго меньший x
, или «none» если такого нет.
В дерево помещаются и извлекаются только целые числа, не превышающие по модулю 109
.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.
*/
#include <iostream>
#include <string>
#include <ctime>

struct NodeTreap {
    int tree_key, priority;
    NodeTreap* left, * right;
    NodeTreap(int new_key) : tree_key(new_key), left(NULL), right(NULL) {
        priority = rand();
    }
};
//Декартово Дерево:
class TreapTree {
    NodeTreap* tree;
    void del_tree(NodeTreap* tree);
    NodeTreap* merge(NodeTreap* left_subtree, NodeTreap* right_subtree);
    void split(NodeTreap* t, int tree_key, NodeTreap*& left_subtree, NodeTreap*& right_subtree);
    NodeTreap* _delete_key(NodeTreap*, int tree_key);
    NodeTreap* print_tree(NodeTreap* pointer_NodeTreap, std::string space);
    NodeTreap* next(NodeTreap* pointer_NodeTreap, int tree_key);
    NodeTreap* prev(NodeTreap* pointer_NodeTreap, int tree_key);
    NodeTreap* exists(NodeTreap* pointer_NodeTreap, int tree_key);

public:
    TreapTree() : tree(NULL) {}
    ~TreapTree() { del_tree(tree); }
    void insert_key(int tree_key);
    void delete_key(int tree_key);
    void exists(int tree_key) {
        NodeTreap* tmp_NodeTreap = exists(this->tree, tree_key);
        if (tmp_NodeTreap == nullptr) {
            std::cout << "false" << std::endl;
        } else {
            std::cout << "true" << std::endl;
        }
    }
    void print_tree(std::string space) {
        NodeTreap* temp_NodeTreap = print_tree(tree, space);
        temp_NodeTreap = nullptr;
        std::cout << std::endl;
    }
    void next(int tree_key) {
        NodeTreap* find_NodeTreap = next(this->tree, tree_key);
        if (find_NodeTreap == nullptr) {
            std::cout << "none" << std::endl;
        } else {
            std::cout << find_NodeTreap->tree_key << std::endl;
        }
        find_NodeTreap = nullptr;
    }
    void prev(int tree_key) {
        NodeTreap* find_NodeTreap = prev(this->tree, tree_key);
        if (find_NodeTreap == nullptr) {
            std::cout << "none" << std::endl;
        } else {
            std::cout << find_NodeTreap->tree_key << std::endl;
        }
        find_NodeTreap = nullptr;
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

NodeTreap* TreapTree::prev(NodeTreap* pointer_NodeTreap, int tree_key) {
    NodeTreap* res = NULL;
    while (pointer_NodeTreap != NULL) {
        if (pointer_NodeTreap->tree_key < tree_key) {
            res = pointer_NodeTreap;
            pointer_NodeTreap = pointer_NodeTreap->right;
        } else {
            pointer_NodeTreap = pointer_NodeTreap->left;
        }
    }
    return res;
}

NodeTreap* TreapTree::next(NodeTreap* pointer_NodeTreap, int tree_key) {
    NodeTreap* res = NULL;
    while (pointer_NodeTreap != NULL) {
        if (pointer_NodeTreap->tree_key > tree_key) {
            res = pointer_NodeTreap;
            pointer_NodeTreap = pointer_NodeTreap->left;
        } else {
            pointer_NodeTreap = pointer_NodeTreap->right;
        }
    }
    return res;
}

void TreapTree::del_tree(NodeTreap* pointer_NodeTreap) {
    if (pointer_NodeTreap->left) del_tree(pointer_NodeTreap->left);
    if (pointer_NodeTreap->right) del_tree(pointer_NodeTreap->right);
    delete pointer_NodeTreap;
}

NodeTreap* TreapTree::merge(NodeTreap* left_subtree, NodeTreap* right_subtree) {
    if (left_subtree == NULL) return right_subtree;
    if (right_subtree == NULL) return left_subtree;
    if (left_subtree->priority > right_subtree->priority) {
        left_subtree->right = merge(left_subtree->right, right_subtree);
        return left_subtree;
    } else {
        right_subtree->left = merge(left_subtree, right_subtree->left);
        return right_subtree;
    }
}

void TreapTree::split(NodeTreap* pointer_NodeTreap, int tree_key, NodeTreap*& left_subtree, NodeTreap*& right_subtree) {
    if (!pointer_NodeTreap)
        left_subtree = right_subtree = NULL;
    if (pointer_NodeTreap->tree_key < tree_key) {
        left_subtree = pointer_NodeTreap;
        if (pointer_NodeTreap->right == NULL)
            right_subtree = NULL;
        else
            split(pointer_NodeTreap->right, tree_key, left_subtree->right, right_subtree);
    } else {
        right_subtree = pointer_NodeTreap;
        if (pointer_NodeTreap->left == NULL)
            left_subtree = NULL;
        else
            split(pointer_NodeTreap->left, tree_key, left_subtree, right_subtree->left);
    }
}

void TreapTree::insert_key(int tree_key) {
    NodeTreap* tmp_NodeTreap = exists(this->tree, tree_key);
    if (tmp_NodeTreap != nullptr) return;
    NodeTreap* new_NodeTreap = new NodeTreap(tree_key);
    if (tree == NULL) {
        tree = new_NodeTreap;
        return;
    }
    NodeTreap* left_subtree = NULL;
    NodeTreap* right_subtree = NULL;
    split(tree, tree_key, left_subtree, right_subtree);
    tree = merge(merge(left_subtree, new_NodeTreap), right_subtree);
}

void TreapTree::delete_key(int tree_key) {
    tree = _delete_key(tree, tree_key);
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

NodeTreap* TreapTree::print_tree(NodeTreap* pointer_NodeTreap, std::string space) {
    if (pointer_NodeTreap != NULL) {
        print_tree(pointer_NodeTreap->left, space + " ");
        std::cout << space << pointer_NodeTreap->tree_key;
        print_tree(pointer_NodeTreap->right, space + " ");
    }
    return pointer_NodeTreap;
}

int main() {
    srand(time(0));
    TreapTree treap_tree;
    int value_command;
    std::string current_command = "";
    while (std::cin >> current_command) {
        if (current_command.compare("insert") == 0) {
            std::cin >> value_command;
            treap_tree.insert_key(value_command);
        } else if (current_command.compare("exists") == 0) {
            std::cin >> value_command;
            treap_tree.exists(value_command);
        } else if (current_command.compare("delete") == 0) {
            std::cin >> value_command;
            treap_tree.delete_key(value_command);
        } else if (current_command.compare("next") == 0) {
            std::cin >> value_command;
            treap_tree.next(value_command);
        } else if (current_command.compare("prev") == 0) {
            std::cin >> value_command;
            treap_tree.prev(value_command);
        }
    }
    return 0;
}

