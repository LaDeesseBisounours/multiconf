#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>

#include <stdlib.h>

using namespace std;

const string tokens[] = {"<*_*>__", "__<*_*>"};

int error = 0;
string is_token_line(const string &line, unsigned line_number) {
    size_t first_token = line.find(tokens[0]);

    if (first_token == string::npos)
        return "";

    first_token += tokens[0].size();

    size_t last_token = line.rfind(tokens[1]);
    if (last_token == string::npos) {
        cerr << "line " << line_number << " is ill-formed : " << line << endl;
        error = 1;
        return "";
    }

    for (; isspace(line[first_token]); first_token++)
        continue;

    for (last_token--; isspace(line[last_token]); last_token--)
        continue;

    last_token++;

    return line.substr(first_token, last_token - first_token);
}

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
    if (argc != 2) {
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
    bool authorized = true

    unsigned count = 0;
    for (; !error && getline(input, line); count++) {
        cout << count << ": " << line << endl;

        if ((token = is_token_line(line, count)).size() != 0) {
            cout << "TOKEN FOUND \"" << token << "\"" << endl;
            
        }
    }

    return error;
}
