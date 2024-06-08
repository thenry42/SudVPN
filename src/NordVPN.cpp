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
        return;
    
    string cmd = runCommand(LOGIN);
    cmd.erase(cmd.end() - 1);
    cmd = runCommand(std::string(XDG_OPEN) + std::string(SPACE) + cmd);
    cout << cmd << endl;
    _isLogged = true;
}

void NordVPN::logout()
{
    _isLogged = false;
}

void NordVPN::connect()
{
    _isConnected = true;
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
    cout << "Countries" << endl;
}

void NordVPN::cities()
{
    cout << "Cities" << endl;
}

void NordVPN::groups()
{
    cout << "Groups" << endl;
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