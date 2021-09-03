#ifndef RESPONSE_MESSAGE_READER_H
#define RESPONSE_MESSAGE_READER_H
#include "buffered_file_in.h"
#include <string>

class ResponseMessageReader:public BufferedFileIn{
    public:
    bool read_response( unsigned char *dp);
    void init(std::string name,int protocol_run_ind,int iteration);
};

#endif