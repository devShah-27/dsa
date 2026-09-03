// ==================================================
// PROBLEM
// - Given two distinct words startWord and targetWord, and a wordList of unique words of equal length M, find the length of the shortest transformation sequence from startWord to targetWord.
// - Only one character can be changed at a time, and every intermediate word must exist in the wordList.
// - Return 0 if no transformation sequence is possible.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// WORD LADDER I — BFS APPROACH
//
// Idea:
// - Model the transformation sequence as an unweighted graph where an edge exists between words differing by exactly one character.
// - Use Breadth-First Search (BFS) to find the shortest transformation path.
// - Store words in an unordered_set for O(1) average lookup
// - Try all 26 lowercase substitutions at each position, and erase visited words from the set to avoid cycles.
//
// Time Complexity: O(N * M * 26) - Where N is the number of words and M is the length of each word.
// Space Complexity: O(N * M)     - For storing words in the unordered_set and BFS queue.
// ==================================================

int wordLadderLength(const string startWord, const string targetWord, const vector<string> &wordList)
{
    // Insert all dictionary words into a hash set for O(1) lookup and deletion
    unordered_set<string> st(wordList.begin(), wordList.end());

    // Queue stores pairs of {currentWord, sequenceLength}
    queue<pair<string, int>> q;

    // Push the starting word with an initial sequence length of 1
    q.push({startWord, 1});

    // Erase startWord from the set so it is not revisited
    st.erase(startWord);

    // Perform BFS traversal level-by-level
    while (!q.empty())
    {
        string word = q.front().first;
        int steps = q.front().second;

        q.pop();

        // If the target word is reached, return the total transformation steps
        if (word == targetWord)
            return steps;

        // Try replacing each character of the word from 'a' to 'z'
        for (int i = 0; i < word.length(); i++)
        {
            char original = word[i];

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                word[i] = ch;

                // If the modified word exists in the dictionary, it is a valid next state
                if (st.find(word) != st.end())
                {
                    st.erase(word); // Mark visited by removing from set
                    q.push({word, steps + 1});
                }
            }

            // Restore the original character before mutating the next index
            word[i] = original;
        }
    }

    // Return 0 if targetWord cannot be reached
    return 0;
}

int main()
{
    string startWord = "der", targetWord = "dfs";

    vector<string> wordList = {"des", "der", "dfr", "dgt", "dfs"};

    int ans = wordLadderLength(startWord, targetWord, wordList);

    cout << "Word ladder length is: " << ans;

    return 0;
}
