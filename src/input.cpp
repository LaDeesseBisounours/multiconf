#include "input.hh"
#include "rules.hh"

#include <cstdlib>
#include <iostream>
#include <set>


using namespace std;

struct IO_Parsed parse_input(const int argc, const char *argv[]) {
    struct IO_Parsed res;
    res.tokens.emplace("ALL");
    int index = 1;

    for (; index < argc; index++) {

        string current(argv[index]);
        bool   is_a_flag = false;

        for (const auto& rule: rules) {
            if (!current.compare(rule->name)) {

                bool error = rule->parse(argc, argv, index, res);

                if (error)
                    cerr << "error flag" << endl;
                is_a_flag = true;
                break;
            }
        }
        if (!is_a_flag) {
            cerr << "UNKNOWN FLAG " << argv[index] << endl;
        }
    }
    return res;
}

void env_parser(const string &env_name, set<string>& tokens) {
    const char *env_p = std::getenv(env_name.c_str());

    if (env_p == nullptr)
        return;

    string         env(env_p);
    size_t         start_index = 0;
    size_t         delimiter;

    while ((delimiter = env.find(",", start_index)) != string::npos) {
        tokens.emplace(env.substr(start_index, delimiter - start_index));
        start_index = delimiter + 1;
    }
    if (start_index < env.size()) {
        tokens.emplace(env.substr(start_index, env.size() - start_index));
    }
}
