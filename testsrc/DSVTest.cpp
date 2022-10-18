#include <gtest/gtest.h>
#include "StringDataSink.h"
#include "StringDataSource.h"
#include "DSVWriter.h"
//#include "DSVReader.h"

TEST(DSVWriter, WriteTest)
{
    std::shared_ptr< CStringDataSink > sink = std::make_shared<CStringDataSink>();
    const std::vector <std::string> v1 = {"this", "is", "a", "test", "vector"};
    char delim = ',';
    CDSVWriter(sink, delim);
    EXPECT_TRUE(CDSVWriter::WriteRow(&v1));
}