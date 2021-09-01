#include "message_bunch_reader.h"
#include <iostream>
#include <string>

using namespace std;
void MessageBunchReader::init(string name,int protocol_run_ind,int iteration){
    BufferedFileIn::init(name,protocol_run_ind,iteration);
    cout<<"Message reader created"<<endl;
}

bool MessageBunchReader::read_message(int *l,int *h,unsigned char *dp){
    //cout<<"in read message"<<endl;
    if (!BufferedFileIn::read_index(l)) return false;
    if (!BufferedFileIn::read_index(h)) return false;
    if (!BufferedFileIn::read_dual_parity(dp)) return false;
    return true;
       
}