#ifndef _INPUT_HH
#define _INPUT_HH

#include <vector>
#include <string>
#include <set>

#include "rules.hh"

using namespace std;
void env_parser(const string &env_name, set<string>& tokens);
struct IO_Parsed parse_input(const int argc, const char* argv[]);

#endif /* _INPUT_HH */
