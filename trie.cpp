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

class TrieNode{
public:
    unordered_map<char, TrieNode *>children;
    bool isEndOfWord;

    TrieNode(){
        isEndOfWord = false;
    }
};

class Trie{
public:
    TrieNode *root;

    Trie(){
        root = new TrieNode();
    }

    void insert(string str);
    void remove(string str);
    bool _remove(TrieNode *current, string str, int index);
    TrieNode *search_exact(string str);
    vector<string> search_pre(string str);
    void draw(TrieNode *current, int depth = 0);
};

void Trie::insert(string str){
    TrieNode *current = root;
    for (char ch : str){
        if (!current->children[ch]) {
            current->children[ch] = new TrieNode();
        }
        current = current->children[ch];
    }
    current->isEndOfWord = true;
}

TrieNode *Trie::search_exact(string str){
    TrieNode *current = root;

    auto start = chrono::high_resolution_clock::now();

    for (char ch : str){
        if (!current->children[ch]) return NULL;
        current = current->children[ch];
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\nExact Search: " << current->isEndOfWord << " result in " << double(duration.count()) / 1e6 << " ms\033[0m\n";

    return current->isEndOfWord ? current :NULL;
}

void get_words_dfs(TrieNode* current, string pre, vector<string>& results){
    if (!current)return;
    if (current->isEndOfWord) results.push_back(pre);
    for (auto [ch, node] : current->children){
        get_words_dfs(node, pre + ch, results);
    }
}

vector<string> Trie::search_pre(string str){
    auto start = chrono::high_resolution_clock::now();

    TrieNode *current = root;
    for (char ch : str){
        if (!current->children[ch]) return {};
        current = current->children[ch];
    }

    vector<string>results;
    get_words_dfs(current, str, results);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\nPrefix Search: " << results.size() << " results in " << double(duration.count()) / 1e6 << " ms\033[0m\n";

    return results;
}

void Trie::remove(string str){
    _remove(root, str, 0);
}

bool Trie::_remove(TrieNode *current, string str, int index){
    if (index == str.length()){
        if (!current->isEndOfWord) return false;
        current->isEndOfWord = false;
        return current->children.empty();
    }

    char ch = str[index];
    if (!current->children[ch]) return false;

    bool shouldDelete = _remove(current->children[ch], str, index + 1);

    if (shouldDelete){
        current->children.erase(ch);
        return current->children.empty();
    }

    return false;
}

void Trie::draw(TrieNode *current, int depth){
    if (!current) current = root;
    for (auto [ch, node] : current->children){
        for (int i = 0; i < depth; i++) cout << "_ ";
        cout << ch << "\n";
        draw(node, depth + 1);
    }
}
