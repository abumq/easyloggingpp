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

#include "stringutils.h"

#include <cstring>
#include <cctype>

#include <algorithm>
#include <sstream>
#include <fstream>


namespace utils {

std::string trim(const std::string &str) {
   size_t s = str.find_first_not_of(" \n\r\t");
   size_t e = str.find_last_not_of(" \n\r\t");
   if ((s == std::string::npos) || (e == std::string::npos))
      return "";
   else
      return str.substr(s, e - s + 1);
}

bool isNumber(const char* str) {
   for (unsigned int i = 0; i < strlen(str); ++i) {
      if (str[i] < 48 || str[i] > 57) {
         return false;
      }
   }
   return true;
}

unsigned int getLineCount(const std::string& str) {
   if (str == "")
      return 0;
   unsigned int count = std::count(str.begin(), str.end(), '\n');
   return ++count;
}

bool startsWith(const std::string& str, const std::string& start) {
   if (str.length() >= start.length()) {
      return (0 == str.compare(0, start.length(), start));
   } else {
      return false;
   }
}

bool endsWith(const std::string& str, const std::string& end) {
   if (str.length() >= end.length()) {
      return (0 == str.compare(str.length() - end.length(), end.length(), end));
   } else {
      return false;
   }
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string>& elems) {
   std::stringstream ss(s);
   std::string item;
   while (std::getline(ss, item, delim)) {
      elems.push_back(item);
   }
   return elems;
}

std::string mergeLines(const std::string& str1, const std::string& str2, bool strict, const std::string& prefix, const std::string& middle,
      const std::string& suffix) {
   if (strict && (getLineCount(str1) != getLineCount(str2))) {
      return "";
   }
   std::stringstream result;

   std::vector<std::string> vecStr1;
   split(str1, '\n', vecStr1);

   std::vector<std::string> vecStr2;
   split(str2, '\n', vecStr2);

   unsigned int smaller = std::min(vecStr1.size(), vecStr1.size());
   for (unsigned int i = 0; i < vecStr1.size(); ++i) {
      result << prefix << vecStr1.at(i) << middle << vecStr2.at(i) << suffix << "\n";
   }
   return result.str();
}

void tolower(std::string& str) {
   std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool iequals(const std::string& str1, const std::string& str2) {
   std::string lowerString(str1);
   std::string lowerString2(str2);
   tolower(lowerString);
   tolower(lowerString2);
   return lowerString == lowerString2;
}

bool ilike(const std::string& str, const std::string& pattern) {
   if (trim(str).size() == 0 && trim(str).size() == 0) return true;
   else if (trim(pattern).size() > trim(str).size()) return false;
   else if (trim(str).size() == 0 || trim(str).size() == 0) return false;
   bool ilikeSoFar = false;
   const char ilikeDelimiter = '%';
   // Create a copy on heap so that we can retain memory half way through
   std::string *patternCopy = new std::string(pattern);
   // strCopy is created so to convert the case to lower and then compare
   std::string *strCopy = new std::string(str);
   // change case to lower for both pattern and *this
   tolower(*patternCopy);
   tolower(*strCopy);
   // split pattern to container by delimiter
   std::vector<std::string> partsOfPattern;
   partsOfPattern = split(*patternCopy, ilikeDelimiter, partsOfPattern);
   // Strict determines whether pattern starts and ends with delimiter or not
   // There is no strictness if start of str is same as first pattern and end is same as last pattern
   std::string lastPattern = partsOfPattern.at(partsOfPattern.size() - 1);
   bool strict = ((*patternCopy)[0] != ilikeDelimiter) && (partsOfPattern.at(0) != str.substr(0, partsOfPattern.at(0).size()));
   strict = strict || (((*patternCopy)[patternCopy->size() - 1] != ilikeDelimiter) && (str.find(lastPattern, str.size()  - lastPattern.size()) == std::string::npos));

   // Retain memory from patternCopy
   delete patternCopy;
   patternCopy = NULL;
   // try and find each of the element of partsOfPattern in strCopy
   size_t searchIndex = 0;
   size_t lastSearchIndex = 0;
   size_t jumpSearchIndexBy = 0;
   for (size_t i = 0; i < partsOfPattern.size(); ++i) {
      lastSearchIndex = searchIndex;
      jumpSearchIndexBy = partsOfPattern.at(i).length() + sizeof(ilikeDelimiter);
      searchIndex = strCopy->find(partsOfPattern.at(i), searchIndex) + jumpSearchIndexBy;
      if ((strict && searchIndex != 1) ||
         (searchIndex <= lastSearchIndex) || (searchIndex == std::string::npos + jumpSearchIndexBy)) {
         ilikeSoFar = false;
         break;
      } else {
         ilikeSoFar = true;
      }
   }
   delete strCopy;
   strCopy = NULL;
   return ilikeSoFar;
}
std::string prependAndAppendILikeDelimiter(const std::string& str) {
   std::string c(std::string("%"));
   c.append(str);
   c.append(std::string("%"));
   return c;
}

std::string replaceAll(const std::string& str, const std::string& replaceWhat, const std::string& replaceWith) {
   if (replaceWhat == replaceWith)
      return str;
   std::string result = str;
   size_t foundAt = -1;
   while ((foundAt = result.find(replaceWhat)) != std::string::npos) {
      result.replace(foundAt, replaceWhat.length(), replaceWith);
   }
   return result;
}

} //namespace utils
