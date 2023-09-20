#include <bits/stdc++.h>

using namespace std;

static const bool DBG = true;

// This program takes as input a grammar in Chomsky Normal Form and a set
// of strings and determines whether each string is in the language generated
// by the grammar.

// A grammar is in Chomsky Normal Form if all of its productions are of the
// form A -> BC or A -> a, where A, B, and C are nonterminals and a is a
// terminal.

// The input format is as follows:
// The first line contains the number of productions in the grammar.
// The next lines contain the productions of the grammar, one per line.
// The next line contains the number of strings to check.
// The next lines contain the strings to check, one per line.

// The output format is as follows:
// For each string, print "yes" if the string is in the language generated
// by the grammar and "no" otherwise.

// Time complexity: O(n^3 * |s|), where n is the number of productions in the
// grammar and |s| is the length of the string.

// Space complexity: O(n^2*m), where n is the number of productions in the
// grammar.

// Prints the matrix to the console. This function is used for debugging.
void print_matrix(const vector<vector<vector<bool>>>& matrix) {
    for(int i=0; i<matrix.size(); ++i) {
        for(int j=0; j<matrix[i].size(); ++j) {
            for(int k=0; k<matrix[i][j].size(); ++k) {
                cout << matrix[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}


// Checks if a string matches a particular grammar in CNF-form. This implementation 
// uses
// dynamic programming to check if a string matches a particular grammar.
// The grammar is represented as a map from nonterminals to the strings that
// they can generate. The indices map maps each nonterminal to an index. The
// symbols vector contains all of the nonterminals in the grammar. The
// function returns true if the string matches the grammar and false otherwise.

// Calls to this function should match the format: 
// check_string(grammar, s, indices, symbols)

// This implementation generates a matrix of size |s| x |s| x |symbols|, where
// |s| is the length of the string and |symbols| is the number of nonterminals
// in the grammar. The entry at position (i, j, k) in the matrix is true if
// the substring of s from i to j matches the nonterminal at position k in the
// symbols vector. The function returns the value at position (0, |s|-1, 0) in
// the matrix.
bool check_string(const vector<pair<string, string>>& non_terminal_grammar,
                    const vector<pair<string, string>>& terminal_grammar,
                    const string& s,
                    const map<string, int>& indices, const vector<string>& non_terminals) {
    if(DBG) {
        cout << "Entered check_string" << endl;
        //cout << "The map of nont_terminal_grammars contains" << endl;
        //print_vector(non_terminal_grammar);
        //cout << "The map of terminal_grammars contains" << endl;
        //print_vector(terminal_grammar);
    }
    int n = s.size();
    vector<vector<vector<bool>>> matrix(n, vector<vector<bool>>(n, vector<bool>(non_terminals.size(), false)));
    // Fill in the diagonal of the matrix. The entry at position (i, i, k) is
    // true if the substring of s from i to i matches the nonterminal at
    // position k in the symbols vector.
    for(int i=0; i<n; ++i) {
        string symbol = s.substr(i, 1);
        for(auto it=terminal_grammar.begin(); it!= terminal_grammar.end(); ++it) {
            //Check if it->second contains the symbol. The symbol is a single character string
            // but it->second may be a two character string.
            if(it->second.find(symbol)!=string::npos) {
                int index = indices.at(it->first);
                matrix[i][i][index] = true;
            }
        }
    }
    if(DBG) {
        cout << "The non_terminal_grammars contain" << endl;
        for(auto it=non_terminal_grammar.begin(); it!=non_terminal_grammar.end(); ++it) {
            cout << it->first << " " << it->second << endl;
        }
        cout << "The terminal_grammars contain" << endl;
        for(auto it=terminal_grammar.begin(); it!=terminal_grammar.end(); ++it) {
            cout << it->first << " " << it->second << endl;
        }
        cout << "The indices map contains" << endl;
        for(auto it=indices.begin(); it!=indices.end(); ++it) {
            cout << it->first << " " << it->second << endl;
        }
        cout << "The symbols vector contains" << endl;
        for(auto it=non_terminals.begin(); it!=non_terminals.end(); ++it) {
            cout << *it << endl;
        }

        cout << "Filled in the diagonal" << endl;
        print_matrix(matrix);
    }
    // Fill in the rest of the matrix. The entry at position (i, j, k) is true
    // if there exists a production A -> BC in the grammar, where the substring
    // of s from i to j matches B and the substring of s from j+1 to k matches
    // C.
    // This implementation will fill in the matrix in a diagonal fashion.

    // The outer loop iterates over the diagonals of the matrix, starting with
    // the diagonal just above the main diagonal and ending with the element
    // with indices (0, n-1).
    
    for(int i=1; i<n; ++i) {
        if(DBG) {
            cout << "Outer loop: i is " << i << endl;
            cout << "n is " << n << endl;
        }
        // The inner loop iterates over the entries in the diagonal.
        for(int j=0; j<n-i; ++j) {
            if(DBG) {
                cout << "Inner loop: j is " << j << endl;
                cout << "Targeting this square" << endl;
                cout << "j is " << j << endl;
                //cout << "j is " << j << endl;
                cout << "j+i is " << j+i << endl;
            }
            // The innermost loop iterates over the rules of the grammar and
            // checks if the substring of s from j to j+i matches the
            // nonterminal at position indices[it->first] in the symbols vector.
            for(auto it=non_terminal_grammar.begin(); it!=non_terminal_grammar.end(); ++it) {
                int index = indices.at(it->first);
                // The substring of s from j to j+i matches the nonterminal at
                // position index in the symbols vector if there exists a
                // production A -> BC in the grammar, where the substring of s
                // from j to j+k matches B and the substring of s from j+k+1 to
                // j+i matches C.
                for(int k=j; k<j+i; ++k) {
                
                    string B = it->second.substr(0, 1);
                    string C = it->second.substr(1,1);
                    int index_B = indices.at(B);
                    int index_C = indices.at(C);
                    if(matrix[j][k][index_B] && matrix[k+1][j+i][index_C]) {
                        matrix[j][j+i][index] = true;
                    }
                }
            }
        }
        
        
    }
    if(DBG) {
            cout << "Filled in the rest of the matrix" << endl;
            print_matrix(matrix);
    }        

    return matrix[0][n-1][0];
}



// Main reads the input and calls the function to check the strings against the grammar.
int main() {
    int N = 0;
    cin >> N;
    vector<pair<string, string>> non_terminal_grammar;
    vector<pair<string, string>> terminal_grammar;
    map<string, int> non_terminal_indices;
    vector<string> non_terminals;
    int index = 0;
    for(int i=0; i<N; ++i) {
        string s;
        cin >> s;
        if(DBG) {
            cout << "s is " << s << endl;
            cout << "i is " << i << endl;
            cout << "N is " << N << endl;
        }
        string lhs = s.substr(0, s.find("->"));
        string rhs = s.substr(s.find("->")+2);
        // Test if rhs is uppercase
        if(rhs[0] >= 'A' && rhs[0] <= 'Z') {
            non_terminal_grammar.push_back(pair<string, string>(lhs, rhs));
            
        } else {
            terminal_grammar.push_back(pair<string, string>(lhs, rhs));
        }
        if(non_terminal_indices.find(lhs) == non_terminal_indices.end()) {
                non_terminal_indices[lhs] = index++;
                non_terminals.push_back(lhs);
        }
    }
    cin >> N;
    if (DBG) {
        cout << "Survived until the testing of the grammar" << endl;
        cout << "N is " << N << endl;
    }
    for(int i=0; i<N; ++i) {
        string s;
        cin >> s;
        bool result = check_string(non_terminal_grammar, terminal_grammar, s, non_terminal_indices, non_terminals);
        if(result) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }
    return 0;

}