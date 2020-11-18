#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>
using std::vector;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::cout;
using std::endl;

struct Calc {
};

class CalcImpl : public Calc {
    public:
        unordered_map<char, int> variables;
        
        int evalExpr(const char *expr, int &result) {
            vector<string> tokens = tokenize(expr);
            switch(tokens.size()) {
                case 1:
                    if (tokens[0].empty()) {
                        return 0;
                    }
                    char var = tokens[0].at(0);
                    if ( (var >= 65 && var <= 90) || 
                        (var >= 97 && var <= 122)) {
                        if (variables.find(var) == variables.end()) {
                            printf("This variable does not have an associated value\n");
                        } else {
                            return variables[var];
                        }
                    }
                    char *endptr;
                    int intVar = strtol(tokens[0], &endptr, 10);
                    //Beginning pointer and endpointer will be the same if conversion failed
                    if (endptr == tokens[0]) {
                        return 0;
                    } else {
                        printf("%d\n", intVar);
                    }
                    break;
                case 3:
                    int second;
                    if (tokens[1].size() > 1) {
                        return 0;
                    }
                    second = sign_check(tokens[1].at(0));
                    if (second == 0) {
                        return 0;
                    }
                    int first;
                    if (tokens[0].size() > 1) {
                        char *endptr;
                        first = strtol(tokens[0], &endptr, 10);
                        if (endptr == tokens[0]) {
                            return 0;
                        }
                    } else {
                        char l = tokens[0].at(0);
                        if (valid_letter(l)) {
                            first = l;
                        } else {
                            return 0;
                        }   
                    }


                    if (second == '/' && third == 0) {
                        printf("Error\n");
                        return 0;
                    }
                    break;
                case 5:
                    break;
                default:
                    return 0;
            }
        }

        // Splits a string into a vector of strings
        vector<string> tokenize(const string &expr) {
            vector<string> vec;
            stringstream s(expr);
            string tok;
            while (s >> tok) {
                vec.push_back(tok);
            }
            return vec;
        }

        bool valid_letter(string s) {
            if ( (var >= 65 && var <= 90) || 
                    (var >= 97 && var <= 122)) {
                return true;
            } else {
                return false;
            }
        }

        int sign_check(char check) {
            if (check == '=' || check == '+' ||
                check == '-' || check == '/' ||
                check == '*') {
                return check;
            } else {
                return 0;
        }
}

extern "C" struct Calc *calc_create(void) {
    return new CalcImpl();
}

extern "C" void calc_destroy(struct Calc *calc) {
    CalcImpl *obj = static_cast<CalcImpl *>(calc);
    delete obj;
}

extern "C" int calc_eval(struct Calc *calc, const char *expr, int *result) {
    CalcImpl *obj = static_cast<CalcImpl *>(calc);
    return obj->evalExpr(expr, *result);
}
