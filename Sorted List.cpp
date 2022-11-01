#include <iostream>
#include <string>

template <typename T>
class LinkedList {
  protected:
    struct Node {
      T value;
      Node* next;
    };
    int _size {0};
    Node* _head;

  public:
    void add (T value, int index=-1) {
      if (index == -1)  // add to end by default
        index = _size;
      Node* temp {_head};
      for (int i {0}; i < index-1; i++) {  // get node to add after
        temp = temp->next;
      }
      Node* temp2 = new Node();  // create new node
      temp2->value = value;
      if (index != 0) {
        temp2->next = temp->next;
        temp->next = temp2;
      } else {
        temp2->next = _head;
        _head = temp2;
      }
      _size++;
    }

    void remove (T value, bool sorted=false) {
      if (_head == nullptr)  // empty list
        return;
      Node* temp {_head};
      if (_head->value == value) {  // remove head
        temp = _head->next;
        delete _head;  // delete old head
        if (_size == 1)
          _head = nullptr;  // empty list
        else
          _head = temp;  // new head
        _size--;
        return;
      } else {  // remove other
        for (int i {0}; i < _size-1; i++) {
          if (temp->next->value == value) {  // find node with next node matching value
            Node* del {temp->next};  // node to be deleted
            temp->next = del->next;  // remove links to deleted node
            delete del;  // delete node
            _size--;
            return;
          } else {
            temp = temp->next;
            if (sorted && temp->value > value)  // break early when sorted
              break;
          }
        }
        std::cout << "Cannot remove\n";
        return;
      }
    }

    T pop (int index) {
      if (index >= _size) {
        std::cout << "Index Error\n";
        return (int) NULL;
      } else {
        Node* temp {_head};
        for (int i {0}; i < index-1; i++) {  // iterate to end of list-1
          temp = temp->next;
        }
        Node* del {temp->next};
        T value = del->value;
        temp->next = del->next;
        delete del;  // delete last element
        _size--;
        return value;  // return removed value
      }
    }

    bool contains (T value) const {
      if (_head == nullptr)  // empty list
        return false;
      Node* temp {_head};
      for (int i {0}; i < _size; i++) {
        if (temp->value == value) {
          return true;
        } else {
          temp = temp->next;
        }
      }
      return false;
    }

    int size () const {
      return _size;
    }

    void print () const {
      Node* temp {_head};
      std::cout << "[ ";
      for (int i {0}; i < _size; i++) {
        std::cout << temp->value << " ";
          temp = temp->next;
      }
      std::cout << "]\n";
    }

    T operator[] (int index) const {
      if (index >= _size || index < -_size ) {  // index out of range
        std::cout << "Index Error\n";
        return;
      } else if (index == 0) {  // return first value
        return _head->value;
      } else if (index > 0) {
        index = ((index %= _size) < 0) ? index+_size: index;
        Node* temp {_head};
        for (int i {0}; i < index; i++) {  // iterate to index
          temp = temp->next;
        }
        return temp->value;
      }
    }
};

template <typename T>
class SortedList: public LinkedList<T> {
  public:
    void add (T value) {
      struct LinkedList<T>::Node* temp = new struct LinkedList<T>::Node();  // create new node
      temp->value = value;
      if (LinkedList<T>::_head == nullptr) {  // add to empty list
        LinkedList<T>::_head = temp;
      } else if (value < LinkedList<T>::_head->value) {  // add to beginning
        temp->next = LinkedList<T>::_head;
        LinkedList<T>::_head = temp;
      } else {  // other
        struct LinkedList<T>::Node* temp2 {LinkedList<T>::_head};
        while (temp2->next != nullptr && value > temp2->next->value) {
          temp2 = temp2->next;
        }
        temp->next = temp2->next;
        temp2->next = temp;
      }
      LinkedList<T>::_size++;
    }
  void remove (T value) {
    LinkedList<T>::remove(value, true);
  }
};

int main() {
  LinkedList<int> l;
  l.add(2);  // [2]
  l.add(5);  // [2, 5]
  l.add(7);  // [2, 5, 7]
  l.print();
  std::cout << l.size() << "\n";  // 3
  std::cout << l.contains(2) << "\n";  // 1
  l.remove(7);  // [2, 5]
  l.print();
  l.remove(2);  // [5]
  l.print();
  std::cout << l.contains(2) << "\n";  // 0
  l.remove(2);  // Cannot remove
  l.remove(5);  // []
  l.print();
  l.add(1, 0);  // [1]
  l.add(2, 1);  // [1, 2]
  l.add(4, 2);  // [1, 2, 4]
  l.print();
  l.add(3, 2);  // [1, 2, 3, 4]
  l.print();
  std::cout << l.pop(3) << std::endl;  // 4; [1, 2, 3]
  l.print();

  SortedList<int> l2;
  l2.add(2);  // [2]
  l2.add(1);  // [1, 2]
  l2.add(3);  // [1, 2, 3]
  l2.add(0);  // [0, 1, 2, 3]
  l2.add(4);  // [0, 1, 2, 3, 4]
  l2.print();
  l2.remove(5);  // Cannot remove
  l2.remove(3);  // [0, 1, 2, 4]
  l2.remove(0);  // [1, 2, 4]
  l2.remove(4);  // [1, 2]
  l2.remove(1);  // [2]
  l2.remove(2);  // []
  l2.print();
}
