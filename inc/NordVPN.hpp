#ifndef NORD_VPN_HPP
#define NORD_VPN_HPP

#include <map>
#include <string>
#include <vector>
#include <iostream>

#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"

#define DB_QUOTE "\""
#define CMD_OPEN_LINK "xdg-open "
#define CMD_LOGIN "nordvpn login"
#define CMD_LOGIN_LINK "nordvpn login | awk '{print $5}'"
#define CMD_LOGIN_CALLBACK "nordvpn login --callback \""
#define CMD_LOGOUT "nordvpn logout"
#define CMD_CONNECT "nordvpn connect"
#define CMD_VERSION "nordvpn --version"

#define RPL_LOGGED_IN "You are already logged in."
#define RPL_NOT_LOGGED_IN "You are not logged in."
#define RPL_WELCOME "Welcome to NordVPN!"
#define RPL_LOGGED_OUT "You are logged out."
#define RPL_CONNECTED "You are connected"

using namespace std;

class NordVPN {
    
    private:

        // Location 
        vector<string> _cities;
        vector<string> _groups;
        vector<string> _countries;
        map<string, vector<string>> _serverLocation;
        
        // Status
        bool    _isLogged;
        bool    _isConnected;
        string  _version;

        // Settings
        bool _dns;
        bool _IPv6;
        bool _meshnet;
        bool _routing;
        bool _firewall;
        bool _analytics;
        bool _killSwitch;
        bool _autoConnect;
        bool _lanDiscovery;
        bool _ThreatProtectionLite;

        // Account Information
        string _email;
        string _vpnService;
    
    public:

        NordVPN();
        ~NordVPN();
        void set();
        void help();
        void login();
        void logout();
        void status();
        void cities();
        void groups();
        void connect();
        void account();
        void version();
        void settings();
        void countries();
        void disconnect();

        bool isLogged() const;
        bool isConnected() const;

        string runCommand(const string&);

        string getEmail(void) const;
        string getVpnService(void) const;
        void getCurrentConfiguration(void);
};

#endif