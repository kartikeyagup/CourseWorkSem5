#include <iostream>
#include <queue>
#include <vector>


std::vector<std::string> join(std::string a)
{
	std::string c = a;
	std::vector<std::string> ret;

	ret.push_back(c.append("-"));
	c=a;
	for(int i=65;i<70;i++)
	{
		std::string b;
		b = (char)i;
		ret.push_back(c.append(b));
		c = a;
	}
	return ret;

}

std::vector<std::string> makeallstrings(std::queue<std::string> init)
{
	std::vector<std::string> final;
	// init.pop();
	// final.push_back(a);
	while(!init.empty())
	{
		std::string a = init.front();
		init.pop();
		std::vector<std::string> newvector;
		if(a.length()<5)
		{
			newvector = join(a);
		}
		for(int i=0;i<newvector.size();i++)
		{
			init.push(newvector[i]);
		}
		if(a.length()==5)
		{
			std::cerr<<a<<"\n";
			final.push_back(a);
		}
	}
	return final;
}
int main()
{
	std::queue<std::string> init;
	init.push("");
	std::vector<std::string> v = makeallstrings(init);
	for(std::vector<std::string>::iterator it = v.begin();it!=v.end();++it)
	{
		std::cerr<<*it<<",";
	}
	std::cerr<<"\n";
	std::cerr<<"Total Strings: "<<v.size()<<"\n";
	return 0;
}