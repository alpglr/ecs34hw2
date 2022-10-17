#include "DSVReader.h"
#include "DSVWriter.h"
#include <memory>
#include <string>
#include "DataSource.h"


struct CDSVReader::SImplementation
{

};

CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter)  //Constructor for DSV reader, src specifies the data source and delimiter specifies the delimiting character
{

}

CDSVReader::~CDSVReader()   // Destructor for DSV reader
{

}

bool CDSVReader::End() const  //Returns true if all rows have been read from the DSV
{

}

bool CDSVReader::ReadRow(std::vector<std::string> &row)   //Returns true if the row is successfully read, one string will be put in the row per column
{

}


'''''
Values that have either the delimiter, double quote character, or newline must be quoted 
with double quotes.  
Double quote character in the cell must be replace with two double quotes. 
An empty line is a valid row where there are not values 
'''''