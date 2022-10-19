#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

TEST(XMLReader, CharacterDataTest) {
	CStringDataSource Source1("<test>This is a test!</test>");
	std::shared_ptr<CStringDataSource> PSource1 = std::make_shared<CStringDataSource>(Source1);
	CXMLReader Reader1(PSource1);
	
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

TEST(XMLWriter, WriteEntityTest) {
	CStringDataSink Sink1;
	std::shared_ptr<CStringDataSink> PSink1 = std::make_shared<CStringDataSink>(Sink1);
	CXMLWriter Writer1(PSink1);

	SXMLEntity Entity1 = {.DType = SXMLEntity::EType::StartElement, .DNameData = "test"};
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1.String(), "<test>");
}
