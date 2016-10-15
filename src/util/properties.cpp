#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;
class Properties
{
private:
    typedef unordered_map<string, string> Dict; 
    Dict _dict;
public:
    Properties();
    Properties(Properties& defaults);

    string getProperty(string key);
    string getProperty(string key, string defaultValue);

    void load(istream& inStream);
private:
    int checkLine(string line);
};

Properties::Properties()
{
    
}

string Properties::getProperty(string key, string defaultValue)
{
    Dict::iterator it = _dict.find(key);
    return (it == _dict.end())? defaultValue : it->second;
}

void Properties::load(istream& inStream)
{
    string line;
    while (getline(inStream, line))
    {
        int pos = checkLine(line);
        if (pos == -1)
        {
            continue;
        }
        string key, value;
        key = line.substr(0, pos);
        value = line.substr(pos + 1);
        _dict[key] = value;
    }
}

/*
 * private member functions
 */

int Properties::checkLine(string line)
{
    if (line.size() == 0)
    {
        return -1;
    }

    char start = line[0];
    if (start == '#'|| start == '\n' || start == '\r') 
    {
        return -1;
    }

    int pos = line.find('=');
    return (pos == string::npos)? -1 : pos;
}

int main()
{
    Properties prop;
    ifstream in("demo.properties");
    prop.load(in);
    cout<<prop.getProperty("merchantID", "000");
    cout<<NULL<<endl;
    cout<<endl;

}

