#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > tower;
int step = 0;

void printTower(){
  for (int h=5; h>0; h--){
    for (int i=0; i<3; i++){
      if (tower[i].size() < h)
        cout <<" \t";
      else
        cout << tower[i][h-1] << "\t";
    }
    cout << endl;
  }
  cout << "==================" << endl;
}

void movePlate(int srcTower, int desTower) {
  tower[desTower].push_back(tower[srcTower].back());
  tower[srcTower].pop_back();
  printTower();
}

void hanoi(int n, int srcTower, int desTower, int bufTower) {
  if (n == 1) 
    movePlate(srcTower, desTower);
  else {
    hanoi(n-1, srcTower, bufTower, desTower);
    movePlate(srcTower, desTower);
    hanoi(n-1, bufTower, desTower, srcTower);
  }
}

int main() {
  tower.resize(3);
  tower[0].push_back(5);
  tower[0].push_back(4);
  tower[0].push_back(3);
  tower[0].push_back(2);
  tower[0].push_back(1);
  hanoi(5, 0, 2, 1);
  cout << step << endl;
  return 0;
}
