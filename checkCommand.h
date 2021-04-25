
#include <bits/stdc++.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<iostream>
#include<cstdio>
#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>
using namespace std;
extern int pipe_count;
//--------------------------------------------------
bool checkPipe(string s)
{
	bool t=false;
	for(int i=0;i<s.length();i++)
	{
		if(s[i] == '|')
		{
			t = true;
			pipe_count++;
		}
	}
	return t;
}
//--------------------------------------------------
int checkRedirect(string s)
{
	int t=0;
	for(int i=0;i<s.length();i++)
	{
		if(s.find(">>") != string::npos)
			t = 2;
		else if(s.find(">") != string::npos)
			t=1;
		else if(s.find("<") != string::npos)
			t=3;
	}
	return t;
}
//--------------------------------------------------

bool checkAlias(string x)
{
	bool flag = false;
	if(x.find("alias") != string::npos)
		flag = true;
	return flag;
}

//--------------------------------------------------

bool checkOpen(string x)
{
	bool flag = false;
	if(x.find("open") != string::npos)
		flag = true;
	return flag;
}
//--------------------------------------------------
string checkTypeOfCommand(string str)
{
	string typeofcmd;
	bool pipe = checkPipe(str);
	int redirect = checkRedirect(str);
	bool ali = checkAlias(str);
	bool Open = checkOpen(str);

	if(pipe == 1 && redirect != 0 && ali == 0 && Open == 0)    //pipe+redirect
		typeofcmd = "piperedirect";
	else if(pipe == 1 && redirect == 0 && ali ==0 && Open == 0)  //pipe
		typeofcmd = "pipe";
	else if(pipe == 0 && redirect != 0 && ali ==0 && Open == 0) //redirect
		typeofcmd = "redirect";	
	else if(pipe == 0 && redirect == 0 && ali == 1 && Open == 0) //alias
		typeofcmd = "ali";	
	else if(pipe == 0 && redirect ==0 && ali ==0 && Open == 1)  //open
		typeofcmd = "Op";
	else if(pipe == 0 && redirect ==0 && ali ==0 && Open == 0)  //normal
		typeofcmd = "normal";

	return typeofcmd;
}