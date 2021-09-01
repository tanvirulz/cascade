#include <cstdio>
#include <cinttypes>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
//#include <ifstream>

//#include "buffered_file_out.h"
#include "message_bunch_writer.h"

#define FILE_NAME_SIZE 256
#define BUFFER_SIZE (32*1024)

#define BLOCK_SIZE 4

#define LEFT 2
#define RIGHT 1

using namespace std;


class Alice{

    private:
    string key_file_name;
    string state_file_name; 
    int protocol_run_id;
    int iteration;
    int random_shuffle_seed;

    
    string sk ; //sifted key
    
    MessageBunchWriter mbfout;
    
    void load_data();
    int get_parity(int l, int h);

    void compute_and_write_dual_block_parity(int l, int h);
    void load_state();
    void store_state();

    public:
    
    void init(string key_file_name, int protocol_run_id,int random_shuffle_seed);
    
    
    bool is_new_run();
    void start_cascade();
    void cascade();
    ~Alice();

};

Alice::~Alice(){
    this->store_state();
}

int Alice::get_parity(int l, int h){
    int p; //parity
    p = 0;
    for(int i=l;i<h;i++){
        p += (sk[i]-'0');
    }
    p %=2;
    return p;
}

void Alice::compute_and_write_dual_block_parity(int l, int h){
    int m = (l+h)/2 ; //compute the midpoinf of the dual block
    uint8_t dual_parity = 0;
    if (get_parity(l,m)){
        dual_parity = dual_parity|LEFT;
    }
    if (get_parity(m,h)){
        dual_parity = dual_parity|RIGHT;
    }
    cout<<"writing: "<<l<<", "<<h<<", "<<int(dual_parity)<<endl;
    mbfout.write_message(l,h,dual_parity);
}

void Alice::cascade(){
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

/*
inline bool Alice::file_exists (const string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void Alice::init_message_bunch_buffer_in(){
    char mbf_in_name[FILE_NAME_SIZE];
    sprintf(mbf_in_name,"mbf_%d_itr_%d.bin",protocol_run_id, iteration-1 ); //Load the message bunch file form the previous iteraiton.  
    cout<<"mbf_in_name: "<<mbf_in_name<<endl;
    this->message_bunch_in_file_name = mbf_in_name;
    cout<< "asstring: "<<this->message_bunch_in_file_name<<" length "<<this->message_bunch_in_file_name.length()<<endl;
    mbfin.rdbuf()->pubsetbuf(this->mbf_in_Buffer, BUFFER_SIZE);
    mbfin.open(message_bunch_in_file_name, ios::in|ios::binary);
    if(!mbfin.is_open()){
        cout<<"ERROR: previous message bunch file not found!"<<endl;

    }

}
void Alice::init_response_bunch_buffer_in(){
    char rbf_in_name[FILE_NAME_SIZE];
    sprintf(rbf_in_name,"mbf_%d_itr_%d.bin",protocol_run_id, iteration-1 );
    cout<<"rbf_in_name: "<<rbf_in_name<<endl;
    this->response_bunch_in_file_name = rbf_in_name;
    cout<< "asstring: "<<this->response_bunch_in_file_name<<" length "<<this->response_bunch_in_file_name.length()<<endl;
    rbfin.rdbuf()->pubsetbuf(this->rbf_in_Buffer, BUFFER_SIZE);
    rbfin.open(response_bunch_in_file_name, ios::in|ios::binary);
    if(!mbfin.is_open()){
        cout<<"ERROR: response bunch file from Bob not found!"<< endl;
    }

}
void Alice::init_message_bunch_buffer_out(){
    char mbf_out_name[FILE_NAME_SIZE];
    sprintf(mbf_out_name,"mbf_%d_itr_%d.bin",protocol_run_id,iteration);
    cout<<mbf_out_name<<endl;
    this->message_bunch_out_file_name = mbf_out_name;
    cout<< "asstring: "<<this->message_bunch_out_file_name<<" length "<<this->message_bunch_out_file_name.length()<<endl;

    mbfout.rdbuf()->pubsetbuf(this->mbf_out_Buffer, BUFFER_SIZE);
    mbfout.open(message_bunch_out_file_name,ios::out|ios::binary|ios::trunc);

}
*/

void Alice::load_data(){
    ifstream sk_file(this->key_file_name.c_str());
    if (sk_file.is_open()){
        cout<<"sifted key file opened"<<endl;
        /*pre assign buffer space for the sifted key string to be loaded*/
        sk_file.seekg(0, std::ios::end);   
        this->sk.reserve(sk_file.tellg());
        sk_file.seekg(0, std::ios::beg);
        this->sk.assign((std::istreambuf_iterator<char>(sk_file)),
            std::istreambuf_iterator<char>());
        cout<<"read success!"<<endl;
        cout<<"sk: "<<this->sk<<endl;
        cout<<"bytes read: "<<sk.length()<<endl;
        
        sk_file.close();

    }
    else{
        cout<<"could not open sifted key file: "<<key_file_name<<endl;
    }
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
    
    
    this->load_data();
    this->load_state();
    //this->init_message_bunch_buffer_out(); 
    this->mbfout.init("messages/alice_mbf",protocol_run_id,iteration);
    if(!this->is_new_run()){ //If this is not a new run, then load the previous message bunch;
    //    this->init_message_bunch_buffer_in();
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
    Alice alice;
    //alice.load_data("test.txt");
    alice.init("test.txt",35,3141562);
    if(alice.is_new_run()){
        alice.start_cascade();
    }
    //alice's state stored in destractor
    
    //int l=1,h=14;
    //cout<<"parity "<<alice.get_parity(l,h)<<endl;
    return 0;
    
   
}