#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

// platform detection

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif


#if PLATFORM == PLATFORM_WINDOWS
    #include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>
    #include <errno.h>
#endif

 #if PLATFORM == PLATFORM_WINDOWS // need to be tested on windows machine
    #pragma comment( lib, "wsock32.lib" )
    #endif

#include "Module.hpp"
#include "Logger.hpp"

namespace Pringine
{

    class Address
    {
    public:

        sockaddr_in address;
        Address();
        
        Address( unsigned char a, 
                unsigned char b, 
                unsigned char c, 
                unsigned char d, 
                unsigned short port );

        // not defined yet
        unsigned int GetAddress() const;
        unsigned char GetA() const;
        unsigned char GetB() const;
        unsigned char GetC() const;
        unsigned char GetD() const;
        unsigned short GetPort() const;

    };

    class Socket
    {
        public:

            Socket();

            ~Socket();

            bool Open( unsigned short port );

            void Close();

            bool IsOpen() const;

            bool Send( const Address & destination, 
                    const void * data, 
                    int size );

            int Receive( Address & sender, 
                        void * data, 
                        int size );
            int handle;


        private:

    };



    class NetworkManager : public Module
    {
        public:
            NetworkManager(const std::string& name, int priority);
            ~NetworkManager();

            void start() override;
            void update() override;
            void end() override;

        private:
            const int port = 30000;
            Socket socket;
    };
}

    #endif