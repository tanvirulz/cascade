#ifndef BUFFERED_FILE_OUT_H
#define BUFFERED_FILE_OUT_H
#include <fstream>
#include <string>



#define OUTFILE_BUFFER_SIZE (32*1024)



class BufferedFileOut{
    private:
    std::string outfilename;
    char buffer[OUTFILE_BUFFER_SIZE];
    std::ofstream out_file;

    protected:
    void write_index(int idx);
    void write_dual_parity(unsigned char dp);

    public:
    
    void init(std::string name,int protocol_run_ind,int iteration);
    
    BufferedFileOut();
    ~BufferedFileOut();

};

#endif