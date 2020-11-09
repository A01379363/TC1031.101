#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class BTreeNode
{

private:
    T val;
    BTreeNode<T> *left;
    BTreeNode<T> *right;

public:
    ~BTreeNode<T>() {}
    BTreeNode<T>() {}
    BTreeNode<T>(T val) : val(val)
    {
        left = NULL;
        right = NULL;
    }
    BTreeNode<T>(T val, BTreeNode<T> *left, BTreeNode<T> *right) : val(val), left(left), right(right) {}

    T get_val() { return val; }
    BTreeNode<T> *get_left() { return left; }
    BTreeNode<T> *get_right() { return right; }

    void set_val(T val) { this->val = val; }
    void set_left(BTreeNode<T> *node) { left = node; }
    void set_right(BTreeNode<T> *node) { right = node; }
};

template <class T>
class BinarySearchTree
{
private:
    BTreeNode<T> *root;
    vector<T> v_inorder;

public:
    ~BinarySearchTree() {}
    BinarySearchTree() { root = NULL; }

    void set_root(BTreeNode<T> *root) { this->root = root; }
    BTreeNode<T>* get_root(){ return root; }

    BTreeNode<T> *find(T val)
    {
        BTreeNode<T> *ptr = root;
        while (ptr != NULL)
        {
            if (ptr->get_val() == val)
                return ptr;

            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }
        return NULL;
    }

    BTreeNode<T> *find_parent(T val)
    {
        BTreeNode<T> *ptr = root;
        BTreeNode<T> *prev = NULL;
        while (ptr != NULL)
        {
            if (ptr->get_val() == val)
                return prev;

            prev = ptr;
            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }
        return NULL;
    }

    bool insert_node(T val)
    {
        BTreeNode<T> *ptr = root;
        BTreeNode<T> *prev = NULL;

        while (ptr != NULL)
        {
            if (ptr->get_val() == val)
                return false;

            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }

        BTreeNode<T> *new_node = new BTreeNode<T>(val);

        if (prev == NULL)
            root = new_node;

        else
        {
            if (prev->get_val() < val)
                prev->set_right(new_node);

            else
                prev->set_left()(new_node);
        }
        return true;
    }

    BTreeNode<T> *insert_node_recursive(BTreeNode<T> *node, T val)
    {
        if (node == NULL)
            return new BTreeNode<T>(val);

        if (val < node->get_val())
            node->set_left(insert_node_recursive(node->get_left(), val));

        else
            node->set_right(insert_node_recursive(node->get_right(), val));

        return node;
    }

    bool insert_node_recursive(T val)
    {
        root = insert_node_recursive(root, val);
        return true;
    }

    BTreeNode<T> *sucessor(BTreeNode<T> *node)
    {
        BTreeNode<T> *ptr = node->get_right();
        while (ptr->get_left() != NULL)
        {
            ptr = ptr->get_left();
        }
        return ptr;
    }

    BTreeNode<T> *delete_node(BTreeNode<T> *node, int key)
    {
        // caso base
        if (node == NULL)
            return node;

        // si el valor a eliminar es menor que el valor del nodo
        // entonces está en el subarbol izquierdo
        if (key < node->get_val())
            node->set_left(delete_node(node->get_left(), key));

        // si el valor a eliminar es mayor que el valor del nodo
        // entonces está en el subarbol derecho
        else if (key > node->get_val())
            node->set_right(delete_node(node->get_right(), key));

        // si el valor a eliminar es igual que el valor del nodo
        // entonces este es el elemento que queremos eliminar
        else
        {
            // nodos con solo un hijo o sin hijos
            if (node->get_left() == NULL)
            {
                BTreeNode<T> *temp = node->get_right();
                delete node;
                return temp;
            }
            else if (node->get_right() == NULL)
            {
                BTreeNode<T> *temp = node->get_left();
                delete node;
                return temp;
            }

            // nodo con dos hijos, entonces obtener el sucesor
            BTreeNode<T> *temp = sucessor(node);

            // copiar el valor del sucesor al nodo que contiene el elemento a borrar
            node->set_val(temp->get_val());

            // borrar el sucesor
            node->set_right(delete_node(node->get_right(), temp->get_val()));
        }
        return node;
    }

    void delete_node(T val)
    {
        root = delete_node(root, val);
    }

    void print_preorder(BTreeNode<T> *node)
    {
        if (node != NULL)
        {
            std::cout << node->get_val() << ", ";
            print_preorder(node->get_left());
            print_preorder(node->get_right());
        }
    }

    void print_preorder()
    {
        print_preorder(root);
        std::cout << std::endl;
    }

    bool are_siblings(T val, T val2)
    {
        BTreeNode<T> *ptr = find_parent(val);

        if ((ptr->get_left()->get_val() == val && ptr->get_right()->get_val() == val2) || (ptr->get_left()->get_val() == val2 && ptr->get_right()->get_val() == val))
            return true;

        return false;
    }

    void same_level_nodes(T val)
    {
        BTreeNode<T> *ptr = find_parent(val);
        BTreeNode<T> *prev = find_parent(ptr->get_val());
        std::cout << ptr->get_left()->get_val() << ", ";
        std::cout << ptr->get_right()->get_val() << ", ";
        if (prev->get_left() == ptr)
        {
            std::cout << prev->get_right()->get_left()->get_val() << ", ";
            std::cout << prev->get_right()->get_right()->get_val() << ", ";
        }
        else
        {
            std::cout << prev->get_left()->get_left()->get_val() << ", ";
            std::cout << prev->get_left()->get_right()->get_val() << std::endl;
        }
        std::cout << std::endl;
    }

    bool is_ancestor(T val, T val2)
    {
        BTreeNode<T> *ptr = root;
        while (ptr != NULL)
        {
            if (ptr->get_val() == val)
                return true;

            ptr = ptr->get_val() > val2 ? ptr->get_left() : ptr->get_right();
        }

        return false;
    }

    bool is_descendant(T val, T val2)
    {
        BTreeNode<T> *ptr = find(val2);
        while (ptr != NULL)
        {
            if (ptr->get_val() == val)
                return true;

            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }

        return false;
    }

    void ancestors(T val)
    {
        BTreeNode<T> *ptr = root;
        while (ptr != NULL)
        {
            std::cout << ptr->get_val() << ", ";
            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }

        std::cout << std::endl;
    }

    void descendants(T val)
    {
        BTreeNode<T> *ptr = find(val);
        print_preorder(ptr);
        std::cout << std::endl;
    }

    int depth(T val)
    {
        BTreeNode<T> *ptr = root;
        int count = 0;
        while (ptr != NULL)
        {
            if (ptr->get_val() == val)
                return count;

            count++;
            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }
        return -1;
    }

    void print_var1(std::string prefix, BTreeNode<T> *node, bool isLeft)
    {
        if(node != NULL)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            std::cout << node->get_val() << std::endl;
            
            print_var1( prefix + (isLeft ? "│   " : "    "), node->get_left(), true);
            print_var1( prefix + (isLeft ? "│   " : "    "), node->get_right(), false);
        }
    }

    void print_inorder_reverse(BTreeNode<T> *node)
    {
        if(node != NULL){
            print_inorder_reverse(node->get_right());
            cout << node->get_val().second << ": " << node->get_val().first << endl;
            print_inorder_reverse(node->get_left());
        }
    }

    void print_inorder_reverse()
    {
        print_inorder_reverse(root);
        cout << endl;
    }

    void inorder_reverse_vector(BTreeNode<T> *node)
    {
        if(node != NULL){
            inorder_reverse_vector(node->get_right());
            v_inorder.push_back(make_pair(node->get_val().first, node->get_val().second));
            inorder_reverse_vector(node->get_left());
        }
    }

    void inorder_reverse_vector()
    {
        inorder_reverse_vector(root);
    }

    vector<T> get_inorder_vector() { return v_inorder; }
};