/*
A. Простое двоичное дерево поиска
ограничение по времени на тест2 секунды
ограничение по памяти на тест512 мегабайт
вводстандартный ввод
выводстандартный вывод
Реализуйте просто двоичное дерево поиска.

Входные данные
Входной файл содержит описание операций с деревом, их количество не превышает 100. В каждой строке находится одна из следующих операций:

insert x — добавить в дерево ключ x. Если ключ x есть в дереве, то ничего делать не надо;
delete x — удалить из дерева ключ x. Если ключа x в дереве нет, то ничего делать не надо;
exists x — если ключ x есть в дереве выведите «true», если нет «false»;
next x — выведите минимальный элемент в дереве, строго больший x, или «none» если такого нет;
prev x — выведите максимальный элемент в дереве, строго меньший x, или «none» если такого нет.
В дерево помещаются и извлекаются только целые числа, не превышающие по модулю 109.
Выходные данные
Выведите последовательно результат выполнения всех операций exists, next, prev. Следуйте формату выходного файла из примера.
*/

// L8, task: A, DS-12 Naumovskiy Alexey
#include <iostream>
#include <string>

class BST {
    struct BSTNode {
        int key;
        BSTNode* left;
        BSTNode* right;
    };
    BSTNode* root;
    BSTNode* search(BSTNode* pointer_node, int tree_key);
    BSTNode* insert(int tree_key, BSTNode* pointer_node);
    BSTNode* del(BSTNode* pointer_node, int tree_key);
    BSTNode* find_max(BSTNode* pointer_node);
    BSTNode* print_tree(BSTNode* pointer_node, std::string space);
    BSTNode* next(BSTNode* pointer_node, int tree_key);
    BSTNode* prev(BSTNode* pointer_node, int tree_key);
    BSTNode* exists(BSTNode* pointer_node, int tree_key);
    BSTNode* clear_bst(BSTNode* pointer_node);

public:
    BST();
    ~BST();
    void print_tree(std::string space) {
        BSTNode* temp_node = print_tree(this->root, space);
        temp_node = nullptr;
        std::cout << std::endl;
    }

    void next(int tree_key) {
        BSTNode* find_node = next(this->root, tree_key);
        if (find_node == nullptr) {
            std::cout << "none" << std::endl;
        } else {
            std::cout << find_node->key << std::endl;
        }
        find_node = nullptr;
    }

    void prev(int tree_key) {
        BSTNode* find_node = prev(this->root, tree_key);
        if (find_node == nullptr) {
            std::cout << "none" << std::endl;
        } else {
            std::cout << find_node->key << std::endl;
        }
        find_node = nullptr;
    }

    void del(int tree_key) {
        this->root = del(this->root, tree_key);
    }

    void insert(int tree_key) {
        this->root = insert(tree_key, this->root);
    }

    void exists(int tree_key) {
        BSTNode* find_node = exists(this->root, tree_key);
        if (find_node == nullptr) {
            std::cout << "false"<<std::endl;
        } else {
            std::cout << "true" << std::endl;
        }
        find_node = nullptr;
    }
};

BST::BST(){
    this->root = NULL;
}

BST::~BST() {
    this->root = clear_bst(root);
}

BST::BSTNode* BST::search(BSTNode* pointer_node, int tree_key) {
    if (pointer_node == NULL) return NULL;
    if (pointer_node->key == tree_key) {
        return pointer_node;
    } else if (tree_key < pointer_node->key) {
        return BST::search(pointer_node->left, tree_key);
    } else {
        return BST::search(pointer_node->right, tree_key);
    }
}

BST::BSTNode* BST::insert(int tree_key, BSTNode* pointer_node) {
    if (pointer_node == NULL) {
        pointer_node = new BSTNode;
        pointer_node->key = tree_key;
        pointer_node->left = pointer_node->right = NULL;
    } else if (tree_key < pointer_node->key) {
        pointer_node->left = insert(tree_key, pointer_node->left);
    } else if (tree_key > pointer_node->key) {
        pointer_node->right = insert(tree_key, pointer_node->right);
    }
    return pointer_node;
}

BST::BSTNode* BST::del(BSTNode* pointer_node, int tree_key) {
    if (pointer_node == NULL) return pointer_node;
    if (tree_key < pointer_node->key) {
        pointer_node->left = del(pointer_node->left, tree_key);
    } else if (tree_key > pointer_node->key) {
        pointer_node->right = del(pointer_node->right, tree_key);
    } else if (pointer_node->right == NULL && pointer_node->left == NULL) {
        pointer_node = NULL;
    } else if (pointer_node->left == NULL) {
        pointer_node = pointer_node->right;
    } else if (pointer_node->right == NULL) {
        pointer_node = pointer_node->left;
    } else {
        pointer_node->key = (find_max(pointer_node->left))->key;
        pointer_node->left = del(pointer_node->left, pointer_node->key);
    }
    return pointer_node;
}

BST::BSTNode* BST::find_max(BSTNode* pointer_node) {
    while (pointer_node->right != NULL) {
        pointer_node = pointer_node->right;
    }
    return pointer_node;
}

BST::BSTNode* BST::print_tree(BSTNode* pointer_node, std::string space) {
    if (pointer_node != NULL) {
        print_tree(pointer_node->left, space + " ");
        std::cout<< space << pointer_node->key;
        print_tree(pointer_node->right,space + " ");
    }
    return pointer_node;
}

BST::BSTNode* BST::next(BSTNode* pointer_node, int tree_key) {
    BSTNode* res = NULL;
    while (pointer_node != NULL) {
        if (pointer_node->key > tree_key) {
            res = pointer_node;
            pointer_node = pointer_node->left;
        } else {
            pointer_node = pointer_node->right;
        }
    }
    return res;
}

BST::BSTNode* BST::prev(BSTNode* pointer_node, int tree_key) {
    BSTNode* res = NULL;
    while (pointer_node != NULL) {
        if (pointer_node->key < tree_key) {
            res = pointer_node;
            pointer_node = pointer_node->right;
        } else {
            pointer_node = pointer_node->left;
        }
    }
    return res;
}

BST::BSTNode* BST::exists(BSTNode* pointer_node, int tree_key) {
    if (pointer_node == NULL)
        return NULL;
    else if (tree_key < pointer_node->key)
        return exists(pointer_node->left, tree_key);
    else if (tree_key > pointer_node->key)
        return exists(pointer_node->right, tree_key);
    else
        return pointer_node;
}

BST::BSTNode* BST::clear_bst(BSTNode* pointer_node) {
    if (pointer_node == NULL) return NULL;
    clear_bst(pointer_node->left);
    clear_bst(pointer_node->right);
    delete pointer_node;
    return NULL;
}

int main() {
    BST bst_tree;
    int value_command;
    std::string current_command = "";
    while (std::cin >> current_command) {
        if (current_command.compare("insert") == 0) {
            std::cin >> value_command;
            bst_tree.insert(value_command);
        } else if (current_command.compare("exists") == 0) {
            std::cin >> value_command;
            bst_tree.exists(value_command);
        } else if (current_command.compare("delete") == 0) {
            std::cin >> value_command;
            bst_tree.del(value_command);
        } else if (current_command.compare("next") == 0) {
            std::cin >> value_command;
            bst_tree.next(value_command);
        } else if (current_command.compare("prev") == 0) {
            std::cin >> value_command;
            bst_tree.prev(value_command);
        }
    }
    return 0;
}

