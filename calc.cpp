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
                    break;
                case 3:
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