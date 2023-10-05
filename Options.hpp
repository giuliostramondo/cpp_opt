#ifndef _OPTIONS_HPP
#define _OPTIONS_HPP

#include <iostream>
#include <map>
#include <list>

using namespace std;
class Option{
    public:
        Option (string name_, string description, unsigned type_) : name(name_), description(description){type =opt_type( type_);};
    string name;
    bool setByUser;
    string description;
    enum opt_type {str, num, boolean, numlist, numrange, generic} type;
    virtual ~Option() {};

};

template <typename T>
class GenericOpt : public Option{
    public:
    GenericOpt(string name_, string description, T def_val): Option(name_,description, opt_type::generic){
        val = def_val;
    }
    void setVal(T val_){
        val = val_;
        setByUser = true;
    }
    T val;
};

class BoolOpt : public Option{
    public:
    BoolOpt(string name_, string description, bool def_val): Option(name_,description, opt_type::boolean){
        val = def_val;
    }
    void setVal(bool val_){
        val = val_;
        setByUser = true;
    }
    bool val;
}; 
class StringOpt : public Option{
    public:
    StringOpt(string name_, string description, string def_val): Option(name_,description,opt_type::str){
        val = def_val;
    }
    void setVal(string val_){
        val = val_;
        setByUser = true;
    }
    string val;
};

class NumOpt : public Option{
    public:
        NumOpt(string name_, string description, int def_val): Option(name_, description,opt_type::num){
        }
        void setVal(int val_){
            val = val_;
            setByUser = true;
        }
        int val;
};
class NumListOpt : public Option{
    public:
        NumListOpt(string name_, string description, int def_val): Option(name_, description,opt_type::numlist){
        }
        void setVal(list<int> val_){
            val = val_;
            setByUser = true;
        }
        list<int> val;
};

class NumRangeOpt : public Option{
   public:
        NumRangeOpt(string name_, string description, int def_val): Option(name_, description,opt_type::numrange){
        }
        void setVal(list<int> val_){
            val = val_;
            setByUser = true;
        }
        list<int> val;
};
class Options{
    public:
    static void AddIntOption(string name_, string description, int def_val){
        NumOpt *opt = new NumOpt(name_, description, def_val); 
        opt_map.emplace(make_pair(name_,opt));  
    }
    static void AddStringOption(string name_, string description, string def_val){
        StringOpt *opt = new StringOpt(name_, description, def_val); 
        opt_map.emplace(make_pair(name_,opt));  
    }
    static void AddBoolOption(string name_, string description, bool def_val){
        BoolOpt *opt = new BoolOpt(name_, description, def_val); 
        opt_map.emplace(make_pair(name_,opt));  
    }
    static void AddIntListOption(string name_, string description){
        NumListOpt *opt = new NumListOpt(name_, description, {}); 
        opt_map.emplace(make_pair(name_,opt));  
    }
    static void AddIntRangeOption(string name_, string description){
        NumRangeOpt *opt = new NumRangeOpt(name_, description, {}); 
        opt_map.emplace(make_pair(name_,opt));  
    }
    static bool wasSet(string name_){
        return opt_map.find(name_)->second->setByUser;
    }

    static int isBoolean(string name_){
        return opt_map.find(name_)->second->type == Option::opt_type::boolean;
    }
    static int isNum(string name_){
        return opt_map.find(name_)->second->type == Option::opt_type::num;
    }
    static int isString(string name_){
        return opt_map.find(name_)->second->type == Option::opt_type::str;
    }
    static int isNumList(string name_){
        return opt_map.find(name_)->second->type == Option::opt_type::numlist;
    }
    static int isRange(string name_){
        return opt_map.find(name_)->second->type == Option::opt_type::numrange;
    }
    static int isGeneric(string name_){
        return opt_map.find(name_)->second->type == Option::opt_type::generic;
    }
    static bool has(string name_){
        return opt_map.find(name_) != opt_map.end();
    }
    static void setVal(string name, bool val){
        if(opt_map.find(name) != opt_map.end()){
            if( auto opt_bool = dynamic_cast<BoolOpt*>((opt_map.find(name)->second)))
                opt_bool->setVal(val);
        }
    }
    static void setVal(string name, int val){
        if(opt_map.find(name) != opt_map.end()){
            if( auto opt_bool = dynamic_cast<NumOpt*>((opt_map.find(name)->second)))
                opt_bool->setVal(val);
        }
    }
    static void setVal(string name, string val){
        if(opt_map.find(name) != opt_map.end()){
            if( auto opt_bool = dynamic_cast<StringOpt*>((opt_map.find(name)->second)))
                opt_bool->setVal(val);
        }
    }
    static void setVal(string name, list<int> val){
        if(opt_map.find(name) != opt_map.end()){
            if( auto opt_bool = dynamic_cast<NumListOpt*>((opt_map.find(name)->second)))
                opt_bool->setVal(val);
            if( auto opt_bool = dynamic_cast<NumRangeOpt*>((opt_map.find(name)->second)))
                opt_bool->setVal(val);
        }
    }
    static int parseArgs(int argc, char *argv[]){
        appName = argv[0];
       for(int i = 1; i< argc; i++){
           if(argv[i][0] != '-'){
               cout<< "cmd opt need to start with '-'\n" <<endl;
               printHelp();
               return 1;
           }
           string opt_name = argv[i]+1;
           if(has(opt_name)){
               if(isBoolean(argv[i]+1)){
                   setVal(argv[i]+1,true);
                   if(BoolOpt* b_opt = dynamic_cast<BoolOpt*>((opt_map.find(argv[i]+1))->second)){
                       b_opt->setVal(true);
                   }
               }
               if(isNum(argv[i]+1)){
                   i++;
                    if(i >=argc){
                            cout <<"Option "<<opt_name<<" requires an argument"<<endl;
                            printHelp();
                            return 1;
                       }
                   if(argv[i][0] == '-'){
                       
                        int j = 1;
                        bool negative_number = true;
                        for(int j=1;argv[i][j]!='\0';j++){
                            if(argv[i][j] < '0' || argv[i][j] > '9'){
                                negative_number = false;
                                break;
                            } 
                        }
                        if(!negative_number){
                            cout <<"Option "<<opt_name<<" requires an argument"<<endl;
                            printHelp();
                            return 1;
                        }
                   }
                   setVal(opt_name, atoi(argv[i]));
                   continue;
               }
               if(isString(argv[i]+1)){
                    i++;
                   if(i >= argc || argv[i][0] == '-'){
                        cout <<"Option "<<opt_name<<" requires an argument"<<endl;
                        printHelp();
                        return 1;
                   }
                   string arg_string(argv[i]);
                   setVal(opt_name, arg_string);
                   continue;
               }
                if(isNumList(argv[i]+1)){
                    i++;
                    if(i >= argc){
                            cout <<"Option "<<opt_name<<" requires an argument"<<endl;
                            printHelp();
                            return 1;
                        }
                   if(argv[i][0] == '-'){
                        int j = 1;
                        bool negative_number = true;
                        for(int j=1;argv[i][j]!='\0' && argv[i][j]!=',';j++){
                            if(argv[i][j] < '0' || argv[i][j] > '9'){
                                negative_number = false;
                                break;
                            } 
                        }
                        if(!negative_number){
                            cout <<"Option "<<opt_name<<" requires an argument"<<endl;
                            printHelp();
                            return 1;
                        }
                   }
                   int j=0;
                   string curr_number= "";
                   list<int> values;
                   while(argv[i][j]!='\0'){
                       if((argv[i][j] < '0' || argv[i][j] > '9')
                               && (argv[i][j]!=',') && (argv[i][j]!='-')){
                                    cout<<"Error, expecting a list of comma separated numbers"<<endl;
                                    printHelp();
                                    return 1;
                               }
                       if( argv[i][j] == ','){
                           if(!curr_number.empty()){
                               values.push_back(atoi(curr_number.c_str()));
                               curr_number="";
                           }
                           else{
                                cout<<"Error, expecting a list of comma separated numbers"<<endl;
                                printHelp();
                                return 1;
                           }
                       }else{
                           curr_number+=argv[i][j];
                       }
                       j++;
                   }
                    if(!curr_number.empty())
                               values.push_back(atoi(curr_number.c_str()));
                   setVal(opt_name, values);
                   continue;
               }
                if(isRange(argv[i]+1)){
                    i++;
                   if(i>=argc || argv[i][0] == '-'){
                        cout <<"Option "<<opt_name<<" requires an argument"<<endl;
                        printHelp();
                        return 1;
                   }
                   int j=0;
                   string curr_number = "";
                   list<int> values;
                   while(argv[i][j]!='\0'){
                       if((argv[i][j] < '0' || argv[i][j] > '9')
                               && (argv[i][j]!=':')){
                                    cout<<"Error, expecting a list of 3 ':' separated numbers"<<endl;
                                    printHelp();
                                    return 1;
                               }
                       if( argv[i][j] == ':'){
                           if(!curr_number.empty()){
                               values.push_back(atoi(curr_number.c_str()));
                               curr_number = "";
                           }
                           else{
                                    cout<<"Error, expecting a list of 3 ':' separated numbers"<<endl;
                                    printHelp();
                                    return 1;
                           }
                       }else{
                           curr_number+=argv[i][j];
                       }
                       j++;
                   }
                    if(!curr_number.empty())
                               values.push_back(atoi(curr_number.c_str()));
                   if(values.size() != 3){
                        cout<<"Error, expecting a list of 3 ':' separated numbers"<<endl;
                        printHelp();
                        return 1;
                   }
                   setVal(opt_name, values);
                   continue;
               }
           }else{
               cout <<"Unrecognized option: "<< argv[i]<<endl;
               printHelp();
               return 1;
           }
       } 
       return 0;
    }
    static void printHelp(){
        cout<<"Usage: "<<appName<<" [Options]"<<endl;
        for(auto opt_pair : opt_map){
            cout<<"-"<<opt_pair.first;
            switch(opt_pair.second->type){
                case Option::num: 
                   if(NumOpt* b_opt = dynamic_cast<NumOpt*>(opt_pair.second)){
                        cout<<" <int>\t "<<b_opt->description<<"\t [default: "<<b_opt->val<<"]"<<endl;
                   }
                   break;
                case Option::boolean: 
                   if(BoolOpt* b_opt = dynamic_cast<BoolOpt*>(opt_pair.second)){
                        cout<<" <boolean>\t "<<b_opt->description<<"\t[default: "<<b_opt->val<<"]"<<endl;
                   }
                   break;
                case Option::numlist: 
                   if(NumListOpt* b_opt = dynamic_cast<NumListOpt*>(opt_pair.second)){
                        cout<<" <num1,num2>\t "<<b_opt->description<<"\t[default: {}]"<<endl;
                   }
                   break;
                case Option::str: 
                   if(StringOpt* b_opt = dynamic_cast<StringOpt*>(opt_pair.second)){
                        cout<<" <string>\t "<<b_opt->description<<"\t[default: '']"<<endl;
                   }
                   break;
                case Option::numrange: 
                   if(NumRangeOpt* b_opt = dynamic_cast<NumRangeOpt*>(opt_pair.second)){
                        cout<<" <begin:end:stride>\t "<<b_opt->description<<"\t[default: 0:0:0]"<<endl;
                   }
                   break;
                default:
                    cout<<"Unrecognized type"<<endl;

            }
        }
    }
    static void dumpOpts(){
        for(auto opt_pair : opt_map){
            cout<<opt_pair.first<< ": ";
            switch(opt_pair.second->type){
                case Option::num: 
                    {
                    NumOpt* b_opt = dynamic_cast<NumOpt*>((opt_pair.second));
                   if(b_opt!= nullptr){
                           cout << b_opt->val;
                   }
                   break;
                    }
                case Option::boolean: 
                   if(BoolOpt* b_opt = dynamic_cast<BoolOpt*>(opt_pair.second)){
                           cout << b_opt->val;
                   }
                   break;
                case Option::numlist: 
                   if(NumListOpt* b_opt = dynamic_cast<NumListOpt*>(opt_pair.second)){
                        for(auto v1_it = b_opt->val.begin(); v1_it != b_opt->val.end(); v1_it ++){
                           if(next(v1_it)!= b_opt->val.end())
                               cout << *v1_it << ",";
                           else
                               cout << *v1_it;
                        }
                   }
                   break;
                case Option::str: 
                   if(StringOpt* b_opt = dynamic_cast<StringOpt*>(opt_pair.second)){
                           cout << b_opt->val;
                   }
                   break;
                case Option::numrange: 
                   if(NumRangeOpt* b_opt = dynamic_cast<NumRangeOpt*>(opt_pair.second)){
                        for(auto v1_it = b_opt->val.begin(); v1_it != b_opt->val.end(); v1_it ++){
                           if(next(v1_it)!= b_opt->val.end())
                               cout << *v1_it << ":";
                           else
                               cout << *v1_it;
                            }
                   }
                   break;
                default:
                    cout<<"Unrecognized type"<<endl;

            }
            if(opt_pair.second->setByUser)
                cout << " (set) "<<endl;
            else
                cout<<endl;
        }
    }
    static map<string,Option*> opt_map;
    static string appName;
};

map<string,Option*> Options::opt_map = {};
string Options::appName = "";

#endif
