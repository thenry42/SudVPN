#include "NordVPN.hpp"

NordVPN::NordVPN()
{
    _isLogged = false;
    _isConnected = false;
    _version = "0.0.1";
    _firewall = false;
    _routing = false;
    _analytics = false;
    _killSwitch = false;
    _ThreatProtectionLite = false;
    _autoConnect = false;
    _IPv6 = false;
    _meshnet = false;
    _dns = false;
    _lanDiscovery = false;
}

NordVPN::~NordVPN() {}

void NordVPN::login()
{
    if (_isLogged)
        return ;
 
    string cmd = runCommand("nordvpn login | awk '{print $5}'");
    if (cmd.find("You are already logged in.") != string::npos)
    {
        cout << "You are already logged in." << endl;
        _isLogged = true;
        return ;
    }  
    cmd.erase(cmd.end() - 1);
    cout << cmd << endl; 
    cmd = runCommand("xdg-open " + cmd);
    cout << cmd << endl;
    string link;
    cout << "You are expected to give a link to login to your NordVPN account" << endl;

    //cin >> link; // WILL USE A TEXT INPUT WITH HINT FROM IMGUI

    cmd = runCommand("nordvpn login --callback \"" + link + "\"");

    if (cmd.find("Welcome to NordVPN!") != string::npos)
    {
        cout << "You are logged in now." << endl;
        _isLogged = true;
    }
    else
        cout << "You are not logged in." << endl;
}

void NordVPN::logout()
{
    _isLogged = false;
}

void NordVPN::connect()
{
    /*
    if (!_isLogged)
    {
        cout << "You need to login first." << endl;
        return ;
    }
    */
    string cmd = runCommand("nordvpn connect");
    if (cmd.find("You are not logged in.") != string::npos)
    {
        cout << "You are not logged in." << endl;
        _isLogged = false;
    }
    else if (cmd.find("You are connected to") != string::npos)
    {
        cout << "You are connected." << endl;
        _isConnected = true;
    }
    else
        cout << "You are not connected." << endl;
}

void NordVPN::disconnect()
{
    _isConnected = false;
}

void NordVPN::status()
{
    cout << "Logged: " << (_isLogged ? "Yes" : "No") << endl;
    cout << "Connected: " << (_isConnected ? "Yes" : "No") << endl;
}

void NordVPN::countries()
{
    cout << "### Countries Command ###" << endl;

    string countries = runCommand("nordvpn countries | sed 's/\t/ /g' | awk '{for (i=1; i<=NF; i++) printf \"%s \", $i} END {print \"\"}'");

    // Parse countries string to vector
    string country;
    for (char c : countries)
    {
        if (c == ' ')
        {
            _countries.push_back(country);
            country.clear();
        }
        else
            country += c;
    }

    /*
    // Display countries
    for (string c : _countries)
        cout << c << endl;
    */
}

void NordVPN::cities()
{
    cout << "### Cities Command ###" << endl;

    if (_countries.empty())
        countries();

    for (size_t i = 0; i < _countries.size(); i++)
    {
        string cities = runCommand("nordvpn cities \"" + _countries[i] + "\" | sed 's/\t/ /g' | awk '{for (i=1; i<=NF; i++) printf \"%s \", $i} END {print \"\"}'");

        // Parse cities string to vector
        string city;
        vector<string> tmp;
        for (char c : cities)
        {
            if (c == ' ')
            {
                tmp.push_back(city);
                city.clear();
            }
            else
                city += c;
        }
        _serverLocation[_countries[i]] = tmp;
    }

    // Display cities per country
    for (auto it = _serverLocation.begin(); it != _serverLocation.end(); it++)
    {
        cout << it->first << endl;
        for (auto itt = it->second.begin(); itt != it->second.end(); itt++)
            cout << *itt << endl;
        cout << "-----------------" << endl;
    }
}

void NordVPN::groups()
{
    cout << "### Groups Command ###" << endl;
    string groups = runCommand("nordvpn groups | sed 's/\t/ /g' | awk '{for (i=1; i<=NF; i++) printf \"%s \", $i} END {print \"\"}'");
    
    // Parse cities string to vector
    string group;
    for (char c : groups)
    {
        if (c == ' ')
        {
            _groups.push_back(group);
            group.clear();
        }
        else
            group += c;
    }

    // Display Groups
    for (string c : _groups)
        cout << c << endl;
}

void NordVPN::account()
{
    cout << "Account" << endl;
}

void NordVPN::set()
{
    cout << "Set" << endl;
}

void NordVPN::help()
{
    cout << "Help" << endl;
}

void NordVPN::version()
{
    _version = runCommand("nordvpn --version");
    cout << "Version: " << _version << endl;
}

void NordVPN::settings()
{
    cout << "Settings" << endl;
}

string NordVPN::runCommand(const string& cmd)
{
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
        return (NULL);
    char buffer[256];
    string result = "";
    while (!feof(pipe))
    {
        if (fgets(buffer, 256, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return (result);
}

bool NordVPN::isLogged() const
{
    return _isLogged;
}

bool NordVPN::isConnected() const
{
    return _isConnected;
}