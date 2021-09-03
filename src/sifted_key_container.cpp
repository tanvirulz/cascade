#include"sifted_key_container.h"

#include<string>
#include<fstream>
#include<iostream>

using namespace std;
int SiftedKeyContainer::get_parity(int l, int h){
    int p; //parity
    p = 0;
    for(int i=l;i<h;i++){
        p += (key[i]-'0');
    }
    p %=2;
    return p;
}
int SiftedKeyContainer::length(){
    return key.length();
}
void SiftedKeyContainer::print_subkey(int l, int h){
    if (h>=key.length()) h = key.length();
    if (l<0) l=0;
    int len = h-l;
    cout<< this->key.substr(l,len);

}



void SiftedKeyContainer::load_data(string data_folder, string name,int iteration){
    string working_sk_file_name = data_folder+"/"+"working_"+name;
    if (iteration==0){ //this is the first load
        ifstream sk_file((data_folder+"/"+name).c_str());
        if (sk_file.is_open()){
            cout<<"sifted key file opened"<<endl;
            /*pre assign buffer space for the sifted key string to be loaded*/
            sk_file.seekg(0, std::ios::end);   
            this->key.reserve(sk_file.tellg());
            sk_file.seekg(0, std::ios::beg);
            this->key.assign((std::istreambuf_iterator<char>(sk_file)),
                std::istreambuf_iterator<char>());
            cout<<"read success!"<<endl;
            cout<<"sk: "<<this->key<<endl;
            cout<<"bytes read: "<<key.length()<<endl;
            
            sk_file.close();

            ofstream working_sk_file(working_sk_file_name.c_str());
            working_sk_file << this->key;
            working_sk_file.close();

        }
        else{
            cout<<"could not open sifted key file: "<<name<<endl;
            exit(1);
        }
    }
    else{

        ifstream sk_file(working_sk_file_name.c_str());
        if (sk_file.is_open()){
            cout<<"sifted key file opened"<<endl;
            /*pre assign buffer space for the sifted key string to be loaded*/
            sk_file.seekg(0, std::ios::end);   
            this->key.reserve(sk_file.tellg());
            sk_file.seekg(0, std::ios::beg);
            this->key.assign((std::istreambuf_iterator<char>(sk_file)),
                std::istreambuf_iterator<char>());
            cout<<"read success!"<<endl;
            cout<<"sk: "<<this->key<<endl;
            cout<<"bytes read: "<<key.length()<<endl;
            
            sk_file.close();

        }
        else{
            cout<<"could not open working sifted key file: "<<working_sk_file_name<<endl;
            exit(1);
        }

    }

}