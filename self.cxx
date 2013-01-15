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
  string s = self_str;  
  int prefix_len = 2 * strlen("const char *self_str=");  
  for (int i=0; i< s.size(); i+=2){  
    cout<<enc(s.substr(i,2));  
    if (i==prefix_len)  
      cout<<s;  
  }  
  return 0;  
}  
