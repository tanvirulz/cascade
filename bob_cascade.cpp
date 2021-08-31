#include <cstdio>
#include <cinttypes>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
//#include <ifstream>

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

    string message_bunch_file_name;

    string sk ; //sifted key

    char mbfBuffer[BUFFER_SIZE];
    ifstream mbfin; //message bunch file in


    
    void load_data();
    void init_message_bunch_buffer();

    
    inline bool file_exists(const string& name);

    void compute_dual_block_parity(int l, int h);

    int get_parity(int l, int h);

    public:
    void init(string key_file_name,string state_file_name, int protocol_run_id,int random_shuffle_seed);
    void start_cascade();

};

void init(string key_file_name,string state_file_name, int protocol_run_id,int random_shuffle_seed){
    this->key_file_name=key_file_name;
    this->state_file_name=state_file_name;
    this->protocol_run_id=protocol_run_id;
    this->random_shuffle_seed=random_shuffle_seed;
    this->iteration=0;
    
}
void Bob::init_message_bunch_buffer(){
    char mbfname[FILE_NAME_SIZE];
    sprintf(mbfname,"mbf_%d_%d.bin",protocol_run_id,iteration);
    cout<<mbfname<<endl;
    this->message_bunch_file_name = mbfname;
    cout<< "asstring: "<<this->message_bunch_file_name<<" length "<<this->message_bunch_file_name.length()<<endl;

    mbfin.rdbuf()->pubsetbuf(this->mbfBuffer, BUFFER_SIZE);
    mbfin.open(message_bunch_file_name, ios::in|ios::binary);

}


int main(){
    return 0;
}