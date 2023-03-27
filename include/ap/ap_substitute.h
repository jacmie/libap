#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include <string>
#include <vector>

namespace ap {

//! Parser for substituting (inserting, or deriving) values of variables in files
/*!
 * ap::SUBSTITUTE object has to be initiated with input file, output file, and unique marks indicating variables.\n
 * Ending mark can be a whitespace, but it is advised to use explicit mark.\n Next map of variables is added and
 * finally variables are inserted to the output file, or extracted from the output file. See examples in tests.
 */
class SUBSTITUTE
{
	struct VARIABLE
	{  
    	std::string name;
    	std::string value;
	};

	struct OUT_VARIABLE
	{  
		unsigned int lineNr;
		unsigned int wordNr;
    	std::string  word;
	};

	std::string inPut;
	std::string outPut;
    char prompt, endPrompt;
    bool endFlag;
	std::vector <OUT_VARIABLE> outVar;

	unsigned int allLinesNr = 0;
    
	public:


	//! Map of varibles
	/*!
	 * Each VARIABLE has std::string name and value.
	 */
	std::vector <VARIABLE> var;

	//! Default constructor
    SUBSTITUTE() = default;

	//! Constructor with parameters
	/*!
 	 * \param inFile  - input file (template) with variables marked with marks
 	 * \param outFile - output file where variables will be substituted with variables values
 	 * \param mark    - start mark indicating beggining of a variable, default '@'
 	 * \param endMark - ending mark indicating ending of a variable, default space
	 */
    SUBSTITUTE(std::string inFile, std::string outFile, char mark = '@', char endMark = ' ');

	//! Init function
	/*!
	 * Need to use when the object was initiated with the default constructor.
 	 * \param inFile  - input file with variables marked with marks
 	 * \param outFile - output file where variables will be substituted with variables values
 	 * \param mark    - start mark indicating beggining of a variable, default '@'
 	 * \param endMark - ending mark indicating ending of a variable, default space
	 */
    void Init(std::string inFile, std::string outFile, char mark = '@', char endMark = ' ');

	//! Adds variable to the ap::SUBSTITUTE object
	/*!
 	 * \param name  - name of the added variable
 	 * \param value - value of the added variable
 	 * \return 0 on success, fails when name, or value has zero length
	 */
	int  AddVariable(std::string name, std::string value);
	
	//! Adds variable to the ap::SUBSTITUTE object
	/*!
 	 * \param name  - name of the added variable
 	 * \param value - value of the added variable
 	 * \return 0 on success, fails when name has zero length
	 */
	int  AddVariable(std::string name, double value);
	
	//! Strips string from marks
	/*!
 	 * \param toStrip - string to strip from marks
 	 * \return 0 on success, fails when marks are not recognized
	 */
	int  StripFromMarks(std::string &toStrip);

	//! Inserts variables values to the output file
	int  Insert();
	
	//! Extracts variables values from the output file
    int  Extract();
};

} // namespace ap

#endif
