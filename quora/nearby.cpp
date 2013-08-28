#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
#include <cfloat>
#include <utility>
#include <cassert>
#include <unordered_map>
#include <limits>
#include <algorithm>
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

    inline static void min_bounding_rectangle(const float x_array[],
        const float y_array[], const size_t array_size, float& new_x,
        float& new_y, float& new_w, float& new_h);
    static void min_bounding_rectangle(
        const BoundingBox& bbox1, const BoundingBox& bbox2,
        float& new_x, float& new_y, float& new_w, float& new_h);

    inline const float enlargement(const float x1, const float y1) const;
    inline const float enlargement(const BoundingBox& bbox) const;
    inline const float area() const { return w * h; }
    inline const float actual_distance(const float x1,
                                       const float y1) const;
    inline const float min_distance(const float x1, const float y1) const;
    inline const float min_max_distance(const float x1,
                                        const float y1) const;
    inline const bool contain(const BoundingBox& bbox) const ;
    inline const bool contain(const float x1, const float y1) const ;
    inline void enlarge(const float x1, const float y1);
    inline void enlarge(const BoundingBox& pbbox);

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

inline const float BoundingBox::actual_distance(const float x1, 
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

inline const float BoundingBox::min_distance(const float x1,
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

inline const float BoundingBox::min_max_distance(const float x1,
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

inline const bool BoundingBox::contain(const float x1,
                                       const float y1) const {
  return (this->enlargement(x1, y1) == 0);
}

inline const bool BoundingBox::contain(const BoundingBox& bbox) const {
  return ((this->enlargement(bbox.x, bbox.y) +
      this->enlargement(bbox.x + bbox.w, bbox.y + bbox.h)) == 0);
}

void BoundingBox::min_bounding_rectangle(
    const BoundingBox& bbox1, const BoundingBox& bbox2,
    float& new_x, float& new_y, float& new_w, float& new_h) {
  const float x_array[] = {bbox1.x, bbox1.x + bbox1.w, 
                           bbox2.x, bbox2.x + bbox2.w};
  const float y_array[] = {bbox1.y, bbox1.y + bbox1.h, 
                           bbox2.y, bbox2.y + bbox2.h};

  min_bounding_rectangle(x_array, y_array, 4, new_x, new_y, new_w, new_h);
}

inline void BoundingBox::min_bounding_rectangle(const float x_array[], 
    const float y_array[], const size_t array_size, float& new_x,
    float& new_y, float& new_w, float& new_h) {
  float new_distance = 0;
  float new_min_x = x_array[0];
  float new_min_y = y_array[0];

  for (size_t index1 = 0; index1 < array_size; index1 ++) {
    if (x_array[index1] < new_min_x) new_min_x = x_array[index1];
    if (y_array[index1] < new_min_y) new_min_y = y_array[index1];

    for (size_t index2 = index1; index2 < array_size; index2 ++) {
      new_distance = abs(x_array[index1] - x_array[index2]);
      if (new_distance > new_w) new_w = new_distance;
      new_distance = abs(y_array[index1] - y_array[index2]);
      if (new_distance > new_h) new_h = new_distance;
    }
  }
  new_x = new_min_x;
  new_y = new_min_y;
}

inline void BoundingBox::enlarge(const float x1, const float y1) {
  const float x_array[] = {x, x + w, x1};
  const float y_array[] = {y, y + h, y1};
  min_bounding_rectangle(x_array, y_array, 3, x, y, w, h);
}

inline void BoundingBox::enlarge(const BoundingBox& bbox) {
  const float x_array[] = {x, x + w, bbox.x, bbox.x + bbox.w};
  const float y_array[] = {y, y + h, bbox.y, bbox.y + bbox.h};
  min_bounding_rectangle(x_array, y_array, 4, x, y, w, h);
}

inline const float BoundingBox::enlargement(const float x1, 
                                            const float y1) const {
  const float x_array[] = {x, x + w, x1};
  const float y_array[] = {y, y + h, y1};
  float new_x = x;
  float new_y = y;
  float new_w = w;
  float new_h = h;
  min_bounding_rectangle(x_array, y_array, 3, 
                         new_x, new_y, new_w, new_h);
  return (new_w * new_h - this->area());
}

inline const float BoundingBox::enlargement(
    const BoundingBox& bbox) const {
  const float x_array[] = {x, x + w, bbox.x, bbox.x + bbox.w};
  const float y_array[] = {y, y + h, bbox.y, bbox.y + bbox.h};
  float new_x = x;
  float new_y = y;
  float new_w = w;
  float new_h = h;
  min_bounding_rectangle(x_array, y_array, 4,
                             new_x, new_y, new_w, new_h);
  return (new_w * new_h - this->area());
}

class Node {
  public:
    Node() { rectangle = new BoundingBox(0.0, 0.0); }
    explicit Node(const float x, const float y) {
      rectangle = new BoundingBox(x, y);
    }
    explicit Node(const size_t ID, const float x, const float y) : id(ID) {
      rectangle = new BoundingBox(x, y);
    }
    explicit Node(const BoundingBox& bbox) {
      rectangle = new BoundingBox(bbox.x, bbox.y);
      rectangle->enlarge(bbox.x + bbox.w, bbox.y + bbox.h);
    }
    ~Node() { delete rectangle; }

    inline void insert(vector<Node*>& container, Node& node);

    void find_seeds(vector<Node*>& containter, Node* &left_seed, 
                    Node* &right_seed) const;
    void quadratic_split(Node& new_leaf, vector<Node*>& parents);
    void quadratic_split(vector<Node*>& parents);
    void split_with_seeds(vector<Node*>& left_container,
        vector<Node*>& right_container, vector<Node*>& container,
        Node* &left_seed, Node* &right_seed, Node* &left_node, 
        Node* &right_node);

    size_t id;
    BoundingBox* rectangle;
    vector<Node*> children;
    vector<Node*> leaves;

    float min_distance;
    float min_max_distance;
};

typedef unordered_map<size_t, Node*> NodeMap;
typedef pair<size_t, Node*> NodePair;

bool compare_leaf(const Node* leaf1, const Node* leaf2) {
  if (fabs(leaf1->min_distance - leaf2->min_distance) < 0.001) {
    return leaf1->id > leaf2->id; 
  } else
    return leaf1->min_distance < leaf2->min_distance;
}

const bool compare_node(const Node* node1, const Node* node2) {
  return node1->min_max_distance < node2->min_max_distance;
}

inline void Node::insert(vector<Node*>& container, Node& node) {
  // push node to children
  container.push_back(&node);
  // enlarge the bounding box
  this->rectangle->enlarge(*node.rectangle); 
}

void Node::find_seeds(vector<Node*>& containter, Node* &left_seed, 
                      Node* &right_seed) const {
  vector<Node*>::const_iterator it1 = containter.begin();
  vector<Node*>::const_iterator it2 = containter.begin();
  float new_x = 0, new_y = 0, new_w = 0, new_h = 0;
  float integral_area = 0;
  float max_integral_area = -numeric_limits<float>::max();

  for (; it1 != containter.end(); it1 ++) {
    for (it2 = it1 + 1; it2 != containter.end(); it2 ++) {
      BoundingBox::min_bounding_rectangle(*(*it1)->rectangle,
          *(*it2)->rectangle, new_x, new_y, new_w, new_h); 

      integral_area = new_w * new_h - (*it1)->rectangle->area() -
                      (*it2)->rectangle->area();
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

void Node::split_with_seeds(vector<Node*>& left_container,
    vector<Node*>& right_container, vector<Node*>& container, 
    Node* &left_seed, Node* &right_seed, Node* &left_node,
    Node* &right_node) {
  // push left and right seed 
  left_container.push_back(left_seed);
  right_container.push_back(right_seed);

  BoundingBox* left_mbbox = left_node->rectangle;
  BoundingBox* right_mbbox = right_node->rectangle;
  float left_enlargement = 0, right_enlargement = 0;
  while (!container.empty()) {
    Node* node = container.back();
    if (node != left_seed && node != right_seed) {
      left_enlargement = left_mbbox->enlargement(*node->rectangle);
      right_enlargement = right_mbbox->enlargement(*node->rectangle);
      if (left_enlargement < right_enlargement) {
        // insert to left node
        left_container.push_back(node);
      } else if (left_enlargement > right_enlargement) {
        // insert to right node
        right_container.push_back(node);
      } else {
        // same enlargement, choose with smaller area 
        if (left_mbbox->area() < right_mbbox->area()) {
          // insert to left node
          left_container.push_back(node);
        } else if (left_mbbox->area() > right_mbbox->area()) {
          // insert to right node
          right_container.push_back(node);
        } else {
          // same area, choose with fewer element
          if (left_container.size() <= right_container.size()) {
            // insert to left node
            left_container.push_back(node);
          } else {
            // insert to right node
            right_container.push_back(node);
          }
        }
      }
    } 
    container.pop_back();
  }
  // enlarge left node
  for (vector<Node*>::iterator it_left = left_container.begin() + 1;
      it_left != left_container.end(); it_left ++) {
    left_node->rectangle->enlarge(*(*it_left)->rectangle);
  }
  // enlarge right node
  for (vector<Node*>::iterator it_right = right_container.begin() + 1;
      it_right != right_container.end(); it_right ++) {
    right_node->rectangle->enlarge(*(*it_right)->rectangle);
  }
}

void Node::quadratic_split(vector<Node*>& parents) {
  Node* left_seed = NULL;
  Node* right_seed = NULL;
  this->find_seeds(this->children, left_seed, right_seed);
  if (left_seed == 0)
    cerr << "left seed null pointer" << endl;
  if (right_seed == 0)
    cerr << "right seed null pointer" << endl;

  // create new left and right node with left and right seed x, y
  Node* left_node = new Node(*left_seed->rectangle);
  Node* right_node = new Node(*right_seed->rectangle);

  this->split_with_seeds(left_node->children, right_node->children, 
      this->children, left_seed, right_seed, left_node, right_node);

  if (!parents.back()) {
      this->insert(this->children, *left_node);
      this->insert(this->children, *right_node);
  } else {
    // insert to parents' children list
    Node* parent = parents.back();
    vector<Node*>::iterator it = parent->children.begin();
    // linearly iterate to find the current node in the parent's list
    for (; (*it) != this && it != parent->children.end(); it ++);

    // remove the current node and insert two new nodes
    parent->children.erase(it); 
    parent->insert(parent->children, *left_node);
    parent->insert(parent->children, *right_node);
  }
}

void Node::quadratic_split(Node& new_leaf, vector<Node*>& parents) {
  // first insert new leaf and enlarge
  this->insert(this->leaves, new_leaf);

  // find most separated seed s1, s2
  Node* left_seed = NULL;
  Node* right_seed = NULL;
  this->find_seeds(this->leaves, left_seed, right_seed);
  if (left_seed == 0)
    cerr << "left leaf seed null pointer" << endl;
  if (right_seed == 0)
    cerr << "right leaf seed null pointer" << endl;

  // create new left and right node with left and right seed x, y
  Node* left_node = new Node(*left_seed->rectangle);
  Node* right_node = new Node(*right_seed->rectangle);
  
  this->split_with_seeds(left_node->leaves, right_node->leaves, 
      this->leaves, left_seed, right_seed, left_node, right_node);
 
  if (!parents.back()) { // current head is top root
    //    cout << "separate parent" << endl;
    this->insert(this->children, *left_node);
    this->insert(this->children, *right_node);
  } else {
    // insert to parents' children list
    Node* parent = parents.back();
    vector<Node*>::iterator it = parent->children.begin();
    // linearly iterate to find the current node in the parent's list
    for (; (*it) != this && it != parent->children.end(); it ++);

    // remove the current node and insert two new nodes
    parent->children.erase(it); 
    parent->insert(parent->children, *left_node);
    parent->insert(parent->children, *right_node);
  }
}

class RTree 
{
  public: 
    RTree() : root(NULL), max_children(50) {}
    RTree(size_t max_child) : root(NULL), max_children(max_child) {}
    ~RTree() {}

    void insert(Node& new_left);
    void search(Node& head, const float query_x, const float query_y,
                const size_t max_query_id, vector<Node*>& list);
    void nsearch(const float query_x, const float query_y,
                 const size_t max_query_id, vector<Node*>& list);

  private:
    void print_tree();
    void print_tree(Node* head);
    Node* root;
    size_t max_children;
};

void RTree::print_tree(Node* head) {
  deque<Node*> node_queue;
  node_queue.push_back(head);

  size_t layer = 0;
  while (!node_queue.empty()) {
    Node* node = node_queue.front();
    cout << "root " << *node->rectangle << endl;    
    for (vector<Node*>::iterator it_node = node->children.begin();
        it_node != node->children.end(); it_node ++) {
      node_queue.push_back(*it_node);
    }
    for (vector<Node*>::iterator it_leaf = node->leaves.begin();
        it_leaf != node->leaves.end(); it_leaf ++) {
      cout << "leaf " << layer << ' ' << (*it_leaf)->id << ' ';
      cout << *(*it_leaf)->rectangle << endl;
    }
    layer ++;
    node_queue.pop_front(); 
  }
}

void RTree::print_tree() {
  print_tree(root);
}

void RTree::insert(Node& new_leaf) {
  BoundingBox& mbbox = *new_leaf.rectangle;
  if (!root) {
    // init root with top-left point of new leaf
    root = new Node(mbbox.x, mbbox.y);
    // enlarge directory rectangle with bottom-right point of new leaf
    root->rectangle->enlarge(mbbox.x + mbbox.w, mbbox.y + mbbox.h);
    root->leaves.push_back(&new_leaf);
    return;
  }
  Node* head = root;   
  vector<Node *> parent_stack;
  parent_stack.push_back(NULL);
  // traverse R-tree top-down
  Node* next_head = NULL;
  while (!head->children.empty()) {
    parent_stack.push_back(head);
    bool found_match = false;
    // first searching node whode DR contains the mbb of new leaf
    vector<Node*>::iterator it_children = head->children.begin();
    for (; it_children != head->children.end(); it_children ++) {
      if ((*it_children)->rectangle->contain(*new_leaf.rectangle)) {
        next_head = *it_children;
        found_match = true;
      }
    }

    // otherwise choose the node with minimal enlargement of the DR
    if (!found_match) {
      vector<Node*>::iterator it_min_enlargement = head->children.begin();
      it_children = head->children.begin(); 
      float min_enlargement_area = FLT_MAX; 
      float enlargement_area = 0;
      for (; it_children != head->children.end(); it_children ++) {
        enlargement_area = (*it_children)->rectangle->
            enlargement(*new_leaf.rectangle); 
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

  // check if the leaf node is not full
  if (head->leaves.size() < max_children) {
    head->insert(head->leaves, new_leaf);
    Node* parent = parent_stack.back();
    // enlarge all parents
    while (parent) {
      parent->rectangle->enlarge(*head->rectangle); 
      parent_stack.pop_back();
      head = parent;
      parent = parent_stack.back();
    }
  } else {
    // Quadratic split
    head->quadratic_split(new_leaf, parent_stack);

    // recursive split parent
    Node* parent = parent_stack.back();
    parent_stack.pop_back();
    while (parent) {
      if (parent->children.size() > max_children) {
        parent->quadratic_split(parent_stack);
      }
      parent->rectangle->enlarge(*head->rectangle);
      head = parent;
      parent = parent_stack.back();
      parent_stack.pop_back();
    } 
  }
}

void RTree::search(Node& head, const float query_x, const float query_y,
                   const size_t max_query_id, vector<Node*>& list) {
  // found leave node
  if (head.children.empty()) {
    vector<Node*>::const_iterator it_leaves = head.leaves.begin();
   
    for(; it_leaves != head.leaves.end(); it_leaves ++) {
      (*it_leaves)->min_distance = (*it_leaves)->rectangle->
          actual_distance(query_x, query_y);
      (*it_leaves)->min_max_distance = (*it_leaves)->rectangle->
          min_max_distance(query_x, query_y);
      list.push_back(*it_leaves);
    }
    if (list.size() >= max_query_id) {
      sort(list.begin(), list.end(), compare_leaf);
      while (list.size() > max_query_id) { list.pop_back(); }
    }
  } else {
    vector<Node*>::const_iterator it_children = head.children.begin();
    for (; it_children != head.children.end(); it_children ++) {
      (*it_children)->min_distance = (*it_children)->rectangle
          ->min_distance(query_x, query_y);
      (*it_children)->min_max_distance = (*it_children)
        ->rectangle->min_max_distance(query_x, query_y);
    } 
    sort(head.children.begin(), head.children.end(), compare_node);
    
    vector<Node*>::iterator it_list = head.children.begin();
    for (; it_list != head.children.end(); it_list ++) {
      // if buffer not full, kepp insert
      if (list.size() < max_query_id) {
        search(*(*it_list), query_x, query_y, max_query_id, list); 
      } else {
      // prune
        sort(list.begin(), list.end(), compare_leaf);
        // if (list.back()->min_distance > (*it_list)->min_max_distance) {
        //   // cout << list.back()->min_distance << ' ';
        //   // cout << (*it_list)->min_max_distance << ' ';
        //   // cout << "downward pruning" << endl;
        //   list.pop_back();
        // }
        // cout << "list size " << list.size() << endl;
        if (!list.empty()) {
          if ((*it_list)->min_distance > list.back()->min_max_distance)
            continue;
        }
        // vector<Node*>::iterator it_compare = head.children.begin();
        // for (it_compare = children_list.begin(); it_compare != it_list &&
        //     it_compare != children_list.end(); it_compare ++) { 
        //   if ((*it_list)->min_distance > (*it_compare)->min_max_distance) {
        //     // cout << "downward pruning" << endl;
        //     continue;
        //   }
        // }
        search(*(*it_list), query_x, query_y, max_query_id, list); 
      }
    } 
  }
}

void RTree::nsearch(const float query_x, const float query_y,
                   const size_t max_query_id, vector<Node*>& list) {
  if (!root) return;   
  Node* closest = NULL;
  search(*root, query_x, query_y, max_query_id, list);
  sort(list.begin(), list.end(), compare_leaf);
}

int main() {
  size_t N = 0, T = 0, Q = 0;
  cin >> T >> Q >> N;

  size_t max_topic_tree_children = T * 0.005;
  const size_t min_children = 4;
  if (max_topic_tree_children < min_children) 
    max_topic_tree_children = min_children;
  RTree topic_tree(max_topic_tree_children);

  NodeMap topics;
  size_t id = 0;
  float x = 0, y = 0;
  for (size_t topic_counter = 0; topic_counter < T; topic_counter ++) {
    cin >> id >> x >> y;
    topics[id] = new Node(id, x, y);
    topic_tree.insert(*topics[id]);
  }

  size_t max_question_tree_children = Q * 0.5;
  if (max_question_tree_children < min_children) 
    max_question_tree_children = min_children; 
  RTree question_tree(max_question_tree_children);
  NodeMap questions;
  size_t topic_number = 0, topic_id;
  for (size_t question_counter = 0; question_counter < Q;
      question_counter ++) {
    cin >> id >> topic_number;
    if (topic_number > 0) {
      cin >> topic_id;
      BoundingBox* topic_mbbox = topics[topic_id]->rectangle;
      questions[id] = new Node(id, topic_mbbox->x, topic_mbbox->y);
      for (size_t topic_counter = 1; topic_counter < topic_number;
          topic_counter ++) {
        cin >> topic_id;
        topic_mbbox = topics[topic_id]->rectangle;
        BoundingBox* question_mbbox = questions[id]->rectangle;
        question_mbbox->enlarge(*topic_mbbox);
        question_mbbox->vertices.push_back(pair<float, float>(
            topics[topic_id]->rectangle->vertices.back().first,
            topics[topic_id]->rectangle->vertices.back().second));
      }
      question_tree.insert(*questions[id]);
    }
  }

  char query_type = '0';
  size_t max_query_id = 0;
  float query_x = 0, query_y = 0;
  vector<Node*> result_list;
  size_t max_length = 0;
  for (int n_counter = 0; n_counter < N; n_counter++) {
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
