#include "string.h"
#include "json.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Astar.h"
#include <fstream>

//MACROS
#define SAVE_TEST_LOG

#ifdef SAVE_TEST_LOG
# define MyLog(...) { FILE* f; f = fopen("Error.log", "a+"); if(f) { fprintf(f, __VA_ARGS__); fclose(f); } }
#else
#  define MyLog(...)
#endif

# define OutputLog(...) { FILE* f; f = fopen("Output.log", "a+"); if(f) { fprintf(f, __VA_ARGS__); fclose(f); } }

#define MAX_RETRYS 5
#define MAP_CHOICES 3
#define POINT_CHOICES 2

using json = nlohmann::json;
//Function to load Json Maps to run the program
int LoadMap(int &rows,int &cols,std::vector<std::vector<int>> &RTS_Map)
{
    int choice=-1;
    int correct_choice=0;
    std::string file_path;
    //Load Map from json file 
    std::cout << "Choosing Map option \n0:Default1(take_home)\n1:Default2\n2:User_Choice\n";
    while(correct_choice<MAX_RETRYS)
    {
        std::cout << "Choice:";
        std::cin >> choice;

        if(choice>=0 && choice < MAP_CHOICES)
        {
            break;
        }
        else
        {
            std::cout << "Error in Choice Input.Please Try Again!!\n";
            correct_choice++;
        }
    }
    
    if(choice<0 || choice >= MAP_CHOICES)
    {
        MyLog("Invalid Map Choice\n");
        return 0;
    }
    correct_choice=0;
    
    if(choice==0)
    {
        file_path = "../examples/take_home_project.json";
        std::cout <<"Choosing Default 1 map\n";
        MyLog("Choosing Default 1 map\n");
    }
    else if(choice==1)
    {
        file_path = "../examples/take_home_project2.json";
        std::cout <<"Choosing Default 2 map\n";
        MyLog("Choosing Default 2 map\n");
    }
    else
    {
        std::cout << "Filepath for the custom json file:";
        std::cin >> file_path;
        std::cout <<"Choosing User Defined map: "<<file_path.c_str()<<"\n";
        MyLog("Choosing User Defined map:%s\n",file_path.c_str());
    }


    //Open the Json file and copy the map here
    std::ifstream ifs(file_path);
    if (!ifs.is_open()) {
        std::cerr << "Error: Unable to open JSON file." << std::endl;
        return 0;
    }

    json jsonObject;
    try {
        ifs >> jsonObject;
    } catch (const json::exception& e) {
    	std::cerr << "Unable to load json map File";
        MyLog("Unable to load json map File\n");
		return 0;
    }
    std::cout <<"Loaded Map to Json Object\n";

    //Extract the exact number of rows and columns from the json file
    
    
    rows = jsonObject["tilesets"][0]["tilewidth"];
    cols = jsonObject["tilesets"][0]["tileheight"];
    std::cout <<"Rows:"<< rows << " and Cols:"<<cols<<"\n";
    MyLog("Rows:%d and Cols:%d\n",rows,cols);	
    //Extract the map from the json file

    json data_array = jsonObject["layers"][0]["data"];

    //Now data is a json array with the map array in it and the no of rows and columns is rows x cols
    //Copy it to a map object which can store this for our processing 
    std::vector<std::vector<int>> full_map(rows,std::vector<int>(cols));
    int index = 0;
    for(size_t i=0;i<rows;i++)
    {
        for(size_t j=0;j<cols;j++)
        {
            //std::cout <<"Extracting Value"<< data_array[index]<<"\n";
            full_map[i][j] = data_array[index++];
        }
    }
    RTS_Map = full_map;
    
/*
    //Print to verify that the map is loaded correctly
    for(size_t i=0;i<cols;i++)
    {
        for(size_t j=0;j<rows;j++)
        {
            //std::cout <<"Checking Value"<< RTS_Map[j][i];
            MyLog("%d",RTS_Map[j][i]);
        }
        MyLog("\n");
    }
*/
    return 1;

}


/*
//Function to make sure that a point is valid within a given map
bool ValidPoint(int x,int y,const std::vector<std::vector<int>> RTS_Map)
{

    //Given that the value 3 is elevated terrain so if we compare the value of the given point and it is not 8 then we are safe
    //In the Future if there are other obstacles they can be added to this function.

    //y corresponds to cols and x corresponds to rows
    if(RTS_Map[x][y] ==3)
    {
        return false;
    }
    return true;
}
*/
//Function to choose a point in the map and make sure that it is a valid point
bool ChoosePoint(int &x,int &y,int Type,int rows,int cols,std::vector<std::vector<int>> RTS_Map) //For Now Type -0 Initial point and Type 1 Final Point
{
    int x_local;
    int y_local;
    int choice=-1;
    int correct_choice=0;
    while(correct_choice<MAX_RETRYS)
    {
        std::cout << "Choice:";
        std::cin >> choice;

        if(choice>=0 && choice < POINT_CHOICES)
        {
            break;
        }
        else
        {
            std::cout << "Error in Choice Input.Please Try Again!!\n";
            correct_choice++;
        }
    }
    
    if(choice<0 || choice >= POINT_CHOICES)
    {
        return 0;
    }
    correct_choice =0;
    if(choice ==0) //User Defined Input
    {
        while(correct_choice<MAX_RETRYS)
        {
            if(Type ==0)
            {
                std::cout <<"Choose Initial Point x value from 0 to "<< (rows-1)<<"\n";
            }
            else
            {
                std::cout <<"Choose Final Point x value from 0 to "<< (rows-1)<<"\n";
            }
            
            std::cout << "X:";
            std::cin >> x_local;

            if(Type ==0)
            {
                std::cout <<"Choose Initial Point y value from 0 to "<< (cols-1)<<"\n";
            }
            else
            {
                std::cout <<"Choose Final Point y value from 0 to "<< (cols-1)<<"\n";
            }
            std::cout << "Y:";
            std::cin >> y_local;

            //Now check if this point is within the map and is not on top of terrain?
            if(x_local>=0 && x_local<rows && y_local>=0 && y_local<cols)
            {
                //Check on map if this is acceptable point
                
                if(RTS_Map[x_local][y_local]!=3)
                {
                    x=x_local;
                    y=y_local;
                    MyLog("X:%d,Y:%d\n",x,y);
                    break;
                }
                else
                {
                    std::cout << "Not a Valid Point Please Try Again!!\n";
                    correct_choice++;
                }
                
            }
            else
            {
                std::cout << "Error in Point Input.Please Try Again!!\n";
                correct_choice++;
            }
        
        }

        if(correct_choice==MAX_RETRYS)
        {
            return 0;
        }
        correct_choice=0;
    }
    else //Random Input Point
    {
        while(correct_choice<MAX_RETRYS)
        {
            //Choose random value from 0 to cols-1 for x
            x_local = rand() % (rows-1);
            //Choose random value from 0 to rows-1 for y
            y_local = rand() % (cols-1);

            //Check if Random Point is not on Terrain
            if(RTS_Map[x_local][y_local]!=3)
            {
                x=x_local;
                y=y_local;
                std::cout << "Random X:"<<x << ", Y:"<<y<<"\n";
                MyLog("Random X:%d,Y:%d\n",x,y);
                break;
            }
            else
            {
                std::cout << "Chosen Random Point on Terrain,Trying again!!\n";
                correct_choice++;
            }

        }
        
        if(correct_choice==MAX_RETRYS)
        {
            return 0;
        }
        correct_choice=0;
    }
    MyLog("X:%d,Y:%d\n",x,y);
    return 1;
}



int main()
{

    int choice;
    int correct_choice=0;
    int x_start=0;
    int y_start=0;
    int x_end=0;
    int y_end=0;
    time_t now = time(0);
    char* dt = ctime(&now);
    int rows;
    int cols;
    std::vector<std::vector<int>> RTS_Map;
    srand(time(nullptr));
    
    //Start Program
    std::cout << "Test Project for Path Finding Algorithms at "<< dt <<"\n";
    MyLog("Test Project for Path Finding Algorithms at %s  \n",dt);
    
    std::cout << "Loading Map\n";
    if(!LoadMap(rows,cols,RTS_Map))
    {
        std::cout << "LoadMap Failed.Exiting Program\n";
        MyLog("LoadMap Failed.Exiting Program\n");
        return 0;
    }
    
    //Now Ask for Initial Point By the user or randomly generated
    std::cout << "Choosing Initial Point option \n0:UserDefined\n1:Random\n";
    if(!ChoosePoint(x_start,y_start,0,rows,cols,RTS_Map))
    {
        std::cout << "ChoosePoint Failed.Exiting Program\n";
        MyLog("ChoosePoint Failed.Exiting Program\n");
        return 0;
    }

    //Ask for the Final Point by the user or randomly generated
    std::cout << "Choosing Final Point option \n0:UserDefined\n1:Random\n";
    if(!ChoosePoint(x_end,y_end,1,rows,cols,RTS_Map))
    {
        std::cout << "ChoosePoint Failed.Exiting Program\n";
        MyLog("ChoosePoint Failed.Exiting Program\n");
        return 0;
    }

    //In the Future If needed ChoosePoint Function can be used to find Multiple Points both initial and Final

    //Run the A* algorithm to get the possible path
    Node* start = new Node(x_start,y_start);
    Node* goal = new Node(x_end,y_end);
    RTS_Map[x_start][y_start]=0;
    RTS_Map[x_end][y_end]=8;
    std::cout << "Start Working on Path\n";
    std::vector<Node*> path = aStar(start, goal, RTS_Map);


    //Get the possible path and print it out and also save the output in a log file
    OutputLog("Output at :%s\n",dt);
    if (!path.empty()) 
    {
        for (Node* node : path) {
            std::cout << "(" << node->x << ", " << node->y << ") ";
            OutputLog("(%d,%d)",node->x,node->y);
        }
        std::cout << std::endl;
        OutputLog("\n");
    } else {
        std::cout << "No path found." << std::endl;
        OutputLog("No path found \n");
    }
    
    return 1;    


}