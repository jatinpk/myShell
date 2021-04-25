
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

void writeToHistory(string ip)
{
	fstream file;
	file.open("/home/jatin/OS_SHELL/mybash_history.txt",ios::app);

	file<<endl;
	file<<ip;
	file.close();
}