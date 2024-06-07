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

void NordVPN::runCommand(const string& cmd)
{
    (void)cmd;
}

void NordVPN::runCommand(const string& cmd, const string& arg1)
{
    (void)cmd, (void)arg1;
}

void NordVPN::runCommand(const string& cmd, const string& arg1, const string& arg2)
{
    (void)cmd, (void)arg1, (void)arg2;
}

void NordVPN::runCommand(const string& cmd, const string& arg1, const string& arg2, const string& arg3)
{
    (void)cmd, (void)arg1, (void)arg2, (void)arg3;
}

bool NordVPN::isLogged() const
{
    return _isLogged;
}

bool NordVPN::isConnected() const
{
    return _isConnected;
}