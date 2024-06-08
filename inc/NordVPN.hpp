#ifndef NORD_VPN_HPP
#define NORD_VPN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>

#define LOGOUT "logout"
#define CONNECT "connect"
#define DISCONNECT "disconnect"
#define STATUS "status"
#define COUNTRIES "countries"
#define CITIES "cities"
#define GROUPS "groups"
#define ACCOUNT "account"
#define SET "set"
#define HELP "help"
#define VERSION "version"
#define SETTINGS "settings"

using namespace std;

class NordVPN {
    
    private:

        // Location 
        vector<string> _countries;
        vector<string> _cities;
        vector<string> _groups;
        map<string, vector<string>> _serverLocation;
        
        // Status
        bool _isLogged;
        bool _isConnected;
        string _version;

        // Settings
        bool _firewall;
        bool _routing;
        bool _analytics;
        bool _killSwitch;
        bool _ThreatProtectionLite;
        bool _autoConnect;
        bool _IPv6;
        bool _meshnet;
        bool _dns;
        bool _lanDiscovery;
    
    public:

        NordVPN();
        ~NordVPN();
        void login();
        void logout();
        void connect();
        void disconnect();
        void status();
        void countries();
        void cities();
        void groups();
        void account();
        void set();
        void help();
        void version();
        void settings();

        bool isLogged() const;
        bool isConnected() const;

        string runCommand(const string&);
};

#endif