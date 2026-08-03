// Problem:
// Given students with minimum cookie size requirements and cookies of different sizes, assign at most one cookie to each student. Maximize the number of students who can receive a cookie and return the maximum number of satisfied students.

#include <bits/stdc++.h>
using namespace std;

// ==================================================
// GREEDY APPROACH
//
// Idea:
// Sort both students and cookies in increasing order.
// Assign the smallest available cookie that can satisfy the current smallest requirement.
// This greedy choice maximizes the chance of satisfying more students.
//
// Time Complexity: O(N log N + M log M)
// Space Complexity: O(1) (excluding sorting overhead)
// ==================================================

int findMaximumCookieStudents(vector<int> &Student, vector<int> &Cookie)
{
    int n = Student.size(), m = Cookie.size();

    sort(Student.begin(), Student.end());
    sort(Cookie.begin(), Cookie.end());

    int l = 0, r = 0;

    while (l < n && r < m)
    {
        if (Student[l] <= Cookie[r])
            l++;

        r++;
    }

    return l;
}

int main()
{
    srand(time(0));

    int n = 100000;
    int m = 100000;

    vector<int> Student(n);
    vector<int> Cookie(m);

    for (int i = 0; i < n; i++)
    {
        Student[i] = rand() % 100000 + 1;
    }

    for (int i = 0; i < m; i++)
    {
        Cookie[i] = rand() % 100000 + 1;
    }

    int result = findMaximumCookieStudents(Student, Cookie);

    cout << "Number of students satisfied: " << result << endl;

    return 0;
}