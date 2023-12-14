#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
unordered_set<char> calculateFirst(char nonTerminal, const unordered_map<char, vector<string>> &productions, unordered_map<char, unordered_set<char>> &firstSets)
{
    if (firstSets.find(nonTerminal) != firstSets.end())
    {
        // If already calculated, return the existing set
        return firstSets[nonTerminal];
    }
    unordered_set<char> firstSet;
    for (const string &production : productions.at(nonTerminal))
    {
        size_t i = 0;
        while (i < production.size())
        {
            if (isalpha(production[i]) && islower(production[i]))
            {
                firstSet.insert(production[i]);
                break;
            }
            else if (isupper(production[i]))
            {
                unordered_set<char> nextFirstSet = calculateFirst(production[i], productions,firstSets);
                firstSet.insert(nextFirstSet.begin(), nextFirstSet.end());
                if (nextFirstSet.count('e') == 0)
                {
                    // If the non-terminal doesn't derive epsilon, stop checking further
                    break;
                }
            }
            else
            {
                // Handle other symbols as needed
                break;
            }
            ++i;
        }
    }
    firstSets[nonTerminal] = firstSet;
    return firstSet;
}
unordered_set<char> calculateFollow(char nonTerminal, const unordered_map<char, vector<string>> &productions, unordered_map<char, unordered_set<char>> &firstSets,
                                    unordered_map<char, unordered_set<char>> &followSets)
{
    if (followSets.find(nonTerminal) != followSets.end())
    {
        // If already calculated, return the existing setreturn followSets[nonTerminal];
    }
    unordered_set<char> followSet;
    if (nonTerminal == 'S')
    {
        followSet.insert('$'); // '$' represents the end of input
    }
    for (const auto &production : productions)
    {
        for (const string &prod : production.second)
        {
            size_t i = prod.find(nonTerminal);
            while (i != string::npos)
            {
                // If the non-terminal is not at the end of the production
                if (i < prod.size() - 1)
                {
                    size_t j = i + 1;
                    while (j < prod.size())
                    {
                        if (isalpha(prod[j]) && islower(prod[j]))
                        {
                            followSet.insert(prod[j]);
                            break;
                        }
                        else if (isupper(prod[j]))
                        {
                            unordered_set<char> nextFirstSet = calculateFirst(prod[j], productions,
                                                                              firstSets);
                            followSet.insert(nextFirstSet.begin(), nextFirstSet.end());
                            if (nextFirstSet.count('e') == 0)
                            { // If the non-terminal doesn't derive epsilon, stop checking further
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                        ++j;
                    }
                    if (j == prod.size())
                    {
                        unordered_set<char> nextFollowSet = calculateFollow(production.first,productions, firstSets,followSets);
                        followSet.insert(nextFollowSet.begin(), nextFollowSet.end());
                    }
                }
                else
                {
                    // If the non-terminal is at the end of the production, add the symbols from the FOLLOW set of the left - hand side 
                    if (production.first != nonTerminal)
                    {
                        unordered_set<char> nextFollowSet = calculateFollow(production.first,productions, firstSets,followSets);
                        followSet.insert(nextFollowSet.begin(), nextFollowSet.end());
                    }
                }
                i = prod.find(nonTerminal, i + 1);
            }
        }
    }
    followSets[nonTerminal] = followSet;
    return followSet;
}
int main()
{
    unordered_map<char, vector<string>> productions = {
        {'S', {"AB", "BC", "a"}},
        {'A', {"a"}},
        {'B', {"b"}},
        {'C', {"c"}},
    };
    unordered_map<char, unordered_set<char>> firstSets;
    unordered_map<char, unordered_set<char>> followSets;
    for (const auto &production : productions)
    {
        char nonTerminal = production.first;
        calculateFirst(nonTerminal, productions, firstSets);
    }
    for (const auto &production : productions)
    {
        char nonTerminal = production.first;
        calculateFollow(nonTerminal, productions, firstSets, followSets);
    }
    cout << "FIRST sets:" << endl;
    for (const auto &firstSet : firstSets)
    {
        cout << firstSet.first << ": ";
        for (char terminal : firstSet.second)
        {
            cout << terminal << " ";
        }
        cout << endl;
    }
    cout << "\nFOLLOW sets:" << endl;
    for (const auto &followSet : followSets)
    {
        cout << followSet.first << ": ";
        for (char terminal : followSet.second)
        {
            cout << terminal << " ";
        }
        cout << endl;
    }
    return 0;
}
