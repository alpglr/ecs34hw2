#ifndef DSVREADER_H
#define DSVREADER_H

#include <memory>
#include <string>
#include "DataSource.h"

class CDSVReader{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;

    public:
        CDSVReader(std::shared_ptr< CDataSource > src, char delimiter);  //Constructor for DSV reader, src specifies the data source and delimiter specifies the delimiting character
        ~CDSVReader();   // Destructor for DSV reader

        bool End() const;   //Returns true if all rows have been read from the DSV
        bool ReadRow(std::vector<std::string> &row);   //Returns true if the row is successfully read, one string will be put in the row per column
};


'''''
Values that have either the delimiter, double quote character, or newline must be quoted 
with double quotes.  
Double quote character in the cell must be replace with two double quotes. 
An empty line is a valid row where there are not values 
'''''

#endif
