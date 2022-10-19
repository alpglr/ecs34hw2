#include "XMLWriter.h"
#include <stack>
#include <iostream>

struct CXMLWriter::SImplementation {
	std::shared_ptr<CDataSink> DSink;
	std::stack<SXMLEntity> DEntities;

	SImplementation(std::shared_ptr < CDataSink > sink) {
		DSink = sink;
	}

	~SImplementation() {

	}

	bool Flush() {
		while (!DEntities.empty()) {
			WriteEntity(DEntities.top());
			DEntities.pop();
		}

		return true;
	}

	bool WriteEntity(const SXMLEntity& entity) {
		switch (entity.DType) {
		case (SXMLEntity::EType::StartElement): {
			std::cout << "Hello";
			DSink->Put('<');
			DSink->Write(std::vector<char>(entity.DNameData.begin(), entity.DNameData.end()));
			for (auto& Attribute : entity.DAttributes) {
				DSink->Put(' ');
				DSink->Write(std::vector<char>(std::get<0>(Attribute).begin(), std::get<0>(Attribute).end()));
				DSink->Put('=');
				DSink->Put('\"');
				DSink->Write(std::vector<char>(std::get<1>(Attribute).begin(), std::get<1>(Attribute).end()));
				DSink->Put('\"');
			}
			DSink->Put('>');

			SXMLEntity entity_copy = { .DType = SXMLEntity::EType::EndElement, .DNameData = entity.DNameData,
										.DAttributes = entity.DAttributes };
			DEntities.push(entity_copy);
			break;
		}
		case (SXMLEntity::EType::EndElement):
			if (DEntities.top().DNameData == entity.DNameData) {
				DSink->Put('<');
				DSink->Put('\\');
				DSink->Write(std::vector<char>(entity.DNameData.begin(), entity.DNameData.end()));
				DSink->Put('>');
				DEntities.pop();
				break;
			}
			else {
				return false;
			}
		case (SXMLEntity::EType::CharData):
			DSink->Write(std::vector<char>(entity.DNameData.begin(), entity.DNameData.end()));
			break;
		case (SXMLEntity::EType::CompleteElement):
			DSink->Put('<');
			DSink->Write(std::vector<char>(entity.DNameData.begin(), entity.DNameData.end()));
			for (auto& Attribute : entity.DAttributes) {
				DSink->Put(' ');
				DSink->Write(std::vector<char>(std::get<0>(Attribute).begin(), std::get<0>(Attribute).end()));
				DSink->Put('=');
				DSink->Put('\"');
				DSink->Write(std::vector<char>(std::get<1>(Attribute).begin(), std::get<1>(Attribute).end()));
				DSink->Put('\"');
			}
			DSink->Put('\\');
			DSink->Put('>');
			break;
		}

		return true;
	}
};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink) {
	DImplementation = std::make_unique<SImplementation>(sink);
}

CXMLWriter::~CXMLWriter() {

}

bool CXMLWriter::Flush() {
	return DImplementation->Flush();
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
	return DImplementation->WriteEntity(entity);
}