#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;



class Token {
private:
    string value;
    string type;
public:
    Token();

    void set_token(string ivalue, string itype);
    void set_token(char c);
    void set_token(string s);
    void print_token();
    string get_type();

    void set_type();
    friend void vector_print(vector<Token> token_vector);
};

void vector_print(vector<Token> token_vector);
void scan(string file_location);
