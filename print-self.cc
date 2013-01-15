#include <iostream>
using namespace std;
#define ENIUQ(TEMPLATE) cout << TEMPLATE << "(" << #TEMPLATE << ");}";
int main()
{ENIUQ("#include <iostream>\nusing namespace std;\n#define ENIUQ(TEMPLATE) cout << TEMPLATE << \"(\" << #TEMPLATE << \");}\";\n\nint main()\n{ENIUQ");}
