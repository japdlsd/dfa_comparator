#include <vector>

using namespace std;

struct DFA {
    int n; // number of states
    int e; // size of input alphabet
    vector<bool> is_accepting; // true if state is accepting [n]
    vector<vector<int> > trans; // transition table [n][e]

    DFA(const int n, 
        const int e, 
        const vector<bool>& is_accepting, 
        const vector<vector<int> >& trans);
};

void print_dfa(DFA A);
bool is_same_language(DFA A1, DFA A2);
