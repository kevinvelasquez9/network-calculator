#include <stdlib.h>
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
        unordered_map<string, int> variables;
        
        int evalExpr(const char *expr, int *result) {
            cout << result << endl;
            vector<string> tokens = tokenize(expr);
            switch(tokens.size()) {
                case 1:
                    evalOne(token[0], result);
                    break;
                case 3:
                    evalThree(tokens, result);
                    break;
                case 5:
                    break;
                default:
                    return 0;
            }
            return (result == NULL) ? 0 : 1;
        }

        // Evaluate for one token
        void evalOne(string token, int *result) {
            // If string is alphabetical
            if (is_alpha(token)) {
                if (variables.find(token) == variables.end()) {
                    cout << "This variable does not have an associated value" << endl;
                } else {
                    *result = variables[token];
                }
            }
            // String has numbers in it
            else {
                char *endptr;
                int num = strtol(tokens[0], &endptr, 10);
                if (*endptr != '\0') {
                    cout << "Error" << endl;
                } else {
                    *result = num;
                }
            }
        }

        // Evaluate for three tokens
        void evalThree(vector<string> tokens, int *result) {
            int ans = 0;
            // If it is an assignment
            if (tokens[1] == "=") {
                // stuff
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

        // Checks if string is alphabetical
        bool is_alpha(string s) {
            for (char const &c : s) {
                if (!isalpha(c)) {
                    return false;
                }
            }
            return true;
        }

        // Checks if string is an operator, otherwise return "."
        string is_op(string op) {
            if (check == "+" || check == "-" || check == "/" || check == "*") {
                return check;
            }
            return ".";
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
    return obj->evalExpr(expr, result);
}
