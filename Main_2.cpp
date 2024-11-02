// 本程序针对Windows环境开发（conio.h）
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

long long map_x = 10, map_y = 10;
int y = 1, x = 1; // 玩家起始位置
char ch;

// 地图数组
char map[1000][1001]; // 加1以便于存储 '\0'

char *Clear()
{
#ifdef __DEBUG__
    printf("\n\n\n\n");
    return "Debug,No Clear";
#endif

#ifdef _WIN32
    system("cls");
    return "Windows";
#elif __linux__
    system("clear");
    return "Linux";
#elif __unix__
    system("clear");
    return "UNIX";
#elif __APPLE__
    system("clear");
    return "Apple";
#else
    // ANSI
    printf("\033[2J");
    return "Other";
#endif
}

// 随机填充地图
void generate_Map()
{
    Clear();
    std::cout << "Generating map..." << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::srand(static_cast<unsigned int>(std::time(NULL))); // 用当前时间作为随机种子
    for (int i = 0; i < map_x; i++)
    {
        for (int j = 0; j < map_y; j++)
        {
            if (i == 0 || i == map_x - 1 || j == 0 || j == map_y - 1)
            {
                map[i][j] = '#'; // 边界
            }
            else
            {
                map[i][j] = (std::rand() % 4 == 0) ? '#' : ' '; // 约25%概率为墙壁
            }
        }
        map[i][map_y] = '\0'; // 结束字符
    }

    // 随机生成玩家的起始位置，并确保该位置不被墙壁覆盖
    do
    {
        x = std::rand() % (map_x - 2) + 1; // 限制范围在 1 到 map_x-2
        y = std::rand() % (map_y - 2) + 1; // 限制范围在 1 到 map_y-2
    } while (map[x][y] == '#' || (x == 1 && y == 1)); // 重新选择直到选中有效位置

    map[x][y] = 'O'; // 玩家起始位置

    // 随机生成终点位置
    int end_x, end_y;
    do
    {
        end_x = std::rand() % (map_x - 2) + 1;
        end_y = std::rand() % (map_y - 2) + 1;
    } while (map[end_x][end_y] == '#' || (end_x == x && end_y == y)); // 确保终点不在墙上或玩家位置

    map[end_x][end_y] = '*'; // 终点
    std::cout << "Player position: x=" << x << " y=" << y << std::endl;
    std::cout << "End position: x=" << end_x << " y=" << end_y << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    Clear();
}

// 打印地图
void print_Map()
{
    for (int i = 0; i < map_x; i++)
    {
        puts(map[i]);
    }
}

// void parseMapSize(const std::string& input) {
//     std::istringstream iss(input);
//     std::string key;
//     while (iss >> key) {
//         if (key.find("map_x=") == 0) {
//             map_x = std::stoi(key.substr(6)); // 提取后面的数字并转换为整数
//         }
//         else if (key.find("map_y=") == 0) {
//             map_y = std::stoi(key.substr(6)); // 提取后面的数字并转换为整数
//         }
//     }
// }

// 主程序
int main()
{
    // 传参进主函数，是随机地图的长和宽
    // 取出字符串中的数字，并赋值给map_x和map_y
    //"map_x=10 map_y=10"
    // 那么map_x
    //// parseMapSize(argv);
    std::cout << "W=Up, A=Left, S=Down, D=Right, E=Regenerate map,Q=Exit,I=Sitting" << std::endl;
    _getch();
    _getch();
    char w = 38, a = 39, s = 40, d = 39;
MainProgram:

    Clear();
    generate_Map(); // 生成随机地图
    int c = 0, e = 0, longSteap = map_y + map_x;
    print_Map();

    while (true)
    {
        ch = _getch();
        ++c;
        if (e >= 3)
        {
            Clear();
            std::cout << "Game Over! (:\nToo many restarts\nThis game is exiting..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "God-bye! （*＾-＾*）";
            return 0;
            // 重来次数过多
        }
        if (c > longSteap)
        {
            Clear();
            // 游戏步数过多
            std::cout << "Game over! \nGame steaps over " << longSteap << ". \nPlease restart the game." << std::endl;
            _getch();
            c = 0;
            // return 0;
            e++;
            goto MainProgram;
            // 请重新开始游戏
        }
        if (ch == 'q' || ch == 'Q')
        {
            std::cout << "Exiting game..." << std::endl;
            // 暂停一下
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 0;
        }
        if (ch == 'I' || ch == 'i')
        {
            Clear();
            printf("now map_x=%d map_y=%d\n", map_x, map_y);
            printf("Now you are sitting.(map_x>1,and this<999 or map_y>1,and this<998)\n");
            printf("map_x=");
            // scanf("%d",&map_x);
            std::cin >> map_x;
            printf("map_y=");
            // scanf("%d",&map_y);
            std::cin >> map_y;
            printf("Now map_x=%d map_y=%d\n", map_x, map_y);
            _getch();
            Clear();
            goto MainProgram;
            // 修改地图大小
        }
        // 玩家移动逻辑
        if (ch == 'w' || ch == 'W' || ch == w)
        { // 向上
            if (x > 1 && map[x - 1][y] != '#' && map[x - 1][y] != '*')
            {
                map[x][y] = ' ';
                x--;
                map[x][y] = 'O';
            }
            else if (map[x - 1][y] == '*')
                break;
        }
        else if (ch == 'a' || ch == 'A' || ch == a)
        { // 向左
            if (y > 1 && map[x][y - 1] != '#' && map[x][y - 1] != '*')
            {
                map[x][y] = ' ';
                y--;
                map[x][y] = 'O';
            }
            else if (map[x][y - 1] == '*')
                break;
        }
        else if (ch == 's' || ch == 'S' || ch == s)
        { // 向下
            if (x < map_x - 2 && map[x + 1][y] != '#' && map[x + 1][y] != '*')
            {
                map[x][y] = ' ';
                x++;
                map[x][y] = 'O';
            }
            else if (map[x + 1][y] == '*')
                break;
        }
        else if (ch == 'd' || ch == 'D' || ch == d)
        { // 向右
            if (y < map_y - 1 && map[x][y + 1] != '#' && map[x][y + 1] != '*')
            {
                map[x][y] = ' ';
                y++;
                map[x][y] = 'O';
            }
            else if (map[x][y + 1] == '*')
                break;
        }
        else if (ch == 'e' || ch == 'E')
        {
            goto MainProgram;
        }

        // 清屏并打印地图
        Clear();
        print_Map();
    }
    Clear();
    // 玩家胜利
    printf("You Win!");
    _getch();
    goto MainProgram;
    return 0;
}
