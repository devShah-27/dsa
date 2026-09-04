// ==================================================
// PROBLEM
// - Given two distinct words startWord and targetWord, and a wordList of unique words of equal lengths, find all shortest transformation sequence(s) from startWord to targetWord. 
// - Each step must change exactly one character, and all intermediate words must exist in wordList.
// ==================================================

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// WORD LADDER II — BFS LEVEL-BY-LEVEL PATH EXPLORATION
//
// Idea:
// - Perform BFS where the queue maintains the entire current transformation path.
// - Process each level completely to find all paths of minimal length. 
// - To allow multiple shortest paths through the same intermediate word at the same depth, erase visited words from the dictionary set only after the entire level finishes.
//
// Time Complexity: O(N * L * 26 + K * L) - Where N is word count, L is word length, and K is total shortest paths.
// Space Complexity: O(N * L + K * L) - For the hash set, queue storing full path vectors, and result.
// ==================================================

vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList)
{
    // Hash set for O(1) word lookup and deletion
    unordered_set<string> st(wordList.begin(), wordList.end());

    // Queue stores full paths to reconstruct sequences
    queue<vector<string>> q;

    q.push({beginWord});

    // Tracks words used in the current BFS level to delete them simultaneously
    vector<string> toErase;

    toErase.push_back(beginWord);

    vector<vector<string>> res;

    // Traverse level by level
    while (!q.empty())
    {
        // Erase words visited in previous levels so they are not reused
        for (string str : toErase)
        {
            st.erase(str);
        }

        toErase.clear();

        int size = q.size();

        bool found = false;

        // Process all sequences at the current BFS depth
        for (int i = 0; i < size; i++)
        {
            vector<string> levelList = q.front();
            q.pop();

            string lastWord = levelList.back();

            // Destination reached: collect sequence and stop expanding deeper
            if (lastWord == endWord)
            {
                res.push_back(levelList);
                found = true;
                continue;
            }

            // Try mutating each character from 'a' through 'z'
            for (int i = 0; i < lastWord.size(); i++)
            {
                char original = lastWord[i];

                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    lastWord[i] = ch;

                    // If valid transformation exists in the current dictionary
                    if (st.find(lastWord) != st.end())
                    {
                        levelList.push_back(lastWord);
                        q.push(levelList);
                        toErase.push_back(lastWord);
                        levelList.pop_back(); // Backtrack path vector
                    }
                }

                lastWord[i] = original;
            }
        }

        // If target was found at this level, no longer look for deeper levels
        if (found)
            break;
    }

    return res;
}

int main()
{
    string beginWord = "der", endWord = "dfs";

    vector<string> wordList = {"des", "der", "dfr", "dgt", "dfs"};

    vector<vector<string>> ans = findSequences(beginWord, endWord, wordList);

    cout << "The different sequences are:\n";

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
