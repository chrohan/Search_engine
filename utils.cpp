#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

vector<string> get_array_from_file(string src){
    fstream file(src);
    string word;
    vector<string>words;

    if (!file){
        cerr << "\nCan't open file: " << src << "\n";
        return words;
    }

    while (getline(file, word)){
        if (!word.empty()) words.push_back(word);
    }

    return words;
}

vector<string> linear_search_pre(vector<string> v, string str){
    vector<string> results;
    auto start = chrono::high_resolution_clock::now();

    for (string s : v){
        if (s.substr(0, str.size()) == str)
            results.push_back(s);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\nLinear Prefix Search: " << results.size() << " results in " << double(duration.count()) / 1e6 << " ms\033[0m\n";
    return results;
}

bool linear_search_exact(vector<string> v, string str){
    auto start = chrono::high_resolution_clock::now();
    bool found = find(v.begin(), v.end(), str) != v.end();
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\nLinear Exact Search: " << found << " result in " << double(duration.count()) / 1e6 << " ms\033[0m\n";
    return found;
}

// KMP utilities
void computeLPSArray(string pat, int M, int *lps){
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) len = lps[len - 1];
            else lps[i++] = 0;
        }
    }
}

int KMPSearch(string pat, string txt){
    int M = pat.length();
    int N = txt.length();
    int lps[M];
    computeLPSArray(pat, M, lps);

    int i = 0, j = 0;
    while (i < N) {
        if (pat[j] == txt[i]){
            j++; i++;
        }
        if (j == M) return i - j;
        else if (i < N && pat[j] != txt[i]){
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return -1;
}

vector<string> search(vector<string> v, string pat){
    vector<string>results;
    auto start = chrono::high_resolution_clock::now();

    for (string s : v){
        if (KMPSearch(pat, s) != -1)
            results.push_back(s);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\nKMP Global Search: " << results.size() << " results in " << double(duration.count()) / 1e6 << " ms\033[0m\n";
    return results;
}
