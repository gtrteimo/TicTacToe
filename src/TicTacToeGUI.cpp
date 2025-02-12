#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

class TicTacToeGUI {
public:
    TicTacToeGUI();
    ~TicTacToeGUI();
    void run();
private:
    GLFWwindow* window;
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;
    void initWindow();
    void initGL();
    void setupShaders();
    void setupGeometry();
    void processInput();
};

unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::exit(-1);
    }
    return shader;
}

TicTacToeGUI::TicTacToeGUI() : window(nullptr), shaderProgram(0), VAO(0), VBO(0), EBO(0) {
    initWindow();
    initGL();
    setupShaders();
    setupGeometry();
}

TicTacToeGUI::~TicTacToeGUI() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void TicTacToeGUI::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(800, 600, "Red Square", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::exit(-1);
    }
    glfwMakeContextCurrent(window);
}

void TicTacToeGUI::initGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::exit(-1);
    }
    glViewport(0, 0, 800, 600);
}

void TicTacToeGUI::setupShaders() {
    const char* vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nvoid main(){gl_Position=vec4(aPos,1.0);}";
    const char* fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\nvoid main(){FragColor=vec4(1.0,0.0,0.0,1.0);}";
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        std::exit(-1);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void TicTacToeGUI::setupGeometry() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void TicTacToeGUI::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void TicTacToeGUI::run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    TicTacToeGUI app;
    app.run();
    return 0;
}
