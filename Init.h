
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


extern string u_NAME;
extern string u_HOME;
extern string prompt;
extern string pwd;
extern string host;
void IntializeShell()
{
	uid_t uid;
	uid=getuid();
	struct passwd *p=getpwuid(uid);
	u_NAME=p->pw_name;
	u_HOME=p->pw_dir;

	//from file
	fstream mybash;
	mybash.open("/home/jatin/OS_SHELL/.mybashrc",ios::in);
	string temp;
	while(getline(mybash,temp))
	{
		//cout<<temp;
		int i=0;
		string key,value;
		while(temp[i]!='=')
		{
			key+=temp[i];
			i++;
		}i++;
		while(i<temp.length())
		{
			value+=temp[i];
			i++;
		}
	
		if(key=="PS1")
			prompt=value;
		else if(key=="HOSTNAME")
			host=value;

	}
}