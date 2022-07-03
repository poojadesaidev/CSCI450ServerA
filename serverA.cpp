#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

#define UDPPORT 21112
#define DOMAIN PF_INET // TODO change domain to AF_INET for Unix
#define MAXBUFLEN 4096
#define IPADDR "127.0.0.1"

int main()
{
  int dg_sock;
  // Create a DG Socket
  // Domain = AF_INET  Type = SOCK_DGRAM Protocol = 0
  // We let the transport layer decide the protocol based on 'Type'
  if ((dg_sock = socket(DOMAIN, SOCK_DGRAM, 0)) == -1)
  {
    cerr << "Datagram socket could not be created for ServerA";
    return -1;
  }

  // Bind the socket to the IP/Port
  sockaddr_in dg_hint; // address (IPV4) for welcoming socket
  dg_hint.sin_family = DOMAIN;
  dg_hint.sin_port = htons(UDPPORT); // htons to do host to network translation for port#
  //inet_pton(DOMAIN, IPADDR, &dg_hint.sin_addr); // inet_pton to convert a number in our IP to array of integers
  inet_pton(DOMAIN, IPADDR, &dg_hint.sin_addr);

  //if ((bind(stream_welcoming_sock, DOMAIN, &stream_hint, sizeof(stream_hint))) == -1)
  if ((::bind(dg_sock, (const sockaddr *)&dg_hint, sizeof(dg_hint))) == -1)
  //if ((bind(stream_welcoming_sock, (sockaddr *)&stream_hint, sizeof(stream_hint))) == -1)
  {
    cerr << "Datagram socket IP/Port binding could not be done for ServerA";
    return -2;
  }

  cout << "The main UDP server is up and running on "
       << IPADDR
       << " and port "
       << UDPPORT
       << endl;

  // Recieve message
  sockaddr_in client;
  socklen_t clientLen = sizeof(client);
  char buf[MAXBUFLEN];
  while (true)
  {
    // Clear the buffer and client
    memset(buf, 0, MAXBUFLEN);
    //memset(&client, 0, clientLen);

    // Recieve message
    int bytesRecv = recvfrom(dg_sock, buf, MAXBUFLEN - 1, 0, (sockaddr *)&client, &clientLen);
    if (bytesRecv == -1)
    {
      cerr << "Datagram socket could not recieve msg from client on ServerA" << endl;
      continue;
    }

    if (bytesRecv == 0)
    {
      cout << "The client did not send on ServerA" << endl;
      continue;
    }

    // Display message that was recieved and client info
    char clientIp[256];

    // Clear the buffer and client
    memset(clientIp, 0, 256);

    inet_ntop(DOMAIN, &client.sin_addr, clientIp, 256); // convert numeric array of the IP to pointer to string

    cout << "Received from " << string(clientIp, 0, 256)
         << " on port " << ntohs(client.sin_port)
         << " : "
         << string(buf, 0, bytesRecv) << endl;

    // // Send message
    // if (send(dg_sock, buf, bytesRecv + 1, 0) == -1)
    // {
    //   cerr << "Error sending message from ServerA to client "
    //        << string(clientIp, 0, 256)
    //        << " who was requesting for service on port "
    //        << ntohs(client.sin_port)
    //        << endl;
    //   continue;
    // }
  }
  // Close the socket
  close(dg_sock);
  return 0;
}
