

#include "mapGen.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>// use smart pointers?
#define ROWNUM  9
#define NODENUM  9
void TestMap::Initialize_Map()
{
    for (int i = 0; i < 6; i += 1) //looping each of the zones 0 to 5
    {
        //Map is an array of zones. zones are a vector of vectors of points(rows/columns).
        Map[i].push_back(new std::vector<Point>{ { } });
        Map[i].push_back(new std::vector<Point>{ { }, { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { }, { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { } ,{ } , { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { } ,{ } , { } , { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { } ,{ } , { } , { } , { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { } ,{ } , { } , { } , { }, { } });
        Map[i].push_back(new std::vector<Point>{ { }, { }, { }, { } ,{ } , { } , { } , { }, { }, { } }); // you can easily add more rows here.
        for (int x_index = 0; x_index < Map[i].size(); x_index++) {
            for (int y_index = 0; y_index < Map[i].at(x_index)->size(); y_index++) {
                Map[i].at(x_index)->at(y_index).position.zone = i;
                Map[i].at(x_index)->at(y_index).position.X_position = x_index;
                Map[i].at(x_index)->at(y_index).position.Y_position = y_index;
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }

}

void TestMap::TestDrawMap()
{
    for (int i = 0; i < 6; i += 1) //looping each of the zones 0 to 5
    {
        for (int x_index = 0; x_index < Map[i].size(); x_index++) {
            for (int y_index = 0; y_index < Map[i].at(x_index)->size(); y_index++) {

                //std::cout << " zone: " << Map[i].at(x_index)->at(y_index).position.zone;
                /*std::cout << " x: " << Map[i].at(x_index)->at(y_index).position.X_position;
                std::cout << " y: " << Map[i].at(x_index)->at(y_index).position.Y_position;
                std::cout << " |";*/

                std::cout << "(" << Map[i].at(x_index)->at(y_index).position.X_position << ",";
                std::cout << Map[i].at(x_index)->at(y_index).position.Y_position << ") ";


            }
            std::cout << std::endl;
        }
        std::cout << "ZONE : " << i + 1 << std::endl;
        std::cout << std::endl;
    }
}

void TestMap::TestDrawMap2() // ai
{
    // Define a fixed width for each coordinate pair like "(x,y) "
    // Ensure this is wide enough for your largest expected coordinate pair + "(,)" + space
    const int coord_width = 6; // e.g., "(7,7) " fits

    for (int i = 0; i < 6; i += 1) // Loop through zones
    {
        if (Map[i].empty()) {
            std::cout << "ZONE : " << i + 1 << " (empty)" << std::endl << std::endl;
            continue;
        }

        int max_x_index = static_cast<int>(Map[i].size() - 1); // Max original row index (e.g., 7) possible loss of data, i know

        // --- Centering Calculation ---
        // Calculate width of the longest row (r=0) based on point count and coord_width
        int num_points_longest_row = max_x_index + 1;
        int max_content_width = num_points_longest_row * coord_width;

        // Loop for each row 'r' in the output triangle (r = x_index - y_index)
        for (int r = 0; r <= max_x_index; ++r)
        {
            // Calculate width and padding for the current row 'r'
            int num_points_current_row = (max_x_index - r) + 1;
            int current_content_width = num_points_current_row * coord_width;
            int total_padding = max_content_width - current_content_width;
            // Calculate leading spaces for centering (integer division handles floor)
            int leading_spaces = total_padding / 2;

            // Print leading spaces using std::string constructor (from <string>)
            if (leading_spaces > 0) {
                std::cout << std::string(leading_spaces, ' ');
            }

            // --- Point Printing Loop with Manual Formatting ---
            // Loop through the points (x_index, y_index) for the current row 'r'
            for (int x_index = r; x_index <= max_x_index; ++x_index)
            {
                int y_index = x_index - r;

                // Get actual coordinates stored in the Point object
                // Ensure Map[i].at(x_index) and ->at(y_index) are valid based on Initialize_Map
                int actual_x = Map[i].at(x_index)->at(y_index).position.X_position;
                int actual_y = Map[i].at(x_index)->at(y_index).position.Y_position;

                // Manually format the coordinate string using std::to_string (from <string>)
                std::string coord_str = "(" + std::to_string(actual_x) + "," + std::to_string(actual_y) + ") ";

                // Calculate needed padding to reach coord_width
                int current_len = static_cast<int>(coord_str.length()); // string::length() is from <string>
                int padding_needed = coord_width - current_len;

                // Append spaces if the string is shorter than the desired width
                if (padding_needed > 0) {
                    // Append the required number of spaces using std::string constructor
                    coord_str += std::string(padding_needed, ' ');
                }
                std::cout << coord_str;
            }
            std::cout << std::endl;
        }
        std::cout << "                          ZONE : " << i + 1 << std::endl;
        std::cout << std::endl;
    }
}

void TestMap::push_neighbours(Position& node_position)
{
    int x = node_position.X_position;
    int y = node_position.Y_position;
    int zone = node_position.zone;

    node_position.nodes_in_neighbour = 0;

    // Basic sanity checks for the input node's coordinates and zone
    if (zone < 0 || zone >= 6) {
        std::cerr << "Error: push_neighbours called with invalid zone: " << zone << std::endl;
        return;
    }
    if (x < 0 || y < 0) {
        std::cerr << "Error: push_neighbours called with negative coordinates: (" << x << "," << y << ")" << std::endl;
        return;
    }
    if (static_cast<size_t>(x) >= Map[zone].size() || !Map[zone].at(x)) {
        std::cerr << "Error: push_neighbours called for invalid x-index " << x << " in zone " << zone << " or vector is null." << std::endl;
        return;
    }
    if (static_cast<size_t>(y) >= Map[zone].at(x)->size()) {
        std::cerr << "Error: push_neighbours called for invalid y-index " << y << " for x=" << x << " in zone " << zone << ". Vector size is " << Map[zone].at(x)->size() << "." << std::endl;
        return;
    }


    auto add_neighbour = [&](int nx, int ny) {

        if (static_cast<size_t>(nx) < Map[zone].size() && Map[zone].at(nx)) {
            // Check y boundary for the inner vector Map[zone].at(nx)
            if (static_cast<size_t>(ny) < Map[zone].at(nx)->size()) {
                Position* potential = &Map[zone].at(nx)->at(ny).position;
                if (!potential->Connected_Check && node_position.nodes_in_neighbour < 6) {
                    node_position.neighbours[node_position.nodes_in_neighbour++] = potential;
                }
                else {
                    std::cerr << "Warning: Exceeded neighbour array capacity for node (" << x << "," << y << ")" << std::endl;
                }
            }
        }
        };

    // (x+1, y)
    if (x + 1 >= 0) add_neighbour(x + 1, y);
    // (x+1, y+1) - Check if y+1 is valid within the (x+1) row
    if (x + 1 >= 0 && y + 1 >= 0) add_neighbour(x + 1, y + 1);
    // (x-1, y)
    if (x - 1 >= 0) add_neighbour(x - 1, y);
    // (x-1, y-1) - Check if y-1 is valid within the (x-1) row
    if (x - 1 >= 0 && y - 1 >= 0) add_neighbour(x - 1, y - 1);
    // (x, y+1)
    if (y + 1 >= 0) add_neighbour(x, y + 1);
    // (x, y-1)
    if (y - 1 >= 0) add_neighbour(x, y - 1);


    // Optional: Null-terminate remaining neighbour slots for extra safety
    for (int k = node_position.nodes_in_neighbour; k < 7; ++k) {
        node_position.neighbours[k] = nullptr;
    }
}
void TestMap::select_neighbours(Position* current_node_ptr)
{
    int road1 = 0;
    int road2 = 0;

    std::vector<int> available_indices;
    for (int i = 0; i < current_node_ptr->nodes_in_neighbour; ++i)
    {
        if (!current_node_ptr->neighbours[i]->Connected_Check)
        {
            available_indices.push_back(i);
        }
    }

    if (available_indices.size() < 1)//if there are no neighbours to choose from, exit
    {
        To_Be_Expanded.erase(To_Be_Expanded.begin());
        return;
    }

    road1 = static_cast<int>(available_indices[GetRandomValue(0, static_cast<int>(available_indices.size()) - 1)]);
    To_Be_Expanded.erase(To_Be_Expanded.begin());


    Position* next1 = current_node_ptr->neighbours[road1];
    TestMap::Road_List.push_back(current_node_ptr);
    TestMap::Road_List.push_back(next1);
    To_Be_Expanded.push_back(next1);
    current_node_ptr->Connected_Check = true;
    next1->Connected_Check = true;

    if (available_indices.size() >= 2)
    {
        do {
            road2 = static_cast<int>(available_indices[GetRandomValue(0, static_cast<int>(available_indices.size()) - 1)]);
        } while (road2 == road1); // repeat so we dont end up with 2 of the same

        Position* next2 = current_node_ptr->neighbours[road2];
        TestMap::Road_List.push_back(current_node_ptr);
        TestMap::Road_List.push_back(next2);
        To_Be_Expanded.push_back(next2);
        next2->Connected_Check = true;
    }
}
void TestMap::Generate_roads(const Position& Player_position) // Pass by const reference
{
    bool clockwise;
    bool end = false;


    for (int zone = 0; zone < 6; ++zone) {
        for (auto& rowPtr : Map[zone]) {
            for (Point& point : *rowPtr) {
                point.position.Connected_Check = false;
            }
        }
    }

    Road_List.clear();       // Clear previous road path data
    To_Be_Expanded.clear();  // Clear previous expansion list
    if (Player_position.Y_position == 0)
    {
        int target_zone = Player_position.zone > 0 ? Player_position.zone - 1 : 5;
        int target_x = ROWNUM;
        int target_y = NODENUM - Player_position.X_position;

        Position* starting_node_ptr = &Map[target_zone].at(target_x)->at(target_y).position;
        clockwise = true;
        To_Be_Expanded.push_back(starting_node_ptr);
    }
    else if (Player_position.X_position == ROWNUM)
    {
        int target_zone = Player_position.zone < 5 ? Player_position.zone + 1 : 0;
        int target_x = Player_position.X_position - Player_position.Y_position;
        int target_y = NODENUM - Player_position.X_position;

        Position* starting_node_ptr = &Map[target_zone].at(target_x)->at(target_y).position;
        clockwise = false;
        To_Be_Expanded.push_back(starting_node_ptr);
    }
    else
    {
        std::cout << "else" << std::endl;
        return;
    }


    while (!end)
    {
        Position* current_node_ptr = To_Be_Expanded.front();
        push_neighbours(*current_node_ptr);
        select_neighbours(current_node_ptr);


        for (Position* roads : Road_List)
        {
            if (!clockwise)
            {
                if (roads->X_position == ROWNUM) end = true;
            }
            else
            {
                if (roads->Y_position == 0) end = true;
            }
        }
    }

    for (int i = 0; i < Road_List.size() - 1; i += 2)
    {
        std::cout << "(" << Road_List.at(i)->X_position << "," << Road_List.at(i)->Y_position << ")  ";
        std::cout << "  (" << Road_List.at(i + 1)->X_position << "," << Road_List.at(i + 1)->Y_position << ")  ";
        std::cout << std::endl;
    }

    std::cout << "WARNING: Manual deletion required for all generated Position objects!" << std::endl;

}
void TestMap::drawMap(Vector2 startpoint, int zone)
{
    zone; //for unref param
    // change so we dont have to draw this all the time. it gets annoying
    for (std::vector<std::vector<Point>*> X : Map)
    {
        for (std::vector<Point>* Y : X)
        {
            for (int node = 0; node < Y->size(); node++)
            {
                int drawPosX = static_cast<int>(startpoint.x + (Y->at(node).position.X_position + Y->at(node).position.Y_position) * 50.0);
                int drawPosY = static_cast<int>(startpoint.y + (Y->at(node).position.X_position - Y->at(node).position.Y_position) * 50.0);

                DrawCircle(drawPosX, drawPosY, 10, WHITE);
            }
        }
    }

    for (int node = 0; node <= drawnRoadSegments; node += 2)
    {
        float drawPosX =   static_cast<float>(startpoint.x + (Road_List.at(node)->X_position + Road_List.at(node)->Y_position) * 50.0);
        float  drawPosY =  static_cast<float>(startpoint.y + (Road_List.at(node)->X_position - Road_List.at(node)->Y_position) * 50.0);
        float  drawPosX2 = static_cast<float>(startpoint.x + (Road_List.at(node + 1)->X_position + Road_List.at(node + 1)->Y_position) * 50.0);
        float  drawPosY2 = static_cast<float>(startpoint.y + (Road_List.at(node + 1)->X_position - Road_List.at(node + 1)->Y_position) * 50.0);

        DrawLineEx({ drawPosX, drawPosY }, { drawPosX2, drawPosY2 }, 6, RED);
    }
    for (int i = 0; i + 1 < Expressway_List.size(); i += 2)
    {
        Vector2 start = {
            startpoint.x + (Expressway_List[i]->X_position + Expressway_List[i]->Y_position) * 50.0f,
            startpoint.y + (Expressway_List[i]->X_position - Expressway_List[i]->Y_position) * 50.0f
        };
        Vector2 end = {
            startpoint.x + (Expressway_List[i + 1]->X_position + Expressway_List[i + 1]->Y_position) * 50.0f,
            startpoint.y + (Expressway_List[i + 1]->X_position - Expressway_List[i + 1]->Y_position) * 50.0f
        };

        DrawLineEx(start, end, 4.0f, BLUE);
    }
    DrawText(TextFormat("roadlist size: %d", Road_List.size()), 60, 10, 10, BLACK);
    DrawText(TextFormat("drawn segments: %d", drawnRoadSegments), 60, 20, 20, BLACK);
    DrawText(TextFormat("road : (%d, %d) to (%d, %d)", Road_List.at(drawnRoadSegments)->X_position, Road_List.at(drawnRoadSegments)->Y_position, Road_List.at(drawnRoadSegments + 1)->X_position, Road_List.at(drawnRoadSegments + 1)->Y_position), 60, 50, 50, BLACK);
    int drawPosX =  static_cast<int>(startpoint.x + (Road_List.at(drawnRoadSegments)->X_position + Road_List.at(drawnRoadSegments)->Y_position) * 50.0);
    int drawPosY =  static_cast<int>(startpoint.y + (Road_List.at(drawnRoadSegments)->X_position - Road_List.at(drawnRoadSegments)->Y_position) * 50.0);
    int drawPosX2 = static_cast<int>(startpoint.x + (Road_List.at(drawnRoadSegments + 1)->X_position + Road_List.at(drawnRoadSegments + 1)->Y_position) * 50.0);
    int drawPosY2 = static_cast<int>(startpoint.y + (Road_List.at(drawnRoadSegments + 1)->X_position - Road_List.at(drawnRoadSegments + 1)->Y_position) * 50.0);
    DrawText(TextFormat(" (%d, %d) to (%d, %d)", drawPosX, drawPosY, drawPosX2, drawPosY2), 60, 100, 50, BLACK);

}

void TestMap::Generate_Expressway1() {
    Expressway_List.clear();

    std::vector<Position*> coords = {
        &Map[0][4]->at(0).position,
        &Map[0][5]->at(1).position,
        &Map[0][5]->at(2).position,
        &Map[0][6]->at(3).position,
        &Map[0][7]->at(4).position,
        &Map[0][7]->at(5).position,
        &Map[0][7]->at(6).position
    };

    for (size_t i = 0; i < coords.size() - 1; ++i) {
        Expressway_List.push_back(coords[i]);
        Expressway_List.push_back(coords[i + 1]);
    }
}

void TestMap::Generate_Expressway2() {
    Expressway_List.clear();

    std::vector<Position*> coords = {
        &Map[1][4]->at(3).position,
        &Map[1][5]->at(2).position,
        &Map[1][6]->at(2).position,
        &Map[1][7]->at(2).position,
        &Map[1][8]->at(3).position,
        &Map[1][9]->at(3).position
    };

    for (size_t i = 0; i < coords.size() - 1; ++i) {
        Expressway_List.push_back(coords[i]);
        Expressway_List.push_back(coords[i + 1]);
    }
}

void TestMap::Generate_Expressway3() {
    Expressway_List.clear();

    std::vector<Position*> coords = {
        &Map[2][7]->at(0).position,
        &Map[2][7]->at(1).position,
        &Map[2][8]->at(2).position,
        &Map[1][7]->at(3).position,
        &Map[2][8]->at(5).position,
        &Map[2][7]->at(6).position
    };

    for (size_t i = 0; i < coords.size() - 1; ++i) {
        Expressway_List.push_back(coords[i]);
        Expressway_List.push_back(coords[i + 1]);
    }
}