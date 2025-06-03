#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <limits>
#include "trie.cpp"
#include "utils.cpp"

using namespace std;

// Debug function to print word details
void debug_print_word(const string& word, const string& label) {
    cout << label << ": '" << word << "' (length: " << word.length() << ")";
    cout << " [";
    for (size_t i = 0; i < word.length(); i++) {
        if (i > 0) cout << ", ";
        cout << (int)word[i];
    }
    cout << "]" << endl;
}

// Debug function to print first few words from file
void debug_print_loaded_words(const vector<string>& words) {
    cout << "\n=== DEBUG: First 10 words loaded from file ===\n";
    for (size_t i = 0; i < min(words.size(), (size_t)10); i++) {
        debug_print_word(words[i], "Word " + to_string(i));
    }
    cout << "=== End of debug info ===\n";
}

// Function to remove whitespace from string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to remove all whitespace characters including newlines
string clean_word(const string& str) {
    string result;
    for (char c : str) {
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
            result += c;
        }
    }
    return result;
}

int main(){
    Trie trie;
    vector<string> words;
    string file_path;
    
    cout << "Enter path to input word file: ";
    getline(cin, file_path);
    
    try {
        words = get_array_from_file(file_path);
        
        // Debugging: Prnting info about loaded words
        cout << "\nLoaded " << words.size() << " words from file.\n";
        debug_print_loaded_words(words);
        
        // Clean ing words and insert into trie
        vector<string> cleaned_words;
        for (const string& word : words) {
            string cleaned = clean_word(word);
            if (!cleaned.empty()) {
                cleaned_words.push_back(cleaned);
                trie.insert(cleaned);
            }
        }
        
        cout << "\nTrie loaded with " << cleaned_words.size() << " cleaned words.\n";
        
        // Debug: checking if the debuggin the working ornot
        cout << "\n=== DEBUG: First 5 cleaned words ===\n";
        for (size_t i = 0; i < min(cleaned_words.size(), (size_t)5); i++) {
            debug_print_word(cleaned_words[i], "Cleaned word " + to_string(i));
        }
        
        // Storing the cleaned words for search
        words = cleaned_words;
        
    } catch (const exception& e) {
        cout << "Error loading file: " << e.what() << endl;
        return 1;
    }
    
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
        cout << "9. Debug: Search with details\n";
        cout << "10. Exit\n";
        
        string choice_str;
        int choice = -1;
        cout << "Choose: ";
        getline(cin, choice_str);
        
        try {
            choice = stoi(choice_str);
        } catch (...) {
            choice = -1;
        }
        
        string query;
        switch (choice) {
        case 1:
            cout << "Enter word to insert: ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                trie.insert(cleaned);
                cout << "Inserted cleaned word: '" << cleaned << "'\n";
            } else {
                cout << "Empty input. Nothing inserted.\n";
            }
            break;
            
        case 2:
            cout << "Enter word to search: ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                debug_print_word(cleaned, "Searching for");
                bool found = trie.search_exact(cleaned);
                cout << (found ? "Found.\n" : "Not Found.\n");
            } else {
                cout << "Empty input.\n";
            }
            break;
            
        case 3:
            cout << "Enter prefix to search: ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                vector<string> res = trie.search_pre(cleaned);
                if (res.empty()) {
                    cout << "No words found with prefix '" << cleaned << "'.\n";
                } else {
                    cout << "Found " << res.size() << " word(s):\n";
                    for (const string& w : res) {
                        cout << w << "\n";
                    }
                }
            } else {
                cout << "Empty input.\n";
            }
            break;
            
        case 4:
            cout << "Enter word to delete: ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                trie.remove(cleaned);
                cout << "Deleted '" << cleaned << "'.\n";
            } else {
                cout << "Empty input. Nothing deleted.\n";
            }
            break;
            
        case 5:
            trie.draw(nullptr);
            break;
            
        case 6:
            cout << "Enter word to search (linear): ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                cout << (linear_search_exact(words, cleaned) ? "Found.\n" : "Not Found.\n");
            } else {
                cout << "Empty input.\n";
            }
            break;
            
        case 7:
            cout << "Enter prefix to search (linear): ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                vector<string> res = linear_search_pre(words, cleaned);
                if (res.empty()) {
                    cout << "No words found with prefix '" << cleaned << "'.\n";
                } else {
                    cout << "Found " << res.size() << " word(s):\n";
                    for (const string& w : res) {
                        cout << w << "\n";
                    }
                }
            } else {
                cout << "Empty input.\n";
            }
            break;
            
        case 8:
            cout << "Enter pattern to search (KMP): ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                vector<string> res = search(words, cleaned);
                if (res.empty()) {
                    cout << "No words found containing pattern '" << cleaned << "'.\n";
                } else {
                    cout << "Found " << res.size() << " word(s):\n";
                    for (const string& w : res) {
                        cout << w << "\n";
                    }
                }
            } else {
                cout << "Empty input.\n";
            }
            break;
            
        case 9:
            cout << "Enter word to debug search: ";
            getline(cin, query);
            if (!query.empty()) {
                string cleaned = clean_word(query);
                debug_print_word(query, "Original input");
                debug_print_word(cleaned, "Cleaned input");
                
                // Check if it exists in the vector
                bool found_in_vector = false;
                for (const string& w : words) {
                    if (w == cleaned) {
                        found_in_vector = true;
                        break;
                    }
                }
                cout << "Found in words vector: " << (found_in_vector ? "YES" : "NO") << "\n";
                cout << "Found in trie: " << (trie.search_exact(cleaned) ? "YES" : "NO") << "\n";
            } else {
                cout << "Empty input.\n";
            }
            break;
            
        case 10:
            cout << "Goodbye!\n";
            return 0;
            
        default:
            cout << "Invalid choice. Please enter a number between 1-10.\n";
        }
    }
    
    return 0;
}