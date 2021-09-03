#ifndef BUFFERED_FILE_IN_H
#define BUFFERED_FILE_IN_H

#include <fstream>
#include <string>



#define INFILE_BUFFER_SIZE (32*1024)



class BufferedFileIn{
    private:
    std::string infilename;
    char buffer[INFILE_BUFFER_SIZE];
    std::ifstream in_file;

    protected:
    bool read_index(int * idx);
    bool read_dual_parity(unsigned char * dp);

    public:
    
    void init(std::string name,int protocol_run_ind,int iteration);
    BufferedFileIn();
    ~BufferedFileIn();

};

#endif 