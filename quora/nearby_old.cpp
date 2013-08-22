#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cassert>
#include <queue>
#include <functional>
#include <ctime>

using namespace std;

const int K = 2;

const float max_w = 1e6 * sqrt(2);

// Question class
class Question {
  public:
    Question() : id(-1), distance(max_w) {}
    explicit Question(const int ID) : id(ID), distance(max_w) {}
    ~Question() {}

    void set_id(const int id) { this->id = id; }
    void set_topic(const int t_id) { topics.push_back(t_id); }
    void set_distance(const float dis) { this->distance = dis; }

    int get_id() const { return id; }
    float get_distance(void) const { return distance; }
    const bool less_than(const Question* q2);
  private:
    friend ostream& operator<<(ostream& out, Question &question);

    int id;
    float distance;
    vector<int> topics;
};

class compare_question {
  public:
    const bool operator()(const Question* q1, const Question* q2) const {
      if (abs(q1->get_distance() - q2->get_distance()) <= 0.001) {
        return q1->get_id() > q2->get_id();
      } else {
        return q1->get_distance() < q2->get_distance();
      }
    }
};

ostream& operator<<(ostream& out, const Question &question) {
  out << "ID: " << question.get_id() << endl;
  return out;
}

const bool Question::less_than(const Question* q2) {
  if (fabs(this->distance - q2->get_distance()) <= 0.001) {
    return this->id > q2->get_id();
  } else
    return this->distance < q2->get_distance();
}

// Topic class
class Topic {
  public:
    Topic(): id(-1), distance(max_w) { dim[0] = -1; dim[1] = -1; }
    Topic(const int ID, const float dim1, const float dim2) 
        : id(ID), distance(max_w) { dim[0] = dim1; dim[1] = dim2; }
    ~Topic() {}

    void set_id(const int id) { this->id = id; }
    void set_dim(const float dim, const int dim_num);
    void set_question(Question * question) { questions.push_back(question); }
    void set_distance(const float dis) { this->distance = dis; }

    const vector<Question *>* get_questions(void) const { return &questions; }
    const float get_distance(void) const { return distance; }
    const int get_id() const { return id; }
    const float get_dim(int dim_num) const { assert(dim_num < K); return dim[dim_num]; }
    const float * get_dims(void) const { return dim; }
    const bool less_than(const Topic* t);
  private:
    friend ostream& operator<<(ostream& out, Topic &topic);

    float dim[2];
    float distance;
    int id;
    vector<Question *> questions;
};

void Topic::set_dim(const float dim, const int dim_num) { 
  assert(dim_num < K); 
  this->dim[dim_num] = dim; 
}

const bool Topic::less_than(const Topic* t2) {
  if (fabs(this->distance - t2->get_distance()) <= 0.001) {
    return this->id < t2->get_id();
  } else
    return this->distance > t2->get_distance();
}

class compare_topic {
  public:
    const bool operator()(const Topic* t1, const Topic* t2) const {
      if (fabs(t1->get_distance() - t2->get_distance()) <= 0.001) {
        return t1->get_id() > t2->get_id();
      } else
        return t1->get_distance() < t2->get_distance();
    }
};

ostream& operator<<(ostream& out, const Topic &topic) {
  out << "ID: " << topic.get_id();
  for (int i = 0; i < K; i ++) {
    out << " dim" << i << ": " << topic.get_dim(i);
  out << " distance: " << topic.get_distance();
  } 
  out << endl;
  out << "Questions: ";
  const vector<Question *>* question = topic.get_questions();
  vector<Question *>::const_iterator it  = question->begin();
  for (; it != question->end(); it ++)
    out << (*it)->get_id() << ' ';
  out << endl;
  return out;
}

template<typename T>
ostream& operator<<(ostream& out, vector<T *> &list) {
  for (int counter = 0; counter < list.size(); counter ++)
    out << list[counter]->get_id() << ':' << list[counter]->get_distance() << ' '; // << list[counter]->get_distance() << endl;
  out << endl;
}

template<typename T>
ostream& operator<<(ostream& out, deque<T *> &list) {
  for (int counter = 0; counter < list.size(); counter ++)
    out << list[counter]->get_id() << ' ';
  out << endl;
}

template<typename T, class T_Compare>
ostream& operator<<(ostream& out, priority_queue<T *, vector<T *>, T_Compare> &list) {
  while (!list.empty() > 0) {
    out << list.top()->get_id() << ' ';
    list.pop();
  }
}

class Tree_Node {
  public:
    Tree_Node() : data(NULL), dim_order(-1), left(NULL), right(NULL) {
        dim[0] = 0.0, dim[1] = 0.0; }
    Tree_Node(const float dim1, const float dim2) 
        : data(NULL), dim_order(-1), left(NULL), right(NULL) {
        dim[0] = dim1, dim[2] = dim2; 
    }
    ~Tree_Node() {}

    void set_data(Topic * data) { this->data = data; };
    void set_dim_order(int dim_order) { this->dim_order = dim_order; }
    void set_left(Tree_Node * left) { this->left = left; };
    void set_right(Tree_Node * right) { this->right = right; };
    void set_dim(const float dim, const int dim_num) { 
        assert(dim_num < K);
        this->dim[dim_num] = dim; 
    }
    void set_rectangle_value(const float value, const int index) {
        assert(index < K * 2);
        this->rectangle[index] = value;
    }
    void set_rectangle(const float x1, const float y1, const float x2, const float y2) {
      rectangle[0] = x1;
      rectangle[1] = y1;
      rectangle[2] = x2;
      rectangle[3] = y2;
    }

    Topic * get_data(void) const { return data; };
    const float get_dim(int dim_num) const { assert(dim_num < K); return dim[dim_num]; }
    const float * get_dims(void) const { return dim; }
    const int get_dim_order() const { return dim_order; }
    const float get_rectangle_value(int index) const { assert(index < 2 * K); return rectangle[index]; } 
    const float * get_rectangle(void) const { return rectangle; }
    Tree_Node * get_left(void) const { return left; }
    Tree_Node * get_right(void) const { return right; }
  
    void assign(Tree_Node* input_node);
  private:
    Topic * data;  
    float dim[2];
    float rectangle[4]; // diagnal, x1, y1, x2, y2
    int dim_order;
    Tree_Node * left;
    Tree_Node * right;
};

void Tree_Node::assign(Tree_Node* input_node) {
  Tree_Node* new_left = input_node->get_left();
  Tree_Node* new_right = input_node->get_right();
  this->data = input_node->get_data();
  for (int i = 0; i < K; i++)
    this->dim[i] = input_node->get_dim(i);
  this->dim_order = input_node->get_dim_order();
  this->left = new_left;
  this->right = new_right;
}

class KD_Tree {
  public:
    KD_Tree() : root(NULL) {}
    ~KD_Tree() {}

    void insert(Topic * node);
    void erase(Topic * node);
    void nn_search(const Tree_Node * head, const float * point, const int max_num, 
                   const int depth, vector<Topic *>& topic_list, set<Topic *>& selected_id);
    void nn_search(const Tree_Node * head, const float * point, const int max_num, 
                   const int depth, vector<Question *>& question_list, 
                   set<int>& unique_question_id, set<Question *>& selected_id);
    void knn_search(const float * point, const int max_num, vector<Topic *>& topic_list);
    void knn_search(const float * point, const int max_num, vector<Question *>& question_list);
    const bool circle_rectangle_intersect(const float * center, const float radius, const float * rectangle);
    const bool line_circle_intersect(const float * center, const float radius, const float x1, const float y1,
                                     const float x2, const float y2) const;
    void export_tree();
  private:
    float get_distance(const float * point1, const float * point2);
    friend ostream& operator<<(ostream &out, KD_Tree & kd_tree);
    void print_tree(Tree_Node * head);
    void print_leaf(Tree_Node * head);

    Tree_Node * root;
};

ostream& operator<<(ostream &out, KD_Tree & kd_tree) {
  queue<Tree_Node *> node_queue; 
  node_queue.push(kd_tree.root);
  while (!node_queue.empty()) {
    Tree_Node * node = node_queue.front();
    if (node->get_data()) {
      out << "leaf: " << "Topic " << node->get_data()->get_id();
      out << " dim1 " << node->get_data()->get_dim(0);
      out << " dim2 " << node->get_data()->get_dim(1);
      out << " rec " << node->get_rectangle_value(0) << ' ' << node->get_rectangle_value(1) << ' '
          << node->get_rectangle_value(2) << ' ' << node->get_rectangle_value(3);
      out << endl;
    } else { 
      out << "non-leaf: " << "split ";
      for (int dim_counter = 0; dim_counter < K; dim_counter++)
        out << node->get_dim(dim_counter);
      out << " rec " << node->get_rectangle_value(0) << ' ' << node->get_rectangle_value(1) << ' '
          << node->get_rectangle_value(2) << ' ' << node->get_rectangle_value(3);
      cout << " dim_order " << node->get_dim_order() << endl;
    }
    if (node->get_left())
      node_queue.push(node->get_left());
    if (node->get_right())
      node_queue.push(node->get_right());
    node_queue.pop();
  }
}

void KD_Tree::export_tree() {
  queue<Tree_Node *> node_queue; 
  node_queue.push(root);
  while (!node_queue.empty()) {
    Tree_Node * node = node_queue.front();
    if (!node->get_data()) {
      for (int dim_counter = 0; dim_counter < K; dim_counter++)
        cout << node->get_dim(dim_counter) << ' ';
      cout << node->get_dim_order() << ' ' << 0;
      cout << endl;
    } else {
      for (int dim_counter = 0; dim_counter < K; dim_counter++)
        cout << node->get_data()->get_dim(dim_counter) << ' ';
      cout << -1 << ' ' << node->get_data()->get_id();
      cout << endl;
    }
    if (node->get_left())
      node_queue.push(node->get_left());
    if (node->get_right())
      node_queue.push(node->get_right());
    node_queue.pop();
  }
}

void KD_Tree::print_tree(Tree_Node* head) {
  queue<Tree_Node *> node_queue; 
  node_queue.push(head);
  while (!node_queue.empty()) {
    Tree_Node * node = node_queue.front();
    if (node->get_data()) {
      cout << "leaf: " << "Topic " << node->get_data()->get_id();
      cout << " dim1 " << node->get_data()->get_dim(0);
      cout << " dim2 " << node->get_data()->get_dim(1) << endl;
    } else { 
      cout << "non-leaf: " << "split " << node->get_dim(node->get_dim_order());
      cout << " dim_order " << node->get_dim_order() << endl;
    }
    if (node->get_left())
      node_queue.push(node->get_left());
    if (node->get_right())
      node_queue.push(node->get_right());
    node_queue.pop();
  }
}

void KD_Tree::print_leaf(Tree_Node* head) {
  queue<Tree_Node *> node_queue; 
  node_queue.push(head);
  while (!node_queue.empty()) {
    Tree_Node * node = node_queue.front();
    if (node->get_data()) {
      cout << "leaf: " << "Topic " << node->get_data()->get_id();
      cout << " dim1 " << node->get_data()->get_dim(0);
      cout << " dim2 " << node->get_data()->get_dim(1) << endl;
    }
    if (node->get_left())
      node_queue.push(node->get_left());
    if (node->get_right())
      node_queue.push(node->get_right());
    node_queue.pop();
  }
}

float KD_Tree::get_distance(const float * point1, const float * point2) {
  float sum = 0;
  for (int i = 0; i < K; i++)
    sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
  return sqrt(sum);
}

void KD_Tree::nn_search(const Tree_Node * head, const float * point, const int max_num, 
                        const int depth, vector<Topic *>& topic_list, set<Topic *>& selected_id) {
  if (!head) return;
  float distance = 0;
  if (!head->get_left()) {
    if (topic_list.empty()) {
      // initiate queue with closest point
      distance = get_distance(point, head->get_data()->get_dims());
      head->get_data()->set_distance(distance);
      selected_id.insert(head->get_data());
      topic_list.push_back(head->get_data());
      cout << "init " << head->get_data()->get_id() << endl;
      push_heap(topic_list.begin(), topic_list.end());
    } else if (topic_list.size() < max_num) {
      // insert maximum of point whenever possible
      distance = get_distance(point, head->get_data()->get_dims());
      selected_id.insert(head->get_data());
      head->get_data()->set_distance(distance);
      cout << "extend " << head->get_data()->get_id() << endl;
      topic_list.push_back(head->get_data());
      push_heap(topic_list.begin(), topic_list.end());
      make_heap(topic_list.begin(), topic_list.end(), compare_topic());
    } else {
      distance = get_distance(point, head->get_data()->get_dims());
      if (head->get_data()->get_distance() > distance) {
        head->get_data()->set_distance(distance);
        selected_id.insert(head->get_data());
      }
      if (head->get_data()->less_than(topic_list.front())) {
        cout << "remove " << topic_list.front()->get_id() << endl;
        pop_heap(topic_list.begin(), topic_list.end(), compare_topic());
        topic_list.pop_back();
        topic_list.push_back(head->get_data());
        push_heap(topic_list.begin(), topic_list.end());
        cout << "update " << head->get_data()->get_id() << endl;
      }
      make_heap(topic_list.begin(), topic_list.end(), compare_topic());
    }
  } else {
    int dim = depth % K;
    float radius = 0;
    if (topic_list.size() < max_num)
      radius = max_w;
    else
      radius = topic_list.front()->get_distance();

    // prune area not in range
    bool left_intersected = circle_rectangle_intersect(point, radius, head->get_left()->get_rectangle());
    if (not left_intersected) {
      cout << "left prune " << endl;
      print_leaf(head->get_left());
    }
    bool right_intersected = circle_rectangle_intersect(point, radius, head->get_right()->get_rectangle());
    if (not right_intersected) {
      cout << "right prune " << endl;
      print_leaf(head->get_right());
    }

    if (point[dim] <= head->get_dim(dim)) {
      if (left_intersected)
        nn_search(head->get_left(), point, max_num, depth + 1, topic_list, selected_id);
      if (right_intersected)
        nn_search(head->get_right(), point, max_num, depth + 1, topic_list, selected_id);
    } else {
      if (right_intersected)
        nn_search(head->get_right(), point, max_num, depth + 1, topic_list, selected_id);
      if (left_intersected)
        nn_search(head->get_left(), point, max_num, depth + 1, topic_list, selected_id);
    } 
  }
}

const bool KD_Tree::line_circle_intersect(const float * center, const float r, const float x1, 
                                          const float y1, const float x2, const float y2) const {
  // line circle intersect check for ony horizontal and vertical line
  float delta = 0;
  float X1 = 0, X2 = 0, Y1 = 0, Y2 = 0;
  if (x1 == x2) {
    delta = r * r - (x1 - center[0]) * (x1 - center[0]); 
    if (delta < 0) return false;
    Y1 = -sqrt(delta) + center[1];
    Y2 = sqrt(delta) + center[1];
    if ((Y1 <= y2) && (Y1 >= y1)) 
      return true;
    else 
      return false;
    if ((Y2 <= y2) && (Y2 >= y1)) 
      return true;
    else 
      return false;
  } else if (y1 == y2) {
    delta = r * r - (y1 - center[1]) * (y1 - center[1]); 
    if (delta < 0) return false;
    X1 = -sqrt(delta) + center[0];
    X2 = sqrt(delta) + center[0];
    if ((X1 <= x2) && (X1 >= x1))
      return true;
    else
      return false;
    if ((X2 <= x2) && (X2 >= x1))
      return true;
    else
      return false;
  }
  return false;
}

const bool KD_Tree::circle_rectangle_intersect(const float * center, const float radius,
                                               const float * rectangle) {
  // circle center inside rectangle
  if ((center[0] <= rectangle[1]) && (center[0] >= rectangle[0]) &&
      (center[1] <= rectangle[3]) && (center[1] >= rectangle[2])) {
//    cout << "center inside " << ' ';
//    cout << center[0] << ' ' << center[1] << ' ' << radius; 
//    cout << ' ' << rectangle[0] << ' ' << rectangle[1] << ' ' << rectangle[2] << ' ' << rectangle[3] << endl;
    return true;
  }
  // one of four side rectangle intersect with circle
  float x1 = rectangle[0];
  float y1 = rectangle[1];
  float x2 = rectangle[2];
  float y2 = rectangle[3];
  // (x1, y1), (x1, y2)
  if (line_circle_intersect(center, radius, x1, y1, x1, y2)) {
//    cout << "side intersect 1 " << ' ';
//    cout << center[0] << ' ' << center[1] << ' ' << radius; 
//    cout << ' ' << rectangle[0] << ' ' << rectangle[1] << ' ' << rectangle[2] << ' ' << rectangle[3] << endl;
    return true;
  }
  // (x1, y2), (x2, y2)
  if (line_circle_intersect(center, radius, x1, y2, x2, y2)) {
//    cout << "side intersect 2 " << ' ';
//    cout << center[0] << ' ' << center[1] << ' ' << radius; 
//    cout << ' ' << rectangle[0] << ' ' << rectangle[1] << ' ' << rectangle[2] << ' ' << rectangle[3] << endl;
    return true;
  }
  // (x2, y1) (x2, y2)
  if (line_circle_intersect(center, radius, x2, y1, x2, y2)) {
//    cout << "side intersect 3 " << ' ';
//    cout << center[0] << ' ' << center[1] << ' ' << radius; 
//    cout << ' ' << rectangle[0] << ' ' << rectangle[1] << ' ' << rectangle[2] << ' ' << rectangle[3] << endl;
    return true;
  }
  // (x1, y1) (x2, y1)
  if (line_circle_intersect(center, radius, x1, y1, x2, y1)) {
//    cout << "side intersect 4 " << ' ';
//    cout << center[0] << ' ' << center[1] << ' ' << radius; 
//    cout << ' ' << rectangle[0] << ' ' << rectangle[1] << ' ' << rectangle[2] << ' ' << rectangle[3] << endl;
    return true;
  }
    
  // all points in circle
  if ((fabs(center[0] - x1) <= radius && fabs(center[1] - y1) <= radius) && 
     (fabs(center[0] - x1) <= radius && fabs(center[1] - y2) <= radius) && 
     (fabs(center[0] - x2) <= radius && fabs(center[1] - y2) <= radius) && 
     (fabs(center[0] - x2) <= radius && fabs(center[1] - y1) <= radius)) {
//    cout << "all points in circle" << endl;
    return true; 
  }
  
  return false;
}

void KD_Tree::knn_search(const float * point, const int max_num, vector<Topic *>& topic_list) {
  set<Topic *> selected_id;
  nn_search(root, point, max_num, 0, topic_list, selected_id);
  sort_heap(topic_list.begin(), topic_list.end(), compare_topic());

  int length = min(max_num, static_cast<int>(topic_list.size()));
  for (int counter = 0; counter < length; counter ++) {
    cout << topic_list[counter]->get_id() << ':' 
         << topic_list[counter]->get_distance() << endl;
  }

  for (set<Topic *>::iterator it = selected_id.begin(); it != selected_id.end(); it ++) {
    (*it)->set_distance(max_w);
  }
}

void KD_Tree::nn_search(const Tree_Node * head, const float * point, const int max_num, 
                        const int depth, vector<Question *>& question_list, 
                        set<int>& unique_question_id, set<Question *>& selected_id) {
  if (!head) return;
  float distance = 0;
  const vector<Question *>* questions;
  set<int>::iterator unique_it;
  vector<Question *>::const_iterator it;
  if (!head->get_left()) {
    if (question_list.empty()) {
      distance = get_distance(point, head->get_data()->get_dims());
      questions = head->get_data()->get_questions();
      for (it = questions->begin(); it != questions->end(); it ++) {
        (*it)->set_distance(distance);
        selected_id.insert(*it);
        // insert to unique id set
//        cout << "init insert " << (*it)->get_id() << endl;
        unique_question_id.insert((*it)->get_id());
        question_list.push_back((*it));
        push_heap(question_list.begin(), question_list.end());
      }
      make_heap(question_list.begin(), question_list.end(), compare_question());
    } else if (question_list.size() < max_num) {
      distance = get_distance(point, head->get_data()->get_dims());
      questions = head->get_data()->get_questions();
      for (it = questions->begin(); it != questions->end(); it ++) {
        if ((*it)->get_distance() > distance) { 
          (*it)->set_distance(distance);
          selected_id.insert(*it);
        }
        if ((unique_it = unique_question_id.find((*it)->get_id())) == unique_question_id.end()) {
          // insert to unique id set if not presented
          unique_question_id.insert((*it)->get_id());
          question_list.push_back((*it));
          push_heap(question_list.begin(), question_list.end());
//          cout << "extend insert " << (*it)->get_id() << endl;
        }
      }
      make_heap(question_list.begin(), question_list.end(), compare_question());
    } else {
      distance = get_distance(point, head->get_data()->get_dims());
      // update question distance
      questions = head->get_data()->get_questions();
      for (it = questions->begin(); it != questions->end(); it ++) {
        if ((*it)->get_distance() > distance) {
          (*it)->set_distance(distance);
          selected_id.insert(*it);
        }
      }
      make_heap(question_list.begin(), question_list.end(), compare_question());

      // update question_list
      for (it = questions->begin(); it != questions->end(); it ++) {
        if ((unique_it = unique_question_id.find((*it)->get_id())) == unique_question_id.end()) {
          if ((*it)->less_than(question_list.front())) {
          // only insert new one
            // remove the front in heap
            unique_question_id.erase(question_list.front()->get_id());
            pop_heap(question_list.begin(), question_list.end());
//            cout << "erase " << question_list.front()->get_id() << endl;
            question_list.pop_back();
            make_heap(question_list.begin(), question_list.end(), compare_question());
            // insert node
            unique_question_id.insert((*it)->get_id());
//            cout << "update " << (*it)->get_id() << endl;
            question_list.push_back((*it));
            push_heap(question_list.begin(), question_list.end());
            make_heap(question_list.begin(), question_list.end(), compare_question());
          }
        }
      }
    }
  } else {
    int dim = depth % K;
    float radius = 0;
    if (question_list.size() < max_num)
      radius = max_w;
    else
      radius = question_list.front()->get_distance();
    // prune area not in range
    bool left_intersected = circle_rectangle_intersect(point, radius, 
                                                  head->get_left()->get_rectangle());
//    if (not left_intersected) 
//      cout << "left pruned" << endl;
    bool right_intersected = circle_rectangle_intersect(point, radius, 
                                             head->get_right()->get_rectangle());
//    if (not right_intersected) 
//      cout << "right pruned" << endl;

    if (point[dim] <= head->get_dim(dim)) {
      if (left_intersected)
        nn_search(head->get_left(), point, max_num, depth + 1, question_list, 
                  unique_question_id, selected_id);
      if (right_intersected)
        nn_search(head->get_right(), point, max_num, depth + 1, question_list, 
                  unique_question_id, selected_id);
     } else {
      if (right_intersected)
        nn_search(head->get_right(), point, max_num, depth + 1, question_list, 
                  unique_question_id, selected_id);
      if (left_intersected)
        nn_search(head->get_left(), point, max_num, depth + 1, question_list, 
                  unique_question_id, selected_id);
    } 
  }
}

void KD_Tree::knn_search(const float * point, const int max_num, 
                         vector<Question *>& question_list) {
  set<int> unique_question_id;
  set<Question *> selected_id;
  nn_search(root, point, max_num, 0, question_list, unique_question_id, selected_id); 
  sort_heap(question_list.begin(), question_list.end(), compare_question());

  for (set<Question *>::iterator it = selected_id.begin(); it != selected_id.end(); it ++) {
    (*it)->set_distance(max_w);
  }
}

void KD_Tree::erase(Topic * node) {
  Tree_Node * head = root;
  Tree_Node * parent = root;
  int dim_order = 0;
  if (!root) { 
    return;
  }
  while (head->get_left()) {
    parent = head;
    dim_order = head->get_dim_order();
    if (head->get_dim(dim_order) >= node->get_dim(dim_order)) {
      head = head->get_left();
    } else {
      head = head->get_right();
    }
  }
  if (!head->get_data()) { 
    return;
  }

  if (head->get_data()->get_id() != node->get_id()) {
    return;
  } else {
    dim_order = parent->get_dim_order();
    if (!parent->get_left()) {
      parent->set_data(NULL);
    } else if (parent->get_dim(dim_order) >= node->get_dim(dim_order)) {
      // prune left
      parent->assign(parent->get_right());
    } else {
      // prune right
      parent->assign(parent->get_left());
    }
  }
}

void KD_Tree::insert(Topic * node) {
  // initially, create a root node
  int depth = 0;
  if (!root) { 
    root = new Tree_Node();
    root->set_rectangle(0.0, 0.0, 1000000.0, 1000000.0);
  }
  Tree_Node * head = root;
  Tree_Node * parent = root;

  // iteratively to find a insert place
  int dim = 0;
  while (head->get_left()) {
    dim = depth % K;
    if (node->get_dim(dim) <= head->get_dim(dim)) {
      parent = head;
      head = head->get_left();
    } else {
      parent = head;
      head = head->get_right();
    }
    depth ++;
  }
  
  // insert data
  if (!head->get_data()) {
    for (int dim_counter = 0; dim_counter < K; dim_counter ++)
      head->set_dim(parent->get_dim(dim_counter), dim_counter);
    head->set_dim_order(depth % K);
    head->set_data(node);
  } else {
    // split node 
    dim = head->get_dim_order();
    if (dim < 0) { dim = depth % K; }
    float split = (head->get_data()->get_dim(dim) + node->get_dim(dim)) / 2;
    head->set_dim(split, dim);
    head->set_dim_order(dim);
    Tree_Node * left_node = new Tree_Node;
    Tree_Node * right_node = new Tree_Node;

    int other_dim = (depth + 1) % K;
    left_node->set_rectangle_value(head->get_rectangle_value(0), 0);
    left_node->set_rectangle_value(head->get_rectangle_value(1), 1);
    left_node->set_rectangle_value(split, dim + 2);
    left_node->set_rectangle_value(head->get_rectangle_value(other_dim + 2), other_dim + 2);
    
    right_node->set_rectangle_value(head->get_rectangle_value(other_dim + 2), other_dim + 2);
    right_node->set_rectangle_value(split, dim);
    right_node->set_rectangle_value(head->get_rectangle_value(2), 2);
    right_node->set_rectangle_value(head->get_rectangle_value(3), 3);

    for (int dim_counter = 0; dim_counter < K; dim_counter++) {
      left_node->set_dim(head->get_dim(dim_counter), dim_counter);
      right_node->set_dim(head->get_dim(dim_counter), dim_counter);
    }

    if (node->get_dim(dim) <= split) {
      left_node->set_data(node);
      right_node->set_data(head->get_data());
    } else {
      left_node->set_data(head->get_data());
      right_node->set_data(node);
    }
    head->set_left(left_node);
    head->set_right(right_node);
    head->set_data(NULL);
  }
}



int main(int argc, char ** argv) {
  KD_Tree kd_tree;

  int T = 0, Q = 0, N = 0;
  // Input T Q N
  cin >> T >> Q >> N;
  // Input topics 
  map<int, Topic> topics;
  int id = 0; 
  float x = 0, y = 0;
  for (int t_counter = 0; t_counter < T; t_counter ++) {
    cin >> id >> x >> y; 
    topics[id] = Topic(id, x, y);
    kd_tree.insert(&topics[id]);
  }

  // Input Questions
  int Qn = 0, tid;
  map<int, Question> questions;
  for (int q_counter = 0; q_counter < Q; q_counter ++) {
    cin >> id >> Qn;
    questions[id] = Question(id); 
    for (int qn_counter = 0; qn_counter < Qn; qn_counter ++) {
      cin >> tid;
      questions[id].set_topic(tid);

      topics[tid].set_question(&questions[id]);
    }
  }
  
  // input queries
  char query_type = '0';
  int max_query_id = 0;
  float query_dim[K];
  
  vector<Topic *> topic_list;
  make_heap(topic_list.begin(), topic_list.end(), compare_topic());
  vector<Question *> question_list;
  make_heap(question_list.begin(), question_list.end(), compare_question());
  for (int n_counter = 0; n_counter < N; n_counter++) {
    cin >> query_type >> max_query_id >> query_dim[0] >> query_dim[1]; 
    if (query_type == 't') {
      topic_list.clear();
      kd_tree.knn_search(query_dim, max_query_id, topic_list);

      int length = min(max_query_id, (int)topic_list.size());
      for (int counter = 0; counter < length; counter ++) {
        cout << topic_list[counter]->get_id() << ' ';
      }
      cout << endl;

//      cout << kd_tree;
//      kd_tree.export_tree();
    } else {
      question_list.clear();
      kd_tree.knn_search(query_dim, max_query_id, question_list);

      int length = min(max_query_id, (int)question_list.size());
      for (int counter = 0; counter < length; counter ++) {
        cout << question_list[counter]->get_id() << ' ';
      }
      cout << endl;
    }
  }

  return 0;
}
