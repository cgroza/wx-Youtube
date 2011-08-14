#include <iostream>
#include <vector>
#include <map>
#include <wx/wx.h>


#ifndef EXTRACT_H
#define EXTRACT_H

	static std::map <std::string, std::string> urls;
	static std::vector<std::string> tmp;
	static std::vector<std::string> tmp_args;
	static std::vector<std::string> stream_map;
	static std::string key;
	static std::string value;
	static std::map<std::string, std::string> params;
	static std::string tmp_url;
	static std::string format;
	static std::string real_url;
	static std::vector<std::string> itag_map;
	static std::string itag_key;
	static std::string itag_value;
	static std::string resolve_buffer;



class Extract
{
    
    public:
	std::vector<std::string> formats;
	static std::string format_url(std::string id);
	static void resolve_real_url(std::string id);
	static void gather_formats();
	static std::string return_url(std::string format);
	static std::string return_ext(std::string url);
	
	
	
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


#endif
