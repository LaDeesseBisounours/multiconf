#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>

#include <stdlib.h>

#include "parser.hh"

using namespace std;

vector<string> env_parser(const string& env_name) {
    const char* env_p = std::getenv(env_name.c_str());
    cout << env_name << " : " << env_p << '\n';
    string env(env_p);
    size_t start_index = 0;
    size_t delimiter;
    vector<string> res({ "ALL" });

    while ((delimiter = env.find(",", start_index)) != string::npos) {
        string tmp = env.substr(start_index, env.size() - start_index);
        cout << "loop " << tmp << endl;
        res.push_back(env.substr(start_index, delimiter - start_index));
        start_index = delimiter + 1;
    }
    if (start_index < env.size()) {
        string tmp = env.substr(start_index, env.size() - start_index);
        cout << "final " << tmp << endl;
        res.push_back(env.substr(start_index, env.size() - start_index));
    }
    return res;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "no path specified" << endl;
        return 1;
    }


    vector<string> multiconf = env_parser("MULTICONF");

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Could not open file : " << argv[1] << endl;
        return 1;
    }

    string line, token;
    bool authorized = true;
    int error = 0;
    unsigned count = 0;
    for (; !error && getline(input, line); count++) {
        //cout << count << ": " << line << endl;

        if ((token = is_token_line(line, count, error)).size() != 0) {
            cout << "TOKEN FOUND \"" << token << "\"" << endl;
            bool found = false;
            for (const string& it : multiconf) {
                if (!token.compare(it)) {
                    authorized = true;
                    found = true;
                    break;
                }
            }
            if (!found)
                authorized = false;

        }
        if (authorized) {
            cout << "authorized string " << line << endl;
        }
    }
    return error;
}
