#include "DSVReader.h"
#include "DSVWriter.h"
#include <memory>
#include <string>
#include "StringDataSource.h"
#include "DataSource.h"
#include "StringUtils.h"

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

}

bool CDSVReader::ReadRow(std::vector<std::string> &row)   //Returns true if the row is successfully read, one string will be put in the row per column. 
{
    //clear whatever is in the row before you write to it.
    //read in strings from the source, separate them by delimiter, put them in the row vector. The source is a CStringDataSource while the row should be a vector of strings.

    if (row.size() != 0)
    {
        row.clear();
    }
       //source = pointer to "Hello,World!"


    //row = StringUtils::Split(DImplementation->source, DImplementation->delim);   //split the source to a vector of strings splitting on the delimeter.
    //access using methods in stringdatasource

}
