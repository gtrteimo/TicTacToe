#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <iostream>

class TicTacToeGUI {
    private:
        uint16_t width = 720, height = 720;
        GLFWwindow* window = nullptr;
    public:    
        TicTacToeGUI();
        TicTacToeGUI(); 
    private:
        void displaLoop();
        
        
};