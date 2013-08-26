#include <iostream>
#include <string>
#include <vector>
#include <istream>

using namespace std;

enum result_type {
  X_WON = 0,
  O_WON,
  DRAW,
  RUN,
};

int check_game(string& field, int size) {
  string validline("....");
  /// check rows
  for (int i = 0; i < field.size(); i+= size) {
    validline = field.substr(i, size);
    if (validline.find("XXXX") != string::npos) return X_WON;
    if (validline.find("OOOO") != string::npos) return O_WON;
    if ((validline.find("XXX") != string::npos) && 
        (validline.find("T") != string::npos)) return X_WON;
    if ((validline.find("OOO") != string::npos) && 
        (validline.find("T") != string::npos))
      return O_WON;
  }
  // check colums
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++)
      validline[j] = field[i + size * j];
    if (validline.find("XXXX") != string::npos) return X_WON;
    if (validline.find("OOOO") != string::npos) return O_WON;
    if ((validline.find("XXX") != string::npos) && 
        (validline.find("T") != string::npos)) return X_WON;
    if ((validline.find("OOO") != string::npos) && 
        (validline.find("T") != string::npos)) return O_WON;
  }
  // check diagnal
  for (int i = 0; i < size; i++)
    validline[i] = field[i + i * size];
  if (validline.find("XXXX") != string::npos) return X_WON;
  if (validline.find("OOOO") != string::npos) return O_WON;
  if ((validline.find("XXX") != string::npos) && 
      (validline.find("T") != string::npos)) return X_WON;
  if ((validline.find("OOO") != string::npos) && 
      (validline.find("T") != string::npos)) return O_WON;

  for (int i = 0; i < size; i++)
    validline[i] = field[(1 + i) * (size - 1)];
  if (validline.find("XXXX") != string::npos) return X_WON;
  if (validline.find("OOOO") != string::npos) return O_WON;
  if ((validline.find("XXX") != string::npos) && 
      (validline.find("T") != string::npos)) return X_WON;
  if ((validline.find("OOO") != string::npos) && 
      (validline.find("T") != string::npos)) return O_WON;

  return (field.find(".") != string::npos)? RUN : DRAW;
}

int main(int argc, char **argv) {
  int T = 0;
  cin >> T;
  const int fieldsize = 4;
  string field;
  field.resize(fieldsize * fieldsize); // 4 x 4 field
  for (int i = 0; i < T; i++) {
    for (int j = 0; j < field.size(); j++) {
      cin >> field[j];
    }
    int ret = check_game(field, fieldsize);
    cout << "Case #" << i + 1 << ": ";
    if (ret == X_WON)
      cout << "X won" << endl;
    else if (ret == O_WON)
      cout << "O won" << endl;
    else if (ret == DRAW)
      cout << "Draw" << endl;
    else
      cout << "Game has not completed" << endl;
  }
  return 1;
}
