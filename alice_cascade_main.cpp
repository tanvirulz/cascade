#include "alice_cascade.h"

#include <iostream>

using namespace std;

int main(){
    //BufferedFileOut mbfout("alice",35,10);
    //MessageBunchWriter mbfout;
    //mbfout.init("alice_mbf",35,10);
    //mbfout.write_message(10,12,2);
    //MessageBunchWriter * test;
    
    //mbfout.write_index(12);
    //mbfout.write_dual_parity('a');
    //ResponseMessageReader rmfin;
    //rmfin.init("messages/bob_rbf",35,0);
    //unsigned char dp;
    //while(rmfin.read_response(&dp)){
    //    cout<<"response freading in Alice: "<<int(dp)<<endl;
    //}
    
    Alice alice("data","alice_sk.txt",35,3141562);
    //alice.load_data("test.txt");
    //alice.init("test.txt",35,3141562);
    if(alice.is_new_run()){
        alice.start_cascade();
    }
    else{
        alice.cascade_step();
    }
    //alice's state stored in destractor

    //int l=1,h=14;
    //cout<<"parity "<<alice.get_parity(l,h)<<endl;
    cout<< "Alice Done"<<endl;
    return 0;
    
   
}