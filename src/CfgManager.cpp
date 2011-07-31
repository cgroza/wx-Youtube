#include "CfgManager.hpp"

CfgManager::CfgManager(std::string& cfg_file) : m_cfg_file(cfg_file), m_cfg_entries(0)
{
    m_cfg_entries = new std::vector<CfgOption*> ();
    if ( ParseCfgFile()){}		// we should add some error handling here, in case config parsing fails
					// this error can occur because there is no config file, in this case we should
					// check for it and create a default configuration file

}

CfgManager::CfgOption* CfgManager::GetOption(std::string& name) const
{
    std::vector<CfgOption*>::const_iterator it = m_cfg_entries -> begin();
    for(it; it < m_cfg_entries -> end(); ++it)
    {
	if ((*it) -> name == name) return (*it);
    }
    return 0;
}

void CfgManager::SetOption(std::string& name, std::string& new_val)
{
    std::vector<CfgOption*>::iterator it = m_cfg_entries -> begin();
    for(it; it < m_cfg_entries -> end(); ++it)
    {
	if ((*it) -> name == name) (*it) -> value = new_val;
    }
    
}

bool CfgManager::ParseCfgFile()
{
    std::ifstream conf_file;
    conf_file.open(m_cfg_file.c_str());
    if (conf_file.fail()) return false; // opening the config file failed

    while( ! conf_file.eof() )
    {
	std::string line;
	std::getline(conf_file, line);
	line.erase( line.find_last_not_of(" ") + 1); // strip trailing whitespace
	line.erase(0 , line.find_first_not_of(" ") ); // strip leading whitespace

	if(line.empty()) continue;

	int eq_pos = line.find_first_of("=");	      // find the position of the first equal space

	if(eq_pos == std::string::npos) continue;     // check if we found an equal sign, if not, skip the line

	std::string opt_name;			      // will hold the the left value
	std::string opt_val;			      // will hold the the rigth value

	opt_name = line.substr(0, eq_pos - 1);        // get the left value
	opt_val = line.substr(eq_pos + 1, std::string::npos); // get the right value
	opt_name.erase(0 , opt_name.find_first_not_of(" ") ); // strip leading whitespace
	opt_val.erase(0 , opt_val.find_first_not_of(" ") );   // strip leading whitespace

	m_cfg_entries -> push_back(new CfgOption(opt_name, opt_val));

    }
    return true;		// return success
}

CfgManager::CfgOption::CfgOption(std::string n, std::string v) : name(n), value(v)
{
}
