#include "XMLReader.h"
#include <expat.h>
#include <deque>

struct CXMLReader::SImplementation {
    std::shared_ptr< CDataSource > DSource;
    XML_Parser DParser;
    std::deque<SXMLEntity> DEntities;

    void StartElement(const XML_Char* name, const XML_Char** atts) {
        SXMLEntity NewEntity;
        size_t Index = 0;
        NewEntity.DNameData = name;
        while (atts[Index]) {
            NewEntity.SetAttribute(atts[Index], atts[Index + 1]);
            Index += 2;
        }
        NewEntity.DType = SXMLEntity::EType::StartElement;
        DEntities.push_back(NewEntity);
    };

    void EndElement(const XML_Char* name) {
        SXMLEntity NewEntity;
        NewEntity.DNameData = name;
        NewEntity.DType = SXMLEntity::EType::EndElement;
        DEntities.push_back(NewEntity);
    };

    void CharacterData(const XML_Char* s, int len) {
        SXMLEntity NewEntity;
        for (int i = 0; i < len; ++i) {
            NewEntity.DNameData += s[i];
        }
        NewEntity.DType = SXMLEntity::EType::CharData;
        DEntities.push_back(NewEntity);
    };

    static void StartElementCallback(void* userData, const XML_Char* name, const XML_Char** atts) {
        SImplementation* ReaderImplementation = (SImplementation*)userData;
        ReaderImplementation->StartElement(name, atts);
    };

    static void EndElementCallback(void* userData, const XML_Char* name) {
        SImplementation* ReaderImplementation = (SImplementation*)userData;
        ReaderImplementation->EndElement(name);
    };

    static void CharacterDataCallback(void* userData, const XML_Char* s, int len) {
        SImplementation* ReaderImplementation = (SImplementation*)userData;
        ReaderImplementation->CharacterData(s, len);
    };

    SImplementation(std::shared_ptr< CDataSource > src) {
        DSource = src;
        DParser = XML_ParserCreate(NULL);
        XML_SetUserData(DParser, this);
        XML_SetElementHandler(DParser, StartElementCallback, EndElementCallback);
        XML_SetCharacterDataHandler(DParser, CharacterDataCallback);
    };

    ~SImplementation() {
        XML_ParserFree(DParser);
    }

    bool End() const {
        return DEntities.empty();
    };

    bool ReadEntity(SXMLEntity& entity, bool skipcdata) {
        bool Done = false;

        while (!Done) {
            std::vector<char> Buffer;
            if (DSource->Read(Buffer, 128)) {
                XML_Parse(DParser, Buffer.data(), Buffer.size(), DSource->End());
            }
            if (!DEntities.empty()) {
                if (skipcdata) {
                    if (DEntities.front().DType != SXMLEntity::EType::CharData) {
                        entity = DEntities.front();
                        DEntities.pop_front();
                        return true;
                    }
                    else {
                        DEntities.pop_front();
                    }
                }
                else {
                    entity = DEntities.front();
                    DEntities.pop_front();
                    return true;
                }
            }
            if (End() && Buffer.empty()) {
                Done = true;
            }
        }

        return false;
    };
};

CXMLReader::CXMLReader(std::shared_ptr< CDataSource > src) {
    DImplementation = std::make_unique<SImplementation>(src);
}

CXMLReader::~CXMLReader() {

}

bool CXMLReader::End() const {
    return DImplementation->End();
}

bool CXMLReader::ReadEntity(SXMLEntity& entity, bool skipcdata) {
    return DImplementation->ReadEntity(entity, skipcdata);
}