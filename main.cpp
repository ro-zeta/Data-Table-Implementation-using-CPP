//
//  main.cpp
//  CS32_Proj4
//
//  Created by rozeta on 5/31/21.
//  Copyright © 2021 rozeta. All rights reserved.
//

#include "Table.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
 //   ////////// ASSERTS for INSERT ////////////
//     Since C++11, vectors can be constructed from initializer lists
       vector<string> cols = {
           "customer", "product", "price", "location"
       };
       Table t("customer", cols);
       assert(t.good());
       assert(t.insert("Patel 12345 42.54 Westwood"));
       assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
       assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
       assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
       assert( ! t.insert("Figueroa 54321 59.95"));
    
//
    
    /////////////////    My own asserts /////////////////
//       Table t("pros", cols);
//       assert(!t.good());
//       assert(!t.insert("Patel 12345 42.54 Westwood"));
//
    
    
 // //////////ASSERTS for FIND ///////////
    
    vector<vector<string>> v;
    t.find("Patel", v);
    assert(v.size() == 2);
    vector<vector<string>> expected = {
        { "Patel", "12345", "42.54", "Westwood" },
        { "Patel", "67890", "142.75", "Hollywood" }
    };
    assert((v[0] == expected[0]  &&  v[1] == expected[1])  ||
           (v[0] == expected[1]  &&  v[1] == expected[0]) );

    
    
//    //////////ASSERTS for SELECT //////////
//    vector<vector<string>> v;
//    assert(t.select("location < Westwood", v) == 0);
//    assert(v.size() == 2);
//    vector<vector<string>> expected = {
//        { "Hoang", "12345", "30.46", "Santa Monica" },
//        { "Patel", "67890", "142.75", "Hollywood" }
//    };
//    assert((v[0] == expected[0]  &&  v[1] == expected[1])  ||
//           (v[0] == expected[1]  &&  v[1] == expected[0]) );
//
    
//    vector<string> cols = { "item name", "price" };
//    Table t("item name", cols);
//    assert(t.good());
//    assert(t.insert("'chocolate bar' 1.69"));
//    assert(t.insert("coffee 7.99"));
//    assert(t.insert("hummus 3.49"));
//    vector<vector<string>> v;
//    assert(t.select("price LT 5", v) == 0);
//    assert(v.size() == 2);  // chocolate bar and hummus
//    assert(t.insert("pretzels 1.W9"));
//    assert(t.select("price LT H", v) == -1);
//    assert(v.size() == 0);
//    assert(t.select("price LT 5", v) == 1);  // 1 because pretzels 1.W9
//    assert(v.size() == 2);  // chocolate bar and hummus
    
    
//    vector<string> cols = { "N", "Z" };
//    Table t("Z", cols);
//    assert(t.good());
//    assert(t.insert("UCLA 90095"));
//    assert(t.insert("Caltech 91125"));
//    vector<vector<string>> v;
//    t.find("90095", v);
//    assert(v.size() == 1);
//    assert(v[0][0] == "UCLA"  &&  v[0][1] == "90095");
//    assert(t.select("Z > 90210", v) == 0);
//    assert(v.size() == 1);
//    assert(v[0][0] == "Caltech"  &&  v[0][1] == "91125");
//
//    vector<string> uclacols = { "last name", "first name", "major", "UID", "GPA" };
//    Table ucla("UID", uclacols);
//    assert(ucla.good());
//    assert(ucla.insert("Bruin Jose 'COG SCI' 304567890 3.4"));
//    assert(ucla.insert("Bruin Josephine 'COM SCI' 605432109 3.8"));
//    assert(ucla.insert("Trojan Tommy LOSING 000000000 1.7"));
//      // Troy brought a wooden horse full of Greek soldiers inside the
//      // city walls and lost the Trojan War.  How strange to look up to
//      // gullible losers as role models.
//    assert(ucla.select("GPA GE 3.2", v) == 0);
//    assert(v.size() == 2);
//    assert(v[0][0] == v[1][0]  &&  v[0][1] != v[1][1]);
    
    
//    BONUS!!!
//   // well-formed query
//    customer = Patel
//    ( customer = Patel ')'
//    ( location == Westwood | location == Hollywood ) '&' price LT 100
//    price GE 20  &  location != Westwood
// //poorly-formed query
//    (customer = Patel)    bad unless "(customer" is a column name
//    product = 12345 location != Westwood
//    location = ( Westwood | Hollywood )
//    std::string str ("look for non-alphabetic characters...");
//    StringParser s(str);
//    std:string s1;
//    cout<< s.getNextField(s1) << endl;
//    std::size_t found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");
//
//    if (found!=std::string::npos)
//    {
//      std::cout << "The first non-alphabetic character is " << str[found];
//      std::cout << " at position " << found << '\n';
//    }
    
    ///////////////////    TESTING HELPER FUNCTIONS    //////////////////
//    std::string alphaNum= "ab0123";
//    for(size_t j=0;j<alphaNum.length(); j++){
//        if(isdigit(alphaNum[j])){ //TODO: check if this works
//            std::cout<< "this is a number"<< endl;
//        }
//    }
//    for(size_t j=0;j<alphaNum.length(); j++){
//        if(isalpha(alphaNum[j])){ //TODO: check if this works
//            std::cout<< "this is a letter"<< endl;
//        }
//    }
    cout << "DONE" << endl;
}

