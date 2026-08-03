// Consider a scenario where a teacher wants to distribute cookies to students, with each student receiving at most one cookie.

// Given two arrays, student and cookie, the ith value in the Student array describes the minimum size of cookie that the ith student can be assigned. The jth value in the Cookie array represents the size of the jth cookie. If Cookie[j] >= Student[i], the jth cookie can be assigned to the ith student.
// Maximize the number of students assigned with cookies and output the maximum number.

#include <bits/stdc++.h>
using namespace std;

// GREEDY APPROACH
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
