//
//  table.hpp
//  CS32_Proj4
//
//  Created by rozeta on 5/31/21.
//  Copyright © 2021 rozeta. All rights reserved.
//

#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <string>
#include <functional>
#include <vector>
#include <list>


class Table
{
  public:
    Table(std::string keyColumn, const std::vector<std::string>& columns);
    bool good() const;
    bool insert(const std::string& recordString);
    void find(std::string key, std::vector<std::vector<std::string>>& records) const;
    int select(std::string query, std::vector<std::vector<std::string>>& records) const;

    Table(const Table&) = delete; //prevent Table object from being copied
    Table& operator=(const Table&) = delete;//prevent Table object from being assigned
  private:
    unsigned int m_index;
    bool tableConstructed;
    unsigned int m_nBuckets; //number of buckets
//    bool stringToDouble(std::string s, double& d);
    unsigned int m_indexValue();
    std::list<std::vector<std::string>>* m_Buckets;
    std::vector<std::string> m_col;
    std::vector<std::list<std::vector<std::string>>> m_table;
    int m_loadingFactor;
    int m_maxLoadingFactor;
    bool findKey(std::string key, std::vector<std::string> cols) const;
    std::string keyName;
    int keyIndex;
  //  ...
};

class StringParser
{
  public:
    StringParser(std::string text = ""){ //constructor that takes in empty string
        setString(text);  //sets the value of text to empty
    }

    void setString(std::string text) {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

  private:
    std::string m_text;
    size_t m_start;
};


inline
bool isOnlyNums(std::string toBeExamined){
    bool isNumsOnly=false;
    int numDigits=0;
    for(size_t j=0;j<toBeExamined.length(); j++){
               if(isdigit(toBeExamined[j])){ //TODO: check if this works
                   numDigits+=1;
               }
           }
    if(numDigits==toBeExamined.length()){
        isNumsOnly=true;
    }
    return isNumsOnly;
}

inline
bool onlyLettersHere(std::string examineLetters){
    bool onlyLetters=false;
    int numLetters=0;
    for(size_t j=0;j<examineLetters.length(); j++){
               if(isalpha(examineLetters[j])){ //TODO: check if this works
                   numLetters+=1;
               }
           }
    if(numLetters==examineLetters.length()){
        onlyLetters=true;
    }
    return onlyLetters;
}

inline
bool stringToDouble(std::string s, double& d){
    char* end;
    d = std::strtof(s.c_str(), &end);
    return end == s.c_str() + s.size()  &&  !s.empty();

}

#endif /* TABLE_H */
