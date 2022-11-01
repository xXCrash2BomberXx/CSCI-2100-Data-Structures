#include <iostream>
#include <vector>

template <typename T>
class Deque {
  private:
    int size {0};
    int front {-1};
    int back {-1};
    std::vector<T> vec;
  public:
    void push_back (T value) {
      if (size+1 > vec.capacity())
        resize();
      if (back == -1 && front == -1) {  // empty
        back = 0;
        front = 0;
      } else
        back++;
      size++;
      vec[back] = value;
    }
    void push_front (T value) {
      if (size+1 > vec.capacity())
        resize();
      if (front == -1 && back == -1) {  // empty
        front = 0;
        back = 0;
      } else
        front--;
      size++;
      vec[front>=0?front:vec.size()+front] = value;
    }
    void pop_back () {
      if (size <= 0) {
        std::cout << "Index Error: pop from empty list" << std::endl;
        return;
      }
      size--;
      if (size <= 0) {
        front = -1;
        back = -1;
      } else {
        back--;
      }
    }
    void pop_front () {
      if (size <= 0) {
        std::cout << "Index Error: pop from empty list" << std::endl;
        return;
      }
      size--;
      if (size <= 0) {
        front = -1;
        back = -1;
      } else {
        front++;
      }
    }
    void resize (int space=-1) {
      std::vector<T> c;
      if (space == -1)
        c.reserve(vec.capacity()==0?1:vec.capacity()*2);
      else
        c.reserve(space);
      for (int i {0}; i < c.capacity(); i++) {
        if (i < size) {
          c.push_back(vec[(i+size+front)%size]);
        } else {
          c.push_back((T) NULL);
        }
      }
      vec = c;
      front = 0;
      back = size-1;
    }
    void print () const {
      std::cout << "Size: " << size << " Front: " << front << " Back: " << back << std::endl;
      std::cout << "Visual: [ ";
      if (size > 0)
        for (int i {front}; i <= back; i++) {
          std::cout << (*this)[i] << " ";
        }
      std::cout << "]" << std::endl;
      std::cout << "Actual: [ ";
      for (int i {0}; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
      }
      std::cout << "]" << std::endl;
    }
    T operator[] (int index) const {
      return vec[index>=0?index:vec.size()+index];
    }
    bool empty () const {
      return (size == 0);
    }
};

int main() {
  Deque<int> d;
  d.push_back(3);  // [3]
  d.push_back(4);  // [3, 4]
  d.push_back(5);  // [3, 4, 5]
  d.push_front(2);  // [2, 3, 4, 5]
  d.push_back(6);  // [2, 3, 4, 5, 6]
  d.push_front(1);  // [1, 2, 3, 4, 5, 6]
  d.print();
  d.pop_front();  // [2, 3, 4, 5, 6]
  d.pop_front();  // [3, 4, 5, 6]
  d.pop_front();  // [4, 5, 6]
  d.pop_front();  // [5, 6]
  d.pop_front();  // [5]
  d.pop_front();  // []
  d.print();
  d.push_front(3);  // [3]
  d.push_front(4);  // [4, 3]
  d.push_front(5);  // [5, 4, 3]
  d.push_back(2);  // [5, 4, 3, 2]
  d.push_front(6);  // [6, 5, 4, 3, 2]
  d.push_back(1);  // [6, 5, 4, 3, 2, 1]
  d.print();
  d.pop_back();  // [6, 5, 4, 3, 2]
  d.pop_back();  // [6, 5, 4, 3]
  d.pop_back();  // [6, 5, 4]
  d.pop_back();  // [6, 5]
  d.pop_back();  // [6]
  d.pop_back();  // []
  d.print();
  d.pop_back();
  d.pop_front();
  
}
