# How does it works?

input: 2 DFAs $A_1$ and $A_2$

1. Construct simmetric difference of $A_1$ and $A_2$: 
$A := (A_1 - A_2) \cup (A_2 - A_1)$

2. Translate $A$ into regular (context-free) grammar $G$

3. Construct set of "terminating" nonterminals of grammar $G$. 
   If it's empty, then $L(A_1) = L(A_2)$.
