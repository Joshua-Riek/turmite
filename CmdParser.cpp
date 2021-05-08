#include "CmdParser.h"

// Default constructor
CmdParser::CmdParser(int argc, const char **argv)
{
    std::string argvStr, tempStr;

    // Convert argv into multiple tokens
    for (int i = 1; i < argc; ++i)
    {
        tempStr.clear();
        if (std::string(argv[i]).find('='))
            for (char ch : std::string(argv[i]))
                ch == '=' ? m_tokens.push_back(tempStr), tempStr.clear() : tempStr.push_back(ch);
        else tempStr = std::string(argv[i]);
        m_tokens.push_back(tempStr);
    }

    // Now get the program name
    argvStr = argv[0];
    tempStr.clear();

    // Split argv[0] into an array, splitting values with '\\'
    for (char ch : argvStr)
        ch == '\\' ? tempStr.clear() : tempStr.push_back(ch);

    // Keep the program name for the help option
    m_programName = tempStr;
}

// Add an argument to parse
void CmdParser::addArgument(const std::vector<std::string> &argFlags, Property property, const std::string &helpText,
                            bool isRequired, const std::string &typeDescription, bool isPositional)
{
    m_cmds.emplace_back(cmd{argFlags, typeDescription, helpText, property, isRequired, false, isPositional});
}

void CmdParser::parse()
{
    for (auto iter = m_tokens.begin(); iter != m_tokens.end(); ++iter)
    {
        int found = 0;
        // Go over each argument and flag
        for (auto &argument : m_cmds)
            for (const auto &flag : argument.flags)
            {
                // Check for the flag and make sure its not the end
                if (*iter != flag || iter == m_tokens.end()) continue;

                // How many m_cmds the flag needs
                int count = argument.property.m_dataType == Property::BOOL_PROP ? 0 : 1;

                // Check to see that the next item is not the end
                if (iter + count != m_tokens.end())
                {
                    // Value has been handled
                    argument.handled = true;
                    found = 1;

                    // Check to see if the argument is one of the flags
                    for (auto &a : m_cmds)
                        for (const auto &f : a.flags)
                            if (*(iter + count) == f && count)
                                throw std::runtime_error("error: invalid value for argument '" + flag + "'");

                    // Handle different argument property types
                    try {
                        switch (argument.property.m_dataType) {
                            case Property::STRING_PROP:
                                *argument.property.m_stringData = *++iter;
                                break;
                            case Property::UNSIGNED_INT_PROP:
                                *argument.property.m_unsignedIntData = std::stoi(*++iter);
                                break;
                            case Property::DOUBLE_PROP:
                                *argument.property.m_doubleData = std::stod(*++iter);
                                break;
                            case Property::FLOAT_PROP:
                                *argument.property.m_floatData = std::stof(*++iter);
                                break;
                            case Property::INT_PROP:
                                *argument.property.m_intData = std::stoi(*++iter);
                                break;
                            case Property::BOOL_PROP:
                                *argument.property.m_boolData = true;
                                if (*iter == "-h" || *iter == "--help")
                                    return;
                                break;
                        }
                    } catch(std::exception const & e) {
                        throw std::runtime_error("error: invalid value for argument '" + flag + "'");
                    }
                } else {
                    throw std::runtime_error("error: missing value for argument '" + flag + "'");
                }
            }

        // Throw an error as an unknown command line arg has been found
        if (!found && !(*iter).empty()) {
            int found2 = 0;
            for (auto &argument : m_cmds)
            {
                if (argument.positional && !argument.handled)
                {
                    // Value has been handled
                    argument.handled = true;
                    found2 = 1;

                    // Handle different argument property types
                    try {
                        switch (argument.property.m_dataType) {
                            case Property::STRING_PROP:
                                *argument.property.m_stringData = *iter;
                                break;
                            case Property::UNSIGNED_INT_PROP:
                                *argument.property.m_unsignedIntData = std::stoi(*iter);
                                break;
                            case Property::DOUBLE_PROP:
                                *argument.property.m_doubleData = std::stod(*iter);
                                break;
                            case Property::FLOAT_PROP:
                                *argument.property.m_floatData = std::stof(*iter);
                                break;
                            case Property::INT_PROP:
                                *argument.property.m_intData = std::stoi(*iter);
                                break;
                            case Property::BOOL_PROP:
                                *argument.property.m_boolData = true;
                                break;
                        }
                    } catch(std::exception const & e) {
                        throw std::runtime_error("error: invalid value for positional argument '" + argument.flags[argument.flags.size()-1] + "'");
                    }
                    break;
                }
            }
            if (!found2) {
                throw std::runtime_error("error: unknown command line argument \"" + *iter + "\"");
            }
        }
    }
    // Go through all required m_cmds, make sure they have been found
    for (auto argument : m_cmds){
        if (!argument.handled && argument.required)
            throw std::runtime_error("error: '" + argument.flags[argument.flags.size()-1] + "' is an required argument");
    }
}

// Display help information
void CmdParser::help()
{
    std::string requiredStr, helpBody;
    int flagLength = 0;

    // First get the maximum length of all flags
    for (const auto& i : m_cmds)
    {
        // First split the flags by commas
        std::string fmt = "  ";
        for (const auto &j : i.flags)
            fmt += j + ", ";

        // Add the value description and get max length
        fmt += i.description.empty() ?  "" : "=" + i.description;
        flagLength = flagLength < fmt.length() ? fmt.length() : flagLength;
    }

    // Handle commands and descriptions
    for (const auto& i : m_cmds)
    {
        // Format the flags of the commands into a string
        std::string flagFmt = "  ";
        for (const auto &j : i.flags) flagFmt += j + ", ";
        flagFmt = flagFmt.substr(0, flagFmt.size()-2) += i.description.empty() ?  "" : "=" + i.description;
        if (flagLength > flagFmt.size())
            flagFmt.insert(flagFmt.end(), flagLength - flagFmt.size(), ' ');

        // Format the required argument info
        if (i.required)
            requiredStr += !i.description.empty() ?
                    " " + i.flags[i.flags.size()-1] + "=" + i.description : " " + i.flags[i.flags.size()-1];

        // Add the text
        flagFmt += i.help;
        helpBody += flagFmt + "\n";
    }

    // Now display the full help command info
    std::cout << "Usage: " << m_programName << "" << requiredStr << " [options] ..." << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << helpBody;
}

Property::Property(std::string *value) {
    m_stringData = value;
    m_dataType = STRING_PROP;
}

Property::Property(unsigned int *value) {
    m_unsignedIntData = value;
    m_dataType = UNSIGNED_INT_PROP;
}

Property::Property(double *value) {
    m_doubleData = value;
    m_dataType = DOUBLE_PROP;
}

Property::Property(float *value) {
    m_floatData = value;
    m_dataType = FLOAT_PROP;
}

Property::Property(int *value) {
    m_intData = value;
    m_dataType = INT_PROP;
}

Property::Property(bool *value) {
    m_boolData = value;
    m_dataType = BOOL_PROP;
}
