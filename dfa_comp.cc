#include <vector>
#include <map>
#include <queue>
#include <cstdio>
#include <cassert>

#include "dfa_comp.h"

#define mp make_pair

using namespace std;
    
DFA::DFA(const int n, 
         const int e, 
         const vector<bool>& is_accepting, 
         const vector<vector<int> >& trans) {
            assert(n > 0);
            assert(e > 0);
            this->n = n;
            this->e = e;
            assert(is_accepting.size() == n);
            this->is_accepting = vector<bool>(is_accepting);
            assert(trans.size() == n && trans[0].size() == e);
            this->trans = vector<vector<int> > (trans);
    }

void print_dfa(DFA A) {
    fprintf(stderr, "A.n = %i, A.e = %i\n", A.n, A.e);
    for (int i = 0; i < A.n; i++) {
        fprintf(stderr, "%i ", static_cast<int>(A.is_accepting[i]));
    }
    fprintf(stderr, "\n");

    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < A.e; j++) {
            fprintf(stderr, "%i ", A.trans[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

DFA simm_diff(DFA A1, DFA A2) {
    // constructs simmetric difference of two DFAs A1 and A2
    fprintf(stderr, "simm_diff\n");
    assert(A1.e == A2.e);

    int amount = 0;
    map<pair<int, int>, int> ordering;

    for (int i = 0; i < A1.n; i++) {
        for (int j = 0; j < A2.n; j++) {
            ordering[mp(i,j)] = amount++;
        }
    }

    vector<bool> is_accepting(amount);
    for (int i = 0; i < A1.n; i++) {
        for (int j = 0; j < A2.n; j++) {
            is_accepting[ordering[mp(i, j)]] = (A1.is_accepting[i] ^ A2.is_accepting[j]);
        }
    }

    fprintf(stderr, "simm_diff is almost over\n");
    vector<vector<int> > trans(amount, vector<int>(A1.e));
    
    for (int i = 0; i < A1.n; i++) {
        for (int j = 0; j < A2.n; j++) {
            for (int a = 0; a < A1.e; a++) {
                assert(ordering[mp(i,j)] < amount);
                trans[ordering[mp(i, j)]][a] = ordering[mp(A1.trans[i][a], A2.trans[j][a])];
            }
        }
    }
    
    return DFA(amount, A1.e, is_accepting, trans);
}

vector<bool> construct_reachability (DFA A) {
    // constructs set of reachable states of DFA A
    fprintf(stderr, "construct_reachability\n");
    vector<bool> reachability(A.n, false);
    
    queue<int> Q;
    
    Q.push(0);
    reachability[0] = true;

    while (!Q.empty()) {
        const int state = Q.front(); 
        Q.pop();
        
        for (int a = 0; a < A.e; a++) {
            const int new_state = A.trans[state][a];
            if (!reachability[new_state]) {
                reachability[new_state] = true;
                Q.push(new_state);
            }
        }
    }

    return reachability;
}

bool is_same_language(DFA A1, DFA A2) {
    // returns true if two automata accepts same languages
    fprintf(stderr, "is_same_language\n");
    if (A1.e != A2.e) {
        return false;
    }

    DFA A = simm_diff(A1, A2);
    print_dfa(A);
    
    vector<bool> reachable_states = construct_reachability(A);
    
    fprintf(stderr, "reachability\n");
    for (int i = 0; i < A.n; i++) {
        fprintf(stderr, "%i ", static_cast<int>(reachable_states[i]));
    }
    fprintf(stderr, "\n");

    bool answer = true;
    for (int i = 0; i < A.n; i++) {
        if (reachable_states[i] && A.is_accepting[i]) {
            answer = false;
        }
    }

    return answer;
}
