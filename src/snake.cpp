#include <bits/stdc++.h>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <fstream>
using namespace std;

// 游戏配置结构体
struct GameConfig {
    bool randz = true;    // 是否随机生成障碍物
    int skin = 0;         // 配色方案
    int xl = 20, yl = 12; // 地图尺寸
    bool faster = true;   // 是否开启加速
    int setspeed = 25;    // 移动速度
    int highScore = 0;    // 最高分
};

// 游戏状态结构体
struct GameState {
    int len = 3;      // 蛇的长度
    int food = 1;     // 食物状态
    int d = 2;        // 当前方向
    COORD head;       // 蛇头坐标
    int room[32][22]; // 游戏地图
    int score = 0;    // 当前分数
};

GameConfig config;
GameState state;

// 修复宏定义，避免浮点数问题
#define getrand(a, b) (rand() % ((int)(b) - (int)(a) + 1) + (int)(a))

// 方向数组
int fangxiang[5][2] = { { 0, 0 },
                        { 0, -1 },
                        { 0, 1 },
                        { -1, 0 },
                        { 1, 0 } };

// 修复字符数组定义 - 增加数组大小
char peise[10][10] = { "简约", "蓝白", "红白", "绿白", "草地",
                       "科技", "随机", "混乱", "浪漫", "黑白" };
char YN[2][10] = { "否", "是" };

// 函数声明
void saveHighScore();
void loadHighScore();
int main();
void choose();
int gaming();
void printr();
bool checkr();
void checkr2(int, int);
void go(int, int);
void color(int);
void move();
void makefood();
bool goout(int, int);
int returnspeed();
void pdot();
void phead();
void pbody();
void pwall();
void pfood();
void pspace();
int showGameOver(); // 修复：改为返回int
void pauseGame();
void showScore();

// 保存和加载最高分
void saveHighScore() {
    ofstream file("snake_highscore.txt");
    if (file.is_open()) {
        file << config.highScore;
        file.close();
    }
}

void loadHighScore() {
    ifstream file("snake_highscore.txt");
    if (file.is_open()) {
        file >> config.highScore;
        file.close();
    }
}

int main() {
    system("chcp 65001");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // 加载最高分
    loadHighScore();

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &cursor_info
    );

    // 设置随机数种子
    unsigned seed = time(0);
    srand(seed);

    // 主菜单
    go(4, 4);
    pdot();
    color(240);
    printf("开始游戏");
    go(4, 7);
    pdot();
    color(15);
    printf("设置游戏");
    go(4, 10);
    pdot();
    color(15);
    printf("最高分: %d", config.highScore);

    int a = 0;
    int key = 0;
    while (key != 13) {
        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72 || key == 80) {
                a = (a == 0) ? 1 : 0;
                if (a == 0) {
                    go(4, 4);
                    pdot();
                    color(240);
                    printf("开始游戏");
                    go(4, 7);
                    pdot();
                    color(15);
                    printf("设置游戏");
                } else {
                    go(4, 4);
                    pdot();
                    color(15);
                    printf("开始游戏");
                    go(4, 7);
                    pdot();
                    color(240);
                    printf("设置游戏");
                }
            }
        }
    }

    if (a) {
        choose();
        return 0;
    }

    while (true) {
        int result = gaming();
        if (result == 1) {
            system("cls");
            system("color 0F");
            main();
            return 0;
        }
    }

    return 0;
}

void go(int x, int y) {
    COORD coord;
    coord.X = x * 2;
    coord.Y = y + 1;
    HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, coord);
}

void choose() {
    system("cls");
    system("color 0F");
    color(15);

    go(3, 2);
    printf("地图长度");
    go(3, 3);
    printf("地图宽度");
    go(3, 4);
    printf("移动速度");
    go(3, 5);
    printf("是否随机生成障碍物");
    go(3, 6);
    printf("是否开启长按加速功能");
    go(3, 7);
    printf("配色");

    color(240);
    go(14, 2);
    printf(" <%d> ", config.xl);
    color(15);
    go(14, 3);
    printf(" <%d>", config.yl);
    go(14, 4);
    printf(" <%d>", returnspeed());
    go(14, 5);
    printf(" <%s>", YN[config.randz]);
    go(14, 6);
    printf(" <%s>", YN[config.faster]);
    go(14, 7);
    printf(" <%s>", peise[config.skin]);

    int a = 1;
    int key = 0;
    go(1, 1 + a);
    printf(">>");

    while (key != 27) {
        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72 || key == 80) {
                // 清除当前选项的标记
                go(1, 1 + a);
                printf("  ");

                if (key == 72 && a > 1)
                    a--;
                if (key == 80 && a < 6)
                    a++;

                // 更新选项显示
                go(1, 1 + a);
                printf(">>");
            } else if (key == 75 || key == 77) {
                // 修改设置
                switch (a) {
                    case 1:
                        if (key == 75 && config.xl > 8)
                            config.xl--;
                        if (key == 77 && config.xl < 30)
                            config.xl++;
                        break;
                    case 2:
                        if (key == 75 && config.yl > 8)
                            config.yl--;
                        if (key == 77 && config.yl < 20)
                            config.yl++;
                        break;
                    case 3:
                        if (key == 75 && config.setspeed < 50)
                            config.setspeed += 5;
                        if (key == 77 && config.setspeed > 10)
                            config.setspeed -= 5;
                        break;
                    case 4:
                        config.randz = !config.randz;
                        break;
                    case 5:
                        config.faster = !config.faster;
                        break;
                    case 6:
                        if (key == 75)
                            config.skin = (config.skin - 1 + 10) % 10;
                        if (key == 77)
                            config.skin = (config.skin + 1) % 10;
                        break;
                }

                // 更新显示
                go(14, 2);
                color(240);
                printf(" <%d> ", config.xl);
                go(14, 3);
                color(240);
                printf(" <%d> ", config.yl);
                go(14, 4);
                color(240);
                printf(" <%d> ", returnspeed());
                go(14, 5);
                color(240);
                printf(" <%s> ", YN[config.randz]);
                go(14, 6);
                color(240);
                printf(" <%s> ", YN[config.faster]);
                go(14, 7);
                color(240);
                printf(" <%s> ", peise[config.skin]);
            }
        }
    }

    system("cls");
    system("color 0F");
    main();
}

int gaming() {
    system("cls");
    system("color 0F");

    // 初始化游戏状态
    state.len = 3;
    state.score = 0;

    // 初始化地图
    for (int i = 0; i <= config.xl + 1; i++) {
        for (int j = 0; j <= config.yl + 1; j++) {
            if (i == 0 || j == 0 || i == config.xl + 1
                || j == config.yl + 1) {
                state.room[i][j] = -1;
            } else {
                state.room[i][j] = 0;
            }
        }
    }

    // 生成随机障碍物
    if (config.randz) {
        do {
            for (int i = 1; i <= config.xl; i++) {
                for (int j = 1; j <= config.yl; j++) {
                    state.room[i][j] = 0;
                }
            }

            int jj = getrand(2, 4) - 1;
            for (int j = jj; j <= config.yl; j += getrand(1, 3)) {
                int ii = getrand(1, config.xl - 1);
                // 修复：避免浮点数，使用整数运算
                int iii = getrand(2, max(2, config.xl / 2));
                for (int i = ii; i <= min(ii + iii, config.xl); i++) {
                    state.room[i][j] = -1;
                }
            }
        } while (!checkr());
    }

    printr();
    makefood();

    state.d = -5;
    int speed = config.setspeed;

    // 显示游戏信息
    go(config.xl * 0.6, -1);
    color(7);
    printf("速度：%d", returnspeed());
    showScore();

    // 初始化蛇头位置
    do {
        state.head.X = getrand(1, config.xl);
        state.head.Y = getrand(1, config.yl);
    } while (state.room[state.head.X][state.head.Y] == -1);

    state.room[state.head.X][state.head.Y] = state.len;
    go(state.head.X, state.head.Y);
    phead();

    // 等待第一次按键
    while (!kbhit()) {
        Sleep(50);
    }

    int key = 0;
    int ld = state.d;
    bool p = false, ped = false;

    while (true) {
        key = 0;
        ld = state.d;
        p = false;

        // 检测按键
        for (int i = 1; i <= speed; i++) {
            if (kbhit() && !p) {
                p = true;
                key = getch();
                if (key == 224) {
                    key = getch();
                    switch (key) {
                        case 72:
                            state.d = 1;
                            break; // 上
                        case 80:
                            state.d = 2;
                            break; // 下
                        case 75:
                            state.d = 3;
                            break; // 左
                        case 77:
                            state.d = 4;
                            break; // 右
                    }
                } else if (key == 32) { // 空格键暂停
                    pauseGame();
                }
            }
            Sleep(5);
        }

        // 方向冲突检查
        if (ld != state.d
            && (ld + state.d == 3 || ld + state.d == 7)) {
            state.d = ld;
        }

        // 加速功能
        if (!p)
            ped = true;
        if (ld != state.d)
            ped = false;

        if (p && ped && ld == state.d && config.faster) {
            speed = config.setspeed / 1.5;
            go(config.xl * 0.6, -1);
            color(15);
            printf("加速中~~");
        } else {
            speed = config.setspeed;
            go(config.xl * 0.6, -1);
            color(7);
            printf("速度：%d  ", returnspeed());
        }

        // 移动蛇
        move();

        // 检查游戏结束
        if (state.room[state.head.X][state.head.Y] != state.len) {
            return showGameOver();
        }

        // 生成新食物
        if (state.food == 0) {
            makefood();
        }
    }
}

bool checkr() {
    int flag = 0;
    for (int i = 1; i <= config.xl; i++) {
        for (int j = 1; j <= config.yl; j++) {
            if (state.room[i][j] == 0) {
                flag = 0;
                if (state.room[i + 1][j] == 0)
                    flag++;
                if (state.room[i - 1][j] == 0)
                    flag++;
                if (state.room[i][j + 1] == 0)
                    flag++;
                if (state.room[i][j - 1] == 0)
                    flag++;
                if (flag < 2)
                    return false;
            }
        }
    }

    if (state.room[1][1] == 0)
        checkr2(1, 1);
    else if (state.room[1][2] == 0)
        checkr2(1, 2);

    for (int i = 1; i <= config.xl; i++) {
        for (int j = 1; j <= config.yl; j++) {
            if (state.room[i][j] == 0)
                return false;
            else if (state.room[i][j] == -3)
                state.room[i][j] = 0;
        }
    }

    return true;
}

void checkr2(int x, int y) {
    if (state.room[x][y] == 0) {
        state.room[x][y] = -3;
        if (x > 1)
            checkr2(x - 1, y);
        if (x < config.xl)
            checkr2(x + 1, y);
        if (y > 1)
            checkr2(x, y - 1);
        if (y < config.yl)
            checkr2(x, y + 1);
    }
}

void printr() {
    for (int i = 0; i <= config.xl + 1; i++) {
        for (int j = 0; j <= config.yl + 1; j++) {
            if (state.room[i][j] == -1) {
                go(i, j);
                pwall();
            }
        }
    }
}

bool goout(int x, int y) {
    return (x >= 1 && y >= 1 && x <= config.xl && y <= config.yl);
}

void move() {
    state.head.X += fangxiang[state.d][0];
    state.head.Y += fangxiang[state.d][1];

    // 检查碰撞
    if (state.room[state.head.X][state.head.Y] != 0
        && state.room[state.head.X][state.head.Y] != -2) {
        return;
    }

    // 吃食物
    if (state.room[state.head.X][state.head.Y] == -2) {
        state.len++;
        state.score = state.len - 3;
        state.food = 0;
        showScore();

        // 更新最高分
        if (state.score > config.highScore) {
            config.highScore = state.score;
            saveHighScore();
        }
    }

    // 移动蛇身
    for (int i = 1; i <= config.xl + 1; i++) {
        for (int j = 1; j <= config.yl + 1; j++) {
            if (state.room[i][j] >= 1) {
                if (state.room[state.head.X][state.head.Y] != -2) {
                    state.room[i][j]--;
                    if (state.room[i][j] == 0) {
                        go(i, j);
                        pspace();
                    }
                }
                if (state.room[i][j] == state.len - 1) {
                    go(i, j);
                    pbody();
                }
            }
        }
    }

    state.room[state.head.X][state.head.Y] = state.len;
    go(state.head.X, state.head.Y);
    phead();
}

void makefood() {
    int attempts = 0;
    int maxAttempts = config.xl * config.yl;

    while (attempts < maxAttempts) {
        int randx = getrand(1, config.xl);
        int randy = getrand(1, config.yl);

        if (state.room[randx][randy] == 0) {
            state.room[randx][randy] = -2;
            go(randx, randy);
            pfood();
            state.food = 1;
            return;
        }
        attempts++;
    }

    // 如果找不到空位，设置食物状态为存在防止无限循环
    state.food = 1;
}

void color(int a) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void phead() {
    switch (config.skin) {
        case 0:
            color(15);
            printf("□");
            break;
        case 1:
            color(63);
            printf("■");
            break;
        case 2:
            color(79);
            printf("■");
            break;
        case 3:
            color(175);
            printf("■");
            break;
        case 4:
            color(175);
            printf("■");
            break;
        case 5:
            color(159);
            printf("■");
            break;
        case 6:
            color(getrand(2, 15) * 16 - 1);
            printf("■");
            break;
        case 7:
            color(getrand(0, 255));
            printf("■");
            break;
        case 8:
            color(79);
            printf("■");
            break;
        case 9:
            color(120);
            printf("■");
            break;
    }
}

void pbody() {
    switch (config.skin) {
        case 0:
            color(15);
            printf("□");
            break;
        case 1:
            color(159);
            printf("■");
            break;
        case 2:
            color(79);
            printf("■");
            break;
        case 3:
            color(175);
            printf("■");
            break;
        case 4:
            color(175);
            printf("■");
            break;
        case 5:
            color(159);
            printf("■");
            break;
        case 6:
            color(getrand(2, 16) * 16 - 1);
            printf("■");
            break;
        case 7:
            color(getrand(0, 255));
            printf("■");
            break;
        case 8:
            color(79);
            printf("■");
            break;
        case 9:
            color(120);
            printf("■");
            break;
    }
}

void pwall() {
    switch (config.skin) {
        case 0:
            color(15);
            break;
        case 1:
            color(143);
            break;
        case 2:
            color(143);
            break;
        case 3:
            color(143);
            break;
        case 4:
            color(42);
            break;
        case 5:
            color(25);
            break;
        case 6:
            color(getrand(2, 16) * 16 - 1);
            break;
        case 7:
            color(getrand(0, 255));
            break;
        case 8:
            color(76);
            break;
        case 9:
            color(127);
            break;
    }
    printf("■");
}

void pfood() {
    switch (config.skin) {
        case 0:
            color(15);
            break;
        case 1:
            color(9);
            break;
        case 2:
            color(12);
            break;
        case 3:
            color(10);
            break;
        case 4:
            color(4);
            break;
        case 5:
            color(3);
            break;
        case 6:
            color(getrand(1, 15));
            break;
        case 7:
            color(getrand(0, 255));
            break;
        case 8:
            color(4);
            break;
        case 9:
            color(15);
            break;
    }
    printf("●");
}

void pspace() {
    color(0);
    printf("  "); // 使用两个空格清空
}

int returnspeed() {
    return (60 - config.setspeed);
}

void pdot() {
    color(15);
    printf("·");
}

void showScore() {
    go(config.xl * 0.2, -1);
    color(15);
    printf("得分: %d  最高分: %d", state.score, config.highScore);
}

void pauseGame() {
    go(config.xl / 2, config.yl / 2);
    color(79);
    printf("游戏暂停");
    go(config.xl / 2, config.yl / 2 + 1);
    printf("按任意键继续");
    getch();
    go(config.xl / 2, config.yl / 2);
    printf("          ");
    go(config.xl / 2, config.yl / 2 + 1);
    printf("              ");
}

int showGameOver() {
    go(0, config.yl + 2);
    color(79);
    printf("游戏结束！得分: %d", state.score);
    go(0, config.yl + 3);
    printf("最高分: %d", config.highScore);
    go(0, config.yl + 5);
    pdot();
    color(240);
    printf("再来一次");
    go(0, config.yl + 6);
    pdot();
    color(15);
    printf("返回主界面");

    int key = 0;
    int a = 0;

    while (key != 13) {
        key = getch();
        if (key == 224) {
            key = getch();
            if (key == 72 || key == 80) {
                a = 1 - a;
                if (a == 0) {
                    go(0, config.yl + 5);
                    pdot();
                    color(240);
                    printf("再来一次");
                    go(0, config.yl + 6);
                    pdot();
                    color(15);
                    printf("返回主界面");
                } else {
                    go(0, config.yl + 5);
                    pdot();
                    color(15);
                    printf("再来一次");
                    go(0, config.yl + 6);
                    pdot();
                    color(240);
                    printf("返回主界面");
                }
            }
        }
    }

    return a;
}