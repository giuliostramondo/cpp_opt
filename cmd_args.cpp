#include "Options.hpp"

int main(int argc, char *argv[]){
    auto arg_int = Options::AddIntOption("testNum", "A test parameter", 1);
    auto arg_string = Options::AddStringOption("testString", "A test parameter", "Boh");
    auto arg_bool = Options::AddBoolOption("testBool", "A flag", false);
    auto arg_int_list = Options::AddIntListOption("testList", "An int list");
    auto add_int_range = Options::AddIntRangeOption("testRange", "An int range");
    if(!Options::parseArgs(argc,argv)){
        Options::dumpOpts();
    }

    if(arg_int->setByUser){
        cout<<"TestNum was set to: "<<arg_int->val <<endl;
    }
    if(arg_int_list->setByUser){
        cout<<"testList was set to: ";
        for(auto i: arg_int_list->val){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}




