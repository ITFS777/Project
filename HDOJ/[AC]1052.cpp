#include <iostream>
#include <cstring>
#include <algorithm>
//////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
bool comp(int a, int b)
{
    return a > b;
}
//////////////////////////////////////////////////////////////////////////
int main(void)
{
    const int score = 200;
    int n = 0, i = 0, result = 0;
    int *s1_start = nullptr, *s1_end = nullptr;
    int *s2_start = nullptr, *s2_end = nullptr;
    int s1[1000] = {0};
    int s2[1000] = {0};
    while (cin >> n)
    {
        if (n)
        {
            memset(s1, 0, sizeof(s1));
            memset(s2, 0, sizeof(s2));
            result = 0;
            for (i = 0; i < n; ++i)
                cin >> s1[i];
            for (i = 0; i < n; ++i)
                cin >> s2[i];
            std::sort(s1, s1 + n, comp);
            std::sort(s2, s2 + n, comp);
            s1_start = s1;
            s1_end = s1 + n - 1;
            s2_start = s2;
            s2_end = s2 + n - 1;
            while (s1_start <= s1_end)
            {
                if (*s1_end > *s2_end)
                {
                    --s1_end;
                    --s2_end;
                    result += score;
                }
                else if (*s1_end == *s2_end)
                {
                    if (*s1_start > *s2_start)
                    {
                        ++s1_start;
                        ++s2_start;
                        result += score;
                    }
                    else if (*s1_start > *s1_end)
                    {
                        --s1_end;
                        ++s2_start;
                        result -= score;
                    }
                    else
                    {
                        --s1_end;
                        ++s2_start;
                    }
                }
                else
                {
                    --s1_end;
                    ++s2_start;
                    result -= score;
                }
            }
            cout << result << endl;
        }
        else
            return 0;
    }
    return 0;
}
