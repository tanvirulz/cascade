// strings and c-strings
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

typedef struct TestType {
  int i;
} TestType;

int main ()
{
  string str ("Please");
  TestType tt;
  tt.i=50;
  cout<<str<<"\n";
  str[2]='1';
  cout<<str<<"\n";
  cout<<str.length()<<"\n";
  cout<<"tt has value: "<<tt.i<<endl;
  return 0;
}


