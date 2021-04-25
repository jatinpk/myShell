#include <bits/stdc++.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<iostream>
#include<cstdio>
#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>

//#include"checkCommand.cpp"
#include"Redirect.h"

extern int status;

using namespace std;

vector<string> parsePipe(string x)
{
	vector<string> tokens;
	stringstream s(x);

	string temp;
	int i=0;
	while(getline(s,temp,'|'))
	{
		tokens.push_back(temp);
	}

	return tokens;
}
//--------------------------------------
void evaluatePipe(string ip)
{
	vector<string> tokens = parsePipe(ip);
	int RD = 0;
	int fd[2];
	for(auto i=tokens.begin();i!=tokens.end();i++)
	{
		char **temp2 = tokenize(*i);
		temp2 = checkinMap(temp2);
		
		pipe(fd);
		int pid = fork();
				
		if(pid == 0)  //child process
		{		
			if(i == tokens.begin())
			{	
				dup2(fd[1],1);
				close(fd[0]);
				close(fd[1]); 
				execvp(temp2[0],temp2);
			}
			else if(i == tokens.end()-1)
			{
				string p = checkTypeOfCommand(*i);
				if(p == "redirect")
				{
					evaluateRedirect(*i,1,&RD,fd);
				}
				else
				{
					dup2(RD,0);
					close(fd[0]);
					close(fd[1]);
					execvp(temp2[0],temp2);
				}
			}
			else
			{
				dup2(RD,0);
				dup2(fd[1],1);
				close(fd[0]);
				close(fd[1]);
				execvp(temp2[0],temp2);	
			}
		}
		else
		{
			wait(&status);
			close(fd[1]);
			RD = fd[0];
		}
				
	}
}
