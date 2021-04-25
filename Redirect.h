#include <bits/stdc++.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<iostream>
#include<cstdio>
#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>


#include"Tokenizer.h"
#include"checkCommand.h"

using namespace std;

extern int status;
extern map<string,string> m;


char **checkinMap(char **args)
{

	char **ret = new char*[10];
	string w = args[0];
	auto i = m.find(w);
	if(i != m.end())
	{
		w = i->second;
		char **interm = tokenize(w);
		int j=0;
		while(interm[j]!=NULL)	j++;
		for(int i=1;args[i]!=NULL;i++,j++)
		{
			interm[j] = args[i];
		}
		ret = interm;
	}
	else
		ret = args;

	return ret;
}

vector<string> parseRedirect(string x)
{
	//ip =  ls -l|wc -x
	vector<string> tokens;
	stringstream s(x);

	string temp;
	int i=0;

	int t = checkRedirect(x);
	char ch;
	if(t == 1)	ch = '>';   //>
	else if(t == 2)			//>>
	{
		string temp1;
		string temp2;
		int i = 0;
		int index = 0;
		for(;x[i]!='>';i++)
		{	
			temp1+=x[i];
		}
		index = 0;
		for(int j=i+2;j<x.length();j++)
		{
			temp2+=x[j];
		}
		
		tokens.push_back(temp1);
		tokens.push_back(temp2);

	}	
	else if(t == 3)	ch = '<';	//<

	while(getline(s,temp,ch))
	{
		tokens.push_back(temp);
	}

	return tokens;
}
//---------------------------------------------------------
void evaluateRedirect(string ip,int flag,int* pRD,int *pfd)
{
	vector<string> tokens = parseRedirect(ip);
	
	int t = checkRedirect(ip);
	char **args1 = tokenize(tokens[0]);     //command
	char **args2 = tokenize(tokens[1]); 
			
	int i =0;
	int j=0;
	while(args1[i]!=NULL)
	{
		cout<<args1[i]<<" ";
		i++;
	}cout<<endl;
		while(args2[j]!=NULL)
	{
		cout<<args2[j]<<" ";
		j++;
	}cout<<endl;

	args1 = checkinMap(args1);

	string trunc_filename = args2[0];
			
	char path1[100]; 
	getcwd(path1,100);
	string path = path1;
			
	path = path +"/"+trunc_filename; 
			
	if(t==1 || t==2)
	{
		int d;
		if(t == 1)
			d = open(path.c_str(),O_CREAT|O_WRONLY|O_TRUNC);
		else if(t == 2)
			d = open(path.c_str(),O_WRONLY|O_APPEND);
		
		fchmod(d,S_IRWXU|S_IRWXG|S_IRWXO);

		if(d==-1)
		{
			cout<<"error in file opening\n";
			return ;
		}
		int pid = fork();

		if(pid == 0)
		{
			if(flag == 1)
			{
				dup2(*pRD,0);
				dup2(d,1);	
				close(pfd[0]);
				close(pfd[1]);
				execvp(args1[0],args1);
			} 
			else
			{
				dup2(d,1);
				execvp(args1[0],args1);
			}
		}
		else
		{
			wait(&status);
		}
	}
}


