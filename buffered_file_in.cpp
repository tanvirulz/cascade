#include "buffered_file_in.h"
#include <iostream>
#

using namespace std;


void BufferedFileIn::init(string name,int protocol_run_ind,int iteration){
    infilename=name+"_"+to_string(protocol_run_ind)+"_iter_"+to_string(iteration)+".bin";
    
    cout<< infilename<<"; name length: "<<infilename.length()<<endl;
    
    in_file.rdbuf()->pubsetbuf(this->buffer, INFILE_BUFFER_SIZE);


    in_file.open(infilename, ios::in|ios::binary);

    if(!in_file.is_open()){
        cout<<"Error: File: "<<infilename<<" not found!"<<endl;
        exit(1);
    }
    

}

bool BufferedFileIn::read_index(int * idx){
    int h=0;
    //cout<<"in read index"<<endl;
    //in_file.write(reinterpret_cast<char *>(&idx),sizeof(idx));
    in_file.read(reinterpret_cast<char *>(&h),sizeof(h));
    if (in_file.eof()){
        return false;
    } 
    else{
        *idx = h;
        return true;
    }
    
}

bool BufferedFileIn::read_dual_parity(unsigned char * dp){
    unsigned char dual_parity=0;
    in_file.read(reinterpret_cast<char *>(&dual_parity),sizeof(dual_parity));
    if (in_file.eof()){
        return false;
    } 
    else{
        *dp = dual_parity;
        return true;
    }
    
}

BufferedFileIn::~BufferedFileIn(){
    cout<<"destructing oufile writer for: "<<infilename<<endl;
    if(in_file.is_open()){
        in_file.close();
    }
    
}