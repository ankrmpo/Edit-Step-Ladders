#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

bool isStep(string s1, string s2)
{
    int i;

    // ako su isti onda nije step
    if(s1 == s2)
        return false;

    // Ako imaju jednak broj rijeci, nije dodano ili oduzeto slovo
    if(s1.size() == s2.size())
    {
        // Dodi do prvog razlicitog znaka, obrisi ga i provjeri jesu li stringovi isti
        for(i = 0; i < s1.size(); ++i)
            if(s1[i] != s2[i])
                break;
            
        s1.erase(i, 1); s2.erase(i, 1);

        if(s1 == s2)
            return true;
    }
    // Ako nemaju isti broj rijeci...
    else
    {
        // jedan podstring drugoga
        if(s1.find(s2) != string::npos || s2.find(s1) != string::npos)
            return true;

        //ili na nekom drugom mjestu dodano ili uklonjeno slovo
        if(s1.size() < s2.size())
            swap(s1, s2);

        for(int k = 1; k < s1.size() - 1; ++k)
        {
            string left = s1.substr(0, s1.size() - k), right = s1.substr(s1.size() - k);
            left.erase(left.size() - 1, 1);

            if(left + right == s2)
                return true;
        }
    }

    return false;
}

void findSteps(vector<string> words, map<string, vector<string> > &steps)
{
    // za svaku rijec pronadi sljedbenike u step nizu
    for(auto it = words.begin(); it != words.end(); ++it)
    {
        auto it2 = it; ++it2;
        while(it2 != words.end())
        {
            if( isStep(*it, *it2) )
            {
                auto mapIT = steps.find(*it);
                if( mapIT == steps.end() )
                {
                    vector<string> newVector;
                    newVector.push_back(*it2);

                    steps.emplace(make_pair(*it, newVector));
                }

                else
                    mapIT->second.push_back(*it2);
            }

            ++it2;
        }
    }
}

int longestESL(string s, map<string, vector<string> > steps)
{
    int num;
    int max = 0;

    if(steps.find(s) == steps.end())
        return 1;

    for(auto IT = steps[s].begin(); IT != steps[s].end(); ++IT)
    {
        num = 1;
        num += longestESL(*IT, steps);
        if(num > max)
            max = num;
    }
    
    return max;
}

int main()
{
    string s;
    vector<string> words;
    map<string, vector<string> > steps;
    int maxStepLadder = 1;

    // Ucitavanje stringova
    cout << "Upisite stringove. Za kraj pritisnite Enter." << "\n";
    for(int i = 0; ; ++i)
    {
        cout << "String " << i + 1 << ": ";
        getline(cin, s);

        if(s.empty())
            break;

        words.push_back(s);
        if(words.size() == 25000)
            break;
    }

    // pronadi sve step prijelaze
    findSteps(words, steps);

    // Provjera sljedbenika
    // for(auto it = steps.begin(); it != steps.end(); ++it)
    // {
    //     cout << "Sljedbenici od " << it->first << ":\n";
    //     for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    //         cout << *it2 << " ";

    //     cout << endl;
    // }

    // Dovoljno provjeravati transformacije rijeci koje imaju prethodnike, sigurno imaju >= step od onih koje nemaju
    for(auto it = steps.begin(); it != steps.end(); ++it)
    {
        int numSteps = longestESL(it->first, steps);

        if(numSteps > maxStepLadder)
            maxStepLadder = numSteps;
    }
    
    cout << "Longest step ladder: " << maxStepLadder << endl;

    return 0;
}