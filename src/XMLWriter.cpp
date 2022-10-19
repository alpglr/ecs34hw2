#include "XMLWriter.h"
#include <stack>

struct CXMLWriter::SImplementation {
	std::shared_ptr<CDataSink> DSink;
	std::stack<SXMLEntity> DEntities;

	SImplementation(std::shared_ptr < CDataSink > sink) {
		DSink = sink;
	}

	~SImplementation() {

	}

	bool Flush() {
		while (DEntities.top()) {
			WriteEntity(DEntities.top());
			DEntities.pop();
		}

		return true;
	}

	bool WriteEntity(const SXMLEntity& entity) {
		switch (entity.DType) {
		case (SXMLEntity::EType::StartElement):
			DSink->Write("<" + entity.DNameData);
			for (auto& Attribute : entity.DAttributes) {
				DSink->Write(" " + std::get<0>(Attribute) + "=\"" + std::get<1>(Attribute) + "\"");
			}
			DSink->Put('>');

			SXMLEntity entity_copy = { .DType = SXMLEntity::EType::EndElement, .DNameData = entity.DNameData, 
										.DAttributes = entity.DAttributes};
			DEntities.push(entity_copy);
			break;
		case (SXMLEntity::EType::EndElement):
			if (DEntities.top().DNameData == entity.DNameData) {
				DSink->Write("</" + entity.DNameData + ">");
				DEntities.pop();
				break;
			}
			else {
				return false;
			}
		case (SXMLEntity::EType::CharData):
			DSink->Write(entity.DNameData);
			break;
		case (SXMLEntity::EType::CompleteElement):
			DSink->Write("<" + entity.DNameData);
			for (auto& Attribute : entity.DAttributes) {
				DSink->Write(" " + std::get<0>(Attribute) + "=\"" + std::get<1>(Attribute) + "\"");
			}
			DSink->Write("/>");
		}

		return true;
	}
};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink) {
	DImplementation = std::make_unique<SImplementation>(sink);
}

CXMLWriter::~CXMLWriter() {

}

bool Flush() {
	return DImplementation->Flush();
}

bool WriteEntity(const SXMLEntity &entity) {
	return DImplementation->WriteEntity(&entity);
}