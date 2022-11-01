
#include <memory>
#include <iostream>
//namespace csci2100 {
template <typename ItemType> 
class BinarySearchTree {
protected:
  class Node {
    private:
      ItemType _data;
      std::unique_ptr<Node> _left{nullptr}, _right{nullptr};
      Node *_parent{nullptr};
      int _height{0};
      int _numSubNodes{0};
    public:
      Node(ItemType data, std::unique_ptr<Node> left,
                     std::unique_ptr<Node> right,
                     Node *parent)
          : _data(data), _left(std::move(left)), _right(std::move(right)),
            _parent(parent) {}
      ItemType getData() const { return _data; }
      
      void setData(ItemType d) { _data = d; }
      
      int getHeight() const { return _height; }
      
      int getNumSubNodes() const {return _numSubNodes; }
  
      
      void setHeight(int h) { _height = h; }
      Node *getLeft() const { return _left.get(); }
      Node *getRight() const { return _right.get(); }
      Node *getParent() const { return _parent; }
      std::unique_ptr<Node> acquireLeft() { return std::move(_left); }
      std::unique_ptr<Node> acquireRight() { return std::move(_right); }
      
      void setNumSubNodes(int newSubNodes){
       _numSubNodes = newSubNodes;
    }
      void setLeft(std::unique_ptr<Node> newLeft) {
        _left = std::move(newLeft);
      }
      void setRight(std::unique_ptr<Node> newRight) {
        _right = std::move(newRight);
      }
      void setParent(Node *newParent) { _parent = newParent; }   
      
      std::unique_ptr<Node>& getLeftLink() { return _left; }
      
      std::unique_ptr<Node>& getRightLink() { return _right; }
  };
  
public:
  class InternalIterator {
    private:
      Node* _position{nullptr};
      BinarySearchTree& _tree;
      
    public:
      InternalIterator(Node* pos, BinarySearchTree& t) : _position(pos), _tree(t) {
}
    
      ItemType getData() const { return _position->getData(); }
      bool isNode() const { return  _position != nullptr; }
      bool isRoot() const { return _position->getParent() == nullptr; }
      bool isLeaf() const { return _position->getLeft() == nullptr && _position->getRight() == nullptr; }
      bool hasRightChild() const { return _position->getRight() != nullptr; }
      bool hasLeftChild() const { return _position->getLeft() != nullptr; }
      
      int getHeight() const { return _position->getHeight(); }
      void setHeight(int h) { _position->setHeight(h); }
      
      void up() { _position = _position->getParent(); }
      void left() { _position = _position->getLeft(); }
      void right() { _position = _position->getRight(); }
      
      bool operator==(const InternalIterator other) { return  _position == other._position; }
    
      void addLeftChild(ItemType data) {
        _position->setLeft(std::make_unique<Node>(data, nullptr, nullptr, _position));
        _tree._size++;
        _tree._updateHeights(_position);
      }
      
      void addRightChild(ItemType data) {
        _position->setRight(std::make_unique<Node>(data, nullptr, nullptr, _position)); 
        _tree._size++;
        _tree._updateHeights(_position);
      }
      
      std::unique_ptr<Node>& getLeftLink() {
        return _position->getLeftLink();
      }
      
      std::unique_ptr<Node>& getRightLink() {
        return _position->getRightLink();
      }
      
      void rotateRight() {
        if (isRoot()) _tree._rotateRight(_tree._root);
        else if (_position->getParent()->getLeft() == _position) 
_tree._rotateRight(_position->getParent()->getLeftLink());
        else _tree._rotateRight(_position->getParent()->getRightLink());
        
        _tree._updateHeights(_position);
      }
      
      void rotateLeft() {
        if (isRoot()) _tree._rotateLeft(_tree._root);
        else if (_position->getParent()->getLeft() == _position) 
_tree._rotateLeft(_position->getParent()->getLeftLink());
        else _tree._rotateLeft(_position->getParent()->getRightLink());
        
        _tree._updateHeights(_position);
      }
    };
protected:
  std::unique_ptr<Node> _root{nullptr};
  int _size{0};  
public:
  BinarySearchTree() { }
  
  int size() const { return _size; }
  bool empty() const { return _size == 0; }
  void clear() { _root = nullptr; }
  
  InternalIterator root() { return InternalIterator(_root.get(), *this); }
  
  void createRoot(ItemType data) {
    _root = std::make_unique<Node>(data, nullptr, nullptr, nullptr);
    _size = 1;
  }

  void insert(ItemType data) {
    if (_root == nullptr) {
      createRoot(data); 
    } else {
      InternalIterator loop {root()};
      while (true) {
        if (loop.getData() >= data) {
          if (loop.hasLeftChild()) {
            loop.left();
          } else {
            loop.addLeftChild(data);
            return;
          }
        } else {
          if (loop.hasRightChild()) {
            loop.right();
          } else {
            loop.addRightChild(data);
            return;
          }
        }
      }
      loop.addLeftChild(data);
    }
  }

  void _rotateRight(std::unique_ptr<Node>& link) {
    std::unique_ptr<Node> original = std::move(link);
    std::unique_ptr<Node> left = original->acquireLeft();
    std::unique_ptr<Node> t1 = left->acquireLeft();
    std::unique_ptr<Node> t2 = left->acquireRight();
    std::unique_ptr<Node> t3 = original->acquireRight();    
    
    if (t1 != nullptr) t1->setParent(left.get());
    left->setLeft(std::move(t1));
        
    if (t2 != nullptr) t2->setParent(original.get());
    original->setLeft(std::move(t2));
    
    if (t3 != nullptr) t3->setParent(original.get());
    original->setRight(std::move(t3));
    
    if (original->getParent() == nullptr)
      left->setParent(nullptr);
    else 
      left->setParent(original->getParent());
      
    original->setParent(left.get());
    left->setRight(std::move(original));
    link = std::move(left);
  }
  
  void _rotateLeft(std::unique_ptr<Node>& link) {
    std::unique_ptr<Node> original = std::move(link);
    std::unique_ptr<Node> right = original->acquireRight();
    std::unique_ptr<Node> t1 = original->acquireLeft();
    std::unique_ptr<Node> t2 = right->acquireLeft();
    std::unique_ptr<Node> t3 = right->acquireRight();    
    
    if (t1 != nullptr) t1->setParent(original.get());
    original->setLeft(std::move(t1));
        
    if (t2 != nullptr) t2->setParent(original.get());
    original->setRight(std::move(t2));
    
    if (t3 != nullptr) t3->setParent(right.get());
    right->setRight(std::move(t3));
    
    if (original->getParent() == nullptr)
      right->setParent(nullptr);
    else 
      right->setParent(original->getParent());
      
    original->setParent(right.get());
    right->setLeft(std::move(original));
    link = std::move(right);
  }
  
  void _updateHeights(Node *location) {
    int h{0};
    if (location->getLeft() != nullptr)
      h = location->getLeft()->getHeight() + 1;
    if (location->getRight() != nullptr) {
      int r = location->getRight()->getHeight() + 1;
      if (r > h)
        h = r;
    }
    location->setHeight(h);
    
    if (location->getParent() != nullptr)
      _updateHeights(location->getParent());
  }

  int count (Node* node) const {
    if (node == nullptr)
      return 0;
    return 1+count(node->getLeft())+count(node->getRight());
  }
  ItemType getMedian () const {
    if (count(_root.get()) % 2 == 0) {
      std::cout << "MultipleMedianError\nMedians: ";
    }
    if (_root == nullptr) {  // no nodes to count
      std::cout << "Cannot get median of empty tree\n";
      return (ItemType) NULL;
    } else {  // count nodes on each side
      int passLeft {0};  // nodes passed on left
      int passRight {0};  // nodes passed on right
      int countLeft, countRight;
      Node* currNode {_root.get()};  // current node
      while (currNode != nullptr) {
        countLeft = count(currNode->getLeft());  // nodes on left
        countRight = count(currNode->getRight());  // nodes on right
        if (std::abs((countLeft+passLeft)-(countRight+passRight)) == 1) {
          std::cout << currNode->getData() << " ";  // found a median of MultipleMedianError
        }
        if (std::abs((countLeft+passLeft)-(countRight+passRight)) >= 1) {  // still unbalanced
          if (countLeft+passLeft > countRight+passRight) {  // heavy on left
            passRight += countRight+1;  // add passed nodes + current node
            currNode = currNode->getLeft();
          } else {  // heavy on right
            passLeft += countLeft+1;  // add passed nodes + current node
            currNode = currNode->getRight();  // move right
          }
        } else {
          return currNode->getData();
        }
      }
      std::cout << "\n";  // only runs if no true median
      return (ItemType) NULL;  // only runs if no true median
    }
  }
};


int main() {
  BinarySearchTree<char> bst_c;
  bst_c.insert('d');
  bst_c.insert('e');
  bst_c.insert('b');
  bst_c.insert('a');
  bst_c.insert('c');
  char median {bst_c.getMedian()};
  std::cout << "Median: " << median << "\n" << std::endl;  // c

  BinarySearchTree<int> bst_i;
  bst_i.insert(5);
  bst_i.insert(3);
  bst_i.insert(9);
  bst_i.insert(1);
  bst_i.insert(4);
  bst_i.insert(8);
  bst_i.insert(11);
  bst_i.insert(-3);
  bst_i.insert(2);
  bst_i.insert(7);
  bst_i.insert(12);
  int median2 {bst_i.getMedian()};
  std::cout << "Median: " << median2 << "\n" << std::endl;  // 5
  
  BinarySearchTree<int> bst_i2;
  bst_i2.insert(5);
  bst_i2.insert(3);
  bst_i2.insert(9);
  bst_i2.insert(1);
  bst_i2.insert(4);
  bst_i2.insert(8);
  bst_i2.insert(11);
  bst_i2.insert(-3);
  bst_i2.insert(2);
  bst_i2.insert(7);
  bst_i2.insert(12);
  bst_i2.insert(13);
  int median3 {bst_i2.getMedian()};
  std::cout << "Median: " << median3 << std::endl;  // 5, 7 (No True Median)
}
