#ifndef MESSAGE_BUNCH_READER_H
#define MESSAGE_BUNCH_READER_H
#include "buffered_file_in.h"
#include <string>

class MessageBunchReader:public BufferedFileIn{
    public:
    bool read_message(int *l, int *h, unsigned char *dp);
    void init(std::string name,int protocol_run_ind,int iteration);
};

#endif