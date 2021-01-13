#include "rules.hh"

const unsigned nbToken = 3;
const string tokens[nbToken] = { "-t", "-i", "-o" };

bool TokenRule::parse(const int argc, const char **argv, int &index, struct IO_Parsed& io) const {
    index++;
    if (index == argc) {
        cerr << "flag " << name << " : needs at least one argument" << endl;
        return true;
    }

    io.tokens.emplace(argv[index]); 
    index++;
    bool is_a_token = false;
    for (; index < argc; index++) {
        for (unsigned nt = 0; nt < nbToken; nt++) {
            string tok(tokens[nt]);
            if (!tok.compare(argv[index])) {
                is_a_token = true;
                break;
            }
        }
        if (is_a_token) {
            break;
        }
        io.tokens.emplace(argv[index]); 
    }
    return false;
}

bool InputRule::parse(const int argc, const char **argv, int &index, struct IO_Parsed& io) const {
    index++;
    if (index == argc) {
        cerr << "flag " << name << " : needs at one argument" << endl;
        return true;
    }
    io.input = argv[index];
    // has_one_input = true;
    return false;
}

bool OutputRule::parse(const int argc, const char **argv, int &index, struct IO_Parsed& io) const {
    index++;
    if (index == argc) {
        cerr << "flag " << name << " : needs at one argument" << endl;
        return true;
    }
    io.output = argv[index];
    return false;
}

const TokenRule                token_r(tokens[0]);
const InputRule                input_r(tokens[1]);
const OutputRule               output_r(tokens[2]);
const vector<const FlagRule *> rules{&token_r, &input_r, &output_r};
