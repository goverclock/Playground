#pragma once

// send to the server
struct ClientDatagram {
    enum { reg, message, operation } type;

};

// send to some client
struct ServerDatagram {
    enum { reg, message, operation } type;

};
