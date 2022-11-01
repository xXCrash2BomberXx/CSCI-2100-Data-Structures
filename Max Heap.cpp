#include <iostream>
#include <cmath>
#include <vector>

template <typename T>
class MaxHeap {
  private:
    std::vector<T> vec;
    int size {0};
  public:
    void percolate (int x, int y) {
      if (getIndex(x, y) > getIndex(x/2, y-1)) {  // if child > parent
        T temp {getIndex(x/2, y-1)};  // copy parent
        setIndex(x/2, y-1, getIndex(x, y));  // swap child with parent
        setIndex(x, y, temp);
        if (y >= 1)
          percolate(x/2, y-1);  // test again with new parent
      }
    }
    void depercolate () {
      for (int y {getHeight()}; y > 0; y--) {
        for (int x {0}; x < std::pow(2, y); x++) {
          if (getIndex(x, y) > getIndex(x/2, y-1)) {  // if child > parent
            T temp {getIndex(x/2, y-1)};  // copy parent
            setIndex(x/2, y-1, getIndex(x, y));  // swap parent with child
            setIndex(x, y, temp);
            depercolate();  // repeat until no changes
          }
        }
      }
    }
    void insert (T value) {
      int y {getHeight()};
      int x {size};
      for (int i {0}; i < y; i++) {
        x -= std::pow(2, i);
      }
      vec.push_back(value);
      size++;
      percolate(x, y);
    }
    void remove () {
      if (size == 0) {
        std::cout << "Cannot remove from empty heap\n";
        return;
      }
      size--;
      vec[0] = vec[size];
      vec.pop_back();
      depercolate();
    }
    int getHeight() const {  // height of tree
      if (size == 0 || size == 1)
        return 0;
      else
        return std::floor(std::log2(size-1)+1);
    }
    int toIndex (int x, int y) const {  // convert 2d index to 1d index
      int index {0};
      for (int i {0}; i < y; i++) {
        index += std::pow(2, i);
      }
      return index+x;
    }
    T getIndex (int x, int y) const {  // get value at 2d index
      int index {toIndex(x, y)};
      return (index<size&&index>=0?vec[index]:NULL);
    }
    void setIndex (int x, int y, T value) {  // change value at 2d index
      vec[toIndex(x, y)] = value;
    }
    void print () const {
      std::cout << "[\n";
      for (int y {0}; y < std::ceil(std::log2(size-1)+1); y++) {
        for (int x {0}; x < std::pow(2, y); x++) {
          std::cout << getIndex(x, y) << " ";
        }
        std::cout << "\n";
      }
      std::cout << "]\n";
      std::cout << "[ ";
      for (auto i: vec) {
        std::cout << i << " ";
      }
      std::cout << "]\n";
    }
};

int main() {
  MaxHeap<int> mhi;
  std::cout << "-- int --" << std::endl;
  mhi.insert(88);
  mhi.insert(80);  // add new min
  mhi.insert(33);  // add new min
  mhi.insert(55);  // add middle
  mhi.print();
  mhi.insert(20);  // add new min
  mhi.print();
  mhi.remove();  // remove max; remove after insert min
  mhi.print();
  mhi.insert(90);  // add new max; insert after remove
  mhi.print();
  mhi.remove();  // remove max; remove after insert max
  mhi.remove();  // remove
  mhi.remove();  // remove
  mhi.remove();  // remove
  mhi.print();
  mhi.remove();  // remove final element
  mhi.print();
  mhi.remove();  // remove from empty

  std::cout << "-- char --" << std::endl;
  MaxHeap<char> mhc;
  mhc.insert('a');
  mhc.insert('b');
  mhc.insert('c');
  mhc.insert('d');
  mhc.insert('e');
  mhc.print();
  mhc.remove();
  mhc.print();
}
