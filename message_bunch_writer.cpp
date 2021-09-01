#include "message_bunch_writer.h"
#include <string>
#include <iostream>

using namespace std;

void MessageBunchWriter::init(string name,int protocol_run_ind,int iteration){
    BufferedFileOut::init(name,protocol_run_ind,iteration);
}

void MessageBunchWriter::write_message(int l, int h, unsigned char dp){
    BufferedFileOut::write_index(l);
    BufferedFileOut::write_index(h);
    BufferedFileOut::write_dual_parity(dp);
}