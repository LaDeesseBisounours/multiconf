#ifndef _RULES_HH
#define _RULES_HH

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct IO_Parsed {
    string      input;
    string      output;
    set<string> tokens;
};

class FlagRule {
public:
    const string name;
    FlagRule(string name)
        : name(name) {}
    virtual bool parse(const int argc, const char **argv, int &index,
                       struct IO_Parsed &io) const = 0;
};

class TokenRule : public FlagRule {
public:
    TokenRule(string name)
        : FlagRule(name) {}
    bool parse(const int argc, const char **argv, int &index,
               struct IO_Parsed &io) const;
};
class InputRule : public FlagRule {
public:
    InputRule(string name)
        : FlagRule(name) {}
    bool parse(const int argc, const char **argv, int &index,
               struct IO_Parsed &io) const;
};

class OutputRule : public FlagRule {
public:
    OutputRule(string name)
        : FlagRule(name) {}
    bool parse(const int argc, const char **argv, int &index,
               struct IO_Parsed &io) const;
};

const unsigned                        nb_rules = 3;
extern const vector<const FlagRule *> rules;
#endif /* _RULES_HH */
