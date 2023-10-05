To Compile
-------

```sh

make

```

Use in a different project
------------------------

1. Move Options.hpp in the same folder as the cpp file including it.
2. Add include in the cpp file using Options.hpp

```cpp

#include "Options.hpp"

```

### Declare your arguments

```cpp
    // (<flag_name>, <description>, <default_value>)
    auto arg_int = Options::AddIntOption("testNum", "A test parameter", 1);
    auto arg_string = Options::AddStringOption("testString", "A test parameter", "Boh");
    auto arg_bool = Options::AddBoolOption("testBool", "A flag", false);
    auto arg_int_list = Options::AddIntListOption("testList", "An int list");
    auto add_int_range = Options::AddIntRangeOption("testRange", "An int range"); 
```

Check if the user provided a command line argument.

```cpp

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

```

Provide arguments from command line

```bash

/cpp_opt$ ./cmd_args 
testBool: 0
testList: 
testNum: 0
testRange: 
testString: Boh

/cpp_opt$ ./cmd_args -testList 1,2,3,4
testBool: 0
testList: 1,2,3,4 (set) 
testNum: 0
testRange: 
testString: Boh
testList was set to: 1 2 3 4 

```
