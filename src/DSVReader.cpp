#include "DSVReader.h"
#include "DSVWriter.h"
#include <memory>
#include <string>
#include "StringDataSource.h"
#include "DataSource.h"
#include "StringUtils.h"
#include <iostream>

struct CDSVReader::SImplementation
{
    std::shared_ptr< CDataSource > source;
    char delim;

};

CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter)  //Constructor for DSV reader, src specifies the data source and delimiter specifies the delimiting character
{
    DImplementation = std::make_unique<SImplementation>();
    DImplementation->source = src;
    DImplementation->delim = delimiter;
}

CDSVReader::~CDSVReader()   // Destructor for DSV reader
{

}

bool CDSVReader::End() const  //Returns true if all rows have been read from the DSV
{
    return CDSVReader::DImplementation->source->End();

}

bool CDSVReader::ReadRow(std::vector<std::string> &row)   //Returns true if the row is successfully read, one string will be put in the row per column. 
{
    //clear whatever is in the row before you write to it.
    //read in strings from the source, separate them by delimiter, put them in the row vector. The source is a CStringDataSource while the row should be a vector of strings.

    if (row.size() != 0)
    {
        row.clear();
    }

    int flag = 0;
    std::string rowelem = "";
    while(true)                  //iterate through every character in the source string
    {
    char tmp;
    if (!CDSVReader::DImplementation->source->Get(tmp))
    return false;

    if (tmp != CDSVReader::DImplementation->delim)  //if not delimeter, add to row elem
    {
        rowelem = rowelem + tmp;

        if ( (tmp == '\"') && (!flag))   
        {
        flag = 1;
        }

        else if ( (tmp == '\"') && (flag))
        {
        flag = 0;
        }

    }

    else if ((tmp == CDSVReader::DImplementation->delim) && flag) //if delim is part of string
    {
        rowelem = rowelem + tmp;

    }

    else if ((tmp == CDSVReader::DImplementation->delim) && !flag)  //if delim is not part of string
    {
        //if char is the delimeter and its not part of the string, don't push, end the vector element (cell). make a new string
        row.push_back(rowelem);
        rowelem = "";
    }

    if (CDSVReader::DImplementation->source->End())
    {
        row.push_back(rowelem);
        break;
    }

    }
    return true;

}
