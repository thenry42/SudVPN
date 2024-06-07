#ifndef NORD_VPN_HPP
#define NORD_VPN_HPP

#include <iostream>
#include <string>

#define NORDVPN "nordvpn"
#define LOGIN "login"
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

        void runCommand(const string&);
        void runCommand(const string&, const string&);
        void runCommand(const string&, const string&, const string&);
        void runCommand(const string&, const string&, const string&, const string&);
};

#endif