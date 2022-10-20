#include "StringDataSource.h"

CStringDataSource::CStringDataSource(const std::string &str) : DString(str), DIndex(0){   //DIndex is 0 at first

}

bool CStringDataSource::End() const noexcept{   //tells if you're at the end yet. use to check the size of the string
    return DIndex >= DString.length();
}

bool CStringDataSource::Get(char &ch) noexcept{  //when called for the first time, get gets you the char at index 0 and increments DIndex to 1
    if(DIndex < DString.length()){
        ch = DString[DIndex];
        DIndex++;
        return true;
    }
    return false;
}

bool CStringDataSource::Peek(char &ch) noexcept{  //calling peek after calling get for the first time will give you what's at index 1 (because calling get incremented DIndex from 0 to 1)
    if(DIndex < DString.length()){                  //peek gives you the same char as get but doesn't increment the index. use at end 
        ch = DString[DIndex];
        return true;
    }
    return false;
}

bool CStringDataSource::Read(std::vector<char> &buf, std::size_t count) noexcept{   //take in a buffer and a string of size count.
    buf.clear();
    while(buf.size() < count){
        char TempChar;
        if(Get(TempChar)){
            buf.push_back(TempChar);
        }
        else{
            break;
        }
    }
    return !buf.empty();
}
