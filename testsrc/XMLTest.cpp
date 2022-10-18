#include <gtest/gtest.h>
#include "XMLReader.h"
#include "StringDataSource.h"

TEST(XMLReader, CharacterDataTest) {
	CStringDataSource Source1("<test>This is a test!</test>");
	std::shared_ptr<CDataSource> PSource1 = std::make_shared<CDataSource>(Source1);
	CXMLReader Reader1(Source1);
	
	SXMLEntity NextEntity;
	Reader1.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "test");
	Reader1.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::CharData);
	EXPECT_EQ(NextEntity.DNameData, "This is a test!");
	Reader1.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "test");
}
