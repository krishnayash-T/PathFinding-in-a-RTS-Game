Path Finding Algorithm for Real-Time Strategy game.<br />

This is a take home assignment for building a path finding algorithm for a Real-Time Strategy Game.I used Cmake to build this in Fedora 29 system.<br />

Programming Language:C++<br />

Third Party Library: nlohmann/json.hpp for json file reading<br />

Prerequisites:Cmake(min Version 3.6) and c++11 compiler<br />

Build Instructions:<br />
1)Download the code from the git repository.<br />
2)delete the existing build folder and create a new build folder.<br />
3)In a Terminal navigate to the build folder and run the command "cmake .."<br />
4)Once the make files are generated run "make"<br />
5)The "Output" Binary would be generated which can be run to execute the code.<br />

Assumptions<br />
1)The code will check the user input MAX_RETRYS(Currently at 5) before exiting,This can be changed in main.cpp<br />
2)The Default TileMaps are stored in the example folder.The Assumption is the Output command would be run either in the build folder or in another folder where "../examples" would work,Otherwise the path can be explicitly specified using the User-Defined option.<br />
3)The user can upload their own TileMaps to run the game.<br />
4)The Output is printed on the screen as well as written to an Output.log file.<br />

Overview of the Project Structure<br />
The project contains 2 source files and 1 header files<br />
main.cpp<br />
Astar.cpp<br />
Astar.h<br />

1)The Astar algorithm is stored in the Astar.cpp<br />
2)Most of the user input is done in the main.cpp<br />
3)LoadMap function allows you to load the Tile map to the program.<br />
4)ChoosePoint Function allows you to choose the Starting Point/Ending Point Either by User Definition or by Random Generation.<br />
5)Any Errors are displayed on the screen as well as saved in a ErrorLog for later Debugging.<br />

Sample Inputs: examples folder
Sample Outputs:Outputs folder

Design Decisions<br />
1)I decided to use the third-party library for parsing the json files instead of manually reading them for saving time.<br />
2)I separated the Algorithm from the rest of the input code so that in the future another algorithm could also be implemented here.<br />
3)I generalised the Choose Point Function so that we can add more Battle Units in the future.<br />
4)I added an Error Log so that we can keep track of any errors that might occur.<br />
