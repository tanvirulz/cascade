#include "bob_cascade.h"
#include <iostream>
using namespace std;

int main(){

    Bob bob;
    bob.init(".","test_bob_sk.txt",35,3141562);
    bob.cascade();
    bob.store_state(); //move to destructor
    cout<<"bob done"<<endl;
    return 0;
}
