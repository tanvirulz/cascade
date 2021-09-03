

#include <string>

#include "message_bunch_reader.h"
#include "response_message_writer.h"
#include "sifted_key_container.h"

#define FILE_NAME_SIZE 256
#define BUFFER_SIZE (32*1024)


#define LEFT 2
#define RIGHT 1


class Bob{
    private:
    std::string key_file_name;
    std::string working_key_file_name;
    std::string state_file_name; 
    int protocol_run_id;
    int iteration;
    int random_shuffle_seed;

    SiftedKeyContainer sk;
    //string sk ; //sifted key
    MessageBunchReader mbfin;
    ResponseMessageWriter rbfout;



    void load_data();
    void init_message_bunch_buffer();

    void init_response_bunch_buffer();

    
    int get_parity(int l, int h);
    bool is_new_run();
    public:
    void init(std::string data_folder,std::string key_file_name, int protocol_run_id,int random_shuffle_seed);
    void cascade();
    void load_state();
    void store_state();
    void compute_and_write_response(int l, int h,unsigned char dual_parity);

};
