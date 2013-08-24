#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
#include <cfloat>
#include <utility>
#include <cassert>
#include <unordered_map>
#include <limits>

using namespace std;

class BoundingBox {
  public:
    explicit BoundingBox(const float input_x, const float input_y)
        : x(input_x), y(input_y), w(0.0), h(0.0) {}
    ~BoundingBox() {}

    static void min_bounding_rectangle(const vector<float>& x_array, 
        const vector<float>& y_array, float* new_x, float* new_y, 
        float* new_w, float* new_h);
    static void min_bounding_rectangle(
        const BoundingBox& bbox1, const BoundingBox& bbox2,
        float* new_x, float* new_y, float* new_w, float* new_h);

    const float enlargement(const float x1, const float y1) const;
    const float enlargement(const BoundingBox* pbbox) const;
    const float area() const { return w * h; }
    const bool contain(const BoundingBox& bbox) const ;
    void enlarge(const float x1, const float y1);
    void enlarge(const BoundingBox* pbbox);

    friend ostream& operator<<(ostream& out, BoundingBox& bbox);
    
    float x;
    float y;
    float w;
    float h;
};

ostream& operator<<(ostream& out, BoundingBox& bbox) {
  out << "x: " << bbox.x << " y: " << bbox.y;
  out << " w: " << bbox.w << " h: " << bbox.h; 
  return out;
}

const bool BoundingBox::contain(const BoundingBox& bbox) const {
  float increased_area = this->enlargement(bbox.x, bbox.y) +
      this->enlargement(bbox.x + bbox.w, bbox.y + bbox.h);
  return increased_area == 0;
}

void BoundingBox::min_bounding_rectangle(
    const BoundingBox& bbox1, const BoundingBox& bbox2,
    float* new_x, float* new_y, float* new_w, float* new_h) {
  const float x_array[] = {bbox1.x, bbox1.x + bbox1.w, 
                           bbox2.x, bbox2.x + bbox2.w};
  const float y_array[] = {bbox1.y, bbox1.y + bbox1.h, 
                           bbox2.y, bbox2.y + bbox2.h};

  vector<float> x_array_vec(x_array, x_array + 4);
  vector<float> y_array_vec(y_array, y_array + 4);
 
  min_bounding_rectangle(x_array_vec, y_array_vec, 
                             new_x, new_y, new_w, new_h);
}

void BoundingBox::min_bounding_rectangle(const vector<float>& x_array, 
    const vector<float>& y_array, float* new_x, float* new_y, 
    float* new_w, float* new_h) {
  float new_distance = 0;
  float new_min_x = x_array[0];
  float new_min_y = y_array[0];
  assert(x_array.size() == y_array.size());

  for (size_t index1 = 0; index1 < x_array.size(); index1 ++) {
    if (x_array[index1] < new_min_x) new_min_x = x_array[index1];
    if (y_array[index1] < new_min_y) new_min_y = y_array[index1];

    for (size_t index2 = index1; index2 < x_array.size(); index2 ++) {
      new_distance = abs(x_array[index1] - x_array[index2]);
      if (new_distance > *new_w) *new_w = new_distance;
      new_distance = abs(y_array[index1] - y_array[index2]);
      if (new_distance > *new_h) *new_h = new_distance;
    }
  }
  *new_x = new_min_x;
  *new_y = new_min_y;
}

void BoundingBox::enlarge(const float x1, const float y1) {
  const float x_array[] = {x, x + w, x1};
  const float y_array[] = {y, y + h, y1};
  vector<float> x_array_vec(x_array, x_array + 3);
  vector<float> y_array_vec(y_array, y_array + 3);
  // cout << "before " << x << ' ' << y << endl;
  min_bounding_rectangle(x_array_vec, y_array_vec, &x, &y, &w, &h);
  // cout << "after " << x << ' ' << y << endl;
}

void BoundingBox::enlarge(const BoundingBox* pbbox) {
//  cout << x << ' ' << y << ' ' << pbbox->x << ' ' << pbbox->y << endl;
  const float x_array[] = {x, x + w, pbbox->x, pbbox->x + pbbox->w};
  const float y_array[] = {y, y + h, pbbox->y, pbbox->y + pbbox->h};
  vector<float> x_array_vec(x_array, x_array + 4);
  vector<float> y_array_vec(y_array, y_array + 4);
  // cout << "before " << x << ' ' << y << endl;
  min_bounding_rectangle(x_array_vec, y_array_vec, &x, &y, &w, &h);
  // cout << "after " << x << ' ' << y << endl;
}

const float BoundingBox::enlargement(const float x1, const float y1) const {
  const float x_array[] = {x, x + w, x1};
  const float y_array[] = {y, y + h, y1};
  vector<float> x_array_vec(x_array, x_array + 3);
  vector<float> y_array_vec(y_array, y_array + 3);
  float new_x = x;
  float new_y = y;
  float new_w = w;
  float new_h = h;
  min_bounding_rectangle(x_array_vec, y_array_vec, 
                             &new_x, &new_y, &new_w, &new_h);
  return (new_w * new_h - this->area());
}

const float BoundingBox::enlargement(const BoundingBox* pbbox) const {
  const float x_array[] = {x, x + w, pbbox->x, pbbox->x + pbbox->w};
  const float y_array[] = {y, y + h, pbbox->y, pbbox->y + pbbox->h};
  vector<float> x_array_vec(x_array, x_array + 4);
  vector<float> y_array_vec(y_array, y_array + 4);
  float new_x = x;
  float new_y = y;
  float new_w = w;
  float new_h = h;
  min_bounding_rectangle(x_array_vec, y_array_vec, 
                             &new_x, &new_y, &new_w, &new_h);
  return (new_w * new_h - this->area());
}

class Leaf {
  public:
    explicit Leaf(const size_t ID, const float x, const float y) : id(ID) {
      min_bounding_box = new BoundingBox(x, y);
    }
    virtual ~Leaf() { delete min_bounding_box; }

    size_t id;
    BoundingBox* min_bounding_box;
};

class Node {
  public:
    Node() { directory_rectangle = new BoundingBox(0.0, 0.0); }
    explicit Node(const float x, const float y) {
      directory_rectangle = new BoundingBox(x, y);
    }
    explicit Node(const BoundingBox& bbox) {
      directory_rectangle = new BoundingBox(bbox.x, bbox.y);
      directory_rectangle->enlarge(bbox.x + bbox.w, bbox.y + bbox.h);
    }
    virtual ~Node() { delete directory_rectangle; }

    void insert_leaf(Leaf* leaf);
    void insert_children(Node* node);

    void find_seeds(Leaf* &left_seed, Leaf* &right_seed) const;
    void find_seeds(Node* &left_seed, Node* &right_seed) const;
    void quadratic_split(Leaf* new_leaf, vector<Node*> parents);
    void quadratic_split(vector<Node*> parents);
    void split_with_seeds(Leaf* &left_seed, Leaf* &right_seed,
                          Node* &left_node, Node* &right_node);
    void split_with_seeds(Node* &left_seed, Node* &right_seed,
                          Node* &left_node, Node* &right_node);

    BoundingBox* directory_rectangle;
    deque<Node*> children;
    deque<Leaf*> leaves;
};


void Node::insert_leaf(Leaf* leaf) {
  // push leaf to leaves
  this->leaves.push_back(leaf);
  // enlarge the bounding box 
  this->directory_rectangle->enlarge(leaf->min_bounding_box);
}

void Node::insert_children(Node* node) {
  // push node to children
  this->children.push_back(node);
  // enlarge the bounding box
  this->directory_rectangle->enlarge(node->directory_rectangle);
}

void Node::find_seeds(Node* &left_seed, Node* &right_seed) const {
  // cout << "leaves size " << this->leaves.size() << endl;
  deque<Node*>::const_iterator it1 = this->children.begin();
  deque<Node*>::const_iterator it2 = this->children.begin();
  float new_x = 0, new_y = 0, new_w = 0, new_h = 0;
  float integral_area = 0;
  float max_integral_area = -numeric_limits<float>::max();

  for (; it1 != this->children.end(); it1 ++) {
    for (it2 = it1 + 1; it2 != this->children.end(); it2 ++) {
      BoundingBox::min_bounding_rectangle(
          *(*it1)->directory_rectangle, *(*it2)->directory_rectangle, 
          &new_x, &new_y, &new_w, &new_h); 

      integral_area = new_w * new_h - 
                      (*it1)->directory_rectangle->area() -
                      (*it2)->directory_rectangle->area();
      // cout << integral_area << endl;
      if (integral_area > max_integral_area) {
        max_integral_area = integral_area;
        left_seed = *it1;
        right_seed = *it2;
      }
    }
  }
  // cout << "find seeds" << endl;
  if (!left_seed) cerr << "find empty null left leaf seed" << endl;
  if (!right_seed) cerr << "find empty null right leaf seed" << endl;
}

void Node::find_seeds(Leaf* &left_seed, Leaf* &right_seed) const {
  // cout << "leaves size " << this->leaves.size() << endl;
  deque<Leaf*>::const_iterator it1 = this->leaves.begin();
  deque<Leaf*>::const_iterator it2 = this->leaves.begin();
  float new_x = 0, new_y = 0, new_w = 0, new_h = 0;
  float integral_area = 0;
  float max_integral_area = -numeric_limits<float>::max();

  for (; it1 != this->leaves.end(); it1 ++) {
    for (it2 = it1 + 1; it2 != this->leaves.end(); it2 ++) {
      // cout << *(*it1)->min_bounding_box << ' ' 
      //       << *(*it2)->min_bounding_box << endl;

      BoundingBox::min_bounding_rectangle(
          *(*it1)->min_bounding_box, *(*it2)->min_bounding_box, 
          &new_x, &new_y, &new_w, &new_h); 

      // cout << "integral area " << new_w << ' ' << new_h << ' ';
      //cout << "b1 " << *(*it1)->min_bounding_box << endl;
      //cout << "b2 " << *(*it2)->min_bounding_box << endl;
      //cout << "large " << new_x << ' ' << new_y << ' '
      //        << new_w << ' ' << new_h << endl;

      integral_area = new_w * new_h - 
                      (*it1)->min_bounding_box->area() -
                      (*it2)->min_bounding_box->area();
      //cout << "integral are " << integral_area << "max integral ";
      //cout << max_integral_area << endl;
      // assert(integral_area >= 0);
      if (integral_area > max_integral_area) {
        max_integral_area = integral_area;
        //cout << "assign area" << endl;
        left_seed = *it1;
        right_seed = *it2;
      }
    }
  }
  // cout << "find seeds" << endl;
  if (!left_seed) cerr << "find empty null left leaf seed" << endl;
  if (!right_seed) cerr << "find empty null right leaf seed" << endl;
}

void Node::split_with_seeds(Node* &left_seed, Node* &right_seed,
                            Node* &left_node, Node* &right_node) {
  // push left and right seed 
  left_node->children.push_back(left_seed);
  right_node->children.push_back(right_seed);

  // cout << this->children.size() << ' ' << left_node->children.size();
  //  << ' ';  cout << right_node->children.size() << endl;

  BoundingBox* left_mbbox = left_node->directory_rectangle;
  BoundingBox* right_mbbox = right_node->directory_rectangle;
  float left_enlargement = 0, right_enlargement = 0;
  while (!this->children.empty()) {
    Node* node = this->children.back();
    if (node != left_seed && node != right_seed) {
      left_enlargement = 
          left_mbbox->enlargement(node->directory_rectangle);
      right_enlargement = 
          right_mbbox->enlargement(node->directory_rectangle);
      if (left_enlargement < right_enlargement) {
        // insert to left node
        left_node->children.push_back(node);
        //        cout << "insert left enlarge " << endl;
      } else if (left_enlargement > right_enlargement) {
        // insert to right node
        right_node->children.push_back(node);
        //        cout << "insert right enlarge " << endl;
      } else {
        // same enlargement, choose with smaller area 
        if (left_mbbox->area() < right_mbbox->area()) {
          // insert to left node
          left_node->children.push_back(node);
          //          cout << "insert left area " << endl;
        } else if (left_mbbox->area() > right_mbbox->area()) {
          // insert to right node
          right_node->children.push_back(node);
          //          cout << "insert right area " << endl;
        } else {
          // same area, choose with fewer element
          if (left_node->children.size() <= right_node->children.size()) {
            // insert to left node
            left_node->children.push_back(node);
            //            cout << "insert left element " << endl;
          } else {
            // insert to right node
            right_node->children.push_back(node);
            //            cout << "insert right element " << endl;
          }
        }
      }
    } 
    this->children.pop_back();
  }
  // enlarge left node
  for (deque<Node*>::iterator it_left = left_node->children.begin() + 1;
      it_left != left_node->children.end(); it_left ++) {
    //    cout << "left " << *(*it_left)->min_bounding_box << endl;
    left_node->directory_rectangle->
        enlarge((*it_left)->directory_rectangle);
    //    cout << *left_node->directory_rectangle << endl;
  }
  // enlarge right node
  for (deque<Node*>::iterator it_right = right_node->children.begin() + 1;
      it_right != right_node->children.end(); it_right ++) {
    //    cout << "right " << *(*it_right)->min_bounding_box << endl;
    right_node->directory_rectangle->
        enlarge((*it_right)->directory_rectangle);
    //    cout << *right_node->directory_rectangle << endl;
  }
}

void Node::split_with_seeds(Leaf* &left_seed, Leaf* & right_seed,
                            Node* &left_node, Node* &right_node) {
  // push left and right seed 
  left_node->leaves.push_back(left_seed);
  right_node->leaves.push_back(right_seed);

  BoundingBox* left_mbbox = left_node->directory_rectangle;
  BoundingBox* right_mbbox = right_node->directory_rectangle;
  float left_enlargement = 0, right_enlargement = 0;
  while (!this->leaves.empty()) {
    Leaf* leaf = this->leaves.back();
    if (this->leaves.back() != left_seed && 
        this->leaves.back() != right_seed) {
      left_enlargement = left_mbbox->enlargement(leaf->min_bounding_box);
      right_enlargement = right_mbbox->enlargement(leaf->min_bounding_box);
      if (left_enlargement < right_enlargement) {
        // insert to left node
        left_node->leaves.push_back(leaf);
        //        cout << "insert left enlarge " << endl;
      } else if (left_enlargement > right_enlargement) {
        // insert to right node
        right_node->leaves.push_back(leaf);
        //        cout << "insert right enlarge " << endl;
      } else {
        // same enlargement, choose with smaller area 
        if (left_mbbox->area() < right_mbbox->area()) {
          // insert to left node
          left_node->leaves.push_back(leaf);
          //          cout << "insert left area " << endl;
        } else if (left_mbbox->area() > right_mbbox->area()) {
          // insert to right node
          right_node->leaves.push_back(leaf);
          //          cout << "insert right area " << endl;
        } else {
          // same area, choose with fewer element
          if (left_node->leaves.size() <= right_node->leaves.size()) {
            // insert to left node
            left_node->leaves.push_back(leaf);
            //            cout << "insert left element " << endl;
          } else {
            // insert to right node
            right_node->leaves.push_back(leaf);
            //            cout << "insert right element " << endl;
          }
        }
      }
    } 
    this->leaves.pop_back();
  }
  // enlarge left node
  for (deque<Leaf*>::iterator it_left = left_node->leaves.begin() + 1;
      it_left != left_node->leaves.end(); it_left ++) {
    //    cout << "left " << *(*it_left)->min_bounding_box << endl;
    left_node->directory_rectangle->enlarge((*it_left)->min_bounding_box);
    //    cout << *left_node->directory_rectangle << endl;
  }
  // enlarge right node
  for (deque<Leaf*>::iterator it_right = right_node->leaves.begin() + 1;
      it_right != right_node->leaves.end(); it_right ++) {
    //    cout << "right " << *(*it_right)->min_bounding_box << endl;
    right_node->directory_rectangle->enlarge((*it_right)->min_bounding_box);
    //    cout << *right_node->directory_rectangle << endl;
  }
}

void Node::quadratic_split(vector<Node*> parents) {
  Node* left_seed = NULL;
  Node* right_seed = NULL;
  this->find_seeds(left_seed, right_seed);
  if (left_seed == 0)
    cerr << "left seed null pointer" << endl;
  if (right_seed == 0)
    cerr << "right seed null pointer" << endl;

  // create new left and right node with left and right seed x, y
  Node* left_node = new Node(*left_seed->directory_rectangle);
  Node* right_node = new Node(*right_seed->directory_rectangle);

  //  cout << "left seed " << *left_seed->directory_rectangle << endl;
  //  cout << "right seed " << *right_seed->directory_rectangle << endl;
  
  this->split_with_seeds(left_seed, right_seed, left_node, right_node);
  // cout << "left children " << left_node->children.size() << endl;
  // cout << "right children " << right_node->children.size() << endl;
  // 
  // cout << "this " << this->children.size() << endl;

  if (!parents.back()) {
    this->insert_children(left_node);
    this->insert_children(right_node);
  } else {
    // insert to parents' children list
    Node* parent = parents.back();
    // cout << "parent stack size " << parents.size() << endl;
    deque<Node*>::iterator it = parent->children.begin();
    // linearly iterate to find the current node in the parent's list
    for (; (*it) != this && it != parent->children.end(); it ++);
    //    cout << this->directory_rectangle->area() << endl;
    //    cout << (*it)->directory_rectangle->area() << endl;
    //  cout << "found head" << endl;

    // remove the current node and insert two new nodes
    // cout << "parent size " << parent->children.size() << endl;
    parent->children.erase(it); 
    // cout << "parent size " << parent->children.size() << endl;
    parent->insert_children(left_node);
    parent->insert_children(right_node);
  }

  //  cout << "parent" << endl;
}

void Node::quadratic_split(Leaf* new_leaf, vector<Node*> parents) {
  //  cout << "add extra " << new_leaf->id << endl;
  // first insert new leaf and enlarge
  //  this->insert_leaf(new_leaf);
  this->leaves.push_back(new_leaf);
  this->directory_rectangle->enlarge(new_leaf->min_bounding_box);
  
  // find most separated seed s1, s2

  Leaf* left_seed = NULL;
  Leaf* right_seed = NULL;
  this->find_seeds(left_seed, right_seed);
  if (left_seed == 0)
    cerr << "left leaf seed null pointer" << endl;
  if (right_seed == 0)
    cerr << "right leaf seed null pointer" << endl;

  // cout << "most separated seeds " << left_seed->id << ' '
  //                                << right_seed->id << endl;
  // cout << "max area " << max_integral_area << endl;
  //  cout << "left seed " << *(*left_seed)->min_bounding_box << endl;
  //  cout << "right seed " << *(*right_seed)->min_bounding_box << endl;
  // split the leaf node  

  // create new left and right node with left and right seed x, y
  Node* left_node = new Node(*left_seed->min_bounding_box);
  Node* right_node = new Node(*right_seed->min_bounding_box);
  
  this->split_with_seeds(left_seed, right_seed, left_node, right_node);
  // cout << left_node->leaves.size() << ' ';
  // cout << right_node->leaves.size() << endl;
 
  if (!parents.back()) { // current head is top root
    //    cout << "separate parent" << endl;
    this->insert_children(left_node);
    this->insert_children(right_node);
  } else {
    // insert to parents' children list
    //    cout << "split root" << endl;
    Node* parent = parents.back();
    deque<Node*>::iterator it = parent->children.begin();
    // linearly iterate to find the current node in the parent's list
    for (; (*it) != this && it != parent->children.end(); it ++);
    //    cout << this->directory_rectangle->area() << endl;
    //    cout << (*it)->directory_rectangle->area() << endl;

    // remove the current node and insert two new nodes
    parent->children.erase(it); 
    parent->insert_children(left_node);
    parent->insert_children(right_node);
  }
  
  //  cout << max_integral_area << ' ' << (*left_seed)->id << ' ' 
  //        << (*right_seed)->id << endl; 
  //  for (deque<Leaf*>::iterator it = this->leaves.begin();
  //      it != this->leaves.end(); it ++) {
  //    if (it == left_seed) 
  //      cout << "found left seed " << endl;
  //    else if (it == right_seed)
  //      cout << "found right seed " << endl;
  //  }

}

class RTree 
{
  public: 
    RTree() : root(NULL) {}
    ~RTree() {}

    void insert(Leaf* new_left);

  private:
    friend ostream& operator<<(ostream& out, RTree& tree);
    void print_tree();
    Node* root;
    static const size_t max_children;
};

const size_t RTree::max_children = 4;

void RTree::print_tree() {
  deque<Node*> node_queue;
  node_queue.push_back(root);

  size_t layer = 0;
  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    cout << "root " << *node->directory_rectangle << endl;    
    for (deque<Node*>::iterator it_node = node->children.begin();
        it_node != node->children.end(); it_node ++) {
      node_queue.push_back(*it_node);
    }
    for (deque<Leaf*>::iterator it_leaf = node->leaves.begin();
        it_leaf != node->leaves.end(); it_leaf ++) {
      cout << "leaf " << layer << ' ' << (*it_leaf)->id << ' ';
      cout << *(*it_leaf)->min_bounding_box << endl;
    }
    layer ++;
    node_queue.pop_front(); 
  }
}

ostream& operator<<(ostream& out, RTree& tree) {
  if (!tree.root) return out;
  deque<Node*> node_queue;
  node_queue.push_back(tree.root);
  //  cout << "init root print" << endl; 
  size_t layer = 0;
  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    out << "root " << *node->directory_rectangle << endl;    
    for (deque<Node*>::iterator it_node = node->children.begin();
        it_node != node->children.end(); it_node ++) {
      node_queue.push_back(*it_node);
    }
    for (deque<Leaf*>::iterator it_leaf = node->leaves.begin();
        it_leaf != node->leaves.end(); it_leaf ++) {
      out << "leaf " << " " << layer << ' ' << (*it_leaf)->id << ' ';
      out << *(*it_leaf)->min_bounding_box << endl;
    }
    layer ++;
    node_queue.pop_front(); 
  }
  return out;
}

void RTree::insert(Leaf* new_leaf) 
{
  // cout << "new leaf " << *new_leaf->min_bounding_box << endl;

  BoundingBox* mbbox = new_leaf->min_bounding_box;
  if (!root) 
  {
    // cout << "new leaf init " << new_leaf->id << endl;
    // init root with top-left point of new leaf
    root = new Node(mbbox->x, mbbox->y);
    // enlarge directory rectangle with bottom-right point of new leaf
    root->directory_rectangle->enlarge(mbbox->x + mbbox->w, 
                                       mbbox->y + mbbox->h);
    root->leaves.push_back(new_leaf);
    return;
  }
  Node* head = root;   
  vector<Node *> parent_stack(1, NULL);
  // traverse R-tree top-down
  Node* next_head = NULL;
  while (!head->children.empty()) {
    // cout << "iterate top-down" << endl;
    parent_stack.push_back(head);
    bool found_match = false;
    // first searching node whode DR contains the mbb of new leaf
    // cout << "children size " << head->children.size() << endl;
    deque<Node*>::iterator it_children = head->children.begin();
    for (; it_children != head->children.end(); it_children ++) {
      // cout << "iterare DRs " << endl; 
      if ((*it_children)->directory_rectangle->
                          contain(*new_leaf->min_bounding_box)) {
        next_head = *it_children;
        found_match = true;
      }
    }

    // cout << "DR contains match " << found_match << endl;
    // otherwise choose the node with minimal enlargement of the DR
    if (!found_match) {
      deque<Node*>::iterator it_min_enlargement = head->children.begin();
      it_children = head->children.begin(); 
      float min_enlargement_area = FLT_MAX; 
      float enlargement_area = 0;
      for (; it_children != head->children.end(); it_children ++) {
        enlargement_area = (*it_children)->directory_rectangle->
            enlargement(new_leaf->min_bounding_box->x,
            new_leaf->min_bounding_box->y); 
        if (enlargement_area < min_enlargement_area) {
          min_enlargement_area = enlargement_area;
          it_min_enlargement = it_children;
        } else if (enlargement_area == min_enlargement_area) {
          // if more then one mode satisfy, choose the one with small area  
          if ((*it_children)->directory_rectangle->area() <
              (*it_min_enlargement)->directory_rectangle->area()) {
            it_min_enlargement = it_children;
          } 
        }
      }
      next_head = *it_min_enlargement;
    }
    head = next_head;
  }
  // cout << "head " << *head->directory_rectangle << endl;

  // check if the leaf node is not full
  if (head->leaves.size() < max_children) {
    //    cout << "new leaf insert " << new_leaf->id << endl;
    //    head->insert_leaf(new_leaf);
    head->leaves.push_back(new_leaf);
    head->directory_rectangle->enlarge(new_leaf->min_bounding_box);
    Node* parent = parent_stack.back();
    // enlarge all parents
    while (parent) {
      parent->directory_rectangle->enlarge(head->directory_rectangle); 
      parent_stack.pop_back();
      head = parent;
      parent = parent_stack.back();
    }
  } else {
    // Quadratic split
//    cout << "before quadratic split " << endl;
//    print_tree();
    head->quadratic_split(new_leaf, parent_stack);
//    cout << "after quadratic split " << endl;
//    print_tree();

    // recursive split parent
    head = parent_stack.back();
    parent_stack.pop_back();
    while (head) {
      if (head->children.size() > max_children) {
      //  cout << "before quadratic root split " << endl;
      //  print_tree();
      //  cout << "split node " << endl;
        head->quadratic_split(parent_stack);
      //  cout << "after quadratic root split " << endl;
      //  print_tree();
      }
      head = parent_stack.back();
      parent_stack.pop_back();
    } 
  }
}

int main() 
{
  typedef unordered_map<size_t, Leaf*> LeafMap;

  size_t N = 0, T = 0, Q = 0;
  cin >> T >> Q >> N;

  RTree topic_tree;
  LeafMap topics;
  size_t id = 0;
  float x = 0, y = 0;
  for (size_t topic_counter = 0; topic_counter < T; topic_counter ++) {
  //  for (size_t topic_counter = 0; topic_counter < 10; topic_counter ++) {
    cin >> id >> x >> y;
    topics[id] = new Leaf(id, x, y);
    topic_tree.insert(topics[id]);
  }
  //  cout << "insert topic tree" << endl;
  cout << topic_tree << endl;

  RTree question_tree;
  LeafMap questions;
  size_t topic_number = 0, topic_id;
  for (size_t question_counter = 0; question_counter < Q;
      question_counter ++) 
  {
    cin >> id >> topic_number;
    if (topic_number > 0) {
      cin >> topic_id;
      BoundingBox* topic_mbbox = topics[topic_id]->min_bounding_box;
      // cout << "topic " << topic_id << endl;
      // cout << *topics[topic_id]->min_bounding_box << endl;
      questions[id] = new Leaf(id, topic_mbbox->x, topic_mbbox->y);
      for (size_t topic_counter = 1; topic_counter < topic_number;
          topic_counter ++) {
        cin >> topic_id;
        topic_mbbox = topics[topic_id]->min_bounding_box;
        BoundingBox* question_mbbox = questions[id]->min_bounding_box;
        question_mbbox->enlarge(topic_mbbox);
      }
      question_tree.insert(questions[id]); 
    }
  }
  // cout << "insert question tree" << endl;
  // cout << question_tree << endl;

  ////////////////////////////////////////
  // for (LeafMap::iterator it = topics.begin();
  //     it != topics.end(); it ++) {
  //   cout << *it->second->min_bounding_box << endl;
  // }

  // cout << "questions " << endl;
  // for (LeafMap::iterator it = questions.begin();
  //     it != questions.end(); it ++) {
  //   cout << it->first << ' ' << it->second->min_bounding_box->area();
  //   cout << ' ' << it->second->min_bounding_box->x;
  //   cout << ' ' << it->second->min_bounding_box->y << endl;
  // }
  ////////////////////////////////////////
 
  return 0;
}
