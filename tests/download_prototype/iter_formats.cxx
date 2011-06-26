#include <iostream>
#include <string>
#include "urilite.h"
#include <cstring>
#include <boost/algorithm/string/split.hpp>
#include <vector>




std::vector<std::string> gather_formats(std::string format_map)
{
    using namespace boost;
    std::string format;
    
    std::string mp4_url;
    std::string flv_url;
    std::string three_gp_url;
    
    std::vector<std::string> formats;
    std::vector<std::string> tmp;
    split(tmp, format_map, is_any_of(","));
    
    
    
    for (int num = 0; num < tmp.size(); num++)
	{
	    
	    
	    
	    std::string tmp_str = tmp[num].substr(0,3);
	    
	    if (tmp_str.find("|") == std::string::npos)
	    {
		//std::cout << "Not valid" << std::endl;
		continue;
	    }
	    
	    else
	    {
		std::string real_url = tmp[num].substr(tmp[num].find("http:"), tmp[num].length());
	    
		if (tmp[num].find("http:") != std::string::npos)
		{
		
	
		    switch (atoi(tmp_str.c_str()))
		    {
			case 5 :  
			case 34: 
			case 35: 
			formats.push_back("flv");
			flv_url = real_url;
			break;
	
			case 18:
			case 22:
			case 37:
			case 38:
			formats.push_back("mp4");
			mp4_url = real_url;
			break;
	
			case 17:
			formats.push_back("3gp");
			three_gp_url = real_url;
			break;
	
			default: 
			std::cout << "No format found" << std::endl;
			break;
		
		}	
	    }
	}
    }
    return formats;

}

int main()
{
    
    
    
    std::string fmt_map = "fmt_url_map=34%7Chttp%3A%2F%2Fv8.lscache2.c.youtube.com%2Fvideoplayback%3Fsparams%3Did%252Cexpire%252Cip%252Cipbits%252Citag%252Calgorithm%252Cburst%252Cfactor%252Coc%253AU0hPTlBOV19FSkNOOV9ISEFD%26fexp%3D903929%252C907605%252C907321%26algorithm%3Dthrottle-factor%26itag%3D34%26ip%3D0.0.0.0%26burst%3D40%26sver%3D3%26signature%3DAA5A697A787F3D3C657C502552DD2C4418F30A54.5082EB2362FCEE56EE0CE27AFE7CF769493A92AC%26expire%3D1309039200%26key%3Dyt1%26ipbits%3D0%26factor%3D1.25%26id%3D38db2ffda2b671f4%2C18%7Chttp%3A%2F%2Fv18.lscache3.c.youtube.com%2Fvideoplayback%3Fsparams%3Did%252Cexpire%252Cip%252Cipbits%252Citag%252Calgorithm%252Cburst%252Cfactor%252Coc%253AU0hPTlBOV19FSkNOOV9ISEFD%26fexp%3D903929%252C907605%252C907321%26algorithm%3Dthrottle-factor%26itag%3D18%26ip%3D0.0.0.0%26burst%3D40%26sver%3D3%26signature%3D0FC5F2BD058888EE54670E65FD00C954DC56467F.39CF7A23F5352F5FDD83F4453DC8A9AD486C139A%26expire%3D1309039200%26key%3Dyt1%26ipbits%3D0%26factor%3D1.25%26id%3D38db2ffda2b671f4%2C5%7Chttp%3A%2F%2Fv7.lscache2.c.youtube.com%2Fvideoplayback%3Fsparams%3Did%252Cexpire%252Cip%252Cipbits%252Citag%252Calgorithm%252Cburst%252Cfactor%252Coc%253AU0hPTlBOV19FSkNOOV9ISEFD%26fexp%3D903929%252C907605%252C907321%26algorithm%3Dthrottle-factor%26itag%3D5%26ip%3D0.0.0.0%26burst%3D40%26sver%3D3%26signature%3D99B6284F841ABA5CB15B234516CC836B51FF8B60.A376C1727ED61B38E6EDBD45E4578ECB071E249A%26expire%3D1309039200%26key%3Dyt1%26ipbits%3D0%26factor%3D1.25%26id%3D38db2ffda2b671f4&allow_ratings=1&keywords=WaT%2CEiji%2CWentz%2CTeppei%2CKoike%2C5%E3%82%BB%E3%83%B3%E3%83%81%2CGo%2CSenchi%2C5cm%2CMV%2CJ-pop%2CJ-Rock&track_embed=0&view_count=98617&fmt_list=34%2F320x240%2F9%2F0%2F115%2C18%2F320x240%2F9%2F0%2F115%2C5%2F320x240%2F7%2F0%2F0&author=CaroYuuki&muted=0&length_seconds=321&user_age=30&plid=AASmiya2oal4_cmk&ftoken=DCvtsH2pCH51yKPbdzjJ7VDfevd8MTMwOTEwMjg4N0AxMzA5MDE2NDg3&status=ok&watermark=http%3A%2F%2Fs.ytimg.com%2Fyt%2Fswf%2Flogo-vfl_bP6ud.swf%2Chttp%3A%2F%2Fs.ytimg.com%2Fyt%2Fswf%2Fhdlogo-vfloR6wva.swf&timestamp=1309016487&has_cc=False&watch_ajax_token=k_Frd8rvbGHrSCmod3IVHEVR0YR8MTMwOTEwMjg4N0AxMzA5MDE2NDg3&fmt_map=34%2F320x240%2F9%2F0%2F115%2C18%2F320x240%2F9%2F0%2F115%2C5%2F320x240%2F7%2F0%2F0&leanback_module=http%3A%2F%2Fs.ytimg.com%2Fyt%2Fswfbin%2Fleanback_module-vflNXuMTT.swf&hl=en_US&endscreen_module=http%3A%2F%2Fs.ytimg.com%2Fyt%2Fswfbin%2Fendscreen-vfls7ND3M.swf&fmt_stream_map=34%7Chttp%3A%2F%2Fv8.lscache2.c.youtube.com%2Fvideoplayback%3Fsparams%3Did%252Cexpire%252Cip%252Cipbits%252Citag%252Calgorithm%252Cburst%252Cfactor%252Coc%253AU0hPTlBOV19FSkNOOV9ISEFD%26fexp%3D903929%252C907605%252C907321%26algorithm%3Dthrottle-factor%26itag%3D34%26ip%3D0.0.0.0%26burst%3D40%26sver%3D3%26signature%3DAA5A697A787F3D3C657C502552DD2C4418F30A54.5082EB2362FCEE56EE0CE27AFE7CF769493A92AC%26expire%3D1309039200%26key%3Dyt1%26ipbits%3D0%26factor%3D1.25%26id%3D38db2ffda2b671f4%7C%7Ctc.v8.cache2.c.youtube.com%2C18%7Chttp%3A%2F%2Fv18.lscache3.c.youtube.com%2Fvideoplayback%3Fsparams%3Did%252Cexpire%252Cip%252Cipbits%252Citag%252Calgorithm%252Cburst%252Cfactor%252Coc%253AU0hPTlBOV19FSkNOOV9ISEFD%26fexp%3D903929%252C907605%252C907321%26algorithm%3Dthrottle-factor%26itag%3D18%26ip%3D0.0.0.0%26burst%3D40%26sver%3D3%26signature%3D0FC5F2BD058888EE54670E65FD00C954DC56467F.39CF7A23F5352F5FDD83F4453DC8A9AD486C139A%26expire%3D1309039200%26key%3Dyt1%26ipbits%3D0%26factor%3D1.25%26id%3D38db2ffda2b671f4%7C%7Ctc.v18.cache3.c.youtube.com%2C5%7Chttp%3A%2F%2Fv7.lscache2.c.youtube.com%2Fvideoplayback%3Fsparams%3Did%252Cexpire%252Cip%252Cipbits%252Citag%252Calgorithm%252Cburst%252Cfactor%252Coc%253AU0hPTlBOV19FSkNOOV9ISEFD%26fexp%3D903929%252C907605%252C907321%26algorithm%3Dthrottle-factor%26itag%3D5%26ip%3D0.0.0.0%26burst%3D40%26sver%3D3%26signature%3D99B6284F841ABA5CB15B234516CC836B51FF8B60.A376C1727ED61B38E6EDBD45E4578ECB071E249A%26expire%3D1309039200%26key%3Dyt1%26ipbits%3D0%26factor%3D1.25%26id%3D38db2ffda2b671f4%7C%7Ctc.v7.cache2.c.youtube.com&avg_rating=5.0&logwatch=1&vq=auto&token=vjVQa1PpcFM0SfYbF6BS7TC1LF385XZZKyGWlcwNcQ0%3D&thumbnail_url=http%3A%2F%2Fi4.ytimg.com%2Fvi%2FONsv_aK2cfQ%2Fdefault.jpg&video_id=ONsv_aK2cfQ&title=WaT+-+5%E3%82%BB%E3%83%B3%E3%83%81+%28Go+Senchi+%2F+5+cm%29+MV";
    
    std::vector<std::string> fmts = gather_formats(urilite::uri::decode2(fmt_map));
    //for (int v = 0; v != fmts.size(); v++) { std::cout << fmts[v] << std::endl; }
    
    
    return 0;

}


