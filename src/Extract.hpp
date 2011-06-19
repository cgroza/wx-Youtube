#include <iostream>

//I have not read too much about making .hpp files, so correct this as you see fit. 

class Extract
{
    public:
	std::string resolve_real_url(std::string url);
	std::string format_url(std::string id);
	static std::string resolve_buffer;
	
    protected:
	
	static int writer(char *data, size_t size, size_t nmemb, std::string *resolve_buffer);
};
