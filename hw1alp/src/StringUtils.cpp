#include "StringUtils.h"
#include <string>
#include <cstring>
//#include "hw1header.h"
#include <iostream>
#include <cctype>
#include <vector>
#include <cmath>

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    int strend;
    if (end == 0)
    strend = str.length();  //slice until the end of the string
    else
    strend = end;    //slice until the specified bit - 1


/*     if (end != 0 && end < start)
    {
        std::cout << "start index out of bounds\n";
        return str;
    } */
    if (start < 0)
    {
        start = str.length() + start;
    }

    if (strend < 0)
    {
        strend = str.length() + strend;
    }
    //std::cout << "the length of the string is: " << strend << std::endl;


    if (start > strend)
    {
        return "";
    }

    std::string newstring = str.substr(start, strend-start);
    return newstring;
}


std::string Capitalize(const std::string &str) noexcept{

    if (str.length() == 0)
    return "";

    char first = str.at(0);
    char capt = toupper(first);
    std::string tempstr = Slice(str, 1);  //remove first letter
    std::string newstring = capt + tempstr;
    return newstring;
}

std::string Upper(const std::string &str) noexcept{
    std::string newstring = str;

    if (str.length() == 0)
    return "";

    for (int i = 0; i < str.length(); i++)
    {
        newstring[i] = toupper(str[i]);
    }

    return newstring;
}

std::string Lower(const std::string &str) noexcept{
    std::string newstring = str;

    if (str.length() == 0)
    return "";

    
    for (int i = 0; i < str.length(); i++)
    {
        newstring[i] = tolower(str[i]);
    }

    return newstring;
}

std::string LStrip(const std::string &str) noexcept{
    std::string newstring = str;
    
    int i = 0;
    int count = 0;
    while (isspace(newstring[i]))
    {
        count++;
        i = i+1;
    }

    newstring = Slice(newstring, count);
    return newstring;
}

std::string RStrip(const std::string &str) noexcept{
    std::string newstring = str;

    int index_toend = newstring.find_last_not_of(" \t\f\v\n\r");
    //std::cout<< "the last non-whitespace char is at index: " << index_toend << std::endl;

    newstring = newstring.substr(0, index_toend+1);

    return newstring;
}

std::string Strip(const std::string &str) noexcept{
    std::string newstring = str;
    std::string newstring1 = LStrip(newstring);
    std::string newstring2 = RStrip(newstring1);

    return newstring2;

}

std::string Center(const std::string &str, int width, char fill) noexcept{
    std::string newstring = str;

    if (width < 0)
    return newstring;

    if (width < (str.length()))
    return newstring;

    if (str.length() == 0)
    {
    std::string newstring(width, fill);
    return newstring;
    }

    std::string leftspaces = "";
    std::string rightspaces = "";

    int filled = width - str.length();

    if (filled % 2 == 1)   //if odd
    {
        leftspaces.append(floor(filled/2), fill);
        rightspaces.append(floor(filled/2) +1, fill);
    }

    else
    {
        leftspaces.append((filled/2), fill);
        rightspaces.append((filled/2), fill);
    }

    newstring = leftspaces + newstring + rightspaces;

    return newstring;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    std::string newstring = str;

    if (width < 0)
    return newstring;

    if (width < (str.length()))
    return newstring;

    if (str.length() == 0)
    {
    std::string newstring(width, fill);
    return newstring;
    }

    std::string spaces = "";

    spaces.append(width - str.length(), fill);
    newstring =  newstring+spaces;

    return newstring;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    std::string newstring = str;

    if (width < 0)
    return newstring;

    if (width < (str.length()))
    return newstring;

    if (str.length() == 0)
    {
    std::string newstring(width, fill);
    return newstring;
    }

    std::string spaces = "";

    spaces.append(width - str.length(), fill);    
    newstring = spaces + newstring;

    return newstring;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
     // Returns the string str with all instances of old replaced with rep
    //iterate through string to find substring, mark the index of each occurance, str.replace() at their index

    std::string newstring = str;
    std::vector< int > founds;        //https://stackoverflow.com/questions/755835/how-to-add-element-to-c-array
    int found;
    int index = str.find(old);

    while (index != std::string::npos)  //while there are matches
    { 
    //index = str.find(old);
   /*  if (std::count(founds.begin(), founds.end(), index))  //if index list already contains index
        break; */
    //std::cout << "found old string at index: " << index << std::endl;
    //if (index != std::string::npos)   //if there is a match
        founds.push_back(index);
        

   /*  if (std::count(founds.begin(), founds.end(), str.find(old, index+1)))  //if index list already contains index
        break;
    else
    { */
    index = str.find(old, index+1);   
    //std::cout << "next old string found at index: " << index << std::endl;
    //founds.push_back(index);
    //}
    
    /* if (found == std::string::npos) //if no matches 
        break;
    else
        std::cout << "next old string found at index: " << found << std::endl;
        founds.push_back(found); */
    }
    
   /*  std::cout << "the indices of substring to be replaced are: ";  
    
    for (int i = 0; i < founds.size(); i++)
    {
        std::cout << founds[i] << " ";
    }
    std::cout << std::endl;
    return str; */


    //NOW REPLACE OLD W REP AT EACH INDEX IN FOUNDS
    
    if (!founds.empty() && old.length() == rep.length())  //if there are any matches
    {
        for (int i = 0; i < founds.size(); i++)
        {
            newstring.replace(founds[i], rep.length(), rep);   //doesn't work when rep and old are not the same length. find another way. slice the string at each index, append rep, and then append the rest of the string??
        }
    }

    else if (!founds.empty() && old.length() != rep.length())
    {
        int iterno = 0;
        for (int i = 0; i < founds.size(); i++)
        {
            int index =  founds[i] + (iterno * (rep.length()) - (iterno* old.length())); //founds[i] + (rep.length() * iterno);
            std::string strfirst = newstring;
            strfirst.resize(index); // index doesn't match the next old's index after replacement
            std::string reststr = newstring.substr(index + old.length());  //from i to end
            //std::cout << "first part of the string: " << strfirst << "\n";
            //std::cout << "2nd part of the string: " << reststr << "\n";
            newstring = strfirst + rep + reststr;
            //std::cout << "new string: " << newstring << "\n";
            //index = founds[i] + rep.length();
            iterno += 1;
        }
    }

    return newstring;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector<std::string> strs;     //https://cplusplus.com/forum/general/63211/
    std::string tempstr = str;
    std::string newstring = str;
    std::vector< int > founds;    //list of split indexes    
    int index; //= str.find(splt);

    if (str.length() == 0)
    {
        std::string blank = "";
        strs.push_back(blank);
        return strs;
    }


    if (splt.empty() || splt == " ") 
    {
        while (index)
       {
            int index = newstring.find(" ");
            if (index == -1)
                break;
            //std::cout << "whitespace found at: " << index << std::endl;
            newstring = Slice(newstring, 0, index);
            //std::cout << "pushed to vector: " << newstring << std::endl;
            if (index != 0)
                strs.push_back(newstring);
            newstring = Slice(tempstr, index+1);
            //std::cout << "rest of string to work on:" << newstring << std::endl;
            tempstr = newstring;
        }

        if (!newstring.empty())
        strs.push_back(newstring);  //push the last elem

    }

    //NOW IMPLEMENT FOR SINGLE CHAR (SAME AS ABOVE) AND SUBSTRING

    if (splt.length() == 1) 
    {
        while (index)
       {
            int index = newstring.find(splt);
            if (index == -1)
                break;
            //std::cout << "whitespace found at: " << index << std::endl;
            newstring = Slice(newstring, 0, index);
            //std::cout << "pushed to vector: " << newstring << std::endl;
            if (index == 0)
            strs.push_back("");    //TEST!!!!!
            if (index != 0)
                strs.push_back(newstring);
            newstring = Slice(tempstr, index+1);
            //std::cout << "rest of string to work on:" << newstring << std::endl;
            tempstr = newstring;
        }

        //if (!newstring.empty())
        strs.push_back(newstring);  //push the last elem

    }


    if (splt.length() > 1)   //substrs
    {
        //slice the length of splt

        while (index)
       {
            int index = newstring.find(splt);
            if (index == -1)
                break;
            //std::cout << "whitespace found at: " << index << std::endl;
            newstring = Slice(newstring, 0, index);
            //std::cout << "pushed to vector: " << newstring << std::endl;
            if (index == 0)
            strs.push_back("");    //TEST!!!!!
            if (index != 0)
                strs.push_back(newstring);
            newstring = Slice(tempstr, (index+splt.length()));
            //std::cout << "rest of string to work on:" << newstring << std::endl;
            tempstr = newstring;
        }

        //if (!newstring.empty())
        strs.push_back(newstring);  //push the last elem
    }


    
/* 
    while (index != std::string::npos)  //while there are matches
    { 
   
        founds.push_back(index);
        
    index = str.find(splt, index+1);   
    }

    for (int i = 0; i < founds.size(); i++)
    {
        newstring.resize(founds[i]);
        strs.push_back(newstring);
        newstring = tempstr;
    }

    int lastelem = founds.size();
    std::cout << "index: " << lastelem << "element: " << founds[lastelem] << std::endl;
    std::cout << "sliced here: " << founds[lastelem] << std::endl;
    newstring = Slice(newstring, founds[lastelem]);   //WILL BE CHANGED???
    strs.push_back(newstring); */

    return strs;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string newstring = "";

    for (int i = 0; i < vect.size(); i++)
    {
        newstring = newstring + vect[i]+ str;
    }

    newstring = Slice(newstring, 0, newstring.length()-str.length());
    return newstring;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    //iterate char by char, find first /t, add to new string:
    //(tabsize - index of /t % tabsize) spaces
    //reset index
    //if char != tab, add it to new string, increment index by 1

    std::string newstring = "";
    int index = 0;

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == '\t')    //if char is tab
        { 
            newstring.append(tabsize - (index % tabsize), ' ');  //how many spaces to add
            index = 0;
        } 

        else    //if char is not tab
        {
            newstring = newstring + str[i];
            if (str[i] == '\n')
                index = 0;
            else 
                index += 1;
        }         
    }

    return newstring;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{   // == case sensitive 
    // Calculates the Levenshtein distance (edit distance) between the two  
    // strings. See https://en.wikipedia.org/wiki/Levenshtein_distance for  
    // more information. 

    int l = left.length();
    int r = right.length();

    //start from the last character
    //if last char is the same for both strings, skip to the char 1 before 
    //if last char is not the same, try insertion, deletion, and substition on the last char of the first string



    int results[l+1][r+1];  //make a table to push each result to

        for (int i = 0; i <= l; i++) 
    {
        for (int j = 0; j <= r; j++)
        {
            if (i == 0)   //left length = 0
            results[i][j] = j;   //if the left string is empty, only way is to insert each char of right to left

            else if (j == 0)  //right length = 0
            results[i][j] = i;  //if right string is empty, only way is to remove each char of right


            else if (ignorecase==true)               //if ignoring case, make left char and right char the same case to make == case insensitive
            {
                if (toupper(left[i-1]) == toupper(right[j-1]))
                    results[i][j] = results[i-1][j-1];      //if last char is the same for each string, move to 1 before
                else    //if last char is not the same
                {
                    int insertion = results[i][j-1];
                    int deletion = results[i-1][j]; 
                    int replace = results[i-1][j-1];

                    int op = std::min(std::min(insertion, deletion), replace);   //push the smallest operation 

                    results[i][j] = 1 + op;
                }
            }

            else if (ignorecase == false)   //if ignorecase is false, compare cases. == compares cases by default so if they're equal, move to 1 before
            {
                if (left[i-1] == right[j-1])   //if chars are same
                results[i][j] = results[i-1][j-1];
            

                else   //if last char is not the same
                {
                    if ( toupper(left[i-1]) == toupper(right[j-1]) ) //if same letter different case
                    {
                /* int insertion = results[i][j-1];
                int deletion = results[i-1][j]; */
                int replace = results[i-1][j-1];

                //int op = std::min(std::min(insertion, deletion), replace);   //push the smallest operation 

                results[i][j] = 1 + replace;
                    }

                    else     //if different letters
                    {
                int insertion = results[i][j-1];
                int deletion = results[i-1][j]; 
                int replace = results[i-1][j-1];

                int op = std::min(std::min(insertion, deletion), replace);   //push the smallest operation 

                results[i][j] = 1 + op;
                    }

                }
            }
        }
    }

    return results[l][r];

    }


};