#include "parser.hh"

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

const string tokens[] = {"<*_*>__", "__<*_*>"};

string is_token_line(const string &line, const unsigned line_number, int& error) {
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
