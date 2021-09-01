#include "buffered_file_out.h"
#include <iostream>


using namespace std;


void BufferedFileOut::init(string name,int protocol_run_ind,int iteration){
    outfilename=name+"_"+to_string(protocol_run_ind)+"_iter_"+to_string(iteration)+".bin";
    
    cout<< outfilename<<"; name length: "<<outfilename.length()<<endl;
    
    out_file.rdbuf()->pubsetbuf(this->buffer, OUTFILE_BUFFER_SIZE);

    out_file.open(outfilename,ios::out|ios::binary|ios::trunc);
    

}

void BufferedFileOut::write_index(int idx){
    out_file.write(reinterpret_cast<char *>(&idx),sizeof(idx));
}

void BufferedFileOut::write_dual_parity(unsigned char dp){
    out_file.write(reinterpret_cast<char *>(&dp),sizeof(dp));
}

BufferedFileOut::~BufferedFileOut(){
    cout<<"destructing oufile: "<<outfilename<<endl;
    if(out_file.is_open()){
        out_file.flush();
        out_file.close();
    }
    
}