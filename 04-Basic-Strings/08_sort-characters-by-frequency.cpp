// You are given a string s. Return the array of unique characters, sorted by highest to lowest occurring characters.

// If two or more characters have same frequency then arrange them in alphabetic order.

#include <bits/stdc++.h>
using namespace std;

bool comparator(pair<int, char> p1, pair<int, char> p2)
{
    if (p1.first > p2.first)
        return true;

    if (p1.first < p2.first)
        return false;

    if (p1.second < p2.second)
        return true;

    return false;
}

vector<char> frequencySort(string &s)
{
    pair<int, char> freq[26];

    for (int i = 0; i < 26; i++)
        freq[i] = {0, i + 'a'};

    for (int i = 0; i < s.size(); i++)
        freq[s[i] - 'a'].first++;

    // freq is a fixed-size array. When used in sort, the name freq decays into a pointer to the first element.
    // freq + 26 is one past the last element, which is exactly what sort expects.
    // sort(start_iterator, end_iterator, comparison_function);
    sort(freq, freq + 26, comparator);

    vector<char> ans;

    for (int i = 0; i < 26; i++)
    {
        if (freq[i].first == 0)
            break;

        ans.emplace_back(freq[i].second);
    }

    return ans;
}

int main()
{
    string s = "tree";

    vector<char> result = frequencySort(s);

    for (char c : result)
        cout << c << " ";

    return 0;
}