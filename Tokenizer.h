
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



char* stringtocharp(string a)
{
	char *x = new char[a.length()+1];
	int i;
	for(i=0;i<a.length();i++)
	{
		x[i] = a[i];
	}x[i] = '\0';
	return x;
}


char** tokenize(string str)
{
	string word;
	char **arr = new char*[10];

		for(int i=0;i<10;i++)
			arr[i] = NULL;
		
		stringstream s(str);

		int index = 0;
		int j=0;
		
		while(s>>word)
		{
			j=0;
			char *temp = new char[word.length()+1];
			int i;
			for(i=0;i<word.length();i++,j++)
			{
				temp[i] = word[i];
			}temp[i] = '\0';

			arr[index] = temp;
			index++;
		}	
	//}
	return arr;
}