#include "response_message_reader.h"
#include <iostream>
#include <string>

using namespace std;
void ResponseMessageReader::init(string name,int protocol_run_ind,int iteration){
    BufferedFileIn::init(name,protocol_run_ind,iteration);
    cout<<"Message reader created"<<endl;
}

bool ResponseMessageReader::read_response(unsigned char *dp){
    cout<<"in read response"<<endl;
    if (!BufferedFileIn::read_dual_parity(dp)) return false;
    return true;
       
}