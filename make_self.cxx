const char *self_str="";  
#include<map>  
#include<string>  
#include<iostream>  
#include<sstream>  
#include<iomanip>  
#include<fstream>  
using namespace std;  
string enc(const string &s){  
  stringstream ss;  
  if (s.size()==1){  
    int i = s[0];  
    ss<<setw(2)<<setfill('0')<<setbase(16)<<i;  
    return ss.str();  
  } else {  
    istringstream ins(s);  
    int c;  
    ins>>setw(2)>>setbase(16)>>c;  
    ss<<static_cast<char>(c);  
    return ss.str();  
  }  
}  
int main(){  
  string s = self_str; int c;  
  ifstream self_f("self.cxx");  
  while((c = self_f.get()) != char_traits<char>::eof()) {  
    string s;  
    s += c;  
    cout<<enc(s);  
  }  
  return 0;  
} 
