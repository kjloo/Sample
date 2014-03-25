//Kaleb Loo
//connection.h
//CPSC 351
//3/7/14
//Provides functionality to allow a client and server to create sockets and
//connections.

#include <errno.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

/*
  Creates a TCP socket.
  Returns: File descriptor of created socket.
*/
int createSocket()
{
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sock < 0) {
	cerr << "Error with socket: " << strerror(errno) << endl;
	exit(-1);
  }
  return sock;
}

/*
  Establishes a connection with a server.
  Params: address, port, sock
*/
void establishConnection(char* address, int port, int sock)
{
  unsigned long servIP;
  int status;
  struct sockaddr_in servAddr;

  //Setup parameters
  status = inet_pton(AF_INET, address, (void*) &servIP);
  if(status == 0) {
	cerr << "Error obtaining network address: Invalid Address" << endl;
	exit(-1);
  }else if(status < 0) {
	cerr << "Error obtaining network address: " << strerror(errno) << endl;
	exit(-1);
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = servIP;
  servAddr.sin_port = htons(port);

  //Request Connection to Server
  cout << "Requesting Connection to Server" << endl;
  
  status = connect(sock, (struct sockaddr*) &servAddr, sizeof(servAddr));
  if(status < 0) {
	cerr << "Error with connect: " << strerror(errno) << endl;
	exit(-1);
  }
  cout << "Connected to Server: " << address << " " << port << endl;
}

/*
  Assigns a port to a socket.
  Params: port, sock
*/
void assignPort(int port, int sock)
{
  int status;
  struct sockaddr_in servAddr;

  //Setup parameters
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(port);

  //Bind port
  status = bind(sock, (struct sockaddr*) &servAddr, sizeof(servAddr));
  if(status < 0) {
	cerr << "Error with bind: " << strerror(errno) << endl;
	exit(-1);
  }
}

/*
  Creates a listener on a socket.
  Params: sock
*/
void requestListener(int sock)
{
  const int MAXPENDING = 5;
  int status;
  status = listen(sock, MAXPENDING);
  if(status < 0) {
	cerr << "Error with listen: " << strerror(errno) << endl;
	exit(-1);
  }
}

/*
  Waits for and accepts a client connection to a socket.
  Params: sock
  Returns: File descriptor of connected client socket.
*/
int acceptConnection(int sock)
{
  char addr[INET_ADDRSTRLEN];
  int clientSock;
  struct sockaddr_in clientAddr;
  socklen_t addrLen = sizeof(clientAddr);
  cout << "Waiting for client request" << endl;
  clientSock = accept(sock, (struct sockaddr*) &clientAddr, &addrLen);
  if(clientSock < 0) {
	cerr << "Error with connect: " << strerror(errno) << endl;
	exit(-1);
  }
  inet_ntop(AF_INET, &clientAddr.sin_addr, addr, INET_ADDRSTRLEN);
  cout << "Connected with Client: " << addr
	   << " " << ntohs(clientAddr.sin_port) << endl;
  return clientSock;
}

/*
  Sends a message through the socket.
  Params: message, sock
*/
bool sendMessage(string message, int sock)
{
  int bytesSent;
  int messageSize = message.length();
  int num;

  //Convert to network order
  num = htonl(messageSize);
  //Send message size
  bytesSent = send(sock, (void*) &num, sizeof(int), 0);
  if(bytesSent == 0) {
	cerr << "Error sending data: No Data Sent" << endl;
	return false;
  }else if(bytesSent < 0) {
	cerr << "Error sending data: " << strerror(errno) << endl;
	return false;
  }else if(bytesSent != sizeof(int)) {
	cerr << "Error sending data: Incorrect Number of Bytes Sent" << endl;
	return false;
  }
  
  //Send message
  bytesSent = send(sock, (void*) message.c_str(), messageSize, 0);
  if(bytesSent == 0) {
	cerr << "Error sending data: No Data Sent" << endl;
	return false;
  }else if(bytesSent < 0) {
	cerr << "Error sending data: " << strerror(errno) << endl;
	return false;
  }else if(bytesSent != messageSize) {
	cerr << "Error sending data: Incorrect Number of Bytes Sent" << endl;
	return false;
  }
  return true;
}

/*
  Sends an int in network order through the socket.
  Params: num, sock
*/
bool sendMessage(int num, int sock)
{
  int bytesSent;
  int messageSize = sizeof(int);

  //Convert to network order
  num = htonl(num);
  //Send message
  bytesSent = send(sock, (void*) &num, messageSize, 0);
  if(bytesSent == 0) {
	cerr << "Error sending data: No Data Sent" << endl;
	return false;
  }else if(bytesSent < 0) {
	cerr << "Error sending data: " << strerror(errno) << endl;
	return false;
  }else if(bytesSent != messageSize) {
	cerr << "Error sending data: Incorrect Number of Bytes Sent" << endl;
	return false;
  }
  return true;
}

/*
  Sends a float through the socket.
  Params: num sock
*/
bool sendMessage(float num, int sock)
{
  int bytesSent;
  int messageSize = sizeof(float);

  //Send message
  bytesSent = send(sock, (void*) &num, messageSize, 0);
  if(bytesSent == 0) {
	cerr << "Error sending data: No Data Sent" << endl;
	return false;
  }else if(bytesSent < 0) {
	cerr << "Error sending data: " << strerror(errno) << endl;
	return false;
  }else if(bytesSent != messageSize) {
	cerr << "Error sending data: Incorrect Number of Bytes Sent" << endl;
	return false;
  }
  return true;
}

/*
  Receives a message through the socket.
  Params: sock
  Returns: message, success
*/
bool recvMessage(string &message, int sock)
{
  int tmp;
  int bytesLeft = sizeof(int);
  int bytesRecv;
  char* bp = (char*) &tmp;
  char* buffer;

  //Receive message size
  while(bytesLeft > 0) {
	bytesRecv = recv(sock, (void*) bp, sizeof(int), 0);
	if(bytesRecv == 0) {
	  cerr << "Error no data received" << endl;
	  return false;
	}else if(bytesRecv < 0) {
	  cerr << "Error receiving data: " << strerror(errno) << endl;
	  return false;
	}
	bytesLeft -= bytesRecv;
	bp += bytesRecv;
  }

  tmp = ntohl(tmp);
  bytesLeft = tmp;
  buffer = new char[bytesLeft];
  bp = buffer;
  
  //Receive message
  while(bytesLeft > 0) {
	bytesRecv = recv(sock, (void*) bp, bytesLeft, 0);
	if(bytesRecv == 0) {
	  cerr << "Error no data received" << endl;
	  return false;
	}else if(bytesRecv < 0) {
	  cerr << "Error receiving data: " << strerror(errno) << endl;
	  return false;
	}
	bp += bytesRecv;
	bytesLeft -= bytesRecv;
  }
  message = buffer;
  return true;
}

/*
  Receives an int in network order through the socket.
  Params: sock
  Returns: num, success
*/
bool recvMessage(int &num, int sock)
{
  int bytesRecv;
  int bytesLeft = sizeof(int);
  char* bp = (char*) &num;
  
  //Receive message
  while(bytesLeft > 0) {
	bytesRecv = recv(sock, (void*) bp, bytesLeft, 0);
	if(bytesRecv == 0) {
	  cerr << "Error no data received" << endl;
	  return false;
	}else if(bytesRecv < 0) {
	  cerr << "Error receiving data: " << strerror(errno) << endl;
	  return false;
	}
	bp += bytesRecv;
	bytesLeft -= bytesRecv;
  }
  num = ntohl(num);
  return true;
}

/*
  Receives a float through the socket.
  Params: sock
  Returns: num, success
*/
bool recvMessage(float &num, int sock)
{
  int bytesRecv;
  int bytesLeft = sizeof(float);
  char* bp = (char*) &num;

  //Receive message
  while(bytesLeft > 0) {
	bytesRecv = recv(sock, (void*) bp, bytesLeft, 0);
	if(bytesRecv == 0) {
	  cerr << "Error no data received" << endl;
	  return false;
	}else if(bytesRecv < 0) {
	  cerr << "Error receiving data: " << strerror(errno) << endl;
	  return false;
	}
	bp += bytesRecv;
	bytesLeft -= bytesRecv;
  }
  return true;
}

/*
  Closes the socket.
  Params: sock
*/
void closeSocket(int sock)
{
  int status;
  status = close(sock);
  if(status < 0)
	cerr << "Error closing socket: " << strerror(errno) << endl;
}
