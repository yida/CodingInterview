#include <iostream>
#include <deque>
#include <vector>
#include <cmath>
#include <utility>
#include <cassert>
#include <unordered_map>

using namespace std;

class BoundingBox {
  public:
    explicit BoundingBox(const float input_x, const float input_y)
        : x(input_x), y(input_y), w(0.0), h(0.0) {}
    ~BoundingBox() {}

    void minimum_bounding_rectangle(const vector<float>& x_array, const vector<float>& y_array,
                                    float* x, float* y, float* new_w, float* new_h) const;
    const float enlargement(const float x1, const float y1) const;
    const float area() const { return w * h; }
    void enlarge(const float x1, const float y1);
    
    float x;
    float y;
    float w;
    float h;
};

void BoundingBox::minimum_bounding_rectangle(const vector<float>& x_array, const vector<float>& y_array,
                                             float* new_x, float* new_y, float* new_w, float* new_h) const {
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
}

void BoundingBox::enlarge(const float x1, const float y1) {
  const float x_array[] = {x, x + w, x1};
  const float y_array[] = {y, y + h, y1};
  vector<float> x_array_vec(x_array, x_array + 3);
  vector<float> y_array_vec(y_array, y_array + 3);
  minimum_bounding_rectangle(x_array_vec, y_array_vec, &x, &y, &w, &h);
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
  minimum_bounding_rectangle(x_array_vec, y_array_vec, &new_x, &new_y, &new_w, &new_h);
  return (new_w * new_h - this->area());
}

class Leaf {
  public:
    explicit Leaf(const size_t ID, const float x, const float y) : id(ID) {
      minimum_bounding_box = new BoundingBox(x, y);
    }
    virtual ~Leaf() { delete minimum_bounding_box; }

    size_t id;
    BoundingBox* minimum_bounding_box;
};

class Node {
  public:
    Node() { directory_rectangle = new BoundingBox(0.0, 0.0); }
    explicit Node(const float x, const float y) {
      directory_rectangle = new BoundingBox(x, y);
    }
    virtual ~Node() { delete directory_rectangle; }

    BoundingBox* directory_rectangle;
    deque<Node*> children;
    deque<Leaf*> leaves;
};

class RTree {
  public: 
    RTree() : root(NULL) {}
    ~RTree() {}

    void insert(Leaf* new_left);

  private:
    Node* root;
};

void RTree::insert(Leaf* new_leaf) {
  if (!root) {
    BoundingBox* mbbox = new_leaf->minimum_bounding_box;
    // init root with top-left point of new leaf
    root = new Node(mbbox->x, mbbox->y);
    // enlarge directory rectangle with bottom-right point of new leaf
    root->directory_rectangle->enlarge(mbbox->x + mbbox->w, mbbox->y + mbbox->h);
  }
   
}

int main() {
  typedef unordered_map<size_t, Leaf*> LeafMap;

  size_t N = 0, T = 0, Q = 0;
  cin >> T >> Q >> N;

  RTree topic_tree;
  LeafMap topics;
  size_t id = 0;
  float x = 0, y = 0;
  for (size_t topic_counter = 0; topic_counter < T; topic_counter ++) {
    cin >> id >> x >> y;
    topics[id] = new Leaf(id, x, y);
  }

  RTree question_tree;
  LeafMap questions;
  size_t topic_number = 0, topic_id;
  for (size_t question_counter = 0; question_counter < Q; question_counter ++) {
    cin >> id >> topic_number;
    if (topic_number > 0) {
      cin >> topic_id;
      questions[id] = new Leaf(id, topics[topic_id]->minimum_bounding_box->x,
                                   topics[topic_id]->minimum_bounding_box->y);
      for (size_t topic_counter = 1; topic_counter < topic_number; topic_counter ++) {
        cin >> topic_id;
        questions[id]->minimum_bounding_box->enlarge(topics[topic_id]->minimum_bounding_box->x,
                                                     topics[topic_id]->minimum_bounding_box->y);
      }
    }
  }

  ////////////////////////////////////////
  // for (LeafMap::iterator it = topics.begin(); it != topics.end(); it ++) {
  //   cout << it->second->minimum_bounding_box->x << ' ' << it->second->minimum_bounding_box->y << endl;
  // }

  // cout << "questions " << endl;
  // for (LeafMap::iterator it = questions.begin(); it != questions.end(); it ++) {
  //   cout << it->first << ' ' << it->second->minimum_bounding_box->area();
  //   cout << ' ' << it->second->minimum_bounding_box->x;
  //   cout << ' ' << it->second->minimum_bounding_box->y << endl;
  // }
  ////////////////////////////////////////
 
  return 0;
}
