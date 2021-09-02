#include<string>

class SiftedKeyContainer{
    public:
    std::string key;
    
    void load_data(std::string name,int iteration);
    int get_parity(int l, int h);
    int length();

};