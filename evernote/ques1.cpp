#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CircularBuffer {
  public:
    CircularBuffer() : first(0), last(0), elements(0) {}
    ~CircularBuffer() {}
    
    void allocate(const size_t length);
    void insert(const string input_str);
    void remove(const size_t number);
    void list() const;
  private:
    vector<string> array;
    size_t first;
    size_t last;
    size_t elements;
};

void CircularBuffer::allocate(const size_t length) { 
  array.resize(length); 
}

void CircularBuffer::insert(const string input_str) {
  if (array.empty()) return;
  if (elements && (first == last)) {
    first ++;
    elements --;
    if (first == array.size()) first = 0; 
  }
  array[last ++] = input_str; 
  elements ++;
  if (last == array.size()) last = 0;
}

void CircularBuffer::remove(const size_t number) {
  if (array.empty()) return;
  size_t remove_number = 0;
  while (elements && remove_number < number) {
    first ++;
    if (first == array.size()) first = 0;
    elements --;
    remove_number ++;    
  }
}

void CircularBuffer::list() const {
  if (array.empty()) return;
  if (!elements) return;

  if (first < last) {
    for (size_t index = first; index < last; index ++)
      cout << array[index] << endl;     
  } else {
    for (size_t index = first; index < array.size(); index ++)
      cout << array[index] << endl;
    for (size_t index = 0; index < last; index ++)
      cout << array[index] << endl;    
  }
}

void append(CircularBuffer& buffer) {
  size_t input_num = 0;
  cin >> input_num;
  string input_str;
  for (size_t counter = 0; counter < input_num; counter ++) {
    cin >> input_str;
    buffer.insert(input_str);
  }
}

void remove(CircularBuffer& buffer) {
  size_t input_num = 0;
  cin >> input_num;
  buffer.remove(input_num);
}

void list(CircularBuffer& buffer) {
  buffer.list();
}

int main() {
  size_t N = 0;
  cin >> N;
  
  string str;
  char command;
  bool running = true;
  
  CircularBuffer buffer;
  buffer.allocate(N);
  while (running) {
    cin >> command;
    switch (command) {
      case 'A':
        append(buffer);
        break;
      case 'L':
        list(buffer);
        break;
      case 'R':
        remove(buffer);
        break;
      case 'Q':
        running = false;
        break;
      default:
        break;
    }
  }

  return 0;
}
