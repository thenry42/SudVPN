#include "NordVPN.hpp"

NordVPN::NordVPN()
{
    // SETTINGS
    _dns = false;
    _IPv6 = false;
    _routing = false;
    _meshnet = false;
    _isLogged = false;
    _firewall = false;
    _version = "0.0.1";
    _analytics = false;
    _killSwitch = false;
    _autoConnect = false;
    _isConnected = false;
    _lanDiscovery = false;
    _ThreatProtectionLite = false;

    // ACCOUNT INFORMATION
    _email = "blob@blob.com";
    _vpnService = "NordVPN";

    // CALLBACK LINK
    _waitingCallbackLink = true;
    buffer = new char[512];
}

NordVPN::~NordVPN() {}

void NordVPN::login()
{
    if (_isLogged == true)
        return ;
 
    string cmd = runCommand(CMD_LOGIN);
    if (cmd.find(RPL_LOGGED_IN) != string::npos)
    {
        _isLogged = true;
        cout << GREEN "You are already logged in now." << endl;
        return ;
    }
    else
    {
        cmd = runCommand(CMD_LOGIN_LINK);
        cmd.erase(cmd.end() - 1); // Remove the last character that is a new line
        
        // For some reason, Firefox needs to be open before clicking on "login"
        cmd = runCommand(CMD_OPEN_LINK + cmd);
        cout << BLUE "You are expected to give a link to login to your NordVPN account" << endl;
    }
}

void NordVPN::loginCallback(void)
{
    string cmd = runCommand(CMD_LOGIN_CALLBACK + string(buffer) + DB_QUOTE);

    if (cmd.find(RPL_WELCOME) != string::npos)
    {
        cout << GREEN "You are logged in now." << endl;
        _isLogged = true;
        _waitingCallbackLink = false;
    }
}

void NordVPN::logout()
{
    string cmd = runCommand(CMD_LOGOUT);
    if (cmd.find(RPL_LOGGED_OUT) != string::npos)
    {
        cout << GREEN "You are logged out." << endl;
        _isLogged = false;
    }
    else
    {
        cout << RED "You are not logged in." << endl;
    }
}

void NordVPN::connect()
{
    string cmd = runCommand(CMD_CONNECT);
    if (cmd.find(RPL_NOT_LOGGED_IN) != string::npos || !_isLogged)
    {
        cout << RED "You need to login first." << endl;
        return ;
    }
    else
    {
        cmd = runCommand(CMD_CONNECT);
        if (cmd.find(RPL_CONNECTED) != string::npos)
        {
            cout << GREEN "You are connected." << endl;
            _isConnected = true;
        }
        else
        {
            cout << RED "You are not connected." << endl;
        }
    }
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
    _version = runCommand(CMD_VERSION);
    cout << GREEN << _version << endl;
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

string NordVPN::getEmail(void) const
{
    return _email;
}

string NordVPN::getVpnService(void) const
{
    return _vpnService;
}

void NordVPN::getCurrentConfiguration(void)
{
    
}

bool NordVPN::isWaitingCallbackLink() const
{
    return _waitingCallbackLink;
}

void NordVPN::setCallbackLink(const string& link)
{
    _callbackLink = link;
}