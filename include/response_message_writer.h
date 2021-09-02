#include "buffered_file_out.h"
#include <string>

class ResponseMessageWriter:public BufferedFileOut{
    public:
    void init(std::string name,int protocol_run_ind,int iteration);
    void write_response(unsigned char dp);
};