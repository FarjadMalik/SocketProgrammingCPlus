#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

int main (int argc, char* argv[])
{
    int listenFd, portNo;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server;
    
    if(argc < 3)
    {
        cerr<<"Syntax : ./client <host name> <port>"<<endl;
        return 0;
    }
    
    portNo = atoi(argv[2]);
    if((portNo > 55556) || (portNo < 55555))
    {
        cerr<<"Please enter port number either 55556 for c++ or 55555 for java."<<endl;
        return 0;
    }       
    
    //create client skt
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }
    
    server = gethostbyname(argv[1]);
    
    if(server == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }
    
    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;
    
    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);
    
    svrAdd.sin_port = htons(portNo);
    
    int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
    
    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        return 0;
    }
    // open a file in read mode.
    streampos size;
    char * memblock=new char [1024];

  	ifstream file ("Hello.txt");
  	if (file.is_open())
  	{
		cout << "File opened. Reading and sending.."<< endl;
    		while(!file.eof()){
    			
    			file.read (memblock, 1024);
    			

			write(listenFd, memblock, strlen(memblock));
		}
		cout << "File sent."<< endl;
    		delete[] memblock;
		file.close();
  	}
  	else cout << "Unable to open file"<< endl;
    //send stuff to server
    /*for(;;)
    {
        char s[300];
        //cin.clear();
        //cin.ignore(256, '\n');
        cout << "Enter stuff: ";
        bzero(s, 301);
        cin.getline(s, 300);
        
        write(listenFd, s, strlen(s));
    }*/
}
