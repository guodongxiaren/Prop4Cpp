#include <iostream>
#include <properties.hpp>
using namespace std;

int main()
{
    Properties prop;
    ifstream in("demo.properties");
    prop.load(in);
    /*
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
    cout<<endl;
    set<string> ss= prop.stringPropertyNames();
    for (auto s:ss)
    {
        cout<<s<<endl;
    }
    */
    cout<<trim("  123  ")<<endl;
    cout<<trim("").empty()<<endl;
    prop.list(cout);
}

