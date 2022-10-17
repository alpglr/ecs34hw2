#ifndef DSVWRITER_H
#define DSVWRITER_H

#include <memory>
#include <string>
#include "DataSink.h"

class CDSVWriter{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;

    public:
        CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall = false);  //Constructor for DSV writer, sink specifies the data destination, delimiter specifies the delimiting character, and quoteall specifies if all values should be quoted or only those that contain the delimiter, a double quote, or a newline
        ~CDSVWriter();   //Destructor for DSV writer

        bool WriteRow(const std::vector<std::string> &row);  // Returns true if the row is successfully written, one string per column should be put in the row vector
};

/*
Values that have either the delimiter, double quote character, or newline must be quoted 
with double quotes.  
Double quote character in the cell must be replace with two double quotes. 
An empty line is a valid row where there are not values 
*/

#endif
