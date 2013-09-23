#include <iostream>
#include <stdint.h>

using namespace std;

int main() {
  uint8_t array[4] = {0, 1, 2, 3};
  uint32_t *array32 = (uint32_t*)array;
  const uint32_t BIGEND = 0x00010203;
  const uint32_t LITEND = 0x03020100;

  if (*array32 == BIGEND)
    cout << "BigEndian" << endl;
  else if (*array32 == LITEND)
    cout << "LittleEndian" << endl;
  else 
    cout << "unknown" << endl;
   
  return 0;
}
