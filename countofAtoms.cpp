#include <bits/stdc++.h>
#include <stack>
using namespace std;

class Solution {
public:
    string countOfAtoms(string formula) {
        stack<unordered_map<string, int>> stk;
        stk.push({});
        int n = formula.size();
        for (int i = 0; i < n;) {
            if (formula[i] == '(') {
                stk.push({});
                i++;
            } else if (formula[i] == ')') {
                auto top = stk.top();
                stk.pop();
                i++;
                int i_start = i;
                while (i < n && isdigit(formula[i])) i++;
                int mul = i_start < i ? stoi(formula.substr(i_start, i - i_start)) : 1;
                for (auto & [name, count] : top) {
                    stk.top()[name] += count * mul;
                }
            } else {
                int i_start = i;
                i++;
                while (i < n && islower(formula[i])) i++;
                string name = formula.substr(i_start, i - i_start);
                i_start = i;
                while (i < n && isdigit(formula[i])) i++;
                int mul = i_start < i ? stoi(formula.substr(i_start, i - i_start)) : 1;
                stk.top()[name] += mul;
            }
        }
        auto& count = stk.top();
        vector<string> elements;
        for (auto& [name, _] : count) {
            elements.push_back(name);
        }
        sort(elements.begin(), elements.end());
        string res;
        for (const auto& name : elements) {
            res += name;
            if (count[name] > 1) {
                res += to_string(count[name]);
            }
        }
        return res;
    }
};
