#include "Options.hpp"

int main(int argc, char *argv[]){
    Options::AddIntOption("testNum", "A test parameter", 1);
    Options::AddStringOption("testString", "A test parameter", "Boh");
    Options::AddBoolOption("testBool", "A flag", false);
    Options::AddIntListOption("testList", "An int list");
    Options::AddIntRangeOption("testRange", "An int range");
    if(!Options::parseArgs(argc,argv)){
        Options::dumpOpts();
    }

    if(Options::wasSet("testBool")){
        cout<<"Test bool was set"<<endl;
    }
    if(Options::wasSet("testList")){
        cout<<"testList was set"<<endl;
        list<int> user_provided_val = {};
    }
}




