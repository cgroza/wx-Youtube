#include "CfgManager.hpp"

CfgManager::CfgManager(std::string& cfg_file) : m_cfg_file(cfg_file), m_cfg_entries(0)
{
    m_cfg_entries = new std::vector<CfgOption*> ();
    if ( ParseCfgFile()){}		// we should ad some error handling here, in case config parsing fails
}

bool CfgManager::ParseCfgFile()
{

}

CfgManager::CfgOption::CfgOption(std::string& n, std::string& v) : name(n), value(v)
{

}
