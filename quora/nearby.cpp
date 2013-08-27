#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
#include <cfloat>
#include <utility>
#include <cassert>
#include <unordered_map>
#include <limits>
#include <list>
#include <unordered_set>

using namespace std;

const float MAX_DISTANCE = 1e6 * 1e6;

class BoundingBox {
  public:
    explicit BoundingBox(const float input_x, const float input_y)
        : x(input_x), y(input_y), w(0.0), h(0.0) { 
      vertices.push_back(pair<float, float>(x, y));
    }
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
    const float actual_distance(const float x1, const float y1) const;
    const float min_distance(const float x1, const float y1) const;
    const float min_max_distance(const float x1, const float y1) const;
    const bool contain(const BoundingBox& bbox) const ;
    const bool contain(const float x1, const float y1) const ;
    void enlarge(const float x1, const float y1);
    void enlarge(const BoundingBox* pbbox);

    friend ostream& operator<<(ostream& out, BoundingBox& bbox);
    
    float x;
    float y;
    float w;
    float h;
    vector<pair<float, float> > vertices;
};

ostream& operator<<(ostream& out, BoundingBox& bbox) {
  out << "x: " << bbox.x << " y: " << bbox.y;
  out << " w: " << bbox.w << " h: " << bbox.h; 
  return out;
}

const float BoundingBox::actual_distance(const float x1, 
                                         const float y1) const {
  float min_distance = numeric_limits<float>::max();
  float distance = 0;
  for (vector<pair<float, float> >::const_iterator it = vertices.begin();
      it != vertices.end(); it ++) {
    distance = sqrt(((*it).first - x1) * ((*it).first - x1) + 
                ((*it).second - y1) * ((*it).second - y1));
    if (distance < min_distance) min_distance = distance;
  } 
  return min_distance;
}

const float BoundingBox::min_distance(const float x1,
                                      const float y1) const {
  // if point(x1, y1) in REC, min_dist = 0, otherwise
  // distance to closest edge or vertex
  float x_rectangle = x1;
  float y_rectangle = y1;
  if (x1 < x) x_rectangle = x;
  else if (x1 > (x + w)) x_rectangle = x + w;
  if (y1 < y) y_rectangle = y;
  else if (y1 > (y + h)) y_rectangle = y + h; 
  return sqrt((x1 - x_rectangle) * (x1 - x_rectangle) + 
         (y1 - y_rectangle) * (y1 - y_rectangle));
}

const float BoundingBox::min_max_distance(const float x1,
                                          const float y1) const {
  // mim over all dimension distance from point to the furthest
  // point of the closest face of the R

  float x_min = 0, y_min = 0, x_max = 0, y_max = 0;
  // x dimension
  if (x1 < (x + w / 2)) x_min = x;
  else x_min = x + w;
  if (y1 < (y + h / 2)) y_min = y + h;
  else y_min = y;
  x_max = sqrt((x_min - x1) * (x_min - x1) + (y_min - y1) * (y_min - y1));
  // y dimension
  if (y1 < (y + h / 2)) y_min = y;
  else y_min = y + h;
  if (x1 < (x + w / 2)) x_min = x + w;
  else x_min = x;
  y_max = sqrt((x_min - x1) * (x_min - x1) + (y_min - y1) * (y_min - y1));
  return (x_max < y_max)? x_max : y_max;   
}

const bool BoundingBox::contain(const float x1, const float y1) const {
  float increased_area = this->enlargement(x1, y1);
  return increased_area == 0;
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

  vector<float> x_vector(x_array, x_array + 4);
  vector<float> y_vector(y_array, y_array + 4);
 
  min_bounding_rectangle(x_vector, y_vector, 
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
  vector<float> x_vector(x_array, x_array + 3);
  vector<float> y_vector(y_array, y_array + 3);
  // cout << "before " << x << ' ' << y << endl;
  min_bounding_rectangle(x_vector, y_vector, &x, &y, &w, &h);
  // cout << "after " << x << ' ' << y << endl;
}

void BoundingBox::enlarge(const BoundingBox* pbbox) {
//  cout << x << ' ' << y << ' ' << pbbox->x << ' ' << pbbox->y << endl;
  const float x_array[] = {x, x + w, pbbox->x, pbbox->x + pbbox->w};
  const float y_array[] = {y, y + h, pbbox->y, pbbox->y + pbbox->h};
  vector<float> x_vector(x_array, x_array + 4);
  vector<float> y_vector(y_array, y_array + 4);
  // cout << "before " << x << ' ' << y << endl;
  min_bounding_rectangle(x_vector, y_vector, &x, &y, &w, &h);
  // cout << "after " << x << ' ' << y << endl;
}

const float BoundingBox::enlargement(const float x1, const float y1) const {
  const float x_array[] = {x, x + w, x1};
  const float y_array[] = {y, y + h, y1};
  vector<float> x_vector(x_array, x_array + 3);
  vector<float> y_vector(y_array, y_array + 3);
  float new_x = x;
  float new_y = y;
  float new_w = w;
  float new_h = h;
  min_bounding_rectangle(x_vector, y_vector, 
                             &new_x, &new_y, &new_w, &new_h);
  return (new_w * new_h - this->area());
}

const float BoundingBox::enlargement(const BoundingBox* pbbox) const {
  const float x_array[] = {x, x + w, pbbox->x, pbbox->x + pbbox->w};
  const float y_array[] = {y, y + h, pbbox->y, pbbox->y + pbbox->h};
  vector<float> x_vector(x_array, x_array + 4);
  vector<float> y_vector(y_array, y_array + 4);
  float new_x = x;
  float new_y = y;
  float new_w = w;
  float new_h = h;
  min_bounding_rectangle(x_vector, y_vector, 
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
    float min_distance;
    float min_max_distance;
};

typedef unordered_map<size_t, Leaf*> LeafMap;
typedef pair<size_t, Leaf*> LeafPair;

bool compare_leaf(const Leaf* leaf1, const Leaf* leaf2) {
  if (fabs(leaf1->min_distance - leaf2->min_distance) < 0.001) {
    return leaf1->id > leaf2->id; 
  } else
    return leaf1->min_distance < leaf2->min_distance;
}

class Node {
  public:
    Node() { rectangle = new BoundingBox(0.0, 0.0); }
    explicit Node(const float x, const float y) {
      rectangle = new BoundingBox(x, y);
    }
    explicit Node(const BoundingBox& bbox) {
      rectangle = new BoundingBox(bbox.x, bbox.y);
      rectangle->enlarge(bbox.x + bbox.w, bbox.y + bbox.h);
    }
    virtual ~Node() { delete rectangle; }

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

    BoundingBox* rectangle;
    deque<Node*> children;
    deque<Leaf*> leaves;

    LeafMap buffer; 

    float min_distance;
    float min_max_distance;
};

class compare_node_pair {
  public:
    const bool operator()(const pair<float, Node*>& p1, 
                          const pair<float, Node*>& p2) const {
      return p1.first < p2.first;
    }
};

bool compare_node(const Node* node1, const Node* node2) {
  return node1->min_max_distance < node2->min_max_distance;
}

void Node::insert_leaf(Leaf* leaf) {
  // push leaf to leaves
  this->leaves.push_back(leaf);
  // enlarge the bounding box 
  this->rectangle->enlarge(leaf->min_bounding_box);
}

void Node::insert_children(Node* node) {
  // push node to children
  this->children.push_back(node);
  // enlarge the bounding box
  this->rectangle->enlarge(node->rectangle);
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
          *(*it1)->rectangle, *(*it2)->rectangle, 
          &new_x, &new_y, &new_w, &new_h); 

      integral_area = new_w * new_h - 
                      (*it1)->rectangle->area() -
                      (*it2)->rectangle->area();
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

  BoundingBox* left_mbbox = left_node->rectangle;
  BoundingBox* right_mbbox = right_node->rectangle;
  float left_enlargement = 0, right_enlargement = 0;
  while (!this->children.empty()) {
    Node* node = this->children.back();
    if (node != left_seed && node != right_seed) {
      left_enlargement = 
          left_mbbox->enlargement(node->rectangle);
      right_enlargement = 
          right_mbbox->enlargement(node->rectangle);
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
    left_node->rectangle->
        enlarge((*it_left)->rectangle);
    //    cout << *left_node->rectangle << endl;
  }
  // enlarge right node
  for (deque<Node*>::iterator it_right = right_node->children.begin() + 1;
      it_right != right_node->children.end(); it_right ++) {
    //    cout << "right " << *(*it_right)->min_bounding_box << endl;
    right_node->rectangle->
        enlarge((*it_right)->rectangle);
    //    cout << *right_node->rectangle << endl;
  }
}

void Node::split_with_seeds(Leaf* &left_seed, Leaf* & right_seed,
                            Node* &left_node, Node* &right_node) {
  // push left and right seed 
  left_node->leaves.push_back(left_seed);
  right_node->leaves.push_back(right_seed);

  BoundingBox* left_mbbox = left_node->rectangle;
  BoundingBox* right_mbbox = right_node->rectangle;
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
    left_node->rectangle->enlarge((*it_left)->min_bounding_box);
    //    cout << *left_node->rectangle << endl;
  }
  // enlarge right node
  for (deque<Leaf*>::iterator it_right = right_node->leaves.begin() + 1;
      it_right != right_node->leaves.end(); it_right ++) {
    //    cout << "right " << *(*it_right)->min_bounding_box << endl;
    right_node->rectangle->enlarge((*it_right)->min_bounding_box);
    //    cout << *right_node->rectangle << endl;
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
  Node* left_node = new Node(*left_seed->rectangle);
  Node* right_node = new Node(*right_seed->rectangle);

  //  cout << "left seed " << *left_seed->rectangle << endl;
  //  cout << "right seed " << *right_seed->rectangle << endl;
  
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
    //    cout << this->rectangle->area() << endl;
    //    cout << (*it)->rectangle->area() << endl;
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
  this->rectangle->enlarge(new_leaf->min_bounding_box);
  
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
    //    cout << this->rectangle->area() << endl;
    //    cout << (*it)->rectangle->area() << endl;

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
    RTree() : root(NULL), max_children(50) {}
    RTree(size_t max_child) : root(NULL), max_children(max_child) {}
    ~RTree() {}

    void insert(Leaf* new_left);
    void search(Node* head, const float query_x, 
                const float query_y, const size_t max_query_id,
                vector<Leaf*>& list, Node* &cloest);
    void nsearch(const float query_x, const float query_y,
                 const size_t max_query_id, vector<Leaf*>& list);

  private:
    friend ostream& operator<<(ostream& out, RTree& tree);
    void print_tree();
    void print_tree(Node* head);
    Node* root;
    size_t max_children;
};

//const size_t RTree::max_children = 50;

void RTree::print_tree(Node* head) {
  deque<Node*> node_queue;
  node_queue.push_back(head);

  size_t layer = 0;
  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    cout << "root " << *node->rectangle << endl;    
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

void RTree::print_tree() {
  print_tree(root);
}

ostream& operator<<(ostream& out, RTree& tree) {
  if (!tree.root) return out;
  deque<Node*> node_queue;
  node_queue.push_back(tree.root);
  //  cout << "init root print" << endl; 
  size_t layer = 0;
  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    out << "root " << *node->rectangle << endl;    
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
    root->rectangle->enlarge(mbbox->x + mbbox->w, 
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
      if ((*it_children)->rectangle->
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
        enlargement_area = (*it_children)->rectangle->
            enlargement(new_leaf->min_bounding_box->x,
            new_leaf->min_bounding_box->y); 
        if (enlargement_area < min_enlargement_area) {
          min_enlargement_area = enlargement_area;
          it_min_enlargement = it_children;
        } else if (enlargement_area == min_enlargement_area) {
          // if more then one mode satisfy, choose the one with small area  
          if ((*it_children)->rectangle->area() <
              (*it_min_enlargement)->rectangle->area()) {
            it_min_enlargement = it_children;
          } 
        }
      }
      next_head = *it_min_enlargement;
    }
    head = next_head;
  }
  // cout << "head " << *head->rectangle << endl;

  // check if the leaf node is not full
  if (head->leaves.size() < max_children) {
    //    cout << "new leaf insert " << new_leaf->id << endl;
    //    head->insert_leaf(new_leaf);
    head->leaves.push_back(new_leaf);
    head->rectangle->enlarge(new_leaf->min_bounding_box);
    Node* parent = parent_stack.back();
    // enlarge all parents
    while (parent) {
      parent->rectangle->enlarge(head->rectangle); 
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
    Node* parent = parent_stack.back();
    parent_stack.pop_back();
    while (parent) {
      if (parent->children.size() > max_children) {
      //  cout << "before quadratic root split " << endl;
      //  print_tree();
      //  cout << "split node " << endl;
        parent->quadratic_split(parent_stack);
      //  cout << "after quadratic root split " << endl;
      //  print_tree();
      }
      parent->rectangle->enlarge(head->rectangle);
      head = parent;
      parent = parent_stack.back();
      parent_stack.pop_back();
    } 
  }
}

void RTree::search(Node* head, const float query_x, 
                   const float query_y, const size_t max_query_id,
                   vector<Leaf*>& list, Node* &closest) {
  // found leave node
  if (!head) cerr << "null head" << endl;
  if (head->children.empty()) {
    if (!closest) closest = const_cast<Node*>(head);
    deque<Leaf*>::const_iterator it_leaves = head->leaves.begin();
   
    // if (closest->buffer.empty()) { 
      for(; it_leaves != head->leaves.end(); it_leaves ++) {
        (*it_leaves)->min_distance = (*it_leaves)->min_bounding_box->
            actual_distance(query_x, query_y);
        (*it_leaves)->min_max_distance = (*it_leaves)->min_bounding_box->
            min_max_distance(query_x, query_y);
        //  cout << "push " << (*it_leaves)->id << endl;
        list.push_back(*it_leaves);
      }
      if (list.size() >= max_query_id) {
        sort(list.begin(), list.end(), compare_leaf);
        // cout << "extra" << endl;
        while (list.size() > max_query_id) { list.pop_back(); }
      }  
    //} else {
    //  // cout << "buffer not empty size :";
    //  // cout << closest->buffer.size() << endl; 
    //  // for (LeafMap::iterator it = closest->buffer.begin(); 
    //  //         it != closest->buffer.end(); it ++) {
    //  //   cout << (*it).first << ' ';
    //  // }
    //  // cout << endl;

    //  LeafMap::iterator it_buffer = closest->buffer.begin();
    //  while (!list.empty()) {
    //    //it_buffer = closest->buffer.find(list.back()->id);
    //    //if (it_buffer == closest->buffer.end()) {
    //      closest->buffer.insert(LeafPair(list.back()->id, list.back()));
    //      // cout << "add more " << list.back()->id << endl;
    //    //}
    //    list.pop_back();
    //  } 
    //  it_buffer = closest->buffer.begin();
    //  for(; it_buffer != closest->buffer.end(); it_buffer ++) {
    //    (*it_buffer).second->min_distance = 
    //        (*it_buffer).second->min_bounding_box->
    //        actual_distance(query_x, query_y);
    //    (*it_buffer).second->min_max_distance = 
    //        (*it_buffer).second->min_bounding_box->
    //        min_max_distance(query_x, query_y);       
    //    list.push_back((*it_buffer).second);
    //  }
    //  deque<Leaf*>::const_iterator it_leaves = head->leaves.begin();
    //  for(; it_leaves != head->leaves.end(); it_leaves ++) {
    //    // cout << "add more " << (*it_leaves)->id << endl;
    //    (*it_leaves)->min_distance = (*it_leaves)->min_bounding_box->
    //        actual_distance(query_x, query_y);
    //    (*it_leaves)->min_max_distance = (*it_leaves)->min_bounding_box->
    //        min_max_distance(query_x, query_y);
    //    // it_buffer = closest->buffer.find((*it_leaves)->id);
    //    // if (it_buffer == closest->buffer.end()) {
    //      closest->buffer.insert(LeafPair((*it_leaves)->id, *it_leaves));
    //      // cout << "add more push " << (*it_leaves)->id << endl;
    //      list.push_back(*it_leaves);
    //    // }
    //  }

    //  // head->buffer.clear(); 
    //  sort(list.begin(), list.end(), compare_leaf);
    //  while (list.size() > max_query_id) { list.pop_back(); }
    //}
  } else {
    vector<Node*> children_list; 
    deque<Node*>::const_iterator it_children = head->children.begin();
    for (; it_children != head->children.end(); it_children ++) {
      (*it_children)->min_distance = (*it_children)->rectangle
          ->min_distance(query_x, query_y);
      (*it_children)->min_max_distance = (*it_children)
        ->rectangle->min_max_distance(query_x, query_y);
      children_list.push_back((*it_children));
    } 
    sort(children_list.begin(), children_list.end(), compare_node);
    
    vector<Node*>::iterator it_list = children_list.begin();
    vector<Node*>::iterator it_compare = children_list.begin();
    for (; it_list != children_list.end(); it_list ++) {
      // if buffer not full, kepp insert
      if (list.size() < max_query_id) {
        // cout << "fill buffer" << endl;
        search(*it_list, query_x, query_y, max_query_id, list, closest); 
      } else {
      // prune
        sort(list.begin(), list.end(), compare_leaf);
        // cout << "list ";
        // for (size_t index = 0; index < list.size(); index ++)
        //   cout << list[index]->id << ':' << list[index]->min_distance << ' ';
        // cout << endl;
        // if (list.back()->min_distance > (*it_list)->min_max_distance) {
        //   // cout << list.back()->min_distance << ' ';
        //   // cout << (*it_list)->min_max_distance << ' ';
        //   // cout << "downward pruning" << endl;
        //   list.pop_back();
        // }
        // cout << "list size " << list.size() << endl;
        if (!list.empty()) {
          if ((*it_list)->min_distance > list.back()->min_max_distance) {
              //  if (fabs((*it_list)->min_distance - 72522.9) < 0.1) {
            // cout << "upward pruning" << endl;
            // cout << (*it_list)->min_distance << " ";
            // cout << (*it_list)->min_max_distance << ' ';
            // cout << list.back()->min_distance << ' ';
            // cout << list.back()->min_max_distance << endl;
            //cout << "root " << *head->rectangle << endl;
            // print_tree(*it_list);
              //  }
            continue;
          }
        }
        // for (it_compare = children_list.begin(); it_compare != it_list &&
        //     it_compare != children_list.end(); it_compare ++) { 
        //   if ((*it_list)->min_distance > (*it_compare)->min_max_distance) {
        //     // cout << "downward pruning" << endl;
        //     continue;
        //   }
        // }
        search(*it_list, query_x, query_y, max_query_id, list, closest); 
      }
    } 
  }
}

void RTree::nsearch(const float query_x, const float query_y,
                   const size_t max_query_id, vector<Leaf*>& list) {
  // cout << query_x << ' ' << query_y << ' ' << max_query_id << endl;
  if (!root) return;   
  Node* closest = NULL;
  search(root, query_x, query_y, max_query_id, list, closest);
  sort(list.begin(), list.end(), compare_leaf);

  if (!closest)
    cout << "not found closest node" << endl;
  else {
    // cout << "found cloest node " << list.size() << endl;
    LeafMap::iterator it_buffer = closest->buffer.begin();
    for (vector<Leaf*>::iterator it = list.begin();
        it != list.end(); it ++) {
      // cout << "insert to buffer" << endl;
      closest->buffer.insert(LeafPair((*it)->id, *it));
    }
  }
}

int main() {
  size_t N = 0, T = 0, Q = 0;
  cin >> T >> Q >> N;

  size_t max_topic_tree_children = T * 0.005;
  const size_t min_children = 4;
  if (max_topic_tree_children < min_children) 
    max_topic_tree_children = min_children;
  RTree topic_tree(max_topic_tree_children);

  LeafMap topics;
  size_t id = 0;
  float x = 0, y = 0;
  for (size_t topic_counter = 0; topic_counter < T; topic_counter ++) {
    cin >> id >> x >> y;
    topics[id] = new Leaf(id, x, y);
    topic_tree.insert(topics[id]);
  }
  //  cout << "insert topic tree" << endl;
  //  cout << topic_tree << endl;

  size_t max_question_tree_children = Q * 0.5;
  if (max_question_tree_children < min_children) 
    max_question_tree_children = min_children; 
  RTree question_tree(max_question_tree_children);
  LeafMap questions;
  size_t topic_number = 0, topic_id;
  for (size_t question_counter = 0; question_counter < Q;
      question_counter ++) {
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
        question_mbbox->vertices.push_back(pair<float, float>(
            topics[topic_id]->min_bounding_box->vertices.back().first,
            topics[topic_id]->min_bounding_box->vertices.back().second));
      }
      question_tree.insert(questions[id]);
    }
  }
  // cout << "insert question tree" << endl;
  // cout << question_tree << endl;

  char query_type = '0';
  size_t max_query_id = 0;
  float query_x = 0, query_y = 0;
  vector<Leaf*> result_list;
  size_t max_length = 0;
  for (int n_counter = 0; n_counter < N; n_counter++) {
  //  for (int n_counter = 0; n_counter < 1; n_counter++) {
 
    cin >> query_type >> max_query_id >> query_x >> query_y;
    result_list.clear();
    if (query_type == 't') {
      // topic_tree
      topic_tree.nsearch(query_x, query_y, max_query_id, result_list);
    } else if (query_type == 'q') {
      // question_tree
      question_tree.nsearch(query_x, query_y, max_query_id, result_list);
    }
    max_length = min(result_list.size(), max_query_id);
    for (size_t index = 0; index < max_length; index ++) {
      cout << result_list[index]->id << ' ';
      // cout << result_list[index]->min_distance << endl;
    } 
    cout << endl;
  }

  return 0;
}
