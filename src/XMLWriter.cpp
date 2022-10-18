#include "XMLWriter.h"
#include <expat.h>

struct CXMLWriter::SImplementation {

};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink) {
	DImplementation = std::make_unique<SImplementation>(sink);
}

CXMLWriter::~CXMLWriter() {

}