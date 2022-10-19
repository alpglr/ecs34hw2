#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

TEST(XMLReader, ReadEntityTest) {
	CStringDataSource Source1(	"<test attr=\"Hello\">"
									"This is a test!"
									"<test2 attr=\"World!\" attr2=\"!!!\"/>"
								"</test>");
	std::shared_ptr<CStringDataSource> PSource1 = std::make_shared<CStringDataSource>(Source1);
	CXMLReader Reader1(PSource1);
	SXMLEntity NextEntity;

	// EXPECT_FALSE(Reader1.End());
	Reader1.ReadEntity(NextEntity);
	EXPECT_FALSE(Reader1.End());
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "test");
	EXPECT_TRUE(NextEntity.AttributeExists("attr"));
	EXPECT_EQ(NextEntity.AttributeValue("attr"), "Hello");
	Reader1.ReadEntity(NextEntity);
	EXPECT_FALSE(Reader1.End());
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::CharData);
	EXPECT_EQ(NextEntity.DNameData, "This is a test!");
	Reader1.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "test2");
	EXPECT_TRUE(NextEntity.AttributeExists("attr"));
	EXPECT_EQ(NextEntity.AttributeValue("attr"), "World!");
	EXPECT_TRUE(NextEntity.AttributeExists("attr2"));
	EXPECT_EQ(NextEntity.AttributeValue("attr2"), "!!!");
	Reader1.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "test2");
	Reader1.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "test");
	EXPECT_FALSE(Reader1.ReadEntity(NextEntity));
	EXPECT_TRUE(Reader1.End());



	CStringDataSource Source2(	"<begin>"
		"<aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa/>"
									"This text is ignored :("
									"<nest1>"
										"<nest2>This text is not ignored :D</nest2>"
									"</nest1>"
								"</begin>");
	std::shared_ptr<CStringDataSource> PSource2 = std::make_shared<CStringDataSource>(Source2);
	CXMLReader Reader2(PSource2);

	Reader2.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "begin");
	EXPECT_FALSE(NextEntity.AttributeExists(""));
	Reader2.ReadEntity(NextEntity, true);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	Reader2.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	Reader2.ReadEntity(NextEntity, true);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "nest1");
	Reader2.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, "nest2");
	Reader2.ReadEntity(NextEntity, false);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::CharData);
	EXPECT_EQ(NextEntity.DNameData, "This text is not ignored :D");
	Reader2.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "nest2");
	Reader2.ReadEntity(NextEntity, true);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "nest1");
	Reader2.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "begin");
	EXPECT_FALSE(NextEntity.AttributeExists(""));
	EXPECT_FALSE(Reader2.ReadEntity(NextEntity));
}

TEST(XMLWriter, WriteEntityTest) {
	std::shared_ptr<CStringDataSink> Sink1 = std::make_shared<CStringDataSink>();
	CXMLWriter Writer1(Sink1);

	SXMLEntity Entity1 = {SXMLEntity::EType::StartElement, "test"};
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1->String(), "<test>");
	SXMLEntity Text1 = { SXMLEntity::EType::CharData, "test string" };
	Writer1.WriteEntity(Text1);
	EXPECT_EQ(Sink1->String(),	"<test>"
									"test string");
	SXMLEntity Complete1 = { SXMLEntity::EType::CompleteElement, "complete" };
	Complete1.SetAttribute("warriors", "good");
	Complete1.SetAttribute("lakers", "bad");
	Writer1.WriteEntity(Complete1);
	EXPECT_EQ(Sink1->String(),	"<test>"
									"test string"
									"<complete warriors=\"good\" lakers=\"bad\"/>");
	Entity1.DType = SXMLEntity::EType::EndElement;
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1->String(),	"<test>"
									"test string"
									"<complete warriors=\"good\" lakers=\"bad\"/>"
								"</test>");
	


	std::shared_ptr<CStringDataSink> Sink2 = std::make_shared<CStringDataSink>();
	CXMLWriter Writer2(Sink2);

	SXMLEntity Entity2 = { SXMLEntity::EType::StartElement, "test2" };
	Entity2.SetAttribute("is_test", "true");
	Writer2.WriteEntity(Entity2);
	EXPECT_EQ(Sink2->String(), "<test2 is_test=\"true\">");
	SXMLEntity Entity3 = { SXMLEntity::EType::StartElement, "test3" };
	SXMLEntity Entity4 = { SXMLEntity::EType::StartElement, "test4" };
	Writer2.WriteEntity(Entity3);
	Writer2.WriteEntity(Entity4);
	EXPECT_EQ(Sink2->String(),	"<test2 is_test=\"true\">"
									"<test3>"
										"<test4>");
	Writer2.Flush();
	EXPECT_EQ(Sink2->String(), "<test2 is_test=\"true\">"
									"<test3>"
										"<test4>"
										"</test4>"
									"</test3>"
								"</test2>");
}
