// Given two strings, one is a text string, text, and the other is a pattern string, pattern. Print the indexes of all occurrences of the pattern string in the text string using the Z function algorithm. Use 0-based indexing while returning the indices.

#include <bits/stdc++.h>
using namespace std;

// Brute Force
vector<int> getZValues(string str) {
    int n = str.size();

    vector<int> zValue(n, 0);

    for (int i = 0; i < n; i++) {
        while ((i + zValue[i] < n) && (str[i + zValue[i]] == str[zValue[i]]))
            zValue[i]++;
    }

    return zValue;
}

vector<int> search(string text, string pattern) {
    int n = text.size(), m = pattern.size();

    string superStr = pattern + "$" + text;

    vector<int> zValue = getZValues(superStr);

    vector<int> res;

    for (int idx = m + 1; idx < superStr.size(); idx++) {
        if (zValue[idx] == m)
            res.push_back(idx - (m + 1));
    }

    return res;
}

int main() {
    string text = "xyzabxyzabxyz";
    string pattern = "xyz";

    vector<int> ans = search(text, pattern);

    for (auto ind : ans)
        cout << ind << " ";
    return 0;
}
