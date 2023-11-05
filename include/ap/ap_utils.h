#ifndef AP_UTILS_H
#define AP_UTILS_H 

namespace ap {

	//! Non case sensitive strings comparison  
	/*!
 	 * \param a - first string to compare
 	 * \param b - second string to compare
 	 * \return Returns true on success
    */
    bool iequals(const std::string &a, const std::string &b);

    //! Splits std::string with specified delimiter  
	/*!
     * Ex. "The.string.to.split", delimiter = '.'
     *      returned_vector[0] == "The"
     *      returned_vector[1] == "string"
     *      returned_vector[2] == "to"
     *      returned_vector[3] == "split"
 	 * \param input - string to split
 	 * \param delimiter - delimiter which splits the string
 	 * \return Returns vector of splited strings
    */
    std::vector <std::string> split(std::string input, char delimiter);

} // namespace ap

#endif // AP_UTILS_H
