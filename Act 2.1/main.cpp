/* 
Main file to show off the newly implemented Linked List methods:
count(), delete_list(), sorted_insert(), remove_duplicates() and reverse()
Enrique Mondelli A01379363
Date Created:    10/01/2020
Date Modified:   10/04/2020
*/

#include "linked_list.h"

using namespace std;

int main()
{
    int item;
    LinkedList<int> list;
    list.push(8);
    list.push(5);
    list.push(3);
    list.push(2);
    list.push(1);
    cout << "Orignial Linked List:\n";
    list.print();
    Node<int> *node5 = new Node<int>(5, NULL);
    list.sorted_insert(node5);
    Node<int> *node1 = new Node<int>(1, NULL);
    list.sorted_insert(node1);
    Node<int> *node0 = new Node<int>(0, NULL);
    list.sorted_insert(node0);
    Node<int> *node4 = new Node<int>(4, NULL);
    list.sorted_insert(node4);
    Node<int> *node7 = new Node<int>(7, NULL);
    list.sorted_insert(node7);
    Node<int> *node6 = new Node<int>(6, NULL);
    list.sorted_insert(node6);
    cout << "Linked List with sort insterted nodes:\n";
    list.print();
    cout << "Number of times a '5' appears in the Linked List: " << list.count(5) << endl;
    list.remove_duplicates();
    cout << "Linked List with duplicates removed:\n";
    list.print();
    list.reverse();
    cout << "Reversed Linked List:\n";
    list.print();
    list.delete_list();
    cout << "print() method called after Linked List has been deleted:\n";
    list.print();

    delete node0, node1, node4, node5, node6, node7;
    return 0;
}