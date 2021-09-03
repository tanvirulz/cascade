#include <cstdio>
#include <cinttypes>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
//#include <ifstream>

//#include "buffered_file_out.h"
#include "message_bunch_writer.h"
#include "message_bunch_reader.h"
#include "response_message_reader.h"
#include "sifted_key_container.h"

#define FILE_NAME_SIZE 256
#define BUFFER_SIZE (32*1024)

#define BLOCK_SIZE 4

#define LEFT 2
#define RIGHT 1

using namespace std;



class Alice{

    private:
    string key_file_name;
    string working_key_file_name;
    string state_file_name; 
    int protocol_run_id;
    int iteration;
    int random_shuffle_seed;

    SiftedKeyContainer sk;
    //string sk ; //sifted key
    
    MessageBunchWriter mbfout;
    MessageBunchReader mbfin;
    ResponseMessageReader rbfin; 

    void compute_and_write_dual_block_parity(int l, int h);
    void load_state();
    void store_state();

    public:
    
    void init(string key_file_name, int protocol_run_id,int random_shuffle_seed);
    
    
    bool is_new_run();
    void start_cascade();
    void cascade_step();
    Alice(string key_file_name, int protocol_run_id,int random_shuffle_seed);
    ~Alice();

};

Alice::Alice(string key_file_name, int protocol_run_id,int random_shuffle_seed){
    this->init(key_file_name,protocol_run_id,random_shuffle_seed);
}

Alice::~Alice(){
    this->store_state();
}



void Alice::compute_and_write_dual_block_parity(int l, int h){
    int m = (l+h)/2 ; //compute the midpoinf of the dual block
    uint8_t dual_parity = 0;
    if (sk.get_parity(l,m)){ //compute parity of the left sub block
        dual_parity = dual_parity|LEFT;
    }
    if (sk.get_parity(m,h)){ //compute parity of right sub block
        dual_parity = dual_parity|RIGHT;
    }
    cout<<"writing: "<<l<<", "<<h<<", "<<int(dual_parity)<<endl;
    mbfout.write_message(l,h,dual_parity);
}

void Alice::cascade_step(){
    return;
}
void Alice::start_cascade(){
    int dual_block_size = BLOCK_SIZE*2;
    int num_message = sk.length()/dual_block_size ;
    //cout<<"num message "<<num_message<<endl; 
    int i, l, h;
    for (i =0;i<num_message;i++){
        l = i*dual_block_size;
        h = (i+1)*dual_block_size;
        this->compute_and_write_dual_block_parity(l,h);
        //cout<<"fff "<<endl;
    }
    //this->mbfout.flush(); //flushed in destractor 
    this->iteration++; // this has to be stored in the state file
}


void Alice::load_state(){
    char state_file_name[FILE_NAME_SIZE];
    FILE * state_file;

    sprintf(state_file_name,"alice_cascade_state_%d.txt",protocol_run_id);
    this->state_file_name = state_file_name;
    state_file= fopen(state_file_name,"r");
    if (!state_file){
        cout<<"State file does not exist!"<<endl;
        cout<<"this is a new run"<<endl;
        //create new state file
        state_file = fopen(state_file_name,"w");
        //write the iteration number for now;
        fprintf(state_file,"%d\n",this->iteration);
        fclose(state_file);
    }
    else{
        cout<< "state pre-exists!!"<<endl;
        fscanf(state_file,"%d\n",&this->iteration);
        cout<< "current state of iteration: "<<this->iteration<<endl;
        fclose(state_file);
    }
    
}

void Alice::store_state(){
    FILE * state_file;
    state_file = fopen(state_file_name.c_str(),"w");
    fprintf(state_file,"%d\n",this->iteration);
    fclose(state_file);
}

void Alice::init(string key_file_name, int protocol_run_id,int random_shuffle_seed){
    this->key_file_name=key_file_name;
    //this->state_file_name=state_file_name;
    this->protocol_run_id=protocol_run_id;
    this->random_shuffle_seed=random_shuffle_seed;
    this->iteration=0;
    
    
    
    this->load_state();
    this->sk.load_data(key_file_name,iteration);
    //this->init_message_bunch_buffer_out(); 
    this->mbfout.init("messages/alice_mbf",protocol_run_id,iteration);
    if(!this->is_new_run()){ //If this is not a new run, 
        //then load the previous message bunch to read;
        this->mbfin.init("messages/alice_mbf",protocol_run_id,iteration-1);
        //load the response bunch received from bob for my previous message bunch
        this->rbfin.init("messages/bob_mbf",protocol_run_id,iteration-1);
    }   
    

}

bool Alice::is_new_run(){
    if (this->iteration==0){
        return true;
    }
    else{
        return false;
    }
}



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
    
    Alice alice("test.txt",35,3141562);
    //alice.load_data("test.txt");
    //alice.init("test.txt",35,3141562);
    if(alice.is_new_run()){
        alice.start_cascade();
    }
    //alice's state stored in destractor

    //int l=1,h=14;
    //cout<<"parity "<<alice.get_parity(l,h)<<endl;
    cout<< "Alice DOne"<<endl;
    return 0;
    
   
}