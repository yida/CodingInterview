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

void hanoi(int n, int srcTower, int desTower, int bufTower) {
  //cout << n << ' ' << srcTower << ' ' << desTower << endl;
  int tmp;
  if (n == 1) {
    tmp = tower[srcTower].back();
    tower[desTower].push_back(tmp);
    tower[srcTower].pop_back();
    printTower();
   }
  else {
    hanoi(n-1, srcTower, bufTower, desTower);
    
    tmp = tower[srcTower].back();
    tower[desTower].push_back(tmp);
    tower[srcTower].pop_back();
    printTower();

    hanoi(n-1, bufTower, desTower, srcTower);
  }

}

int main() {
  tower.resize(3);
  tower[1].push_back(5);
  tower[1].push_back(4);
  tower[0].push_back(3);
  tower[0].push_back(2);
  tower[0].push_back(1);
  hanoi(3, 0, 2, 1);
  cout << step << endl;
//  cout << "Tower 1" << endl;
//  while (!tower[0].empty())
//    cout << tower[0].pop() << endl;
//  cout << "Tower 2" << endl;
//  while (!tower[1].empty())
//    cout << tower[1].pop() << endl;
//  cout << "Tower 3" << endl;
//  while (!tower[2].empty())
//    cout << tower[2].pop() << endl;  
  return 0;
}
