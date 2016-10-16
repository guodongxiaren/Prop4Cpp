#include <iostream>
#include <fstream>
#include <string>
#include <set>
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

    const char* setProperty(string key, string value);

    const char* getProperty(string key);
    const char* getProperty(string key, const char* defaultValue);
    string getProperty(string key, string defaultValue);

    void load(istream& inStream);

    set<string> stringPropertyNames();
    void list(ostream& outStream);
private:
    int checkLine(string line);
};

Properties::Properties()
{
    
}

const char* Properties::setProperty(string key, string value)
{
    const char* preValue = getProperty(key, value.c_str());
    if (!preValue)
    {
        _dict.insert(Dict::value_type(key, value));
        return preValue;
    }
    _dict[key] = value;
    return preValue;
    
}
const char* Properties::getProperty(string key)
{
    Dict::iterator it = _dict.find(key);
    return (it == _dict.end())? nullptr : it->second.c_str();
}

const char* Properties::getProperty(string key, const char* defaultValue)
{
    Dict::iterator it = _dict.find(key);
    return (it == _dict.end())? defaultValue : it->second.c_str();
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
        //_dict[key] = value;
        _dict.insert(Dict::value_type(key, value));
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
    cout<<prop.getProperty("merchantID", "000")<<endl;

    string dv = "xxoo";
    cout<<prop.getProperty("name", dv).size()<<endl;
    
    if (prop.getProperty("name") == nullptr)
    {
        cout<<"fucker!";
    }
    cout<<endl;
    const char* p = prop.setProperty("name", "abc");
    if (!p)
    {
        cout<<p<<endl;
    }
    if (prop.getProperty("name") == nullptr)
    {
        cout<<"fucker!";
    }
    else
    {
        cout<<prop.getProperty("name");
    }
    cout<<endl;
    /*
    set<string> ss = prop.stringPropertyNames();
    for(auto key:ss)
    {
        cout<<key<<endl;
    }
    */
    prop.list(cout);
}

