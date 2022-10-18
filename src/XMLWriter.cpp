#include "XMLWriter.h"
#include <deque>

struct CXMLWriter::SImplementation {
	std::shared_ptr<CDataSink> DSink;
	std::deque<SXMLEntity> DEntities;

	SImplementation(std::shared_ptr < CDataSink > sink) {
		DSink = sink;
	}

	~SImplementation() {

	}

	bool Flush() {

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