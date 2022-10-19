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
	std::shared_ptr<CStringDataSink> Sink1 = std::make_shared<CStringDataSink>();
	CXMLWriter Writer1(Sink1);
	SXMLEntity Entity1 = {SXMLEntity::EType::StartElement, "test"};
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1->String(), "<test>");
	Entity1.DType = SXMLEntity::EType::EndElement;
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1->String(), "<test></test>");
	
	std::shared_ptr<CStringDataSink> Sink2 = std::make_shared<CStringDataSink>();
	CXMLWriter Writer2(Sink2);
	SXMLEntity Entity2 = { SXMLEntity::EType::StartElement, "test2" };
	Entity2.SetAttribute("is_test", "true");
	Writer2.WriteEntity(Entity2);
	EXPECT_EQ(Sink2->String(), "<test2 is_test=\"true\">");
}
