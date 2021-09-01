#include "response_message_writer.h"
#include <string>
#include <iostream>

using namespace std;

void ResponseMessageWriter::init(std::string name,int protocol_run_ind,int iteration){
    BufferedFileOut::init(name,protocol_run_ind,iteration);
    cout<<"response message writer created"<<endl;
}

void ResponseMessageWriter::write_response(unsigned char dp){
    BufferedFileOut::write_dual_parity(dp);
}