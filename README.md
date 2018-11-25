# RakNet Fake Client for San Andreas Multiplayer
### This is an incomplete wrap of RakNet SAMP Fake Client for NodeJS
___

### Basic Informations
This is a fork of https://github.com/P3ti/RakSAMP. I used node-gyp to wrap basic RakSAMP functions to read SA:MP messages on a Node environment. I'm not a C/CPP expert so the CPP code may be bad written. 
If you need more SA:MP feature you can get them by copying RakSAMP classes in the project and adding them in *binding.gyp*.

### Setup
- Install *Node-GYP*.
    https://github.com/nodejs/node-gyp
- Insert your Python 2.7 path in *app/package.json*
    Node-GYP uses Python 2.7 for some routines.
    ```
    "scripts": {
        "build": "node-gyp --python="YOUR_PYTHON_ABSOLUTE_PATH" build",
        "configure": "node-gyp --python="YOUR_PYTHON_ABSOLUTE_PATH" configure",
        "debug": "node-gyp --python="YOUR_PYTHON_ABSOLUTE_PATH" build --debug"
      }
    ```
- Open a console in *app* and type `npm install`
    This command will install all dependencies defined in package.json. You clearly need NodeJS installed.
- Configure and build the code
    Use `npm run configure && npm run debug`. This will configure the building environment and build the code in a new folder called *Build*. 
- Insert your nickname and the server IP in *RakSAMPClient.xml*
- Run the software by using `node index.js`

    
### Known issues
- The code won't compile in Release mode. At the end of compiling it says that's impossible to open the compiled file (*samp.node*) while in Debug mode it compiles correctly.

- The main loop in *src/main/main.cpp* makes it impossible to use other Cpp functions because the thread is occupied. I've tried to put the loop on another thread but - for some reason - it suddenly crashes. As I said I'm not a C/Cpp expert so I don't know very well how can I solve this issue. If you want you can try to fix it and send a pull request.


