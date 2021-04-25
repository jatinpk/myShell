
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
extern map<string,string> m;

vector<string> parseAlias(string x)
{
	vector<string> tokens;
	
	string lhs,rhs;

	int i=6;
	for(;x[i]!='=';i++)
	{
		lhs+=x[i];
	}i++;

	for(;i<x.length();i++)
	{
		rhs+=x[i];
	}

	tokens.push_back(lhs);
	tokens.push_back(rhs);

	return tokens;


}
//-------------------------------------------------------
void evaluateAlias(string ip)
{
	vector<string> tokens=parseAlias(ip);

	if(m.find(tokens[0]) == m.end())
	{
		auto i = m.find(tokens[1]);
		if(i== m.end())
			m.insert(make_pair(tokens[0],tokens[1]));
		else
			m.insert(make_pair(tokens[0],i->second));
	}
	else
	{	
		m[tokens[0]] = tokens[1];
	}
	for(auto i=m.begin();i!=m.end();i++)
	{
		cout<<i->first<<" "<<i->second<<endl;
	}
}
