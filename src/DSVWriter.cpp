#include "DSVWriter.h"
#include <memory>
#include <string>
#include "StringDataSink.h"
#include "DataSink.h"
#include "StringUtils.h"
#include <iostream>

struct CDSVWriter::SImplementation
{
    std::shared_ptr< CDataSink > sink;
    char delim;
    bool flag;
};



CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall = false)  //Constructor for DSV writer, sink specifies the data destination, delimiter specifies the delimiting character, and quoteall specifies if all values should be quoted or only those that contain the delimiter, a double quote, or a newline
{
    DImplementation = std::make_unique<SImplementation>();
    DImplementation->sink= sink;
    DImplementation->delim = delimiter;
    DImplementation->flag = quoteall;


}

CDSVWriter::~CDSVWriter()   //Destructor for DSV writer
{
//leave empty?
}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row)  // Returns true if the row is successfully written, one string per column should be put in the row vector
{

//for each character in each string, put the character in the sink
std::shared_ptr< CStringDataSink > sink = std::make_shared<CStringDataSink>();


for (int i = 0; i < row.size(); i++)
{
    if (row[i].find('"') != std::string::npos)   //Double quote character in the cell must be replaced with two double quotes. 

        {
            StringUtils::Replace(row[i], "\"", "\"\"");
        }


    if ( (row[i].find(CDSVWriter::DImplementation->delim) != std::string::npos) || (row[i].find('\"') != std::string::npos) || (row[i].find('\n') != std::string::npos) )  //if delimeter, double quote, or newline is in the string, add double quotes
    sink->Put('\"');

    for (int j = 0; j < row[i].length(); j++)
    {
        sink->Put(row[i][j]);
    }

    if ( (row[i].find(CDSVWriter::DImplementation->delim) != std::string::npos) || (row[i].find('\"') != std::string::npos) || (row[i].find('\n') != std::string::npos) )  //if delimeter, double quote, or newline is in the string, add double quotes
    sink->Put('\"');

    sink->Put(DImplementation->delim);   //to separate the strings
}

//check the string. if it is successfully written, return true
//sink->String()
return true;

}

/* Values that have either the delimiter, double quote character, or newline must be quoted 
with double quotes.  
Double quote character in the cell must be replace with two double quotes. 
An empty line is a valid row where there are not values  */
