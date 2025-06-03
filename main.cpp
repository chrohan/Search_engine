#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include "trie.cpp"
#include "utils.cpp"
using namespace std;

int main(){
    Trie trie;
    vector<string>words;
    string file_path;

    cout << "Enter path to input word file: ";
    cin >> file_path;

    words = get_array_from_file(file_path);
    for (string word: words){
        trie.insert(word);
    }

    cout << "\nTrie loaded with " << words.size() << " words.\n";

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Trie: Insert word\n";
        cout << "2. Trie: Search exact\n";
        cout << "3. Trie: Search prefix\n";
        cout << "4. Trie: Delete word\n";
        cout << "5. Trie: Draw tree\n";
        cout << "6. Linear Search: Exact\n";
        cout << "7. Linear Search: Prefix\n";
        cout << "8. KMP Global Search\n";
        cout << "9. Exit\n";
        cout << "Choose: ";

        int choice;
        cin >> choice;

        string query;
        switch (choice){
        case 1:
            cout << "Enter word to insert: ";
            cin >> query;
            trie.insert(query);
            cout << "Inserted.\n";
            break;
        case 2:
            cout << "Enter word to search: ";
            cin >> query;
            cout << (trie.search_exact(query) ? "Found.\n" : "Not Found.\n");
            break;
        case 3:
            cout << "Enter prefix to search: ";
            cin >> query;
            {
                vector<string> res = trie.search_pre(query);
                for (string w : res) cout << w << "\n";
            }
            break;
        case 4:
            cout << "Enter word to delete: ";
            cin >> query;
            trie.remove(query);
            cout << "Deleted.\n";
            break;
        case 5:
            trie.draw(nullptr);
            break;
        case 6:
            cout << "Enter word to search (linear): ";
            cin >> query;
            cout << (linear_search_exact(words, query) ? "Found.\n" : "Not Found.\n");
            break;
        case 7:
            cout << "Enter prefix to search (linear): ";
            cin >> query;
            {
                vector<string> res = linear_search_pre(words, query);
                for (string w : res) cout << w << "\n";
            }
            break;
        case 8:
            cout << "Enter pattern to search (KMP): ";
            cin >> query;
            {
                vector<string> res = search(words, query);
                for (string w : res) cout << w << "\n";
            }
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
