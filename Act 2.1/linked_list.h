/* 
Header file for class Node and class Linked List
Enrique Mondelli A01379363
Date created:   10/01/2020
Date Modified:  10/04/2020
*/

#pragma once

#include <stddef.h>
#include <iostream>

template <class T>
class Node
{
private:
    T val;
    Node<T> *next;

public:
    ~Node<T>(){};
    Node<T>(T pVal, Node<T> *pNext)
    {
        val = pVal;
        next = pNext;
    }

    T get_val() { return val; }
    void set_val(T pVal) { val = pVal; }
    Node<T> *get_next() { return next; }
    void set_next(Node<T> *pNext) { next = pNext; }
};

template <class T>
class LinkedList
{
protected:
    Node<T> *head;

public:
    ~LinkedList()
    {
        Node<T> *prev = NULL;
        Node<T> *ptr = head;
        while (ptr != NULL)
        {
            prev = ptr;
            delete prev;
            ptr = ptr->get_next();
        }
        delete ptr;
        head = NULL;
    }

    LinkedList()
    {
        head = NULL;
    }

    void print()
    {
        if (is_empty())
            std::cout << "List is empty";

        else
        {
            Node<T> *ptr = head;
            while (ptr != NULL)
            {
                std::cout << ptr->get_val() << ", ";
                ptr = ptr->get_next();
            }
        }

        std::cout << std::endl;
    }

    int length()
    {
        Node<T> *ptr = head;
        int count = 0;
        while (ptr != NULL)
        {
            count++;
            ptr = ptr->get_next();
        }

        return count;
    }

    void push(T pVal)
    {
        Node<T> *node = new Node<T>(pVal, head);
        head = node;
    }

    void append(T pVal)
    {
        Node<T> *ptr = head;
        while (ptr->get_next() != NULL)
        {
            ptr = ptr->get_next();
        }
        Node<T> *node = new Node<T>(pVal, NULL);
        ptr->set_next(node);
    }

    int insert_item(T pVal, int index)
    {
        if (index > length() || index < 0)
            return -1;

        if (index == 0)
        {
            push(pVal);
            return 1;
        }

        int i = 0;
        Node<T> *ptr = head;
        Node<T> *prev = NULL;
        while (ptr != NULL && i < index)
        {
            i++;
            prev = ptr;
            ptr = ptr->get_next();
        }
        Node<T> *node = new Node<T>(pVal, ptr);
        prev->set_next(node);
        return 1;
    }

    bool is_empty()
    {
        return head == NULL;
    }

    int delete_item(int index)
    {
        if (index >= length() || index < 0 || is_empty())
            return -1;

        if (index == 0)
        {
            Node<T> *temp = head;
            head = head->get_next();
            delete temp;
            return 1;
        }

        int i = 0;
        Node<T> *ptr = head;
        Node<T> *prev = NULL;
        while (ptr->get_next() != NULL && i < index)
        {
            prev = ptr;
            ptr = ptr->get_next();
            i++;
        }
        prev->set_next(ptr->get_next());
        delete ptr;
        return 1;
    }

    int get_nth(int index, T &item)
    {
        if (index >= length() || index < 0)
            return -1;

        int i = 0;
        Node<T> *ptr = head;
        while (ptr->get_next() != NULL && i < index)
        {
            ptr = ptr->get_next();
            i++;
        }
        item = ptr->get_val();
        return 1;
    }

    int count(T search)
    {
        Node<T> *ptr = head;
        int count = 0;
        while (ptr != NULL)               // loop that cycles a pointer through each node in the list.
        {                                 // if the current element the pointer is pointing to
            if (ptr->get_val() == search) // has the same value as what is being searched for
                count++;                  // increase counter by one.

            ptr = ptr->get_next(); // increment the pointer to the next node.
        }

        return count;
    } // O(n)

    void delete_list()
    {
        std::cout << "Deleting Linked List...\n";
        Node<T> *ptr = head;
        Node<T> *next = NULL;
        while (ptr != NULL) // loop that cycles a pinter through each node in the list
        {
            next = ptr->get_next(); // saves the node after the current node
            delete ptr;             // deletes the node the pointer is currently pointing to
            ptr = next;             // increments the pointer to the next node
        }
        head = NULL; // since the list is empty head now has to be NULL;
        std::cout << "Done\n";

    } // O(n)

    int sorted_insert(Node<T> *newNode)
    {
        Node<T> *ptr = head;
        if (newNode->get_val() <= ptr->get_val()) // if the value of the given node is less than or equal to
        {                                         // the first element in the list
            push(newNode->get_val());             // add element to the beggining of the list.
            return 1;
        }

        Node<T> *prev = NULL;
        while (ptr->get_val() < newNode->get_val()) // loop that cycles a pointer through each node in the list as long as the
        {                                           // element the pointer is pointing to is less than the value of the node being inserted.
            prev = ptr;                             // saves current node the pointer is pointing to.
            ptr = ptr->get_next();                  // increments the pointer to the next node.
        }
        newNode->set_next(ptr);  // makes the node being insterted point to the current node.
        prev->set_next(newNode); // makes the previous node point to the new node.
        return 1;
    } // O(n)

    int remove_duplicates()
    {
        if (length() <= 1) // if the list has 1 or less nodes
            return -1;     // return -1 because there can't be duplicates

        Node<T> *ptr = head;
        Node<T> *next_next = NULL;      // node to save 2 nodes ahead of the current pointer
        while (ptr->get_next() != NULL) // loop that cycles a pointer pointing to each node in the list.
        {
            if (ptr->get_val() == ptr->get_next()->get_val()) // if the value of the current node is the same as the next node
            {
                next_next = ptr->get_next()->get_next(); // saves 2 nodes ahead of the current node.
                delete ptr->get_next();                  // deletes the node after the current node.
                ptr->set_next(next_next);                // makes the current node point to the previously established next_next node.
            }
            else
            { // if the previous block of code doesn't happen then just increment the pointer to the next node.
                ptr = ptr->get_next();
            }
        }

        return 1;
    } // O(n)

    int unsorted_remove_duplicates()
    {
        if (length() <= 1)
            return -1;

        int i = 0, j = 1;
        Node<T> *ptr = head;
        Node<T> *ptr2 = ptr->get_next();
        while (ptr->get_next() != NULL)
        {

            while (ptr2 != NULL)
            {
                if (ptr->get_val() == ptr2->get_val())
                {
                    delete_item(j);
                    j--;
                }
                ptr2 = ptr2->get_next();
                j++;
            }

            ptr = ptr->get_next();
            ptr2 = ptr->get_next();
            i++;
            j = i + 1;
        }

        return 1;
    } // O(n^2)

    int reverse()
    {
        if (is_empty()) // if the list is empty
            return -1;  // return -1 because an empty list can't be reversed

        if (length() == 1) // if the list has 1 or less nodes
            return 1;      // return 1 because the reversed list is the same as the current list

        Node<T> *ptr = head;
        Node<T> *prev = NULL; // node to save the previous node.
        Node<T> *next = NULL; // node to save the next node.
        while (ptr != NULL)   // loop that cycles a pointer through each node in the list.
        {
            next = ptr->get_next(); // saves the node after the current node.
            ptr->set_next(prev);    // makes the current node point to the previous node.
            prev = ptr;             // prevous is now current node.
            ptr = next;             // increments the pointer to the next node.
        }
        head = prev; // makes the pointer of the beginning of the list point to the
                     // prevoius node which is now the actual beginning of the list
        return 1;
    } // O(n)
};