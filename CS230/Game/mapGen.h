#include <vector>
#include <raylib.h>


class TestMap {
public:
    struct Position { //when you delete a position please please please delete neighbours as well as they arent needed

        int zone;
        int X_position;
        int Y_position;
        int nodes_in_neighbour = 0;
        Position* neighbours[6] = { };
        Position* connectedRoads[6] = {};
        Position* parent = nullptr;
        bool Connected_Check = false;
    };
    struct Road
    {


    };
    struct Point
    {
        int value;
        Position position;
        Position* parent = nullptr;

        enum Events
        {
            nothing, Gas, Money, Humanity, misc
        }Event;

    };

    static inline int drawnRoadSegments = 0;
    static inline int awd = 0;
    static void Initialize_Map();
    static void TestDrawMap();
    static void TestDrawMap2();
    static void push_neighbours(Position& node_position);
    static void select_neighbours(Position* current_node_ptr);

    static inline std::vector<std::vector<Point>*> Map[6] = {};
    static inline std::vector<Point> Map_info[6] = {}; // information about points.
    static inline std::vector<Position*> Road_List; // information about points.
    static inline std::vector<Position*> To_Be_Expanded;
    static void Generate_roads(const Position& Player_position);
    //static void Populate_zone(int zone);

    static void drawMap(Vector2 startPoint, int zone);

};