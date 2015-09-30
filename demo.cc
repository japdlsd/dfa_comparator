#include <cstdio>
#include <vector>

#include "dfa_comp.h"

using namespace std;

DFA read_dfa() {
    int n, e;
    scanf(" %i", &n);
    scanf(" %i", &e);
    
    vector<bool> is_accepting(n);
    vector<vector<int> > trans(n, vector<int> (e));

    for (int i = 0; i < n; i++) {
        int buf;
        scanf(" %i", &buf);
        is_accepting[i] = (buf != 0);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < e; j++) {
            int buf;
            scanf(" %i", &buf);
            trans[i][j] = buf;
        }
    }
    
    return DFA(n, e, is_accepting, trans);
}


int main() {
    // read 2 DFAs from standard input
    fprintf(stderr, "reading first DFA\n");
    DFA A1 = read_dfa();
    fprintf(stderr, "reading second DFA\n");
    DFA A2 = read_dfa();
    
    print_dfa(A1); 
    print_dfa(A2);

    // call function
    fprintf(stderr, "calling function\n");
    const bool answer = is_same_language(A1, A2);
    // print the answer
    if (answer) printf("YES\n");
    else printf("NO\n");
}
