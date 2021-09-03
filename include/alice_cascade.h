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


class Alice{

    private:
    std::string data_folder;
    std::string key_file_name;
    std::string working_key_file_name;
    std::string state_file_name; 
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
    
    void init(std::string data_folder,std::string key_file_name, int protocol_run_id,int random_shuffle_seed);
    
    
    bool is_new_run();
    void start_cascade();
    void cascade_step();
    Alice(std::string data_folder, std::string key_file_name, int protocol_run_id,int random_shuffle_seed);
    ~Alice();

};
