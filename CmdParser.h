#ifndef CMD_PARSER_H
#define CMD_PARSER_H
#include <iostream>
#include <string>
#include <vector>

class Property
{
public:
    Property(std::string *value);

    Property(unsigned int *value);

    Property(double *value);

    Property(float *value);

    Property(int *value);

    Property(bool *value);

    union {
        std::string *m_stringData;
        unsigned int *m_unsignedIntData;
        double *m_doubleData;
        float *m_floatData;
        bool *m_boolData;
        int *m_intData;
    };

    enum {STRING_PROP, UNSIGNED_INT_PROP, DOUBLE_PROP, FLOAT_PROP, INT_PROP, BOOL_PROP} m_dataType;
};

/**
 * @brief A simple command line parser
 *
 * Example of using the command line parser below
 *
 * @code
 * bool oHelp = false;
 * int oInteger = 1;
 *
 * CmdParser parser(argc, argv);
 * parser.addArgument({"-h", "--help"}, &oHelp, "Display help information", false);
 * parser.addArgument({"-i", "--int"}, &oInteger, "A integer value", false);
 *
 * try {
 *     parser.parse();
 * } catch (std::runtime_error const& e) {
 *     std::cout << e.what() << std::endl;
 *     return -1;
 * }
 *
 * if (oHelp) {
 *     parser.help();
 *     return 1;
 * }
 * @endcode
 */
class CmdParser
{
public:
    /**
     * @brief Handle and convert the argv
     *
     * @param argc Argument count
     * @param argv Argument vector
     */
    CmdParser(int argc, const char* argv[]);

    /**
     * @brief Add an argument to parse
     *
     * @param argFlags Flags to access the argument
     * @param property Type of value
     * @param helpText Help text for the argument
     * @param isRequired If the argument is required
     * @param typeDescription Value type description
     * @param isPositional If the argument is positional
     */
    void addArgument(const std::vector<std::string> &argFlags, Property property, const std::string &helpText,
                     bool isRequired = false, const std::string &typeDescription = "", bool isPositional = false);

    /**
     * @brief Preform the actual parsing of the command line options
     */
    void parse();

    /**
     * @brief Format and display help information
     */
    void help();

private:

    struct cmd {
        std::vector<std::string> flags; // Flags to identify the argument
        std::string description;        // Description of the argument
        std::string help;               // Help information string
        Property property;              // Property of the argument (type / data)
        bool required;                  // If the argument is required
        bool handled;                   // If the argument has been handled
        bool positional;
    };

    std::vector<std::string> m_tokens;  // Command line options split into strings
    std::string m_programName;          // Name of the program
    std::vector<cmd> m_cmds;            // Information related to each argument
};


#endif //CMD_PARSER_H
