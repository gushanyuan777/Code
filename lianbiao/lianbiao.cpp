#include <iostream>  
  
template <class T>  
class SingleLinkedList {  
private:  
    struct Node {  
        T data;  
        Node* next;  
        Node(const T& _data) : data(_data), next(nullptr) {}  
    };  
    Node* head;  
    Node* current;  
  
public:  
    SingleLinkedList() : head(nullptr), current(nullptr) {}  
    SingleLinkedList(const std::initializer_list<T>& values) : head(nullptr), current(nullptr) {  
        for (const T& val : values) {  
            insert(val);  
        }  
    }  
  
    T getCurrentVal() const {  
        if (current == nullptr) {  
            throw std::runtime_error("Empty current position! Can't get value!");  
        }  
        return current->data;  
    }  
  
    void setCurrentVal(const T& _val) {  
        if (current == nullptr) {  
            throw std::runtime_error("Empty current position! Can't set value!");  
        }  
        current->data = _val;  
    }  
  
    bool isEmpty() const {  
        return head == nullptr;  
    }  
  
    void insert(T _val) {  
        if (isEmpty()) {  
            head = new Node(_val);  
            current = head;  
        } else {  
            Node* newNode = new Node(_val);  
            newNode->next = current->next;  
            current->next = newNode;  
        }  
    }  
  
    void remove() {  
        if (current != nullptr) {  
            if (head == current) {  
                head = current->next;  
                delete current;  
                current = head;  
            } else {  
                Node* temp = head;  
                while (temp != nullptr && temp->next != current) {  
                    temp = temp->next;  
                }  
                if (temp != nullptr) {  
                    temp->next = current->next;  
                    delete current;  
                    current = temp->next;  
                }  
            }  
        }  
    }  
  
    void printList() {  
        Node* temp = head;  
        while (temp != nullptr) {  
            std::cout << temp->data << " ";  
            temp = temp->next;  
        }  
        std::cout << std::endl;  
    }  
};