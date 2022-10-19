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

	SXMLEntity Entity1 = { SXMLEntity::EType::StartElement, "test" };
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1->String(), "<test>");
	SXMLEntity Text1 = { SXMLEntity::EType::CharData, "test string" };
	Writer1.WriteEntity(Text1);
	EXPECT_EQ(Sink1->String(), "<test>"
		"test string");
	SXMLEntity Complete1 = { SXMLEntity::EType::CompleteElement, "complete" };
	Complete1.SetAttribute("warriors", "good");
	Complete1.SetAttribute("lakers", "bad");
	Writer1.WriteEntity(Complete1);
	EXPECT_EQ(Sink1->String(), "<test>"
		"test string"
		"<complete warriors=\"good\" lakers=\"bad\"/>");
	Entity1.DType = SXMLEntity::EType::EndElement;
	Writer1.WriteEntity(Entity1);
	EXPECT_EQ(Sink1->String(), "<test>"
		"test string"
		"<complete warriors=\"good\" lakers=\"bad\"/>"
		"</test>");
}

TEST(XMLWriter, FlushTest) {
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

TEST(XMLWriter, ReadAndWriteTest) {
	std::shared_ptr<CStringDataSink> Sink = std::make_shared<CStringDataSink>();
	CXMLWriter Writer(Sink);

	SXMLEntity ArtistStart = { SXMLEntity::EType::StartElement, "artist" };
	SXMLEntity ArtistName = { SXMLEntity::EType::CharData, "Bladee" };
	SXMLEntity AlbumStart = { SXMLEntity::EType::StartElement, "album" };
	SXMLEntity AlbumEnd = { SXMLEntity::EType::EndElement, "album" };
	SXMLEntity ReleaseDate = { SXMLEntity::EType::CompleteElement, "release-date" };

	Writer.WriteEntity(ArtistStart);
	Writer.WriteEntity(ArtistName);
	AlbumStart.SetAttribute("name", "Eversince");
	ReleaseDate.SetAttribute("date", "05/25/2016");
	Writer.WriteEntity(AlbumStart);
	Writer.WriteEntity(ReleaseDate);
	Writer.WriteEntity(AlbumEnd);
	AlbumStart.SetAttribute("name", "Icedancer");
	ReleaseDate.SetAttribute("date", "12/29/2018");
	Writer.WriteEntity(AlbumStart);
	Writer.WriteEntity(ReleaseDate);
	Writer.WriteEntity(AlbumEnd);
	AlbumStart.SetAttribute("name", "The Fool");
	ReleaseDate.SetAttribute("date", "05/28/2021");
	Writer.WriteEntity(AlbumStart);
	Writer.WriteEntity(ReleaseDate);
	Writer.Flush();

	EXPECT_EQ(Sink->String(),	"<artist>Bladee"
									"<album name=\"Eversince\">"
										"<release-date date=\"05/25/2016\"/>"
									"</album>"
									"<album name=\"Icedancer\">"
										"<release-date date=\"12/29/2018\"/>"
									"</album>"
									"<album name=\"The Fool\">"
										"<release-date date=\"05/28/2021\"/>"
									"</album>"
								"</artist>");

	CStringDataSource Source(Sink->String());
	std::shared_ptr<CStringDataSource> PSource = std::make_shared<CStringDataSource>(Source);
	CXMLReader Reader(PSource);

	SXMLEntity NextEntity;
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, ArtistStart.DType);
	EXPECT_EQ(NextEntity.DNameData, ArtistStart.DNameData);
	EXPECT_FALSE(NextEntity.AttributeExists("artist"));
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, ArtistName.DType);
	EXPECT_EQ(NextEntity.DNameData, ArtistName.DNameData);
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, AlbumStart.DType);
	EXPECT_EQ(NextEntity.DNameData, AlbumStart.DNameData);
	EXPECT_EQ(NextEntity.AttributeValue("name"), "Eversince");
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, ReleaseDate.DNameData);
	EXPECT_EQ(NextEntity.AttributeValue("date"), "05/25/2016");
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, ReleaseDate.DNameData);
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, AlbumEnd.DType);
	EXPECT_EQ(NextEntity.DNameData, AlbumEnd.DNameData);
	Reader.ReadEntity(NextEntity);
	Reader.ReadEntity(NextEntity);
	EXPECT_FALSE(Reader.End());
	Reader.ReadEntity(NextEntity);
	Reader.ReadEntity(NextEntity);
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, AlbumStart.DType);
	EXPECT_EQ(NextEntity.DNameData, AlbumStart.DNameData);
	EXPECT_EQ(NextEntity.AttributeValue("name"), AlbumStart.AttributeValue("name"));
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(NextEntity.DNameData, ReleaseDate.DNameData);
	EXPECT_EQ(NextEntity.AttributeValue("date"), ReleaseDate.AttributeValue("date"));
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, ReleaseDate.DNameData);
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, AlbumEnd.DType);
	EXPECT_EQ(NextEntity.DNameData, AlbumEnd.DNameData);
	Reader.ReadEntity(NextEntity);
	EXPECT_EQ(NextEntity.DType, SXMLEntity::EType::EndElement);
	EXPECT_EQ(NextEntity.DNameData, "artist");
	EXPECT_TRUE(Reader.End());
}
