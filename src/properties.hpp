#include <cctype>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;

static string trim(string str) 
{
    int i, j;
    for (i = 0; i < str.size(); i++)
    {
        if (!isspace(str[i]))
        {
            break;
        }
    }
    for (j = str.size() - 1; j >=0; j--)
    {
        if (!isspace(str[j]))
        {
            break;
        }
    }

    return str.substr(i, j + 1);
}
class Properties
{
private:
    typedef unordered_map<string, string> Dict; 
    Dict _dict;
public:
    Properties();
    Properties(Properties& defaults);

    string&& setProperty(string key, string value);

    string getProperty(string key);
    string getProperty(string key, const char* defaultValue);
    string getProperty(string key, string defaultValue);

    void load(istream& inStream);

    set<string> stringPropertyNames();
    void list(ostream& outStream);
private:
    bool isValidLine(string line);
    pair<int, int> checkLine(string line);
};

Properties::Properties()
{
    
}

string&& Properties::setProperty(string key, string value)
{
    string preValue = getProperty(key, value);
    if (preValue == "")
    {
        _dict.insert(Dict::value_type(key, value));
        return move(preValue);
    }
    _dict[key] = value;
    return move(preValue);
    
}
string Properties::getProperty(string key)
{
    Dict::iterator it = _dict.find(key);
    return (it == _dict.end())? "" : it->second;
}

string Properties::getProperty(string key, const char* defaultValue)
{
    Dict::iterator it = _dict.find(key);
    return (it == _dict.end())? defaultValue : move(it->second);
}

string Properties::getProperty(string key, string defaultValue)
{
    Dict::iterator it = _dict.find(key);
    return (it == _dict.end())? defaultValue : move(it->second);
}

void Properties::load(istream& inStream)
{
    string line;
    while (getline(inStream, line))
    {
        if (!isValidLine(line))
        {
            continue;
        }

        line = trim(line);
        pair<int, int> pos = checkLine(line);
        string key, value;
        key = line.substr(0, pos.first);
        if (pos.second == line.size())
        {
            value = "";
        }
        else
        {
            value = line.substr(pos.second);
        }
        //_dict[key] = value;
        _dict.insert(Dict::value_type(trim(key), trim(value)));
    }
}

set<string> Properties::stringPropertyNames()
{
    set<string>ss;
    for (auto item : _dict)
    {
        ss.insert(item.first);
    }
    return ss;
}

void Properties::list(ostream& outStream)
{
    outStream<<"-- listing properties --"<<endl;
    for (auto item : _dict)
    {
        outStream<<item.first<<"="<<item.second<<endl;
    }
}
/*
 * private member functions
 */
bool Properties::isValidLine(string line)
{
    /*
     * because of getline, line can't contain \r or \n
     */
    if (line.size() == 0)
    {
        return false;
    }

    if (line[0] == '=' || line[0] == ':')
    {
        return false;
    }

    for (char ch : line)
    {
        if (!isspace(ch) && ch != '#')
        {
            return true;
        }

    }
    return false;

}

pair<int, int> Properties::checkLine(string line)
{
    int i = line.size(), j = line.size();
    for (i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ' || line[i] == '=' || line[i] == ':' )
        {
            break;
        }
    }

    for (j = i; i < line.size(); j++)
    {
        if (line[j] != ' ' && line[j] != '=' && line[j] != ':')
        {
            break;
        }
    }

    return make_pair(i, j);
}
