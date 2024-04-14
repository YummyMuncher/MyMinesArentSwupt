#include <imgui.h>
#include <cstdlib>
#include <new>
using namespace ImGui;
namespace Minesweep {
    int size = 9;
    int size2 = 9;

    //Makes the general board with a nothrow so it can be dynamic and compile time
    int** board = new (std::nothrow) int* [size];

    void initializeBoard(int s, int s2) {
        bool cont = true;
        size = s;
        size2 = s2;

        //if to check validity of board
        if (board == nullptr) {
            Text("KILL THE WORLD AHHH");
            cont = false;
        }

        for (int i = 0; i < size2; i++) {
            //make the pointer in the array of pointers to arrays so thte array can point to the next array
            board[i] = new (std::nothrow) int[size2];
            //null pointer checker again
            if (board[i] == nullptr) {
                Text("AHHHHH");
            }
        }

        SeparatorText("");
        BeginGroup();
        Text("");
        //Set everything to 0
        for (int i = 0; i < size; i++) {
            for (int j = 0; i < size2; i++) {
                board[i][j] = 0;
                SameLine(0.0f, 1.0f);
                Button("  ");
                SameLine(0.0f, -1.0f);
                Text("6");
            }
        }
        EndGroup();
    }


    void populateBoard(int bombs) {
        int placedBombs = 0;
        while (placedBombs < bombs) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; i < size2; i++) {

                    if (std::rand() % bombs + 1 == 1) {
                        board[i][j] = 1;
                        placedBombs += 1;
                    }

                }
            }
        }
    }

    void destroyBoard() {
        for (int i = 0; i < size2; i++) {
            //make the pointer in the array of pointers to arrays so thte array can point to the next array
            board[i] = nullptr;
            //null pointer checker again
            if (board[i] == nullptr) {
                Text("bye bye" + i);
            }
        }
    
    }

    void StarterUp() {
        static int slide1 = 9;
        static int slide2 = 9;
        bool inited = false;
        Begin("Mine Sweeper :)");

        if (TreeNode("Settings")) {
            SetNextItemOpen(true, ImGuiCond_Once);
            SliderInt("Height", &slide1, 9, 30);
            SliderInt("Width", &slide2, 9, 40);
            TreePop();
        }


        initializeBoard(slide1, slide2);

        if (Button("Destroy")) {
            destroyBoard();
        }
        
        ShowDemoWindow();
        End();
        
        
        
    }
}
