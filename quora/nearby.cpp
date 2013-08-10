#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

#define K 2

const float max_w = 1e6 * 1e6;

// Topic class
class Topic {
  private:
    float dim[2];
    float distance;
    int id;
    vector<int> belong_to;
  public:
    Topic(): id(-1), distance(max_w) { dim[0] = -1; dim[1] = -1; }
    Topic(int ID, float dim1, float dim2)
           : id(ID), distance(max_w) { dim[0] = dim1; dim[1] = dim2; }
    ~Topic() {}
    int get_id() { return id; }
    float get_dim(int dim_num) { assert(dim_num < K); return dim[dim_num]; }
    float * get_dims(void) { return dim; }
    void set_id(int id) { this->id = id; }
    void set_dim(float dim, int dim_num) { assert(dim_num < K); this->dim[dim_num] = dim; }
    void set_question(int q_id) { belong_to.push_back(q_id); }
    vector<int>* get_questions(void) { return &belong_to; }
    float get_distance(void) { return distance; }
    void set_distance(float dis) { this->distance = dis; }
    friend ostream& operator<<(ostream& out, Topic &topic);
    friend bool topic_compare(Topic * t1, Topic * t2);
};

// t1 < t2 ?
bool topic_compare(Topic * t1, Topic * t2) {
  if (fabs(t1->distance - t2->distance) <= 0.001) {
    return t1->id > t2->id;
  } else
    return t1->distance < t2->distance;
}

ostream& operator<<(ostream& out, Topic &topic) {
  out << "ID: " << topic.id;;
  for (int i = 0; i < K; i ++) {
    out << " dim" << i << ": " << topic.dim[i];
  } 
  out << endl;
  out << "Questions: ";
  for (vector<int>::iterator it = topic.belong_to.begin();
                    it != topic.belong_to.end(); it ++)
    out << *it << ' ';
  out << endl;
  return out;
}

// Question class
class Question {
  private:
    int id;
    float distance;
    vector<int> topics;
  public:
    Question(): id(-1), distance(max_w) {}
    Question(int ID): id(ID), distance(max_w) {}
    ~Question() {}
    int get_id() { return id; }
    void set_id(int id) { this->id = id; }
    void set_topic(int t_id) { topics.push_back(t_id); }
    friend ostream& operator<<(ostream& out, Question &question);
    friend bool question_compare(Question * t1, Question * t2);
    void set_distance(float dis) { this->distance = dis; }
    float get_distance(void) { return distance; }
};

// t1 < t2 ?
bool question_compare(Question * t1, Question * t2) {
  if (fabs(t1->distance - t2->distance) <= 0.001) {
    return t1->id > t2->id;
  } else
    return t1->distance < t2->distance;
}

ostream& operator<<(ostream& out, Question &question) {
  out << "ID: " << question.id << endl;
  out << "Topics: ";
  for (vector<int>::iterator it = question.topics.begin();
                    it != question.topics.end(); it ++)
    out << *it << ' ';
  out << endl;
  return out;
}

class Tree_Node {
  private:
    Topic * data;  
    float dim;
    int dim_order;
    Tree_Node * left;
    Tree_Node * right;
  public:
    Tree_Node():data(NULL), dim(0.0), dim_order(-1), left(NULL), right(NULL) {}
    Tree_Node(float dim):data(NULL), dim(dim), dim_order(-1), left(NULL), right(NULL) {}
    ~Tree_Node() {}
    int get_dim_order() { return dim_order; }
    void set_dim_order(int dim_order) { this->dim_order = dim_order; }
    void set_data(Topic * data) { this->data = data; };
    Topic * get_data(void) { return data; };
    void set_left(Tree_Node * left) { this->left = left; };
    Tree_Node * get_left(void) { return left; }
    void set_right(Tree_Node * right) { this->right = right; };
    Tree_Node * get_right(void) { return right; }
    float get_dim(void) { return dim; }
    void set_dim(float dim) { this->dim = dim; }
    float get_distance();
};

class KD_Tree {
  private:
    Tree_Node * root;
    float get_distance(float * point1, float * point2);
  public:
    KD_Tree():root(NULL) {}
    ~KD_Tree() {}
    void insert(Topic * node);
    void erase(Topic * node);
    Topic * nn_search(Tree_Node * head, Topic * selected_node, float * point, int depth, float * w);
    void knn_search(float * dim, int num, vector<Topic *>& topic_list);
    void knn_search(float * dim, int num, vector<Question *> &question_list, map<int, Question> &questions);
    void print_tree(void);
    friend ostream& operator<<(ostream &out, KD_Tree & kd_tree);
};

ostream& operator<<(ostream &out, KD_Tree & kd_tree) {
  queue<Tree_Node *> node_queue; 
  node_queue.push(kd_tree.root);
  while (!node_queue.empty()) {
    Tree_Node * node = node_queue.front();
    if (node->get_data()) {
      out << "leaf: " << "Topic " << node->get_data()->get_id();
      out << " dim1 " << node->get_data()->get_dim(0);
      out << " dim2 " << node->get_data()->get_dim(1) << endl;
//      cout << " dim_order " << node->get_dim_order() << endl;
    } else { 
      out << "non-leaf: " << "split " << node->get_dim();
      cout << " dim_order " << node->get_dim_order() << endl;
    }
    if (node->get_left())
      node_queue.push(node->get_left());
    if (node->get_right())
      node_queue.push(node->get_right());
    node_queue.pop();
  }
}

void KD_Tree::print_tree(void) {
  queue<Tree_Node *> node_queue; 
  node_queue.push(root);
  while (!node_queue.empty()) {
    Tree_Node * node = node_queue.front();
    if (node->get_data()) {
      cout << "leaf: " << "Topic " << node->get_data()->get_id();
      cout << " dim1 " << node->get_data()->get_dim(0);
      cout << " dim2 " << node->get_data()->get_dim(1) << endl;
//      cout << " dim_order " << node->get_dim_order() << endl;
    } else { 
      cout << "non-leaf: " << "split " << node->get_dim();
      cout << " dim_order " << node->get_dim_order() << endl;
    }
    if (node->get_left())
      node_queue.push(node->get_left());
    if (node->get_right())
      node_queue.push(node->get_right());
    node_queue.pop();
  }
}

float KD_Tree::get_distance(float * point1, float * point2) {
  float sum = 0;
  for (int i = 0; i < K; i++)
    sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
  return sqrt(sum);
}

Topic * KD_Tree::nn_search(Tree_Node * head, Topic * selected_node, float * point, int depth, float *w) {
  if (!root) return selected_node;
  if (!head->get_left()) {
    if (!head->get_data()) {
//      cout << "empty node" << endl;
      return selected_node;
    }
    Topic * closest_node = head->get_data();
    float distance = 0;
    if ((distance = get_distance(closest_node->get_dims(), point)) < *w) {
      *w = distance; 
      return head->get_data();
    }
    return selected_node;
  } else {
    int dim = depth % K; 
    if (point[dim] <= head->get_dim()) {
      Topic * local_selected_node = nn_search(head->get_left(), selected_node, point, depth + 1, w);
      if (local_selected_node) {
        if (head->get_dim() < (*w + point[dim]) && head->get_dim() > (*w - point[dim])) {
          local_selected_node = nn_search(head->get_right(), local_selected_node, point, depth + 1, w);
        }
      }
      return local_selected_node;
    } else {
      Topic * local_selected_node = nn_search(head->get_right(), selected_node, point, depth + 1, w);
      if (local_selected_node) {
        if (head->get_dim() < (*w + point[dim]) && head->get_dim() > (*w - point[dim])) {
          local_selected_node = nn_search(head->get_left(), local_selected_node, point, depth + 1, w);
        }
      }
      return local_selected_node;
    }
  }
}

void KD_Tree::knn_search(float * dim, int num, vector<Topic *> &topic_list) {
  if (!root) return;
  float min_w = max_w;
  Topic * nn_node = NULL;
  for (int counter = 0; counter < num; counter ++) {
    nn_node = NULL;
    min_w = max_w;
    nn_node = nn_search(root, nn_node, dim, 0, &min_w);
    if (nn_node) {
//      cout << *nn_node;
      nn_node->set_distance(min_w);
      topic_list.push_back(nn_node);
      erase(nn_node);
    } else break;
  }
  sort(topic_list.begin(), topic_list.end(), topic_compare);

  for (int counter = 0; counter < topic_list.size(); counter ++) {
    topic_list[counter]->set_distance(max_w);
    insert(topic_list[counter]);
  }
}

void KD_Tree::knn_search(float * dim, int num, vector<Question *> &question_list, map<int, Question> &questions) {
  if (!root) return;
  float min_w = max_w;
  Topic * nn_node = NULL;
  vector<Topic *> topic_list;
  int question_num = 0;
  set<int> unique_question;
  set<int>::iterator unique_it;
  while (question_list.size() < num) { 
    nn_node = NULL;
    min_w = max_w;
    nn_node = nn_search(root, nn_node, dim, 0, &min_w);
    if (nn_node) {
//      cout << *nn_node;
      topic_list.push_back(nn_node);
      erase(nn_node);
      vector<int> * belong_to = nn_node->get_questions();
      for (vector<int>::iterator it = belong_to->begin(); it != belong_to->end(); it ++) {
        unique_question.insert(*it);
        if (min_w < questions[*it].get_distance()) questions[*it].set_distance(min_w);
      }
    } else break;
  }
  for (unique_it = unique_question.begin(); unique_it != unique_question.end(); unique_it ++) {
    question_list.push_back(&questions[*unique_it]); 
  }
  sort(question_list.begin(), question_list.end(), question_compare);
  for (int counter = 0; counter < topic_list.size(); counter ++) {
    topic_list[counter]->set_distance(max_w);
    insert(topic_list[counter]);
  }
  
  for (int counter = 0; counter < question_list.size(); counter ++)
    question_list[counter]->set_distance(max_w);
}

void KD_Tree::erase(Topic * node) {
//  cout << node->get_id() << endl;
  Tree_Node * head = root;
  Tree_Node * parent = root;
  if (!root) { 
    return;
  }
  while (head->get_left()) {
    parent = head;
    if (head->get_dim() >= node->get_dim(head->get_dim_order())) {
      head = head->get_left();
    } else {
      head = head->get_right();
    }
  }
  if (!head->get_data()) { 
    return;
  }

  if (head->get_data()->get_id() != node->get_id()) {
//    cout  << "not match " << head->get_data()->get_id() << endl;
    return;
  } else {
    if (!parent->get_left()) {
      parent->set_data(NULL);
    } else if (parent->get_dim() >= node->get_dim(parent->get_dim_order())) {
      // prune left
      parent->set_data(parent->get_right()->get_data()); 
      parent->set_dim(parent->get_right()->get_dim()); 
      parent->set_dim_order(parent->get_right()->get_dim_order()); 
      parent->set_left(parent->get_right()->get_left());
      parent->set_right(parent->get_right()->get_right());
    } else {
      // prune right
      parent->set_data(parent->get_left()->get_data()); 
      parent->set_dim(parent->get_left()->get_dim()); 
      parent->set_dim_order(parent->get_left()->get_dim_order()); 
      parent->set_right(parent->get_left()->get_right());
      parent->set_left(parent->get_left()->get_left());
    }
  }
}

void KD_Tree::insert(Topic * node) {
  // initially, create a root node
  int depth = 0;
  if (!root) root = new Tree_Node();
  Tree_Node * head = root;

  // iteratively to find a insert place
  int dim = 0;
  while (head->get_left()) {
    dim = head->get_dim_order();
    if (dim < 0) { dim = depth % K; depth ++; }
    if (node->get_dim(dim) <= head->get_dim())
      head = head->get_left();
    else
      head = head->get_right();
  }
  
  // insert data
  if (!head->get_data()) {
    head->set_dim_order(depth % K);
    head->set_data(node);
  } else {
    // split node 
    dim = head->get_dim_order();
    if (dim < 0) { dim = depth % K; }
    float split = (head->get_data()->get_dim(dim) + node->get_dim(dim)) / 2;
    head->set_dim(split);
    head->set_dim_order(dim);
    Tree_Node * left_node = new Tree_Node;
    Tree_Node * right_node = new Tree_Node;
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

template<typename T>
ostream& operator<<(ostream& out, vector<T *> &list) {
  for (int counter = 0; counter < list.size(); counter ++)
    out << list[counter]->get_id() << ' ';
  out << endl;
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
    topics.insert(make_pair<int, Topic>(id, Topic(id, x, y)));
    kd_tree.insert(&topics[id]);
  }

  // Input Questions
  int Qn = 0, tid;
  map<int, Question> questions;
  for (int q_counter = 0; q_counter < Q; q_counter ++) {
    cin >> id >> Qn;
    questions.insert(make_pair<int, Question>(id, Question(id))); 
    for (int qn_counter = 0; qn_counter < Qn; qn_counter ++) {
      cin >> tid;
      questions[id].set_topic(tid);
      topics[tid].set_question(id);
    }
  }
  
//  cout << kd_tree;
//  cout << "print tree" << endl;

  // input queries
  char query_type = '0';
  int max_query_id = 0;
  float query_dim[K];
   
  vector<Topic *> topic_list;
  vector<Question *> question_list;
  for (int n_counter = 0; n_counter < N; n_counter++) {
    cin >> query_type >> max_query_id >> query_dim[0] >> query_dim[1]; 
    if (query_type == 't') {
      topic_list.clear();
      kd_tree.knn_search(query_dim, max_query_id, topic_list);
      cout << topic_list;
    } else {
      question_list.clear();
      kd_tree.knn_search(query_dim, max_query_id, question_list, questions);
      cout << question_list;
    }
  }

  return 0;
}
