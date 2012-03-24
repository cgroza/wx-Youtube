//Copyright (C) 2011  Groza Cristian, N3
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



#include "CfgManager.hpp"


CfgManager::CfgManager(std::string cfg_file) : m_cfg_file(cfg_file), m_cfg_entries(0)
{
    m_cfg_entries = new std::vector<CfgOption*>();
    if ( ! ParseCfgFile())	// check if config parsing was OK
    {
        if (WriteDefaultCfg())	// if not, write default config
            ParseCfgFile();     // re-parse the file if config was written successfully
        else
            std::cerr << "ERROR: Could not create default configuration file. Expect trouble." << std::endl;
    }
}

CfgManager::CfgOption* CfgManager::GetOption(std::string name) const
{
    std::vector<CfgOption*>::const_iterator it = m_cfg_entries -> begin();
    for(it; it < m_cfg_entries -> end(); ++it)
    {
        if ((*it) -> name == name) return (*it);
    }
    return 0;
}

void CfgManager::SetOption(std::string name, std::string new_val)
{
    std::vector<CfgOption*>::iterator it = m_cfg_entries -> begin();
    for(it; it < m_cfg_entries -> end(); ++it)
    {
        if ((*it) -> name == name) (*it) -> value = new_val;
    }
    SaveCfg();
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
        line.erase(line.find_last_not_of(" ") + 1); // strip trailing whitespace
        line.erase(0, line.find_first_not_of(" ")); // strip leading whitespace

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
        //std::cout << opt_name << std::endl << opt_val << std::endl;
    }
    conf_file.close();
    return true;		// return success
}

bool CfgManager::WriteDefaultCfg() const
{
    std::ofstream conf_file(m_cfg_file.c_str());
    if(conf_file.is_open())
    {
        conf_file.write(m_default_cfg.c_str(), m_default_cfg.size());
        conf_file.close();
        return true;
    }
    return false;
}

void CfgManager::SaveCfg() const
{
    std::ofstream conf_file(m_cfg_file.c_str());
    if(conf_file.is_open())
    {
        std::vector<CfgOption*>::const_iterator it = m_cfg_entries -> begin();
        std::string conf;
        for(it; it < m_cfg_entries -> end(); ++it)
        {
            conf.append((*it) -> name).append(" = ").append((*it) -> value).append("\n");
        }
        conf_file.write(conf.c_str(), conf.size());
    }
}

CfgManager::CfgOption::CfgOption(std::string n, std::string v) : name(n), value(v)
{
}

std::string CfgManager::m_default_cfg = (
        "video_save_dir = \n"
        "ask_save_path_on_download = True\n"
        "comments_board = True\n"
        "video_description = True\n"
        "\n"
                                        );
