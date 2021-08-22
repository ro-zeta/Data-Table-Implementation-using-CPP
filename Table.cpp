//
//  table.cpp
//  CS32_Proj4
//
//  Created by rozeta on 5/31/21.
//  Copyright © 2021 rozeta. All rights reserved.
//

#include "Table.h"
#include <functional>
#include <cstdlib>

Table::Table(std::string keyColumn, const std::vector<std::string>& columns){
    m_nBuckets=1000;
    if(keyColumn==" "|| columns.empty()==true || findKey(keyColumn, columns)==false ){ //invalid table: if the keyColumn not = any of the column names.
        tableConstructed=false; //set the state of the object to be tested using the good member function.
        return;
    }
    keyName= " ";
    for (int i=0; i<columns.size(); i++){  // Construct an empty Table
        if(columns[i]==" "){ //the columns vector are empty
            tableConstructed=false;
            return;
        }
        else{
            if(keyColumn==columns[i]){
                keyName=keyColumn;
            }
            for(int j=0; j<columns.size()-1; j++){//TODO: update checking only next to each other
                if(columns[j]==columns[j+1]){ //or contain empty or duplicate strings,
                    tableConstructed=false;
                    return;
                }
            }
            if(i==columns.size()-1){
                if(keyName!=keyColumn){
                    tableConstructed=false;
                    return;
                }
            }
        }
    }
    for(int i=0; i<columns.size(); i++){
        m_col.push_back(columns[i]);
               //       m_table[i]=m_col;
        if(keyColumn==columns[i]){
                keyName=keyColumn;
                keyIndex=i;
        }
    }
    m_table.resize(m_nBuckets);
    tableConstructed=true; //if everything good, make tableConstructed true
}


bool Table::good() const{
    return  tableConstructed; //Return true if the table was successfully constructed, and false otherwise.
}

bool Table::insert(const std::string& recordString){ //Insert a record into the database.
    if(!(this-> good())){
        return false;
    }
    StringParser record(recordString);
    std::string s= "";
    std::vector<std::string> vi;
    while(record.getNextField(s)){
        vi.push_back(s);
    }
    if(vi.size()==m_col.size()){  //If the string has the correct number of fields for the table,
        unsigned int index=std::hash<std::string>()(vi[keyIndex])% 997; //TODO: may need a better hashing function?
        m_table[index].push_back(vi); // insert a record with those fields into the table
        return true; // and return true;
    }
    return false; //otherwise, leave the table unchanged and return false.
}

void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const{
    if(!(this-> good())){
           return; //TODO: check if this makes sense
       }
    unsigned int index=std::hash<std::string>()(key)% 997;
    std::list<std::vector<std::string>> bucket=m_table[index];
    for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){
        records.push_back(*itr);
        }
}

int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const{ //TODO: bonus: count how many records bad not how many queries bad!!!
    // IF THE TABLE IS MESSED UP DON'T EVEN RUN THE SELECT FUNCTION
    if(!(this-> good())){
           return -1;
       }
    //OTHERWISE USE THE PARSER TO SEPARATE WORDS FROM THE QUERY INTO DIFFERENT SLOTS OF A VECTOR
     StringParser parse(query);
     std::string s= "";
     std::vector<std::string> vi;
     while(parse.getNextField(s)){
         vi.push_back(s);
     }
    //SOME VARIABLES THAT WILL BE USEFUL IN BOOKKEEPING LATER
    std::string ColName="";
    std::string queryDouble="";
    std::string queryString="";
    std::string stringCompare="";
    std::string numCompare="";
    int totalIncorrect=0;
//LOOP THROUGH THE VECTOR THAT CONTAINS THE QUERY FIELDS AND SEPARATE WHAT NEEDS TO BE EXAMINED
    for (size_t k=0; k<vi.size(); k++){
        if(k!=0 || k!=vi.size()-1){
        if(vi[k]==">"|| vi[k]=="<" || vi[k]=="==" || vi[k]=="=" || vi[k]==">=" || vi[k]=="<=" || vi[k]=="!="){
            ColName=vi[k-1];    // IF THE COMPARISON OPERATOR IS USED AS THE NOTATION IT IS TRYING TO COMARE STRINGS, SO IM MAKING NOTE OF THAT
            queryString=vi[k+1];
            if(vi[k]==">"){
                stringCompare="GT";
                break;
            }
            else if(vi[k]=="<" ){
                stringCompare="LT";
                break;
            }
            else if(vi[k]=="==" || vi[k]=="="  ){
                stringCompare="EQ";
                break;
            }
            else if(vi[k]=="<=" ){
                stringCompare="LE";
                break;
            }
            else if(vi[k]==">=" ){
                stringCompare="GE";
                break;
            }
            else if(vi[k]=="!="){
                stringCompare="NE";
                break;
            }
        }
        else if(vi[k]=="GT"|| vi[k]=="gt"|| vi[k]=="LT" || vi[k]=="lt" || vi[k]=="EQ" || vi[k]=="eq" || vi[k]=="LE" || vi[k]=="le" || vi[k]=="GE" || vi[k]=="ge" || vi[k]=="NE" || vi[k]=="ne"){
            ColName=vi[k-1]; // IF THE COMPARISON OPERATOR USED IS LETTERS IT IS TRYING TO COMARE NUMBERS, SO IM MAKING NOTE OF THAT
            queryDouble=vi[k+1];
            if(vi[k]=="GT"|| vi[k]=="gt"){
                numCompare="GT";
                break;
            }
            else if(vi[k]=="LT" || vi[k]=="lt" ){
                numCompare="LT";
                break;
            }
            else if(vi[k]=="EQ" || vi[k]=="eq"  ){
                numCompare="EQ";
                break;
            }
            else if(vi[k]=="LE" || vi[k]=="le"  ){
                numCompare="LE";
                break;
            }
            else if(vi[k]=="GE" || vi[k]=="ge"){
                numCompare="GE";
                break;
            }
            else if(vi[k]=="NE" || vi[k]=="ne"){
                numCompare="NE";
                break;
            }
            
        }
    }
        if(k==vi.size()-1){ //if looped through and did not find any or query term is badly formed
           if((numCompare=="" && stringCompare=="") || ((numCompare!="NE"&& numCompare!="GE" && numCompare!="LE" && numCompare!="LT" &&numCompare!="GT" && numCompare!="EQ") || (stringCompare!="NE"&& stringCompare!="GE" && stringCompare!="LE" && stringCompare!="LT" &&stringCompare!="GT" && stringCompare!="EQ") || findKey(ColName, m_col)==false )){
                   records.clear(); //select sets its second parameter to be an empty vector
                   totalIncorrect= -1; // and returns −1.
                   break;
            }
        }
    }
    
    int searchIndex=0;
    bool stillGood=false;
    for (size_t k=0; k<m_col.size(); k++){
        if(ColName==m_col[k]){ //is the col name provided by the user even in my table columns?
            searchIndex=k; //if it is, then save which column the user is interested in
            stillGood=true; //mark still good to go
        }
    }

    double queryItem=0.00;
    if(queryDouble!=""){ //if the user wanted to compare a numerical value, convert that to a double
        stillGood=stringToDouble(queryDouble, queryItem);
    }
    else if(queryString!=""){ //if the user wanted to compare a string value, convert that to a double
       stillGood= stringToDouble(queryString, queryItem);
    }
    else if(queryDouble=="" && queryString==""){ // if none of the user's information match the format that we want, should not make comparisons
        stillGood=false;
    }
    double recordItem=0.00; //will use this to store values from the table itself
    if(stillGood==true && (numCompare=="GT" ||stringCompare=="GT")){ //if we had a match with the format and the user is interested in > comparison
        for(std::vector<std::list<std::vector<std::string>>>::const_iterator it= m_table.begin(); it!=m_table.end(); it++){
            std::list<std::vector<std::string>> bucket=*it; // loop through the entire hash table vector & set each col that contains a list to look at
            for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){ //go through the list
                if( stringToDouble((*itr)[searchIndex], recordItem)){ //get each corresponding column in the table
                    if(recordItem>queryItem){  //if the comparison is true
                        records.push_back((*itr)); //add the matching vector to the record vector (which is vector of vectors)
                    }
                }
            }
        }
    }
    else if(stillGood==true && (numCompare=="GE" ||stringCompare=="GE")){ //if we had a match with the format and the user is interested in >= comparison
        for(std::vector<std::list<std::vector<std::string>>>::const_iterator it= m_table.begin(); it!=m_table.end(); it++){
            std::list<std::vector<std::string>> bucket=*it; //TODO: does this work vs not m_table[it]????
            for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){
                if( stringToDouble((*itr)[searchIndex], recordItem)){
                    if(recordItem>queryItem){  //TODO: ASK IF OK??
                        records.push_back((*itr));
                    }
                }
            }
        }
    }
    else if(stillGood==true && (numCompare=="LT" ||stringCompare=="LT")){//if we had a match with the format and the user is interested in < comparison
        for(std::vector<std::list<std::vector<std::string>>>::const_iterator it= m_table.begin(); it!=m_table.end(); it++){
            std::list<std::vector<std::string>> bucket=*it; //TODO: does this work vs not m_table[it]????
            for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){
                if( stringToDouble((*itr)[searchIndex], recordItem)){
                    if(recordItem>queryItem){  //TODO: ASK IF OK??
                        records.push_back((*itr));
                    }
                }
            }
        }
    }
    else if(stillGood==true && (numCompare=="LE" ||stringCompare=="LE")){//if we had a match with the format and the user is interested in <= comparison
        for(std::vector<std::list<std::vector<std::string>>>::const_iterator it= m_table.begin(); it!=m_table.end(); it++){
            std::list<std::vector<std::string>> bucket=*it; //TODO: does this work vs not m_table[it]????
            for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){
                if( stringToDouble((*itr)[searchIndex], recordItem)){
                    if(recordItem>queryItem){  //TODO: ASK IF OK??
                        records.push_back((*itr));
                    }
                }
            }
        }
    }
    else if(stillGood==true && (numCompare=="EQ" ||stringCompare=="EQ")){//if we had a match with the format and the user is interested in ==
           for(std::vector<std::list<std::vector<std::string>>>::const_iterator it= m_table.begin(); it!=m_table.end(); it++){
               std::list<std::vector<std::string>> bucket=*it; //TODO: does this work vs not m_table[it]????
               for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){
                   if( stringToDouble((*itr)[searchIndex], recordItem)){
                       if(recordItem>queryItem){  //TODO: ASK IF OK??
                           records.push_back((*itr));
                       }
                   }
                }
            }
       }
    else if(stillGood==true && (numCompare=="NE" ||stringCompare=="NE")){ //if we had a match with the format and the user is interested in !=
        for(std::vector<std::list<std::vector<std::string>>>::const_iterator it= m_table.begin(); it!=m_table.end(); it++){
            std::list<std::vector<std::string>> bucket=*it; //TODO: does this work vs not m_table[it]????
            for(std::list<std::vector<std::string>>::iterator itr=bucket.begin(); itr!=bucket.end(); itr++){
                if( stringToDouble((*itr)[searchIndex], recordItem)){
                    if(recordItem>queryItem){  //TODO: ASK IF OK??
                        records.push_back((*itr));
                    }
                }
            }
        }
    }
    return totalIncorrect; //TODO: return any record whose value for that field is not in the proper form
}

unsigned int Table::m_indexValue(){
    if(!(this-> good())){
            return -1;
        }
    
    return 1;
}

bool Table::findKey(std::string key,  std::vector<std::string> cols) const{
    for (int i=0; i<cols.size(); i++){
        if(cols[i]==key){
            return true;
        }
    }
    return false;
}



// StringParser

// A StringParser object is constructed from a string.  Successive calls
// to the getNextField member function extract the next field from the
// string, returning true if it got one and false if there was no next field.
// Fields are separated by blank, tab, carriage return, or newline, and
// may be surrounded by single quotes, which are stripped off in the
// extracted field.  Two consecutive single quotes in a quoted field are
// converted to one.
//
// Here's an example of what it does:
//     StringParser parser("  abc  'def ghi'  'Don''t cry'  ''  jk ");
//     string s;
//     assert(parser.getNextField(s)  &&  s == "abc");
//     assert(parser.getNextField(s)  &&  s == "def ghi");
//     assert(parser.getNextField(s)  &&  s == "Don't cry");
//     assert(parser.getNextField(s)  &&  s == "");
//     assert(parser.getNextField(s)  &&  s == "jk");
//     assert(!parser.getNextField(s));

#include <string>

///////////////////// PROVIDED BY INSTRUCTOR ////////////// TAKES CARE OF DELIMITERS ///////////////////////////
bool StringParser::getNextField(std::string& fieldText) { //divide string into tokens based on the given delimiters
    m_start = m_text.find_first_not_of(" \t\r\n", m_start); //Search string for 1st char not \t\r\n & get its position
    if (m_start == std::string::npos) { //means end here? => if start is the end aka empty
        m_start = m_text.size(); //assign the size of the text to m_start
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'') {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1); // where is the 1st char of the string that's not " \t\r\n"
        fieldText = m_text.substr(m_start, end-m_start); //make fieldText=substring from m_start till end-1?
        m_start = end; //make m_start the next value in " \t\r\n"
        return true;
    }
    fieldText = "";
    for (;;){ 
        m_start++; //
        size_t end = m_text.find('\'', m_start); //look for '\' after current m_start, the entire sequence must match
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());//If expres'n 1 is true, then expres'n 2 is evaluated.
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}


