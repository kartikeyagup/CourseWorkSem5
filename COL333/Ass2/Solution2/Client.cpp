#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <unordered_map>
#define SAFETY_MAX_CHATTER 1000

int safety_count = 1;
int board_dimenstion;

std::unordered_map<std::string,std::string> parse_server(char* fromserver,int size_fromserver)
{
	bool keyorvalue = 0;
	std::string temp_key = "";
	std::string temp_value = "";
	// contains the message from the server after parsing
	std::unordered_map<std::string,std::string> map_server;
	std::cout<<"Size: "<<size_fromserver<<"\n";
	for(int i=0;i<size_fromserver;i++)
	{
		if(fromserver[i]=='}')
		{
			std::cout<<"Key: "<<temp_key<<"\n";
			std::cout<<"Value: "<<temp_value<<"\n";

			//  put the value in the unordered map
			// reset temp_key and temp_value to empty string

			map_server[temp_key] = temp_value;
			break;
		}
		else if(fromserver[i]=='"' || fromserver[i]==' ' || fromserver[i] == '{')
		{
			continue;
		}
		else if(fromserver[i]==':')
		{
			keyorvalue = 1;
		}
		else if(fromserver[i]==',')
		{

			std::cout<<"Key: "<<temp_key<<"\n";
			std::cout<<"Value: "<<temp_value<<"\n";

			//  put the value in the unordered map
			// reset temp_key and temp_value to empty string

			map_server[temp_key] = temp_value;

			keyorvalue = 0;
			temp_key = "";
			temp_value = "";
		}
		else
		{
			if(keyorvalue == 0)
			{
				temp_key += fromserver[i];
			}
			else
			{
				temp_value += fromserver[i];
			}
		}
	}
	return map_server;
}


void take_apt_action(std::unordered_map<std::string,std::string> map_server)
{
	std::string a = map_server["purpose"];

	// write exception if a does not exist
	if(a == "reset")
	{
		safety_count = 0;
	}
	else if(a == "kill")
	{
		safety_count = 0;
	}
	else if(a == "update")
	{
		// take move
		// send it to server

	}
	else if(a == "update_only")
	{
		std::cout<<map_server["payload"]<<"\n";
	}
}


int main(int argc, char* argv[])
{
	std::string botname = "harvey";
	int sockfd,portno,n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int length = 256;					// length of the buffer
	char buffer[length];				// buffer for reading and writing into the socket
	if(argc<3)
	{
		std::cout<<"Incorrect no. of inputs\n";
		exit(0);
	}
	portno = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);  // creating new socket using TCP denoted by SOCK_STREAM
	if(sockfd<0)
	{
		std::cout<<"Error opening the socket\n";
		exit(0);
	}
	server = gethostbyname(argv[2]);
	// printf("%s : Server",argv[2]);
	// std::cout<<"\n";
	if(server == NULL)
	{
		std::cout<<"No such host\n";
		exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]);

	memset(buffer,'-', length);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    {
    	std::cout<<"Error Connecting\n";
    }
	std::cout<<"Connected\n";
	n = write(sockfd,botname.c_str(),strlen(botname.c_str()));
	std::cout<<"Botname send\n";
    if(n<0)
    {
    	std::cout<<"Error writing to the socket\n";
    }
    std::unordered_map<std::string,std::string> map_server;
    while(true)
    {
	    safety_count += 1;
	 	if (safety_count > SAFETY_MAX_CHATTER)
	 	{
	 		std::cout<<"Too much talking\n";
			exit(0);
		}
	    n = read(sockfd,buffer,255);
	    std::cout<<"Reading from the server\n";
	    std::cout<<buffer<<"\n";
	    map_server = parse_server(buffer,strlen(buffer));
	 	std::cout<<"parsing done\n";
	 	take_apt_action(map_server);



	    // std::string buff_string;
	    // buff_string = std::string(buffer);
	    // std::cout<<buff_string<<"\n";
	    // std::cout<<buffer[0]<<"\n";
    	
    }
	std::cout<<"Testing Client\n";
	return 0;
}