#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

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
  double pivot = topic[r]->get_dis();
  while (p < r) {
    while (topic[p]->get_dis() < pivot) p++;
    while (topic[r]->get_dis() > pivot) r--;
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
  int result = min(query->get_results(), (int)TopicList.size());
  for (int i = 1; i <= result; i++) {
    kth = quick_selection(TopicList, 0, TopicList.size() - 1, i);
    cout << TopicList[kth]->get_id() << ' ';
  }
  cout << endl;
}

void QueryQuestion(Query* query, unordered_map<unsigned long, Question*>& Questions, vector<Topic*>& TopicList) {
  unsigned long kth = 0;
  int numRes = 0, i = 1;
  unordered_set<unsigned long> result;
  while (result.size() < query->get_results() && i <= TopicList.size()) {
    kth = quick_selection(TopicList, 0, TopicList.size() - 1, i++);
    Topic* topic = TopicList[kth];
    for (auto it = topic->inQuestions.begin(); it != topic->inQuestions.end(); ++it) {
      unordered_set<unsigned long>::const_iterator got = result.find(*it);
      if ( got == result.end() ) {
        cout << *it << ' ';
        result.insert(*it);
      }
    }
  }
  cout << endl;
}

int main(int argc, char** argv) {
  int numTopics = 0, numQuestions = 0, numQueries = 0;
  unordered_map<unsigned long, Topic*> Topics;
  unordered_map<unsigned long, Question*> Questions;
  vector<Query*> Queries;

///////////////////////////////////////////////////////////////////////////////////
  numTopics = 3;
  numQuestions = 6;
  numQueries = 2;
  Topics.insert(make_pair<unsigned long, Topic*>(0, new Topic(0, 0.0, 0.0)));
  Topics.insert(make_pair<unsigned long, Topic*>(1, new Topic(1, 1.0, 1.0)));
  Topics.insert(make_pair<unsigned long, Topic*>(2, new Topic(2, 2.0, 2.0)));
  Questions.insert(make_pair<unsigned long, Question*>(0, new Question(0, 1)));
  Questions[0]->haveTopics.insert(0);
  Topics[0]->inQuestions.insert(0);
  Questions.insert(make_pair<unsigned long, Question*>(1, new Question(1, 2)));
  Questions[1]->haveTopics.insert(0);
  Questions[1]->haveTopics.insert(1);
  Topics[0]->inQuestions.insert(1);
  Topics[1]->inQuestions.insert(1);
  Questions.insert(make_pair<unsigned long, Question*>(2, new Question(2, 3)));
  Questions[2]->haveTopics.insert(0);
  Questions[2]->haveTopics.insert(1);
  Questions[2]->haveTopics.insert(2);
  Topics[0]->inQuestions.insert(2);
  Topics[1]->inQuestions.insert(2);
  Topics[2]->inQuestions.insert(2);
  Questions.insert(make_pair<unsigned long, Question*>(3, new Question(3, 0)));
  Questions.insert(make_pair<unsigned long, Question*>(4, new Question(4, 0)));
  Questions.insert(make_pair<unsigned long, Question*>(5, new Question(5, 2)));
  Questions[5]->haveTopics.insert(1);
  Questions[5]->haveTopics.insert(2);
  Topics[1]->inQuestions.insert(5);
  Topics[2]->inQuestions.insert(5);
  Queries.push_back(new Query('t', 2, 0.0, 0.0));
  Queries.push_back(new Query('q', 5, 100.0, 100.0));
///////////////////////////////////////////////////////////////////////////////////

//  cin >> numTopics >> numQuestions >> numQueries;
//  // Read topics 
//  unsigned long id = 0;
//  double x = 0, y = 0;
//  for (int i = 0; i < numTopics; i++) {
//    cin >> id >> x >> y; 
//    Topics.insert(make_pair<unsigned long&, Topic*>(id, new Topic(id, x, y)));
//  }
//  // Read Questions
//  int topicnums;
//  unsigned long topicid;
//  for (int i = 0; i < numQuestions; i++) {
//    cin >> id >> topicnums;
//    Questions.insert(make_pair<unsigned long&, Question*>(id, new Question(id, topicnums)));
//    for (int j = 0; j < topicnums; j++) {
//      cin >> topicid;
//      Questions[id]->haveTopics.insert(topicid);
//      Topics[topicid]->inQuestions.insert(id);
//    }
//  }
//  // Read Queries
//  char querytype = 0;
//  int numresults = 0;
//  for (int i = 0; i < numQueries; i++) {
//    cin >> querytype >> numresults >> x >> y;
//    Queries.push_back(new Query(querytype, numresults, x, y));
//  }


//  cout << numTopics << ' ' << numQuestions << ' ' << numQueries << endl;
//  for (auto it = Topics.begin(); it != Topics.end(); ++it)
//    cout << it->second;
//  for (auto it = Questions.begin(); it != Questions.end(); ++it)
//    cout << it->second;
//  for (auto it = Queries.begin(); it != Queries.end(); ++it)
//    cout << *it;

  
  // Response Queries
  // Maintain topiclist
  vector<Topic*> TopicList;
  for (auto it = Topics.begin(); it != Topics.end(); ++it)
    TopicList.push_back(it->second);
  for (int i = 0; i < Queries.size(); i++) {
    Query* query = Queries[i];
    for (int i = 0; i < TopicList.size(); i++)
      TopicList[i]->set_dis(dis(TopicList[i]->get_x(), TopicList[i]->get_y(), query->get_x(), query->get_y()));
    if (query->get_type() == 't') {
      QueryTopic(query, TopicList);
    } else if (query->get_type() == 'q') {
      QueryQuestion(query, Questions, TopicList);
    }
  }

  return 0;
}
