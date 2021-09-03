
#include "alice_cascade.h"

using namespace std;



Alice::Alice(string data_folder, string key_file_name, int protocol_run_id,int random_shuffle_seed){
    this->init(data_folder, key_file_name,protocol_run_id,random_shuffle_seed);
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

void Alice::init(string data_folder, string key_file_name, int protocol_run_id,int random_shuffle_seed){
    this->data_folder = data_folder;
    this->key_file_name=key_file_name;
    //this->state_file_name=state_file_name;
    this->protocol_run_id=protocol_run_id;
    this->random_shuffle_seed=random_shuffle_seed;
    this->iteration=0;
    
    
    
    this->load_state();
    this->sk.load_data(data_folder, key_file_name,iteration);
    //this->init_message_bunch_buffer_out(); 
    this->mbfout.init("messages/alice_mbf",protocol_run_id,iteration);
    if(!this->is_new_run()){ //If this is not a new run, 
        //load the response bunch received from bob for my previous message bunch
        this->rbfin.init("messages/bob_rbf",protocol_run_id,iteration-1);

        //then load the previous message bunch to read;
        this->mbfin.init("messages/alice_mbf",protocol_run_id,iteration-1);
        
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



