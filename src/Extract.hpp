#include <iostream>
#include <vector>

//I have not read too much about making .hpp files, so correct this as you see fit. 

class Extract
{
    public:
	static std::string mp4_url;
	static std::string flv_url;
	static std::string three_gp_url;
	static std::string resolve_real_url(std::string id);
	static std::string format_url(std::string id);
	static std::string resolve_buffer;
	static std::string extension();
	static void gather_formats();
	static std::vector<std::string> formats;
	static std::string return_url();
	
	
	
	struct video_struct
	{
	    std::string actual_url;
	    std::string id;
	    std::string best_ext;
	    std::string title;
	    std::string save_dir;
	    std::string extension;
	    std::string full_save_path;
	};
	
    protected:
	
	static int writer(char *data, size_t size, size_t nmemb, std::string *resolve_buffer);
};
