// L9, task: D, DS-12 Naumovskiy Alexey
/*
D. Развороты
ограничение по времени на тест1 секунда
ограничение по памяти на тест512 мегабайт
вводстандартный ввод
выводстандартный вывод
Вам дан массив a1 = 1, a2 = 2, ..., an = n и последовательность операций: переставить элементы с li по ri в обратном порядке. Например, для массива 1, 2, 3, 4, 5, после операции (2, 4) новый порядок будет 1, 4, 3, 2, 5. А после применения операции (3, 5) порядок элементов в массиве будет 1, 4, 5, 2, 3.

Выведите порядок элементов в массиве после выполнения всех операций.

Входные данные
В первой строке входного файла указаны числа n и m (2 ≤ n ≤ 100 000, 1 ≤ m ≤ 100 000) — число элементов в массиве и число операций. Следующие m строк содержат операции в виде двух целых чисел: li и ri (1 ≤ li ≤ ri ≤ n).

Выходные данные
Выведите n целых чисел — порядок элементов в массиве после применения всех операций.
*/
#include <iostream>
#include <string>
#include <ctime>

struct NodeTreap {
    int tree_key, priority, size = 1;
    bool rev;
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
    NodeTreap* _move_to_beginning(int left_position, int right_position);
    NodeTreap* _reverse(int left_position, int right_position);
    void push(NodeTreap* pointer_NodeTreap);

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
        { return this->tree ? this->tree->size : 0; }
    }
    void update_size(NodeTreap* v) { v->size = 1 + size(v->left) + size(v->right); }
    void print_tree(std::string space) {
        NodeTreap* temp_NodeTreap = print_tree(tree, space);
        temp_NodeTreap = nullptr;
        std::cout << std::endl;
    }
    void move_to_beginning(int left_position, int right_position);
    void reverse(int left_position, int right_position);
};

// меняем ссылки на детей, после скидываем флаги реверса:
//(добавляем push в merge, split и print)
void TreapTree::push(NodeTreap* pointer_NodeTreap) {
    if (pointer_NodeTreap && pointer_NodeTreap->rev) {
        pointer_NodeTreap->rev = false;
        NodeTreap* buff = pointer_NodeTreap->left;
        pointer_NodeTreap->left = pointer_NodeTreap->right;
        pointer_NodeTreap->right = buff;
        if (pointer_NodeTreap->left)
            pointer_NodeTreap->left->rev ^= 1;
        if (pointer_NodeTreap->right)
            pointer_NodeTreap->right->rev ^= 1;
    }
}

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
    push(left_subtree);
    push(right_subtree);
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
    push(pointer_NodeTreap);
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

void TreapTree::move_to_beginning(int left_position, int right_position) {
    tree = _move_to_beginning(left_position, right_position);
}

void TreapTree::reverse(int left_position, int right_position) {
    tree = _reverse(left_position, right_position);
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
        push(pointer_NodeTreap);
        print_tree(pointer_NodeTreap->left, space);
        std::cout << pointer_NodeTreap->tree_key << space;
        print_tree(pointer_NodeTreap->right, space);
    }
    return pointer_NodeTreap;
}
//"Переместить в начало":
NodeTreap* TreapTree::_move_to_beginning(int left_position, int right_position) {
    NodeTreap* left_subtree = NULL;
    NodeTreap* right_subtree = NULL;
    NodeTreap* sub_left_subtree = NULL;
    NodeTreap* sub_right_subtree = NULL;
    //разбили на две части по позиции right_position:
    split(tree, right_position, left_subtree, right_subtree);
    //левую часть из предыдущего разбиения разбили по left_position:
    split(left_subtree, left_position - 1, sub_left_subtree, sub_right_subtree);
    //склеили кусочки в нужном нам порядке( с r по l в начало, а после все остальные слева направо):
    return merge(merge(sub_right_subtree, sub_left_subtree), right_subtree);
}

//вырезаем нужный отрезок, меняем флаг реверса и склеиваем назад. 
//при склейке метод push поменяет ссылки на детей местами, тем самым проведя переворот:
NodeTreap* TreapTree::_reverse(int left_position, int right_position) {
    if (left_position == right_position) return this->tree;
    NodeTreap* left_subtree = NULL;
    NodeTreap* right_subtree = NULL;
    NodeTreap* sub_left_subtree = NULL;
    NodeTreap* sub_right_subtree = NULL;
    split(tree, left_position - 1, left_subtree, right_subtree);
    split(right_subtree, right_position - left_position + 1, sub_left_subtree, sub_right_subtree);
    sub_left_subtree->rev ^= 1;
    return merge(merge(left_subtree, sub_left_subtree), sub_right_subtree);
}

int main() {
    srand(time(0));
    TreapTree treap_tree;
    int len_array;
    int count_requests;
    int position_left;
    int position_right;
    std::cin >> len_array >> count_requests;
    for (int i = 0; i < len_array; ++i) {
        treap_tree.add_key(i, i + 1);
    }
    for (int i = 0; i < count_requests; ++i) {
        std::cin >> position_left >> position_right;
        treap_tree.reverse(position_left, position_right);
    }
    treap_tree.print_tree(" ");
    return 0;
}

