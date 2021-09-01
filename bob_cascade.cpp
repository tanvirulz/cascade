#include <cstdio>
#include <cinttypes>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
//#include <ifstream>

#include "message_bunch_reader.h"
#include "response_message_writer.h"

#define FILE_NAME_SIZE 256
#define BUFFER_SIZE (32*1024)

#define BLOCK_SIZE 4

#define LEFT 2
#define RIGHT 1

using namespace std;

class Bob{
    private:
    string key_file_name;
    string state_file_name; 
    int protocol_run_id;
    int iteration;
    int random_shuffle_seed;

    string sk ; //sifted key
    MessageBunchReader mbfin;
    ResponseMessageWriter rbfout;


    void load_data();
    void init_message_bunch_buffer();

    void init_response_bunch_buffer();

    
    int get_parity(int l, int h);

    public:
    void init(string key_file_name, int protocol_run_id,int random_shuffle_seed);
    void cascade();
    void load_state();
    void store_state();
    void compute_and_write_response(int l, int h,uint8_t dual_parity);

};

void Bob::store_state(){
    FILE * state_file;
    state_file = fopen(state_file_name.c_str(),"w");
    fprintf(state_file,"%d\n",this->iteration);
    fclose(state_file);
}

void Bob::load_state(){
    char state_file_name[FILE_NAME_SIZE];
    FILE * state_file;

    sprintf(state_file_name,"bob_cascade_state_%d.txt",protocol_run_id);
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
void Bob::load_data(){
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
void Bob::init(string key_file_name, int protocol_run_id,int random_shuffle_seed){
    this->key_file_name=key_file_name;
    //this->state_file_name=state_file_name;
    this->protocol_run_id=protocol_run_id;
    this->random_shuffle_seed=random_shuffle_seed;
    this->iteration=0;
    
    this->load_data();
    this->load_state();
    this->mbfin.init("messages/alice_mbf",protocol_run_id,iteration);
    this->rbfout.init("messages/bob_rbf",protocol_run_id,iteration);

}


int Bob::get_parity(int l, int h){
    int p; //parity
    p = 0;
    for(int i=l;i<h;i++){
        p += (sk[i]-'0');
    }
    p %=2;
    return p;
}
void Bob::compute_and_write_response(int l, int h,uint8_t alcie_dp){
    int m = (l+h)/2;
    uint8_t response;
    uint8_t dual_parity = 0;

    if (get_parity(l,m)){ //compute parity of the left sub-block
        dual_parity = dual_parity|LEFT;
    }
    if (get_parity(m,h)){ // compute parity of the right sub-block
        dual_parity = dual_parity|RIGHT;
    }

    response = dual_parity^alcie_dp; //response bit is set to 1 if the corresponding block has missmatch in alice and bobs parity
                                     // the exor operation ensures it
    cout<<"response: "<< int(response)<<endl;
    rbfout.write_response(response);
    //rbfout.write(reinterpret_cast<char *>(&response),sizeof(response));
}

void Bob::cascade(){
    int l=0, h=0;
    uint8_t dual_parity;
    


    //while (1)
        //read next messages (low, high, dual_parity)
        // if not finished
            //process message
            //create response bunch
    //iteration ++

    while(mbfin.read_message(&l,&h,&dual_parity)){
        
        this->compute_and_write_response(l,h,dual_parity);

    }
    this->iteration++;
    
}
int main(){

    Bob bob;
    bob.init("test_bob_sk.txt",35,3141562);
    bob.cascade();
    bob.store_state();
        
    return 0;
}
