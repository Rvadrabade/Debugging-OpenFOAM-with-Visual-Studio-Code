# Debugging OpenFOAM® with Visual Studio Code  

## Motivation  
I remember when I started learning OpenFOAM a few years back (in 2017), I wondered how OpenFOAM works and usually new enthusiast wonders too. Over these years while learning OpenFOAM, I came across [HowTo Debugging OpenFOAM](https://openfoamwiki.net/index.php/HowTo_debugging) which helped me to get more insights of OpenFOAM and its Architecture. However it is very difficult to debug a application on command line (terminal in Ubuntu) which limits the study. Also, a few tools viz., eclipse, Data Display Debugger (ddd) can be used to debug OpenFOAM application interactively. In addition to these tool there is one more code editor i.e. Visual Studio Code (**VSCode**) which let you to debug OpenFOAM application interactively. So, in this tutorial i will be sharing my experiences and explaining how to setup VSCode environment for OpenFOAM development i.e. debug an application which will help you to create enhanced application(s).

## Requirements 
- VSCode - with c/c++ Microsoft extension installed. 
- OpenFOAM - compiled in *FULLDEBUG* mode - V1912.
- Third Party - Default with OpenFOAM version.
- OS - Ubuntu - V1804.
- Basic VSCode terminology like build task, launch task, debug etc and how to debug simple c++ code. More info is available here().
- Basic/Advance C++ topics such as pointers,references, classes, inheritance, polymorphism, templates, STL - Only for deep dive into source code.



## Steps for setting up the requirements.
### 1. Installing VSCode and extensions
+ Download latest VSCode from this [link](https://code.visualstudio.com/).
+ Install C/C++ extension for intellisense from [here](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

### 2. Compiling OpenFOAM in debug mode.
+ Download OpenFOAM v1912 and Third Party from [here](https://www.openfoam.com/download/install-source.php).
+ Extract packages into `$HOME/OpenFOAM` 
+ Edit `~/OpenFOAM/OpenFOAM-v1912/etc/bashrc` and change `WM_COMPILE_OPTION=Debug` (mind spaces before and after '=' ).
+ Append  `~/.bashrc` with ` source ~/OpenFOAM/OpenFOAM-v1912/etc/bashrc ` then cd into `~/OpenFOAM/OpenFOAM-v1912/` and compile with `./Allwmake`.
+ Note: 
    * Make appropriate changes for new OF version or read the [documentation](https://www.openfoam.com/download/install-source.php).

## Setting up VSCode environment for OpenFOAM Debugging

+ Create and cd into user directory.
    ~~~bash
    mkdir -p $FOAM_RUN 
    cd $FOAM_RUN
    ~~~
+ Make local copy of OpenFOAM tests and cd into vector test case.
    ~~~bash
    cp -r $WM_PROJECT_DIR/applications/test $FOAM_RUN
    cd test/vector
    ~~~
+ Understand the following process once and then can be eliminated just by copy and pasting the  `vscode` folder contents.
+ Open VSCode in present directory.
    ~~~bash
    code .
    ~~~
    * Go to *Terminal* tab in VSCode, select *configure build task* and choose *g++ build active file* ; Edit *task.json* as follows and remove *args* options.
        ~~~json
        "label": "wmake-build",
        "command": "wmake"
        ~~~
    * Go to *Debug* symbol in VSCode and create *launch.json* for *g++ build and debug active file*. Edit following fields
        ~~~json
        "name": "OF-Debug",
        "program": "${env:FOAM_USER_APPBIN}/{fileBasenameNoExtension}",
        "preLaunchTask": "wmake-build",
        ~~~
    * Now it is time to lunch debugger. So, put breakpoint at line no 123.
    * Perform step in, step out, continue as per study.
+ Owing to large source code and high use of c++ templates it is quite difficult for any IDE to provide code completion and intellisense but to some extent it is available in VSCode.

    * Open command pallet `ctrl+shift+p` and select `c/c++ : Edit Configuration UI ` which creates `c_cpp_properties.json` file. 
    * Edit includePath
        ~~~json
        "includePath": [
            "${workspaceFolder}/**",
            "${FOAM_SRC}"
        ],
        "intelliSenseMode": "gcc-x64"
        ~~~
    * Then go to File > Preferences > Settings and change `C_Cpp: IntelliSense Engine` to `Tag Parser`.
+ Now to develope OpenFOAM application like icoFoam, repeat same procedure.
+ To avoid all setting up manually, copy above `vscode` folder and replace or paste in your working directory then launch vscode as `code .` in terminal.

## References:
+ VSCode
+ OpenFOAM
+ [Probabilistic Money](http://www.probabilisticmoney.com/?page_id=84)
+ OpenFOAM wiki
+ YouTube Tutorials