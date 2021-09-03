#ifndef SIFTED_KEY_CONTAINER_H
#define SIFTED_KEY_CONTAINER_H
#include<string>

class SiftedKeyContainer{
    private:
    std::string key;
    public:
    
    
    void load_data(std:: string data_folder, std::string name,int iteration);
    int get_parity(int l, int h);
    void print_subkey(int l, int h);
    int length();

};

#endif