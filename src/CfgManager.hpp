#ifndef CFG_MANAGER_H
#define CFG_MANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class CfgManager
{
public:

    struct CfgOption
    {
	CfgOption(std::string n, std::string v);

	std::string name;
	std::string value;
    };

    CfgManager(std::string cfg_file);
    CfgOption* GetOption(std::string name) const; // returns a CfgOption, returns 0 if not found
    void SetOption(std::string, std::string new_val); // sets the option name to new_val

private:
    std::vector<CfgOption*> * m_cfg_entries; // holds the cfg entries
    std::string m_cfg_file;	// contains the cfg file path
    bool ParseCfgFile();	        // parses the config file. If it fails, returns false
    bool WriteDefaultCfg() const;	// writes a default configuration file at m_cfg_file
    void SaveCfg() const;		// Saves the configuration to the m_cfg_file

    static std::string m_default_cfg; // stores th default config string
};

#endif     //CFG_MANAGER_H
