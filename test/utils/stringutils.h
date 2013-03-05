///////////////////////////////////////////////////////////////////////////
//        stringutils.h rev.1.0                                          //
//        Written to be reused                                           //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, version 3 of the Licence.               //
//                                                                       //
// Author mkhan3189                                                      //
// http://www.icplusplus.com                                             //
// https://github.com/mkhan3189/EasyLoggingPP                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////

#ifndef _EASYLOGGINGPP_TEST_STRINGUTILS_H
#define _EASYLOGGINGPP_TEST_STRINGUTILS_H

#include <string>
#include <vector>

namespace utils {

extern std::string trim(const std::string &str);

extern bool isNumber(const char* str);

extern unsigned int getLineCount(const std::string& str);

extern bool startsWith(std::string const &str, std::string const &start);

extern bool endsWith(std::string const &str, std::string const &end);

extern std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

extern std::string mergeLines(const std::string& str1, const std::string& str2, bool strict = false, const std::string& prefix =
      std::string(), const std::string& middle = std::string(), const std::string& suffix = std::string());

extern void tolower(std::string& str);

extern bool iequals(const std::string& str1, const std::string& str2);

extern bool ilike(const std::string& str, const std::string& pattern);

extern std::string prependAndAppendILikeDelimiter(const std::string& str);

extern std::string replaceAll(const std::string& str, const std::string& replaceWhat, const std::string& replaceWith);

} //namespace utils
#endif // _EASYLOGGINGPP_TEST_STRINGUTILS_H
