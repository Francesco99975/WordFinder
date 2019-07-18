/*
    @Author: Francesco Michele Barranca
    Date: 05/29/2018
    Description: Singly Linked List, an Abstract Data Type
    capable of storing large numbers of data of any type.
*/


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>

using namespace std;

namespace sll
{
    template<class T>
    struct Node
    {
        T data;
        Node<T>* next;
    };

    template<class T>
    class LinkedList
    {
        Node<T>* head;
        Node<T>* tail;
        unsigned int size;

            public:
                LinkedList<T>()
                {
                    head = NULL;
                    tail = NULL;
                    size = 0;
                }

                void enqueue(T val)
                {
                    Node<T>* temp = new Node<T>;
                    temp->data = val;
                    temp->next = this->head;
                    this->head = temp;
                    this->size++;
                }

                void push(T val)
                {
                    if(!this->head)
                    {
                        this->head = new Node<T>;
                        this->head->data = val;
                        this->head->next = NULL;
                        this->tail = this->head;
                    }
                    else
                    {
                        if(this->tail == this->head)
                        {
                            this->tail = new Node<T>;
                            this->tail->data = val;
                            this->tail->next = NULL;
                            this->head->next = this->tail;
                        }
                        else
                        {
                            Node<T>* insdata = new Node<T>;
                            insdata->data = val;
                            insdata->next = NULL;
                            this->tail->next = insdata;
                            this->tail = insdata;
                        }
                    }
                    this->size++;
                }

                void addAt(T val, int pos)
                {
                    Node<T>* pre = new Node<T>;
                    Node<T>* cur = new Node<T>;
                    Node<T>* temp = new Node<T>;

                    cur = this->head;
                        for(int i = 0; i < pos; i++)
                        {
                            pre = cur;
                            cur = cur->next;
                        }
                            temp->data = val;
                            pre->next = temp;
                            temp->next = cur;
                            this->size++;
                }

                T dequeue()
                {
                    T rt;
                    Node<T>* temp = new Node<T>;
                    temp = this->head;
                    this->head = this->head->next;
                    rt = temp->data;
                    delete temp;
                    this->size--;

                    return rt;
                }

                T pop()
                {
                    T rt;
                    Node<T>* cur = new Node<T>;
                    Node<T>* pre = new Node<T>;

                    cur = this->head;
                        while(cur->next != NULL)
                        {
                            pre = cur;
                            cur = cur->next;
                        }
                            rt = cur->data;
                            this->tail = pre;
                            pre->next = NULL;
                            delete cur;
                            this->size--;

                    return rt;
                }

                T deleteAt(int pos)
                {
                    T rt;
                    Node<T>* cur = new Node<T>;
                    Node<T>* pre = new Node<T>;

                    cur = this->head;
                        for(int i = 1; i <= pos; i++)
                        {
                            pre = cur;
                            cur = cur->next;
                        }
                            rt = cur->data;
                            pre->next = cur->next;
                            this->size--;

                    return rt;
                }

                T& get(int index)
                {
                    if(index == 0)
                        return this->head->data;
                    else
                    {
                        Node<T>* cur = this->head;
                            for(int i = 0; i < index; i++)
                                cur = cur->next;

                                return cur->data;
                    }
                }

                T& operator[](int index)
                {
                    return this->get(index);
                }

                void show() const
                {
                    Node<T>* temp = new Node<T>;
                    temp = this->head;
                    cout << "[ ";
                        while(temp != NULL)
                        {
                            cout << temp->data << (temp->next != NULL ? " - " : " ]\n");
                            temp = temp->next;
                        }
                }

                void showVert() const
                {
                    Node<T>* temp = new Node<T>;
                    temp = this->head;
                        while(temp != NULL)
                        {
                            cout << temp->data << endl;
                            temp = temp->next;
                        }
                }


                T* toArray()
                {
                    T* arr = new T[this->size];
                    Node<T>* tmp = new Node<T>;
                    tmp = this->head;
                    int i = 0;
                        while(tmp != NULL)
                        {
                            arr[i] = tmp->data;
                            i++;
                            tmp = tmp->next;
                        }
                    return arr;
                }

                bool isEmpty() const
                {
                    return (this->head == NULL);
                }

                unsigned int length() const
                {
                    return this->size;
                }
    };
}

#endif // LINKEDLIST_H
