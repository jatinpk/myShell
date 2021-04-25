
#include <bits/stdc++.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<iostream>
#include<cstdio>
#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>

//#include"OpenAPP.cpp"
//#include"Redirect.cpp"
//#include"checkCommand.cpp"
//#include"Tokenizer.cpp"
#include"Pipe.h"


#include"Alias.h"
#include"Init.h"
#include"History.h"



using namespace std;

int pipe_count;
map<string,string> m;
string u_NAME,u_HOME,prompt,pwd,host;
int status;


void evaluateNormal(string ip)
{
	int status;
	if(ip=="$$")
	{
		cout<<getpid()<<endl;
	}
	else if(ip=="$?")
 	{
	}
	else
	{

		char **temp = tokenize(ip);	

		temp = checkinMap(temp);

		int pid = fork();

		if(pid == 0) //child process
		{
			if(strcmp(temp[0],"cd") == 0) //for change dir
			{
				if(strcmp(temp[1],"~") == 0)
					chdir(u_HOME.c_str());	
				else
					chdir(temp[1]);	
			}
			else
			{	
				execvp(temp[0],temp);	
			}
		}
		waitpid(pid,&status,0);
		    
	}
}
//-----------------------------------------------------
void evaluateOpen(string str)
{
	//get the extension
	cout<<"m here\n";
	int i=0;
	for(;str[i]!='.';i++);
	i++;

	string extension;
	string ss,temp;
	string binPath;
	for(;i<str.length();i++)
		extension+=str[i];

	cout<<extension<<endl;

	//cout<<extension<<endl;
	//extension = .pdf
	//get value from file for .pdf

	fstream file;
	file.open("/home/jatin/OS_SHELL/.myrc",ios::in);


	while(getline(file,temp))
	{
		int j=0;
		for(;temp[j]!='=';j++);
		j--;

		ss=temp.substr(1,j);

		if(ss == extension)
		{	
			j=j+2;
			for(;j<temp.length();j++)
			{
				binPath+=temp[j];
				cout<<temp[j];
				cout<<ss<<endl;
			}	

			break;
		}
	}
	cout<<binPath<<endl;
	char **fN=tokenize(str);
	/*string trunc_filename = fN[1];
			
	char path1[100]; 
	getcwd(path1,100);
	string path = path1;
			
	path = path +"/"+trunc_filename;*/ 

	char **args=new char*[3];
	args[0]=stringtocharp(binPath);
	args[1]=fN[1];

	cout<<args[0]<<" "<<args[1]<<endl;

	int pid=fork();
	if(pid == 0)
	{
		execvp(args[0],args);
	}	
	else
		wait(&status);
}

//-------------------------------------------------------------------
int main()
{
	int pid;
	string ip;
	
	IntializeShell();

	while(1)
	{	
		char cwd[100];
		getcwd(cwd,100);
		
		string pwd = cwd;
		string disp;

		if(pwd==u_HOME)
			disp = u_NAME+"@"+host+":~"+prompt+" ";	
		else
			disp = u_NAME+"@"+host+":"+pwd+prompt+" ";

		cout<<disp;

		getline(cin,ip,'\n');

		writeToHistory(ip);

		string typeofcmd = checkTypeOfCommand(ip);

		if(typeofcmd == "normal")              		//without pipe
			evaluateNormal(ip);
		if(typeofcmd == "Op")              		//without pipe
			evaluateOpen(ip);
		else if(typeofcmd == "redirect")   		 	//reddirect operator in input
			evaluateRedirect(ip,0,NULL,NULL);
		else if(typeofcmd == "ali")  				//aliasing command
			evaluateAlias(ip);
		else if(typeofcmd == "pipe") 	          	 //pipe
			evaluatePipe(ip);
		else if(typeofcmd == "piperedirect") 	          	 //pipe+redirect
			evaluatePipe(ip);	

	}

	return 0;
}