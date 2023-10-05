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
    Options::AddIntOption("testNum", "A test parameter", 1);
    Options::AddStringOption("testString", "A test parameter", "Boh");
    Options::AddBoolOption("testBool", "A flag", false);
    Options::AddIntListOption("testList", "An int list");
    Options::AddIntRangeOption("testRange", "An int range");
```

Check if the user provided a command line argument.

```cpp

if(Options::wasSet("testBool")){
    cout<<"Test bool was set"<<endl;
}

```

Provide arguments from command line

```bash

cpp_opt$ ./cmd_args
testBool: 0
testList: 
testNum: 0
testRange: 
testString: Boh

cpp_opt$ ./cmd_args -testBool -testList 1,2,3,4,10,1253 -testNum 5 -testRange 10:20:5 -testString "Hello World"
testBool: 1 (set) 
testList: 1,2,3,4,10,1253 (set) 
testNum: 5 (set) 
testRange: 10:20:5 (set) 
testString: Hello World (set) 
Test bool was set
testList was set

```
