CC=gcc
CXX=g++

INC_DIR=./include
SRC_DIR=./src
TESTSRC_DIR=./testsrc
BIN_DIR=./bin
OBJ_DIR=./obj

CXXFLAG=-std=c++17 -I $(INC_DIR) -I /opt/local/include
LDFLAGS=-L /opt/local/lib -lgtest -lgtest_main -lpthread -lexpat

all: directories runstrtest rundatasourcetest rundatasinktest rundsvtest runxmltest

runstrtest: $(BIN_DIR)/teststrutils
	$(BIN_DIR)/teststrutils
rundatasourcetest: $(BIN_DIR)/teststrdatasource
	$(BIN_DIR)/teststrdatasource
rundatasinktest: $(BIN_DIR)/teststrdatasink
	$(BIN_DIR)/teststrdatasink
rundsvtest: $(BIN_DIR)/testdsv
	$(BIN_DIR)/testdsv
runxmltest: $(BIN_DIR)/testxml
	$(BIN_DIR)/testxml

$(BIN_DIR)/teststrutils: $(OBJ_DIR)/StringUtilsTest.o $(OBJ_DIR)/StringUtils.o								
	$(CXX) -o $(BIN_DIR)/teststrutils $(OBJ_DIR)/StringUtilsTest.o $(OBJ_DIR)/StringUtils.o $(LDFLAGS)

$(BIN_DIR)/teststrdatasource: $(OBJ_DIR)/StringDataSourceTest.o $(OBJ_DIR)/StringDataSource.o								
	$(CXX) -o $(BIN_DIR)/teststrdatasource $(OBJ_DIR)/StringDataSourceTest.o $(OBJ_DIR)/StringDataSource.o $(LDFLAGS)

$(BIN_DIR)/teststrdatasink: $(OBJ_DIR)/StringDataSinkTest.o $(OBJ_DIR)/StringDataSink.o								
	$(CXX) -o $(BIN_DIR)/teststrdatasink $(OBJ_DIR)/StringDataSinkTest.o $(OBJ_DIR)/StringDataSink.o $(LDFLAGS)


$(BIN_DIR)/testdsv: $(OBJ_DIR)/DSVTest.o $(OBJ_DIR)/DSVWriter.o $(OBJ_DIR)/DSVReader.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o			#test						
	$(CXX) -o $(BIN_DIR)/testdsv $(OBJ_DIR)/DSVTest.o $(OBJ_DIR)/DSVWriter.o $(OBJ_DIR)/DSVReader.o $(LDFLAGS) $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o


$(BIN_DIR)/testxml: $(OBJ_DIR)/XMLTest.o $(OBJ_DIR)/XMLWriter.o $(OBJ_DIR)/XMLReader.o $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o					#test						
	$(CXX) -o $(BIN_DIR)/testxml $(OBJ_DIR)/XMLTest.o $(OBJ_DIR)/XMLWriter.o $(OBJ_DIR)/XMLReader.o $(LDFLAGS) $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringUtils.o



$(OBJ_DIR)/StringUtilsTest.o: $(TESTSRC_DIR)/StrUtilsTest.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtilsTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/StrUtilsTest.cpp 

$(OBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtils.o $(CXXFLAG) -c $(SRC_DIR)/StringUtils.cpp



$(OBJ_DIR)/StringDataSourceTest.o: $(TESTSRC_DIR)/StringDataSourceTest.cpp $(INC_DIR)/StringDataSource.h $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/StringDataSourceTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/StringDataSourceTest.cpp 

$(OBJ_DIR)/StringDataSource.o: $(SRC_DIR)/StringDataSource.cpp $(INC_DIR)/StringDataSource.h $(INC_DIR)/DataSource.h   
	$(CXX) -o $(OBJ_DIR)/StringDataSource.o $(CXXFLAG) -c $(SRC_DIR)/StringDataSource.cpp



$(OBJ_DIR)/StringDataSinkTest.o: $(TESTSRC_DIR)/StringDataSinkTest.cpp $(INC_DIR)/StringDataSink.h $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/StringDataSinkTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/StringDataSinkTest.cpp

$(OBJ_DIR)/StringDataSink.o: $(SRC_DIR)/StringDataSink.cpp $(INC_DIR)/StringDataSink.h $(INC_DIR)/DataSink.h
	$(CXX) -o $(OBJ_DIR)/StringDataSink.o $(CXXFLAG) -c $(SRC_DIR)/StringDataSink.cpp



$(OBJ_DIR)/DSVTest.o: $(TESTSRC_DIR)/DSVTest.cpp $(INC_DIR)/DSVWriter.h $(INC_DIR)/DSVReader.h $(INC_DIR)/DataSink.h $(INC_DIR)/DataSource.h $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/DSVTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/DSVTest.cpp

$(OBJ_DIR)/DSVWriter.o: $(SRC_DIR)/DSVWriter.cpp $(INC_DIR)/DSVWriter.h $(INC_DIR)/DataSink.h $(INC_DIR)/StringUtils.h $(INC_DIR)/StringDataSink.h

	$(CXX) -o $(OBJ_DIR)/DSVWriter.o $(CXXFLAG) -c $(SRC_DIR)/DSVWriter.cpp

$(OBJ_DIR)/DSVReader.o: $(SRC_DIR)/DSVReader.cpp $(INC_DIR)/DSVReader.h $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/DSVReader.o $(CXXFLAG) -c $(SRC_DIR)/DSVReader.cpp



$(OBJ_DIR)/XMLTest.o: $(TESTSRC_DIR)/XMLTest.cpp $(INC_DIR)/XMLWriter.h $(INC_DIR)/XMLReader.h $(INC_DIR)/XMLEntity.h $(INC_DIR)/DataSink.h $(INC_DIR)/DataSource.h
	$(CXX) -o $(OBJ_DIR)/XMLTest.o $(CXXFLAG) -c $(TESTSRC_DIR)/XMLTest.cpp

$(OBJ_DIR)/XMLWriter.o: $(SRC_DIR)/XMLWriter.cpp $(INC_DIR)/XMLWriter.h $(INC_DIR)/DataSink.h $(INC_DIR)/XMLEntity.h
	$(CXX) -o $(OBJ_DIR)/XMLWriter.o $(CXXFLAG) -c $(SRC_DIR)/XMLWriter.cpp

$(OBJ_DIR)/XMLReader.o: $(SRC_DIR)/XMLReader.cpp $(INC_DIR)/XMLReader.h $(INC_DIR)/DataSource.h $(INC_DIR)/XMLEntity.h
	$(CXX) -o $(OBJ_DIR)/XMLReader.o $(CXXFLAG) -c $(SRC_DIR)/XMLReader.cpp


#add expat library??



directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)


.PHONY : clean
clean :
		-rm -rf $(BIN_DIR)
		-rm -rf $(OBJ_DIR)




#The Makefile you develop needs to implement the following: \
• Must create obj directory for object files (if doesn't exist) \
• Must create bin directory for binary files (if doesn't exist) \
• Must compile cpp files using C++17 \
\
• Must link string utils and string utils tests object files to make teststrutils executable \
• Must link StringDataSource and StringDataSourceTest object files to make teststrdatasource executable \
• Must link StringDataSink and StringDataSinkTest object files to make teststrdatasink executable \
• Must link DSV reader/writer and DSV tests object files to make testdsv executable \
• Must link XML reader/writer and XML tests object files to make testxml executable \
\
• Must  execute  the  teststrutils,  teststrdatasource,  teststrdatasink, testdsv, and testxml executables \
• Must provide a clean that will remove the obj and bin directories \
\
the order of the tests to be run should be teststrutils, teststrdatasource, teststrdatasink, testdsv, and then testxml \
