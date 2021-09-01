#include "buffered_file_out.h"
#include <string>

class MessageBunchWriter: public BufferedFileOut{
    public:
    
    void init(std::string name,int protocol_run_ind,int iteration);
    void write_message(int l, int h, unsigned char dp);
};