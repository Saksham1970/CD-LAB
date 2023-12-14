#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
unordered_set<char> calculateLeading(char nonTerminal, const unordered_map<char, vector<string>> &productions, unordered_map<char, unordered_set<char>> &leadingSets)
{
    if (leadingSets.find(nonTerminal) != leadingSets.end())
    {
        // If already calculated, return the existing set
        return leadingSets[nonTerminal];
    }
    unordered_set<char> leadingSet;
    for (const string &production : productions.at(nonTerminal))
    {
        size_t i = 0;
        while (i < production.size())
        {
            if (isalpha(production[i]) && islower(production[i]))
            {
                leadingSet.insert(production[i]);
                break;
            }
            else if (isupper(production[i]))
            {
                unordered_set<char> nextLeadingSet = calculateLeading(production[i],
                                                                      productions, leadingSets);
                leadingSet.insert(nextLeadingSet.begin(), nextLeadingSet.end());
                if (nextLeadingSet.count('e') == 0)
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
    leadingSets[nonTerminal] = leadingSet;
    return leadingSet;
}
unordered_set<char> calculateTrailing(char nonTerminal, const unordered_map<char, vector<string>> &productions, unordered_map<char, unordered_set<char>> &trailingSets)
{
    if (trailingSets.find(nonTerminal) != trailingSets.end())
    { // If already calculated, return the existing set
        return trailingSets[nonTerminal];
    }
    unordered_set<char> trailingSet;
    for (const auto &production : productions.at(nonTerminal))
    {
        size_t i = production.size() - 1;
        while (i != string::npos)
        {
            if (isalpha(production[i]) && islower(production[i]))
            {
                trailingSet.insert(production[i]);
                break;
            }
            else if (isupper(production[i]))
            {
                unordered_set<char> nextTrailingSet = calculateTrailing(production[i],
                                                                        productions, trailingSets);
                trailingSet.insert(nextTrailingSet.begin(), nextTrailingSet.end());
                if (nextTrailingSet.count('e') == 0)
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
            --i;
        }
    }
    trailingSets[nonTerminal] = trailingSet;
    return trailingSet;
}
int main()
{
    unordered_map<char, vector<string>> productions = {
        {'S', {"aA", "BbC", "d"}},
        {'A', {"B", "c"}},
        {'B', {"e"}},
        {'C', {"f"}},
    };
    // Map to store leading sets for non-terminals
    unordered_map<char, unordered_set<char>> leadingSets;
    // Map to store trailing sets for non-terminals
    unordered_map<char, unordered_set<char>> trailingSets;
    for (const auto &production : productions)
    {
        char nonTerminal = production.first;
        calculateLeading(nonTerminal, productions, leadingSets);
    }
    for (const auto &production : productions)
    {
        char nonTerminal = production.first;
        calculateTrailing(nonTerminal, productions, trailingSets);
    }
    cout << "Leading sets:" << endl;
    for (const auto &leadingSet : leadingSets)
    {
        cout << leadingSet.first << ": ";
        for (char terminal : leadingSet.second)
        {
            cout << terminal << " ";
        }
        cout << endl;
    }
    cout << "\nTrailing sets:" << endl;
    for (const auto &trailingSet : trailingSets)
    {
        cout << trailingSet.first << ": ";
        for (char terminal : trailingSet.second)
        {
            cout << terminal << " ";
        }
        cout << endl;
    }
    return 0;
}
