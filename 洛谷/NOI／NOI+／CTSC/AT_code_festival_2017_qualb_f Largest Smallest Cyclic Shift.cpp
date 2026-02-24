#include <cstdio>
#include <set>
#include <string>

int a, b, c;
std::multiset <std::string> s;

int main(void)
{
	scanf("%d %d %d", &a, &b, &c);
	
	while (a--)
	{
		s.insert("a");
	}
	
	while (b--)
	{
		s.insert("b");
	}
	
	while (c--)
	{
		s.insert("c");
	}
	
	while (s.size() > 1)
	{
		std::multiset <std::string>::iterator it1 = s.begin(), it2 = (--s.end()) ;
		s.insert((*it1) + (*it2));
		s.erase(it2) ;
		s.erase(it1) ;
	}
	
	printf("%s\n", &(*s.begin())[0]);
	return 0;
}