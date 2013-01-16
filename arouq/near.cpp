#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

class Topic {
  unsigned long id;
  double x;
  double y;
  double dis;
  public:
    unordered_set<unsigned long> inQuestions;
    unsigned long get_id() { return id; }
    double get_x() { return x; }
    double get_y() { return y; }
    double get_dis() { return dis; }
    void set_id(unsigned long ID) { id = ID; }
    void set_x(double X) { x = X; }
    void set_y(double Y) { y = Y; }
    void set_dis(double DIS) { dis = DIS; }
    Topic(unsigned long ID, double X, double Y):
      id(ID), x(X), y(Y), dis(0) {}
    ~Topic() {}
    friend ostream& operator<<(ostream& out, Topic* topic);
};

ostream& operator<<(ostream& out, Topic* topic) {
  out << "Topic " << topic->id << ' '  << topic->x << ' ' << topic->y << endl;
  out << "In Questions" << endl;
  for (auto it = topic->inQuestions.begin(); it != topic->inQuestions.end(); ++it) out << *it << ' ';
  out << endl;
  return out;
}

class Question {
  unsigned long id;
  int numQuestions;
  public:
    unordered_set<unsigned long> haveTopics;
    unsigned long get_id() { return id; }
    int get_numQuestions() { return numQuestions; }
    void set_id(unsigned long ID) { id = ID; }
    void set_numQuestions(int num) { numQuestions = num; }
    Question(unsigned long ID, int num):
      id(ID), numQuestions(num) {};
    ~Question() {}
    friend ostream& operator<<(ostream& out, Question*);
};

ostream& operator<<(ostream& out, Question* question) {
  out << "Question " << question->id << ' ' << question->numQuestions << endl;
  out << "Have Topics " << endl;
  for (auto it = question->haveTopics.begin(); it != question->haveTopics.end(); ++it)
    out << *it << ' ';
  out << endl;
  return out;
}

class Query {
  char type;
  int results;
  double x;
  double y;
  public:
    char get_type() { return type; }
    int get_results() { return results; }
    double get_x() { return x; }
    double get_y() { return y; }
    void set_type(char TYPE) { type = TYPE; }
    void set_results(int RESULT) { results = RESULT; }
    void set_x(double X) { x = X; }
    void set_y(double Y) { y = Y; }
    Query(char TYPE, int RESULTS, double X, double Y):
      type(TYPE), results(RESULTS), x(X), y(Y) {}
    ~Query() {}
    friend ostream& operator<<(ostream& out, Query*);
};

ostream& operator<<(ostream& out, Query* query) {
  out << "Query " << query->type << ' ' << query->results << ' '
      << query->x << ' ' << query->y << endl;
  return out;
}

inline double dis(double x1, double y1, double x2, double y2) {
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}


int partition(vector<Topic*>& topic, int p, int r) {
  Topic* pivot = topic[r];
  while (p < r) {
    while (topic[p]->get_dis() < pivot->get_dis()) p++;
    while (topic[r]->get_dis() > pivot->get_dis()) r--;
    if (topic[p]->get_dis() == topic[r]->get_dis()) p++;
    else if (p < r) {
      Topic* tempTopic = topic[p];
      topic[p] = topic[r];
      topic[r] = tempTopic;
    }
  }
  return r;
}

int quick_selection(vector<Topic*>& topic, int p, int r, int k) {
  if (p == r) return p;
  int j = partition(topic, p, r);
  int length = j - p + 1;
  if (length == k) return j;
  else if (k < length) return quick_selection(topic, p, j-1, k);
  else return quick_selection(topic, j+1, r, k-length);
}

void QueryTopic(Query* query, vector<Topic*>& TopicList) {
  unsigned long kth = 0;
  priority_queue<unsigned long> result_local;
  queue<unsigned long> result_queue;
  Topic* lastTopic = NULL;
  int i = 0;
  while (i < TopicList.size()) {
    kth = quick_selection(TopicList, 0, TopicList.size() - 1, ++i);
    Topic* topic = TopicList[kth];
    if (lastTopic != NULL) {
      if (abs(lastTopic->get_dis() - topic->get_dis()) > 0.001) {
        while (result_local.size() > 0) {
          result_queue.push(result_local.top());
          result_local.pop();
        }
        if (result_queue.size() > query->get_results())
          break;
      }
    }
    lastTopic = topic;
    result_local.push(topic->get_id());
//    cout << TopicList[kth]->get_id() << ' ';
  }
  while (result_local.size() > 0) {
    result_queue.push(result_local.top());
    result_local.pop();
  }

  int resultnum = min(query->get_results(), (int)result_queue.size());
  for (int i = 0; i < resultnum; i++) {
    cout << result_queue.front() << ' ';
    result_queue.pop();
  }
  cout << endl;
}

void QueryQuestion(Query* query, unordered_map<unsigned long, Question*>& Questions, vector<Topic*>& TopicList) {
  unsigned long kth = 0;
  int numRes = 0, i = 1;
  unordered_set<unsigned long> result;
  priority_queue<unsigned long> result_local;
  queue<unsigned long> result_queue;
  Topic* lastTopic = NULL;
  while (i <= TopicList.size()) {
    kth = quick_selection(TopicList, 0, TopicList.size() - 1, i++);
    Topic* topic = TopicList[kth];
    if (lastTopic != NULL) {
      if (abs(lastTopic->get_dis() - topic->get_dis()) > 0.001) {
        while (result_local.size() > 0) {
          result_queue.push(result_local.top());
          result_local.pop();
        }
        if (result_queue.size() > query->get_results())
          break;
      }
    }
    lastTopic = topic;

    for (auto it = topic->inQuestions.begin(); it != topic->inQuestions.end(); ++it) {
      unordered_set<unsigned long>::const_iterator got = result.find(*it);
      if ( got == result.end() ) {
        result.insert(*it);
        result_local.push(*it);
      }
    }
  }
  while (result_local.size() > 0) {
    result_queue.push(result_local.top());
    result_local.pop();
  }

  int resultnum = min(query->get_results(), (int)result_queue.size());
  for (int i = 0; i < resultnum; i++) {
    cout << result_queue.front() << ' ';
    result_queue.pop();
  }
  cout << endl;
}

int main(int argc, char** argv) {
  int numTopics = 0, numQuestions = 0, numQueries = 0;
  unordered_map<unsigned long, Topic*> Topics;
  unordered_map<unsigned long, Question*> Questions;
  queue<Query*> Queries;

  cin >> numTopics >> numQuestions >> numQueries;
  // Read topics 
  unsigned long id = 0;
  double x = 0, y = 0;
  for (int i = 0; i < numTopics; i++) {
    cin >> id >> x >> y; 
    Topics.insert(make_pair<unsigned long&, Topic*>(id, new Topic(id, x, y)));
  }
  // Read Questions
  int topicnums;
  unsigned long topicid;
  for (int i = 0; i < numQuestions; i++) {
    cin >> id >> topicnums;
    Questions.insert(make_pair<unsigned long&, Question*>(id, new Question(id, topicnums)));
    for (int j = 0; j < topicnums; j++) {
      cin >> topicid;
      Questions[id]->haveTopics.insert(topicid);
      Topics[topicid]->inQuestions.insert(id);
    }
  }
  // Read Queries
  char querytype = 0;
  int numresults = 0;
  for (int i = 0; i < numQueries; i++) {
    cin >> querytype >> numresults >> x >> y;
    Query* query = new Query(querytype, numresults, x, y);
    Queries.push(query);
  }

//  cout << numTopics << ' ' << numQuestions << ' ' << numQueries << endl;
//  for (auto it = Topics.begin(); it != Topics.end(); ++it)
//    cout << it->second;
//  for (auto it = Questions.begin(); it != Questions.end(); ++it)
//    cout << it->second;

   // Maintain topiclist
  vector<Topic*> TopicList;
  for (auto it = Topics.begin(); it != Topics.end(); ++it)
    TopicList.push_back(it->second);
  
  for (int i = 0; i < numQueries; i++) {
    Query* query = Queries.front();
    for (int i = 0; i < TopicList.size(); i++)
      TopicList[i]->set_dis(dis(TopicList[i]->get_x(), TopicList[i]->get_y(), query->get_x(), query->get_y()));
    if (query->get_type() == 't') {
      QueryTopic(query, TopicList);
    } else if (query->get_type() == 'q') {
      QueryQuestion(query, Questions, TopicList);
    }
    Queries.pop();
  }
 
  return 0;
}


