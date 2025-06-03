
#Trie & Search Engine CLI Tool

This is a command-line search engine built in **C++** that supports various string searching techniques including:
- Trie-based exact and prefix matching
- Linear search
- KMP (Knuth-Morris-Pratt) pattern matching

##Project Structure

```
.
├── main.cpp           # Main CLI interface
├── trie.cpp           # Trie data structure and operations
├── utils.cpp          # File handling and search functions
├── music.txt          # Sample input file (list of strings)
├── README.md          # You're here!
```

##Features

- Insert words into a Trie
- Exact word search (Trie & Linear)
- Prefix search (Trie & Linear)
- Pattern search (KMP)
- Delete words from the Trie
- Visualize the Trie structure
- Benchmark each operation's performance (in milliseconds)

##How to Run

### 1. Compile


### 2. Run


### 3. Input

When prompted:

- **Enter file path**: If the file is in the same directory, just enter the filename, e.g., `music.txt`.
- Follow the **menu options** to interact.

## Menu Options

```
===== MENU =====
1. Trie: Insert word
2. Trie: Search exact
3. Trie: Search prefix
4. Trie: Delete word
5. Trie: Draw tree
6. Linear Search: Exact
7. Linear Search: Prefix
8. KMP Global Search
9. Exit
```

##Sample Input (music.txt)

Each line should contain one entry:

```
After A Few - Travis Denning
Hotel California - Eagles
Shape of You - Ed Sheeran
...
```

##Dependencies

- Standard C++17
- Works on Linux/Mac. For Windows, use MinGW or WSL.

##Future Improvements

- Add fuzzy matching with Levenshtein distance
- Integrate GUI for visualization
- Use a file picker dialog for better UX
- Integrate AI for search suggestion

## Author

Rohan Chauhan  
chrohan007@gmail.com  
🌐 [GitHub](https://github.com/chrohan) | [LinkedIn](https://www.linkedin.com/in/rohan-chauhan2003/)
