#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <stdlib.h>

#include "rules.hh"
#include "parser.hh"
#include "input.hh"


using namespace std;


int main(int argc, char *argv[]) {
    struct IO_Parsed io = parse_input(argc, const_cast<const char**>(argv));
    (void)io;

    env_parser("MULTICONF", io.tokens);

    ifstream input(io.input);
    if (!input.is_open()) {
        cerr << "Could not open file : " << argv[1] << endl;
        return 1;
    }


    ofstream output(io.output);
    if (output.is_open()) {
        cout.rdbuf(output.rdbuf());
    }

    

    string line, token;
    bool authorized = true;
    int error = 0;
    unsigned count = 0;
    for (; !error && getline(input, line); count++) {

        if ((token = is_token_line(line, count, error)).size() != 0) {
            //cout << "TOKEN FOUND \"" << token << "\"" << endl;
            authorized = false;
            if (io.tokens.find(token) != io.tokens.end()) {
                authorized = true;
            }
        }
        if (authorized) {
            cout << line << endl;
        }
    }
    return error;
}
