#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Event {
	public:
	char value;
	vector<Event*> deps;
	Event(char val):value(val) {}
};

int main() {
	Event* events[128] = {NULL};
	events['A'] = new Event('A');
	events['B'] = new Event('B');
	events['C'] = new Event('C');
	events['A']->deps.push_back(events['B']);	
	events['A']->deps.push_back(events['C']);
	events['E'] = new Event('E');
	events['B']->deps.push_back(events['C']);
	events['B']->deps.push_back(events['E']);
	events['G'] = new Event('G');
	events['C']->deps.push_back(events['G']);
	events['D'] = new Event('D');
	events['F'] = new Event('F');
	events['D']->deps.push_back(events['A']);
	events['D']->deps.push_back(events['F']);
	events['E'] = new Event('E');
	events['E']->deps.push_back(events['F']);
	events['H'] = new Event('H');
	events['F']->deps.push_back(events['H']);

	
	for (char c = 'A'; c < 'Z'; c++) {
		if (events[c] != NULL) {
			queue<Event*> waitingdeps;
			char visited[128] = {0};
			if (events[c]->deps.size() < 1) break;
			waitingdeps.push(events[c]);
			Event* d = waitingdeps.front();
			while (waitingdeps.size() > 0) {
				d = waitingdeps.front();
				waitingdeps.pop();
				if (!visited[d->value]) {
					for (int i = 0; i < events[d->value]->deps.size(); i++)
						waitingdeps.push(events[d->value]->deps[i]);
					cout << d->value << ' ';
					visited[d->value] = 1;
				}
			}
			cout << endl;
		}
	}

