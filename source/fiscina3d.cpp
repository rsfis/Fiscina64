#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <filesystem>
#include <fstream>
#include <thread>
#include <mutex>

#define GLM_ENABLE_EXPERIMENTAL
#include "dependencies/glad/glad.h"
#include "dependencies/GLFW/glfw3.h"
#include "dependencies/glm/glm.hpp"
#include "dependencies/glm/gtc/matrix_transform.hpp"
#include "dependencies/glm/gtc/type_ptr.hpp"
#include "dependencies/glm/gtx/quaternion.hpp"
#include "dependencies/glm/gtx/euler_angles.hpp"

#include "dependencies/stb/stb_image.h"

#include "dependencies/fmod/inc/fmod.hpp"
#include "dependencies/fmod/inc/fmod_errors.h"

#include "dependencies/ft2build.h"
#include "dependencies/freetype/freetype.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "dependencies/tinygltf/tiny_gltf.h"

#include "dependencies/vlc/vlc.h"
#include "dependencies/vlc/libvlc.h"

#include "dependencies/bullet/btBulletDynamicsCommon.h"
#include "dependencies/bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"
#include "dependencies/bullet/BulletCollision/Gimpact/btGImpactShape.h"
#include "dependencies/bullet/BulletDynamics/Vehicle/btRaycastVehicle.h"

#define     PI 3.14159265358979323846f
#define 	KEY_SPACE   32
#define 	KEY_APOSTROPHE   39 /* ' */
#define 	KEY_COMMA   44 /* , */
#define 	KEY_MINUS   45 /* - */
#define 	KEY_PERIOD   46 /* . */
#define 	KEY_SLASH   47 /* / */
#define 	KEY_0   48
#define 	KEY_1   49
#define 	KEY_2   50
#define 	KEY_3   51
#define 	KEY_4   52
#define 	KEY_5   53
#define 	KEY_6   54
#define 	KEY_7   55
#define 	KEY_8   56
#define 	KEY_9   57
#define 	KEY_SEMICOLON   59 /* ; */
#define 	KEY_EQUAL   61 /* = */
#define 	KEY_A   65
#define 	KEY_B   66
#define 	KEY_C   67
#define 	KEY_D   68
#define 	KEY_E   69
#define 	KEY_F   70
#define 	KEY_G   71
#define 	KEY_H   72
#define 	KEY_I   73
#define 	KEY_J   74
#define 	KEY_K   75
#define 	KEY_L   76
#define 	KEY_M   77
#define 	KEY_N   78
#define 	KEY_O   79
#define 	KEY_P   80
#define 	KEY_Q   81
#define 	KEY_R   82
#define 	KEY_S   83
#define 	KEY_T   84
#define 	KEY_U   85
#define 	KEY_V   86
#define 	KEY_W   87
#define 	KEY_X   88
#define 	KEY_Y   89
#define 	KEY_Z   90
#define 	KEY_LEFT_BRACKET   91 /* [ */
#define 	KEY_BACKSLASH   92 /* \ */
#define 	KEY_RIGHT_BRACKET   93 /* ] */
#define 	KEY_GRAVE_ACCENT   96 /* ` */
#define 	KEY_WORLD_1   161 /* non-US #1 */
#define 	KEY_WORLD_2   162 /* non-US #2 */
#define 	KEY_ESCAPE   256
#define 	KEY_ENTER   257
#define 	KEY_TAB   258
#define 	KEY_BACKSPACE   259
#define 	KEY_INSERT   260
#define 	KEY_DELETE   261
#define 	KEY_RIGHT   262
#define 	KEY_LEFT   263
#define 	KEY_DOWN   264
#define 	KEY_UP   265
#define 	KEY_PAGE_UP   266
#define 	KEY_PAGE_DOWN   267
#define 	KEY_HOME   268
#define 	KEY_END   269
#define 	KEY_CAPS_LOCK   280
#define 	KEY_SCROLL_LOCK   281
#define 	KEY_NUM_LOCK   282
#define 	KEY_PRINT_SCREEN   283
#define 	KEY_PAUSE   284
#define 	KEY_F1   290
#define 	KEY_F2   291
#define 	KEY_F3   292
#define 	KEY_F4   293
#define 	KEY_F5   294
#define 	KEY_F6   295
#define 	KEY_F7   296
#define 	KEY_F8   297
#define 	KEY_F9   298
#define 	KEY_F10   299
#define 	KEY_F11   300
#define 	KEY_F12   301
#define 	KEY_F13   302
#define 	KEY_F14   303
#define 	KEY_F15   304
#define 	KEY_F16   305
#define 	KEY_F17   306
#define 	KEY_F18   307
#define 	KEY_F19   308
#define 	KEY_F20   309
#define 	KEY_F21   310
#define 	KEY_F22   311
#define 	KEY_F23   312
#define 	KEY_F24   313
#define 	KEY_F25   314
#define 	KEY_KP_0   320
#define 	KEY_KP_1   321
#define 	KEY_KP_2   322
#define 	KEY_KP_3   323
#define 	KEY_KP_4   324
#define 	KEY_KP_5   325
#define 	KEY_KP_6   326
#define 	KEY_KP_7   327
#define 	KEY_KP_8   328
#define 	KEY_KP_9   329
#define 	KEY_KP_DECIMAL   330
#define 	KEY_KP_DIVIDE   331
#define 	KEY_KP_MULTIPLY   332
#define 	KEY_KP_SUBTRACT   333
#define 	KEY_KP_ADD   334
#define 	KEY_KP_ENTER   335
#define 	KEY_KP_EQUAL   336
#define 	KEY_LEFT_SHIFT   340
#define 	KEY_LEFT_CONTROL   341
#define 	KEY_LEFT_ALT   342
#define 	KEY_LEFT_SUPER   343
#define 	KEY_RIGHT_SHIFT   344
#define 	KEY_RIGHT_CONTROL   345
#define 	KEY_RIGHT_ALT   346
#define 	KEY_RIGHT_SUPER   347
#define 	KEY_MENU   348

#define     MOUSE_BUTTON_1   0
#define     MOUSE_BUTTON_2   1
#define     MOUSE_BUTTON_3   2
#define	    MOUSE_BUTTON_4   3
#define     MOUSE_BUTTON_5   4
#define     MOUSE_BUTTON_6   5
#define     MOUSE_BUTTON_7   6
#define     MOUSE_BUTTON_8   7
#define     MOUSE_BUTTON_LAST   MOUSE_BUTTON_8
#define     MOUSE_BUTTON_LEFT   MOUSE_BUTTON_1
#define     MOUSE_BUTTON_RIGHT  MOUSE_BUTTON_2
#define     MOUSE_BUTTON_MIDDLE MOUSE_BUTTON_3

#define VERSION "1.0.0"
#define PROJECT_NAME "Fiscina3D"
#define CURRENT_MONITOR 0
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// GLOBALS
float lastX = 640, lastY = 360;
bool firstMouse = true;
float deltaTime = 0.0f, lastFrame = 0.0f;

GLuint staticModelShader;
GLuint skinnedModelShader;
GLuint imageShader;
GLuint textShader;
GLuint videoShader;
GLuint physicsdebugShader;
GLuint image3Dshader;

struct Vector2 {
    float x, y;
    Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}

    Vector2 operator+(const Vector2& other) const { return Vector2(x + other.x, y + other.y); }
    Vector2 operator-(const Vector2& other) const { return Vector2(x - other.x, y - other.y); }

    Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }
    Vector2 operator/(float scalar) const { return Vector2(x / scalar, y / scalar); }

    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
    Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    float dot(const Vector2& o) const {
        return x * o.x + y * o.y;
    }

    float cross(const Vector2& o) const {
        return x * o.y - y * o.x;
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    float lengthSquared() const {
        return x * x + y * y;
    }

    Vector2 normalized() const {
        float len = length();
        return (len > 0) ? (*this / len) : Vector2();
    }

    float distance(const Vector2& o) const {
        return (*this - o).length();
    }

    static Vector2 lerp(const Vector2& a, const Vector2& b, float t) {
        return a + (b - a) * t;
    }

    Vector2 perpendicular() const {
        return Vector2(-y, x);
    }

    Vector2 reflect(const Vector2& normal) const {
        return *this - normal * (2.0f * this->dot(normal));
    }

    Vector2 project(const Vector2& onNormal) const {
        Vector2 n = onNormal.normalized();
        return n * (this->dot(n));
    }

    Vector2 reject(const Vector2& onNormal) const {
        return *this - project(onNormal);
    }
};

struct Vector3 {
    float x, y, z;
    Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

    Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
    Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }

    Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
    Vector3 operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }

    Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
    Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
    Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    Vector3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    float dot(const Vector3& o) const {
        return x * o.x + y * o.y + z * o.z;
    }

    Vector3 cross(const Vector3& o) const {
        return Vector3(
            y * o.z - z * o.y,
            z * o.x - x * o.z,
            x * o.y - y * o.x
        );
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    float lengthSquared() const {
        return x * x + y * y + z * z;
    }

    Vector3 normalized() const {
        float len = length();
        return (len > 0) ? (*this / len) : Vector3();
    }

    float distance(const Vector3& o) const {
        return (*this - o).length();
    }

    static Vector3 lerp(const Vector3& a, const Vector3& b, float t) {
        return a + (b - a) * t;
    }

    Vector3 reflect(const Vector3& normal) const {
        return *this - normal * (2.0f * this->dot(normal));
    }

    Vector3 project(const Vector3& onNormal) const {
        Vector3 n = onNormal.normalized();
        return n * (this->dot(n));
    }

    Vector3 reject(const Vector3& onNormal) const {
        return *this - project(onNormal);
    }
};

struct Vector4 {
    float x, y, z, w;
    Vector4(float _x = 0, float _y = 0, float _z = 0, float _w = 0)
        : x(_x), y(_y), z(_z), w(_w) {
    }

    Vector4 operator+(const Vector4& o) const { return Vector4(x + o.x, y + o.y, z + o.z, w + o.w); }
    Vector4 operator-(const Vector4& o) const { return Vector4(x - o.x, y - o.y, z - o.z, w - o.w); }
    Vector4 operator*(float s) const { return Vector4(x * s, y * s, z * s, w * s); }
    Vector4 operator/(float s) const { return Vector4(x / s, y / s, z / s, w / s); }

    Vector4& operator+=(const Vector4& o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
    Vector4& operator-=(const Vector4& o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
    Vector4& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
    Vector4& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }

    bool operator==(const Vector4& o) const { return x == o.x && y == o.y && z == o.z && w == o.w; }
    bool operator!=(const Vector4& o) const { return !(*this == o); }

    float dot(const Vector4& o) const {
        return x * o.x + y * o.y + z * o.z + w * o.w;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    float lengthSquared() const {
        return x * x + y * y + z * z + w * w;
    }

    Vector4 normalized() const {
        float len = length();
        return (len > 0) ? (*this / len) : Vector4();
    }

    float distance(const Vector4& o) const {
        return (*this - o).length();
    }

    static Vector4 lerp(const Vector4& a, const Vector4& b, float t) {
        return a + (b - a) * t;
    }

    Vector4 homogenized() const {
        return (w != 0.0f) ? Vector4(x / w, y / w, z / w, 1.0f) : *this;
    }
};

// =================== Shader Loader ===================
GLuint LoadShader(const char* vertexSrc, const char* fragmentSrc);

// =================== File System ====================
struct File {
    std::fstream rawfile;
    std::string path;
    std::string file;

    File(std::string _path) {
        path = _path;

        if (std::filesystem::exists(path)) {
            readFile();
        }
        else {
            std::ofstream novoArquivo(path);
            if (novoArquivo.is_open()) {
                readFile();
                std::cout << "[FILE SYSTEM] File created at " << path << std::endl;
            }
            else {
                std::cerr << "ERR 0x003 - Couldn't create new file at " << path << std::endl;
                glfwTerminate();
                system("pause");
                std::exit(-8);
            }
        }
    }

    void readFile() {
        std::fstream rawfile(path);

        if (rawfile.is_open()) {
            for (std::string line; std::getline(rawfile, line);) {
                file += line + "\n";
            }
        }
        else {
            std::cerr << "ERR 0x004 - Couldn't read file at " << path << std::endl;
            glfwTerminate();
            system("pause");
            std::exit(-9);
        }
    }

    void clearFile() {
        rawfile.clear();
        file.clear();
    }

    void saveFile(std::string outputPath) {
        std::ofstream outFile(outputPath, std::ios::out | std::ios::trunc); // flags to indicate it is an output file and will be truncated (clear) before the fileStr being paste
        outFile << file;
        outFile.close();
    }

    /* HOW TO USE:
        File* newFileCreation = new File("savefile.giromba");
        newFileCreation->file += "Creating File Example\nHello!";
        newFileCreation->saveFile("savefile.giromba");
        newFileCreation->rawfile.close();
        free(newFileCreation);

        File* readingFile = new File("savefile.giromba");
        std::cout << readingFile->file;
        readingFile->rawfile.close();
        free(readingFile);
    */
};

// IMAGES
struct Image2D {
    GLuint texture;
    GLuint VAO, VBO;

    float alpha = 1.0f;
    float rotation = 0.0f; // Degrees
    Vector2 position = Vector2(0.0f, 0.0f);
    glm::vec2 scale = glm::vec2(1.0f);

    float aspect_ratio = 1.0f;
    int w_, h_;

    Image2D(const char* path) {
        int w, h, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &w, &h, &channels, STBI_rgb_alpha);
        if (!data) {
            std::cerr << "ERR 0x010 - Cannot create raw image texture: " << stbi_failure_reason() << std::endl;
            glfwTerminate();
            system("pause");
            std::exit(-7);
        }

        w_ = w;
        h_ = h;
        aspect_ratio = (float)w / (float)h;

        // Cria textura
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        float quad[] = {
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f,
             1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f
        };

        GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        GLuint EBO;
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void flip(bool flipx, bool flipy) {
        float u0 = flipx ? 1.0f : 0.0f;
        float u1 = flipx ? 0.0f : 1.0f;
        float v0 = flipy ? 1.0f : 0.0f;
        float v1 = flipy ? 0.0f : 1.0f;

        float _w = 1.0f;
        float _h = 1.0f;

        float quad[] = {
            -_w, -_h, u0, v0,
             _w, -_h, u1, v0,
             _w,  _h, u1, v1,
            -_w,  _h, u0, v1
        };

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad), quad);
    }

    void draw() {
        glm::mat4 projection = glm::ortho(
            0.0f, (float)SCREEN_WIDTH,
            0.0f, (float)SCREEN_HEIGHT
        );

        glDisable(GL_DEPTH_TEST);
        glUseProgram(imageShader);
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(imageShader, "tex"), 0);

        glUniform1i(glGetUniformLocation(imageShader, "posMode"), 1);
        glUniform2f(glGetUniformLocation(imageShader, "position"), position.x, position.y);
        glUniformMatrix4fv(glGetUniformLocation(imageShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform2f(glGetUniformLocation(imageShader, "scale"), scale.x, scale.y);

        float aRx = (float)SCREEN_WIDTH / 1100.0f;
        float aRy = (float)SCREEN_HEIGHT / 620.0f;
        glUniform2f(glGetUniformLocation(imageShader, "texSize"), w_ * aRx, h_ * aRy);

        glUniform1f(glGetUniformLocation(imageShader, "rotation"), rotation);
        glUniform1f(glGetUniformLocation(imageShader, "alpha"), alpha);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
    }
};

struct Image3D {
    std::string path;
    int width, height, nrChannels;
    float aspect_ratio;
    Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
    float alpha = 1.0f;

    GLuint VAO, VBO, EBO, texture;

    glm::mat4 model;

    std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

    Image3D(const char* _path) {
        path = _path;

        //Create texture
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        aspect_ratio = (float)width / (float)height;

        //Generate Buffers
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        //vert
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //texcoord
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void draw(glm::mat4 view, glm::mat4 projection) {
        glDisable(GL_CULL_FACE);
        glUseProgram(image3Dshader);
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE20);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1f(glGetUniformLocation(image3Dshader, "tex"), 20);

        glUniform1f(glGetUniformLocation(image3Dshader, "alpha"), alpha);
        glUniform3f(glGetUniformLocation(image3Dshader, "position"), position.x, position.y, position.z);
        glUniform3f(glGetUniformLocation(image3Dshader, "rotation"), rotation.x, rotation.y, rotation.z);
        glUniform3f(glGetUniformLocation(image3Dshader, "scale"), scale.x, scale.y, scale.z);
        glUniform1f(glGetUniformLocation(image3Dshader, "aspect_ratio"), aspect_ratio);
        glUniformMatrix4fv(glGetUniformLocation(image3Dshader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(image3Dshader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glEnable(GL_CULL_FACE);
    }
};

// TEXTS
struct Glyph {
    glm::vec2 uv0, uv1;    // UV min/max atlas
    glm::ivec2 sizePx;     // gliph in pixels in atlas
    glm::ivec2 bearingPx;  // gliph offset starting from the base line
    int advancePx;         // horizontal advance to the next gliph based on font size
};

struct Font {
    std::map<char, Glyph> Characters;
    GLuint textureAtlas;
    int atlasWidth, atlasHeight;
    GLuint textVAO, textVBO;

    Font(const char* fontPath, int pixelSize = 48) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "ERR 0x014 - Could not init FreeType" << std::endl;
            std::exit(-20);
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath, 0, &face)) {
            std::cerr << "ERR 0x015 - Failed to load font: " << fontPath << std::endl;
            std::exit(-21);
        }

        FT_Set_Pixel_Sizes(face, 0, pixelSize);

        atlasWidth = 0;
        atlasHeight = 0;
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;
            atlasWidth += face->glyph->bitmap.width;
            atlasHeight = std::max(atlasHeight, (int)face->glyph->bitmap.rows);
        }

        glGenTextures(1, &textureAtlas);
        glBindTexture(GL_TEXTURE_2D, textureAtlas);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        int xOffset = 0;
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;

            FT_Bitmap& bmp = face->glyph->bitmap;

            std::vector<unsigned char> pixels(bmp.width * bmp.rows);
            for (int y = 0; y < bmp.rows; y++) {
                memcpy(&pixels[y * bmp.width],
                    &bmp.buffer[y * bmp.pitch],
                    bmp.width);
            }

            glTexSubImage2D(GL_TEXTURE_2D, 0,
                xOffset, 0,
                bmp.width, bmp.rows,
                GL_RED, GL_UNSIGNED_BYTE,
                pixels.data());

            Glyph glyph;
            glyph.uv0 = glm::vec2((float)xOffset / atlasWidth, 0.0f);
            glyph.uv1 = glm::vec2((float)(xOffset + bmp.width) / atlasWidth,
                (float)bmp.rows / atlasHeight);
            glyph.sizePx = glm::ivec2(bmp.width, bmp.rows);
            glyph.bearingPx = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            glyph.advancePx = (face->glyph->advance.x >> 6);

            Characters.insert(std::pair<char, Glyph>(c, glyph));

            xOffset += bmp.width;
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        glGenVertexArrays(1, &textVAO);
        glGenBuffers(1, &textVBO);
        glBindVertexArray(textVAO);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    ~Font() {
        glDeleteTextures(1, &textureAtlas);
    }
};

void DrawText(Font* font, const char* text, glm::vec2 position, float scale, glm::vec4 color, float rotation) {
    glUseProgram(textShader);

    glm::mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH,
        0.0f, (float)SCREEN_HEIGHT);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(textShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(textShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4f(glGetUniformLocation(textShader, "color"), color.x, color.y, color.z, color.w);
    glUniform1f(glGetUniformLocation(textShader, "rotation"), rotation);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font->textVAO);
    glBindTexture(GL_TEXTURE_2D, font->textureAtlas);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    float x = 0.0f;
    for (const char* p = text; *p; p++) {
        Glyph ch = font->Characters[*p];

        float xpos = x + ch.bearingPx.x * scale;
        float ypos = -(ch.sizePx.y - ch.bearingPx.y) * scale;
        float w = ch.sizePx.x * scale;
        float h = ch.sizePx.y * scale;

        float u0 = ch.uv0.x, v0 = ch.uv0.y;
        float u1 = ch.uv1.x, v1 = ch.uv1.y;

        float vertices[6][4] = {
            { xpos,     ypos + h, u0, v0 },
            { xpos,     ypos,     u0, v1 },
            { xpos + w, ypos,     u1, v1 },

            { xpos,     ypos + h, u0, v0 },
            { xpos + w, ypos,     u1, v1 },
            { xpos + w, ypos + h, u1, v0 }
        };

        glBindBuffer(GL_ARRAY_BUFFER, font->textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advancePx) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST);
}

// VIDEO
static const float _videoQuadTemplate[] = {
    -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, 1.0f, 1.0f,
     0.5f,  0.5f, 1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 0.0f
};

static const GLuint _videoIdx[] = { 0,1,2, 2,3,0 };

struct Video {
    libvlc_instance_t* vlcInstance = nullptr;
    libvlc_media_t* media = nullptr;
    libvlc_media_player_t* mediaPlayer = nullptr;

    std::vector<unsigned char> pixels;
    std::mutex pixelMutex;
    bool hasNewFrame = false;

    GLuint texture = 0;
    GLuint VAO = 0, VBO = 0, EBO = 0;

    float alpha = 1.0f;
    float rotation = 0.0f; // radians
    glm::vec2 scale = glm::vec2(1, 1);
    float aspect_ratio = 1.0f;
    int width = 0, height = 0;

    Video(const char* path, int desiredWidth = 640, int desiredHeight = 360) {
        width = desiredWidth > 0 ? desiredWidth : 640;
        height = desiredHeight > 0 ? desiredHeight : 360;
        aspect_ratio = (height != 0) ? ((float)width / (float)height) : 1.0f;

        pixels.resize((size_t)width * height * 4);

        const char* const vlc_args[] = {
            "--no-xlib",
            "--vout=vmem",
            "--no-video-title-show",
            "--quiet"
        };
        vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
        if (!vlcInstance) { std::cerr << "ERR 0x016 - Couldn't initialize VLC video instance\n"; return; }

        media = libvlc_media_new_path(vlcInstance, path);
        if (!media) {
            std::cerr << "ERR 0x017 - Couldn't open video instance at " << path << "\n";
            libvlc_release(vlcInstance); vlcInstance = nullptr;
            return;
        }

        mediaPlayer = libvlc_media_player_new_from_media(media);
        libvlc_media_release(media); media = nullptr;

        // registra callbacks
        libvlc_video_set_callbacks(mediaPlayer,
            &Video::lockCallback,
            &Video::unlockCallback,
            &Video::displayCallback,
            this
        );

#ifdef VIDEO_RGBA_FIX
        libvlc_video_set_format(mediaPlayer, "RGBA", width, height, width * 4);
#else
        libvlc_video_set_format(mediaPlayer, "RV32", width, height, width * 4);
#endif

        libvlc_audio_set_mute(mediaPlayer, 0);
        libvlc_audio_set_volume(mediaPlayer, 100);

        // cria quad OpenGL
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        float aspectRatio = width / (float)height;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_videoQuadTemplate), _videoQuadTemplate, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_videoIdx), _videoIdx, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }
    ~Video() {
        stop();

        if (mediaPlayer) {
            libvlc_media_player_release(mediaPlayer);
            mediaPlayer = nullptr;
        }
        if (media) {
            libvlc_media_release(media);
            media = nullptr;
        }
        if (vlcInstance) {
            libvlc_release(vlcInstance);
            vlcInstance = nullptr;
        }

        if (texture) {
            glDeleteTextures(1, &texture);
            texture = 0;
        }
        if (EBO) {
            glDeleteBuffers(1, &EBO);
            EBO = 0;
        }
        if (VBO) {
            glDeleteBuffers(1, &VBO);
            VBO = 0;
        }
        if (VAO) {
            glDeleteVertexArrays(1, &VAO);
            VAO = 0;
        }
    }

    void play() {
        if (mediaPlayer) {
            libvlc_media_player_play(mediaPlayer);
        }
    }
    void pause() {
        if (mediaPlayer) {
            libvlc_media_player_set_pause(mediaPlayer, 1);
        }
    }
    void stop() {
        if (mediaPlayer) {
            libvlc_media_player_stop(mediaPlayer);
        }
    }

    void update() {
        if (!pixelMutex.try_lock()) return;
        if (!hasNewFrame) { pixelMutex.unlock(); return; }

        createTextureIfNeeded();
        if (!texture) return;
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef VIDEO_RGBA_FIX
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
            GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
#else
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,
            GL_BGRA, GL_UNSIGNED_BYTE, pixels.data());
#endif

        hasNewFrame = false;
        pixelMutex.unlock();
    }
    void draw(glm::vec2 position) {
        if (!texture) return;
        GLuint shaderProgram = videoShader;
        if (!shaderProgram) return;

        glDisable(GL_DEPTH_TEST);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        GLint locTex = glGetUniformLocation(shaderProgram, "videoTex");
        if (locTex >= 0) glUniform1i(locTex, 0);

        float halfW = (float)SCREEN_WIDTH * 0.5f;
        float halfH = (float)SCREEN_HEIGHT * 0.5f;
        glm::mat4 projection = glm::ortho(-halfW, halfW, -halfH, halfH);
        GLint locProj = glGetUniformLocation(shaderProgram, "projection");
        if (locProj >= 0) glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(projection));

        float sizeX = (float)width * scale.x * 2;
        float sizeY = (float)height * scale.y * 2;
        GLint locScale = glGetUniformLocation(shaderProgram, "scale");
        if (locScale >= 0) glUniform2f(locScale, sizeX, sizeY);

        GLint locPos = glGetUniformLocation(shaderProgram, "position");
        if (locPos >= 0) glUniform2f(locPos, position.x, position.y);

        GLint locRot = glGetUniformLocation(shaderProgram, "rotation");
        if (locRot >= 0) glUniform1f(locRot, rotation);

        GLint locA = glGetUniformLocation(shaderProgram, "alpha");
        if (locA >= 0) glUniform1f(locA, alpha);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glDisable(GL_BLEND);
        glBindVertexArray(0);
        glUseProgram(0);
        glEnable(GL_DEPTH_TEST);
    }

    void createTextureIfNeeded() {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    static void* lockCallback(void* opaque, void** planes) {
        Video* self = reinterpret_cast<Video*>(opaque);
        self->pixelMutex.lock();
        *planes = self->pixels.data();
        return self->pixels.data();
    }
    static void unlockCallback(void* opaque, void* const picture, void* const* planes) {
        Video* self = reinterpret_cast<Video*>(opaque);
        self->hasNewFrame = true;
        self->pixelMutex.unlock();
    }
    static void displayCallback(void* opaque, void* picture) {
        Video* self = reinterpret_cast<Video*>(opaque);
        self->hasNewFrame = true;
    }
};

// CAMERA
struct Camera {
    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 front = glm::vec3(0, 0, -1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right;
    float     yaw = -90.0f;
    float     pitch = 0.0f;
    float     speed = 2.0f;
    float     sensitivity = 0.1f;

    Camera() {
        updateVectors();
    }

    glm::mat4 GetView() {
        return glm::lookAt(position, position + front, up);
    }

    void ProcessMouse(float xoffset, float yoffset) {
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch -= yoffset;

        if (pitch > 89.0f)  pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        updateVectors();
    }

    void updateVectors() {
        glm::vec3 dir;
        dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        dir.y = sin(glm::radians(pitch));
        dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(dir);
        right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));
        up = glm::normalize(glm::cross(right, front));
    }

    void update(GLFWwindow* window) {
        float vel = speed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += front * vel;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= front * vel;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= right * vel;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += right * vel;
    }
};

Camera camera;

// INPUT
struct Input {
    static Vector2 mousePosition;
    static Vector2 mouseDelta;
    static Vector2 scrollOffset;

    static bool GetKeyPressed(GLFWwindow* window, int key) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            return true;
        }
        return false;
    }
    static bool GetKeyReleased(GLFWwindow* window, int key) {
        if (glfwGetKey(window, key) == GLFW_RELEASE) {
            return true;
        }
        return false;
    }
    static Vector2 GetMousePosition() {
        return mousePosition;
    }
    static Vector2 GetMouseDelta() {
        return mouseDelta;
    }
    static Vector2 GetScrollOffset() {
        return scrollOffset;
    }
    static bool GetMouseButtonPressed(GLFWwindow* window, int button) {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }
};
Vector2 Input::mousePosition = { 0, 0 };
Vector2 Input::mouseDelta = { 0, 0 };
Vector2 Input::scrollOffset = { 0, 0 };

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouse(xoffset, yoffset);
    Input::mousePosition = Vector2(xpos, ypos);
    Input::mouseDelta = Vector2(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Input::scrollOffset = Vector2(xoffset, yoffset);
}

struct Scene {
    static Vector3 LightDirection;
    static Vector3 LightColor;
    static float LightIntensity;
    static float AmbientLightIntensity;
    static Vector3 AmbientLightColor;
};

Vector3 Scene::LightDirection = Vector3(0.5f, -0.5f, 0.0f);
Vector3 Scene::LightColor = Vector3(1.0f, 1.0f, 1.0f);
float Scene::LightIntensity = 1.0f;
float Scene::AmbientLightIntensity = 0.8f;
Vector3 Scene::AmbientLightColor = Vector3(1.0f, 1.0f, 1.0f);

// Models
struct Instance {
    int id = 0;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    std::vector<glm::mat4> nodeTransforms;
    std::vector<glm::mat4> finalBoneMatrices;
    std::vector<glm::mat4> localNodeTransforms;

    std::string currentAnim;
    std::string queuedAnim;
    bool looping = true;
    float currentTime = 0.0f;

    int cameraNodeIndex = -1;
    bool drivesCamera = false;
    bool cameraAnimFinished = false;

    glm::mat4 getModelMatrix() const {
        glm::mat4 mat = glm::mat4(1.0f);
        mat = glm::translate(mat, position);
        mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        mat = glm::scale(mat, scale);
        return mat;
    }

    void computeNodeTransforms(const tinygltf::Model& model, int nodeIndex, glm::mat4 parentTransform,
        const std::vector<glm::mat4>& local, std::vector<glm::mat4>& global) {
        glm::mat4 current = parentTransform * local[nodeIndex];
        global[nodeIndex] = current;

        for (int child : model.nodes[nodeIndex].children) {
            computeNodeTransforms(model, child, current, local, global);
        }
    }

    void playAnimation(const std::string& animName, bool repeat, const std::string& nextAnimIfDoesntRepeat = "") {
        currentAnim = animName;
        queuedAnim = repeat ? "" : nextAnimIfDoesntRepeat;
        looping = repeat;
        currentTime = 0.0f;
        if (cameraNodeIndex >= 0) {
            drivesCamera = true;
            cameraAnimFinished = false;
        }
    }

    void update(float deltaTime, tinygltf::Model* gltfModel) {
        currentTime += deltaTime;

        // Reset local transforms com base nos dados do GLTF
        for (size_t i = 0; i < gltfModel->nodes.size(); i++) {
            const auto& node = gltfModel->nodes[i];

            glm::mat4 local(1.0f);

            if (!node.matrix.empty()) {
                local = glm::make_mat4x4(node.matrix.data());
            }
            else {
                glm::vec3 translation(0.0f);
                if (!node.translation.empty()) translation = glm::make_vec3(node.translation.data());

                glm::quat rotation = glm::quat(1, 0, 0, 0);
                if (!node.rotation.empty()) rotation = glm::make_quat(node.rotation.data());

                glm::vec3 scale(1.0f);
                if (!node.scale.empty()) scale = glm::make_vec3(node.scale.data());

                local = glm::translate(glm::mat4(1.0f), translation) *
                    glm::mat4_cast(rotation) *
                    glm::scale(glm::mat4(1.0f), scale);
            }

            localNodeTransforms[i] = local;
        }

        // Aplicar animação nos canais
        for (const auto& animation : gltfModel->animations) {
            if (animation.name != currentAnim) continue;

            float endTime = 0.0f;

            // Collect animated T/R/S per node first, then build matrix once
            struct NodeTRS {
                glm::vec3 T; glm::quat R; glm::vec3 S;
                bool hasT = false, hasR = false, hasS = false;
            };
            std::unordered_map<int, NodeTRS> animatedTRS;

            for (const auto& channel : animation.channels) {
                const auto& sampler = animation.samplers[channel.sampler];
                const auto& inputAccessor = gltfModel->accessors[sampler.input];
                const auto& outputAccessor = gltfModel->accessors[sampler.output];

                const auto& inputView = gltfModel->bufferViews[inputAccessor.bufferView];
                const auto& outputView = gltfModel->bufferViews[outputAccessor.bufferView];

                const float* inputData = reinterpret_cast<const float*>(
                    &gltfModel->buffers[inputView.buffer].data[inputView.byteOffset + inputAccessor.byteOffset]);
                const float* outputData = reinterpret_cast<const float*>(
                    &gltfModel->buffers[outputView.buffer].data[outputView.byteOffset + outputAccessor.byteOffset]);

                size_t keyCount = inputAccessor.count;
                endTime = std::max(endTime, inputData[keyCount - 1]);

                float tSample = currentTime;
                if (tSample > inputData[keyCount - 1]) tSample = inputData[keyCount - 1];

                size_t prevIndex = 0, nextIndex = 0;
                for (size_t i = 0; i < keyCount - 1; ++i) {
                    if (tSample >= inputData[i] && tSample <= inputData[i + 1]) {
                        prevIndex = i; nextIndex = i + 1; break;
                    }
                }

                float t1 = inputData[prevIndex], t2 = inputData[nextIndex];
                float alpha = (t2 - t1 > 0.0f) ? glm::clamp((tSample - t1) / (t2 - t1), 0.0f, 1.0f) : 0.0f;

                int ni = channel.target_node;
                NodeTRS& trs = animatedTRS[ni];

                if (channel.target_path == "translation") {
                    trs.T = glm::mix(glm::make_vec3(&outputData[prevIndex * 3]),
                        glm::make_vec3(&outputData[nextIndex * 3]), alpha);
                    trs.hasT = true;
                }
                else if (channel.target_path == "rotation") {
                    trs.R = glm::slerp(glm::make_quat(&outputData[prevIndex * 4]),
                        glm::make_quat(&outputData[nextIndex * 4]), alpha);
                    trs.hasR = true;
                }
                else if (channel.target_path == "scale") {
                    trs.S = glm::mix(glm::make_vec3(&outputData[prevIndex * 3]),
                        glm::make_vec3(&outputData[nextIndex * 3]), alpha);
                    trs.hasS = true;
                }
            }

            // Build localNodeTransforms from collected TRS (falling back to node defaults)
            for (auto& [ni, trs] : animatedTRS) {
                const tinygltf::Node& node = gltfModel->nodes[ni];
                glm::vec3 T(0.0f), S(1.0f); glm::quat R(1, 0, 0, 0);
                if (!node.translation.empty()) T = glm::make_vec3(node.translation.data());
                if (!node.rotation.empty())    R = glm::make_quat(node.rotation.data());
                if (!node.scale.empty())       S = glm::make_vec3(node.scale.data());
                if (trs.hasT) T = trs.T;
                if (trs.hasR) R = trs.R;
                if (trs.hasS) S = trs.S;
                localNodeTransforms[ni] =
                    glm::translate(glm::mat4(1.0f), T)
                    * glm::mat4_cast(R)
                    * glm::scale(glm::mat4(1.0f), S);
            }

            if (currentTime > endTime) {
                if (looping)
                    currentTime = fmod(currentTime, endTime);
                else {
                    currentAnim = queuedAnim;
                    queuedAnim.clear();
                    currentTime = 0.0f;
                }
            }

            break;
        }
        // Recalculates final hierarchie by animated localNodeTransforms
        nodeTransforms.resize(gltfModel->nodes.size(), glm::mat4(1.0f));
        for (int nodeIndex : gltfModel->scenes[gltfModel->defaultScene].nodes) {
            computeNodeTransforms(*gltfModel, nodeIndex, glm::mat4(1.0f), localNodeTransforms, nodeTransforms);
        }

        // Generates final bone matrices
        finalBoneMatrices.clear();
        if (!gltfModel->skins.empty()) {
            const auto& skin = gltfModel->skins[0];
            const auto& ibmAccessor = gltfModel->accessors[skin.inverseBindMatrices];
            const auto& ibmView = gltfModel->bufferViews[ibmAccessor.bufferView];
            const float* ibmData = reinterpret_cast<const float*>(
                &gltfModel->buffers[ibmView.buffer].data[ibmView.byteOffset + ibmAccessor.byteOffset]);

            for (size_t i = 0; i < skin.joints.size(); i++) {
                glm::mat4 inverseBind = glm::make_mat4(ibmData + i * 16);
                glm::mat4 jointMat = nodeTransforms[skin.joints[i]];
                finalBoneMatrices.push_back(jointMat * inverseBind);
            }
        }

        // Drive camera from animated camera node
        if (drivesCamera && !cameraAnimFinished && cameraNodeIndex >= 0
            && cameraNodeIndex < (int)nodeTransforms.size()) {
            glm::mat4 worldMat = getModelMatrix() * nodeTransforms[cameraNodeIndex];
            camera.position = glm::vec3(worldMat[3]);
            glm::vec3 fwd = glm::normalize(-glm::vec3(worldMat[2]));
            camera.yaw = glm::degrees(std::atan2(fwd.z, fwd.x));
            camera.pitch = glm::degrees(std::asin(glm::clamp(fwd.y, -1.0f, 1.0f)));
            camera.updateVectors();
            if (!looping && currentAnim.empty()) {
                drivesCamera = false;
                cameraAnimFinished = true;
            }
        }
    }

    Instance(int i, glm::vec3 pos, glm::vec3 rot, glm::vec3 scal) {
        id = i;
        position = pos;
        rotation = rot;
        scale = scal;
    }
};

struct SubMesh {
    GLuint VAO = 0, VBO = 0, EBO = 0;
    GLuint jointVBO = 0, weightVBO = 0;

    GLuint texture = 0;
    int indexCount = 0;

    bool isSkinned = false;

    GLenum indexType = GL_UNSIGNED_INT;

    void draw(GLuint shader) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

struct Model {
    tinygltf::Model gltfModel;

    bool isSkinned = false;

    int cameraNodeIndex = -1; // set in constructor, copied to each Instance

    std::vector<SubMesh> allSubMeshes;
    size_t nodeCount = 0;

    std::vector<Instance> AllInstances;

    void CreateInstance(glm::vec3 pos, glm::vec3 rot, glm::vec3 scal) {
        int id;
        if (!AllInstances.empty()) {
            id = AllInstances[AllInstances.size() - 1].id + 1;
        }
        else {
            id = 0;
        }
        Instance inst = Instance(id, pos, rot, scal);
        inst.nodeTransforms.assign(nodeCount, glm::mat4(1.0f));
        inst.localNodeTransforms.assign(nodeCount, glm::mat4(1.0f));
        inst.cameraNodeIndex = cameraNodeIndex;
        AllInstances.push_back(inst);
    }

    Model(std::string path) {
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err, warn;

        bool result;
        if (path.size() >= 4 && path.substr(path.size() - 4) == ".glb")
            result = loader.LoadBinaryFromFile(&model, &err, &warn, path);
        else
            result = loader.LoadASCIIFromFile(&model, &err, &warn, path);
        if (!warn.empty()) std::cout << "[MODEL LOADER] WARN >> " << warn << std::endl;
        if (!err.empty()) std::cout << "[MODEL LOADER] ERR >> " << err << std::endl;
        if (!result) {
            std::cerr << "ERR 0x009: Failed to load model at " << path << std::endl;
            glfwTerminate();
            system("pause");
            exit(-9);
            return;
        }

        gltfModel = model;

        nodeCount = model.nodes.size();
        if (!model.skins.empty()) isSkinned = true;

        const auto& buffer = model.buffers[0].data;

        for (const auto& node : model.nodes) {
            if (node.mesh < 0) continue;

            const auto& mesh = model.meshes[node.mesh];

            for (const auto& primitive : mesh.primitives) {
                SubMesh sub;

                std::vector<float> positions;
                std::vector<float> normals;
                std::vector<float> uvs;
                std::vector<unsigned int> indices;

                // POSITION
                if (primitive.attributes.count("POSITION")) {
                    const auto& acc = model.accessors[primitive.attributes.at("POSITION")];
                    const auto& view = model.bufferViews[acc.bufferView];
                    const float* data = reinterpret_cast<const float*>(&buffer[view.byteOffset + acc.byteOffset]);

                    for (size_t i = 0; i < acc.count * 3; i++) {
                        positions.push_back(data[i]);
                    }
                }

                // NORMAL
                if (primitive.attributes.count("NORMAL")) {
                    const auto& acc = model.accessors[primitive.attributes.at("NORMAL")];
                    const auto& view = model.bufferViews[acc.bufferView];
                    const float* data = reinterpret_cast<const float*>(&buffer[view.byteOffset + acc.byteOffset]);

                    for (size_t i = 0; i < acc.count * 3; i++) {
                        normals.push_back(data[i]);
                    }
                }

                // UV
                if (primitive.attributes.count("TEXCOORD_0")) {
                    const auto& acc = model.accessors[primitive.attributes.at("TEXCOORD_0")];
                    const auto& view = model.bufferViews[acc.bufferView];
                    const float* data = reinterpret_cast<const float*>(&buffer[view.byteOffset + acc.byteOffset]);

                    for (size_t i = 0; i < acc.count * 2; i++) {
                        uvs.push_back(data[i]);
                    }
                }

                // INDICES
                GLenum componentType = 0;
                if (primitive.indices >= 0) {
                    const auto& acc = model.accessors[primitive.indices];
                    const auto& view = model.bufferViews[acc.bufferView];
                    const void* data = &buffer[view.byteOffset + acc.byteOffset];
                    componentType = acc.componentType;

                    for (size_t i = 0; i < acc.count; ++i) {
                        switch (acc.componentType) {
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: {
                            const uint8_t* d = static_cast<const uint8_t*>(data);
                            indices.push_back(d[i]);
                            break;
                        }
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: {
                            const uint16_t* d = static_cast<const uint16_t*>(data);
                            indices.push_back(d[i]);
                            break;
                        }
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: {
                            const uint32_t* d = static_cast<const uint32_t*>(data);
                            indices.push_back(d[i]);
                            break;
                        }
                        default:
                            std::cerr << "ERR 0x009 - Unsupported index type\n";
                            break;
                        }
                    }
                }

                // INTERLEAVE POS + NORMAL + UV
                std::vector<float> finalVerts;
                size_t count = positions.size() / 3;

                for (size_t i = 0; i < count; i++) {
                    // POS
                    finalVerts.push_back(positions[i * 3 + 0]);
                    finalVerts.push_back(positions[i * 3 + 1]);
                    finalVerts.push_back(positions[i * 3 + 2]);

                    // NORMAL
                    if (!normals.empty()) {
                        finalVerts.push_back(normals[i * 3 + 0]);
                        finalVerts.push_back(normals[i * 3 + 1]);
                        finalVerts.push_back(normals[i * 3 + 2]);
                    }
                    else {
                        finalVerts.push_back(0.0f);
                        finalVerts.push_back(0.0f);
                        finalVerts.push_back(1.0f);
                    }

                    // UV
                    if (!uvs.empty()) {
                        finalVerts.push_back(uvs[i * 2 + 0]);
                        finalVerts.push_back(uvs[i * 2 + 1]);
                    }
                    else {
                        finalVerts.push_back(0.0f);
                        finalVerts.push_back(0.0f);
                    }
                }

                // TEXTURE
                int texIndex = -1;
                if (primitive.material >= 0) {
                    const auto& mat = model.materials[primitive.material];
                    if (mat.pbrMetallicRoughness.baseColorTexture.index >= 0)
                        texIndex = mat.pbrMetallicRoughness.baseColorTexture.index;
                }

                if (texIndex >= 0) {
                    const auto& image = model.images[model.textures[texIndex].source];
                    GLuint tex;
                    glGenTextures(1, &tex);
                    glBindTexture(GL_TEXTURE_2D, tex);

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        image.width, image.height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        image.image.data());

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glGenerateMipmap(GL_TEXTURE_2D);

                    sub.texture = tex;
                }

                std::vector<glm::uvec4> joints;
                std::vector<glm::vec4> weights;

                if (primitive.attributes.count("JOINTS_0")) {
                    const auto& acc = model.accessors[primitive.attributes.at("JOINTS_0")];
                    const auto& view = model.bufferViews[acc.bufferView];
                    const unsigned short* data =
                        reinterpret_cast<const unsigned short*>(&buffer[view.byteOffset + acc.byteOffset]);

                    for (size_t i = 0; i < acc.count; i++)
                        joints.emplace_back(
                            data[i * 4 + 0],
                            data[i * 4 + 1],
                            data[i * 4 + 2],
                            data[i * 4 + 3]
                        );
                }

                if (primitive.attributes.count("WEIGHTS_0")) {
                    const auto& acc = model.accessors[primitive.attributes.at("WEIGHTS_0")];
                    const auto& view = model.bufferViews[acc.bufferView];
                    const float* data =
                        reinterpret_cast<const float*>(&buffer[view.byteOffset + acc.byteOffset]);

                    for (size_t i = 0; i < acc.count; i++)
                        weights.emplace_back(
                            data[i * 4 + 0],
                            data[i * 4 + 1],
                            data[i * 4 + 2],
                            data[i * 4 + 3]
                        );
                }

                // VAO / VBO / EBO
                glGenVertexArrays(1, &sub.VAO);
                glGenBuffers(1, &sub.VBO);
                glGenBuffers(1, &sub.EBO);

                glBindVertexArray(sub.VAO);

                // VBO
                glBindBuffer(GL_ARRAY_BUFFER, sub.VBO);
                glBufferData(GL_ARRAY_BUFFER,
                    finalVerts.size() * sizeof(float),
                    finalVerts.data(),
                    GL_STATIC_DRAW);

                // STRIDE = 8 floats (pos3 + normal3 + uv2)

                // POS
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                    8 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                // NORMAL
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                    8 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);

                // UV
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                    8 * sizeof(float), (void*)(6 * sizeof(float)));
                glEnableVertexAttribArray(2);

                // EBO
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sub.EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                    indices.size() * sizeof(unsigned int),
                    indices.data(),
                    GL_STATIC_DRAW);

                sub.indexCount = indices.size();
                sub.indexType = componentType;

                // SKIN VBOs
                if (!joints.empty()) {
                    glGenBuffers(1, &sub.jointVBO);
                    glBindBuffer(GL_ARRAY_BUFFER, sub.jointVBO);
                    glBufferData(GL_ARRAY_BUFFER,
                        joints.size() * sizeof(glm::uvec4),
                        joints.data(),
                        GL_STATIC_DRAW);

                    glVertexAttribIPointer(3, 4, GL_UNSIGNED_INT,
                        sizeof(glm::uvec4), (void*)0);
                    glEnableVertexAttribArray(3);
                }

                if (!weights.empty()) {
                    glGenBuffers(1, &sub.weightVBO);
                    glBindBuffer(GL_ARRAY_BUFFER, sub.weightVBO);
                    glBufferData(GL_ARRAY_BUFFER,
                        weights.size() * sizeof(glm::vec4),
                        weights.data(),
                        GL_STATIC_DRAW);

                    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,
                        sizeof(glm::vec4), (void*)0);
                    glEnableVertexAttribArray(4);
                }

                sub.isSkinned = (!joints.empty() && !weights.empty());

                glBindVertexArray(0);
                allSubMeshes.push_back(sub);
            }
        }

        // Detect the first camera node in the glTF
        cameraNodeIndex = -1;
        for (int i = 0; i < (int)gltfModel.nodes.size(); ++i) {
            if (gltfModel.nodes[i].camera >= 0) {
                cameraNodeIndex = i;
                break;
            }
        }

    }

    void update(float deltaTime) {
        for (auto& inst : AllInstances) {
            inst.update(deltaTime, &gltfModel);
        }
    }


    void draw(glm::mat4 view, glm::mat4 perspective) {
        if (!isSkinned) {
            glUseProgram(staticModelShader);

            glUniformMatrix4fv(glGetUniformLocation(staticModelShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(staticModelShader, "projection"), 1, GL_FALSE, glm::value_ptr(perspective));

            glUniform3fv(glGetUniformLocation(staticModelShader, "LightDirection"), 1, glm::value_ptr(glm::vec3(Scene::LightDirection.x, Scene::LightDirection.y, Scene::LightDirection.z)));
            glUniform3fv(glGetUniformLocation(staticModelShader, "LightColor"), 1, glm::value_ptr(glm::vec3(Scene::LightColor.x, Scene::LightColor.y, Scene::LightColor.z)));
            glUniform1f(glGetUniformLocation(staticModelShader, "LightIntensity"), Scene::LightIntensity);
            glUniform1f(glGetUniformLocation(staticModelShader, "AmbientLightIntensity"), Scene::AmbientLightIntensity);
            glUniform3fv(glGetUniformLocation(staticModelShader, "AmbientLightColor"), 1, glm::value_ptr(glm::vec3(Scene::AmbientLightColor.x, Scene::AmbientLightColor.y, Scene::AmbientLightColor.z)));

            for (auto& mesh : allSubMeshes) {
                for (Instance& inst : AllInstances) {
                    glm::mat4 modelMatrix = inst.getModelMatrix();
                    glUniformMatrix4fv(glGetUniformLocation(staticModelShader, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
                    mesh.draw(staticModelShader);
                }
            }
        }
        else {
            glUseProgram(skinnedModelShader);

            glUniformMatrix4fv(glGetUniformLocation(skinnedModelShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(skinnedModelShader, "projection"), 1, GL_FALSE, glm::value_ptr(perspective));

            glUniform3fv(glGetUniformLocation(skinnedModelShader, "LightDirection"), 1, glm::value_ptr(glm::vec3(Scene::LightDirection.x, Scene::LightDirection.y, Scene::LightDirection.z)));
            glUniform3fv(glGetUniformLocation(skinnedModelShader, "LightColor"), 1, glm::value_ptr(glm::vec3(Scene::LightColor.x, Scene::LightColor.y, Scene::LightColor.z)));
            glUniform1f(glGetUniformLocation(skinnedModelShader, "LightIntensity"), Scene::LightIntensity);
            glUniform1f(glGetUniformLocation(skinnedModelShader, "AmbientLightIntensity"), Scene::AmbientLightIntensity);
            glUniform3fv(glGetUniformLocation(skinnedModelShader, "AmbientLightColor"), 1, glm::value_ptr(glm::vec3(Scene::AmbientLightColor.x, Scene::AmbientLightColor.y, Scene::AmbientLightColor.z)));

            for (auto& mesh : allSubMeshes) {
                for (Instance& inst : AllInstances) {
                    glm::mat4 modelMatrix = inst.getModelMatrix();
                    glUniformMatrix4fv(glGetUniformLocation(skinnedModelShader, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

                    if (!inst.finalBoneMatrices.empty()) {
                        GLuint boneLoc = glGetUniformLocation(skinnedModelShader, "finalBones");
                        glUniformMatrix4fv(boneLoc, inst.finalBoneMatrices.size(), GL_FALSE, glm::value_ptr(inst.finalBoneMatrices[0]));
                    }

                    mesh.draw(skinnedModelShader);
                }
            }
        }
    }
};

// =================== Audio ====================
FMOD_RESULT SYS;
FMOD::System* FMOD_SYS;

struct AudioSystem {
    FMOD_VECTOR listenerPos = { 0, 0, 0 };
    FMOD_VECTOR forward = { 0.0f, 0.0f, 0.0f };
    FMOD_VECTOR up = { 0.0f, 0.0f, 0.0f };
    FMOD_VECTOR velocity = { 0.0f, 0.0f, 0.0f };

    void init() {
        SYS = FMOD::System_Create(&FMOD_SYS);
        if (SYS != FMOD_OK) {
            std::cerr << "ERR 0x011 - FMOD Audio System couldn't be created" << std::endl;
            glfwTerminate();
            system("pause");
            std::exit(-11);
        }

        SYS = FMOD_SYS->init(512, FMOD_INIT_NORMAL, nullptr);
        if (SYS != FMOD_OK) {
            std::cerr << "ERR 0x012 - FMOD Audio System couldn't be initialized" << std::endl;
            glfwTerminate();
            system("pause");
            std::exit(-12);
        }

        SYS = FMOD_SYS->set3DSettings(1.0, 1.0f, 1.0f);
    }

    void update() {
        FMOD_SYS->update();

        FMOD_SYS->set3DListenerAttributes(0, &listenerPos, &velocity, &forward, &up);
    }
};

struct Sound;

std::vector<Sound*> AllSounds;

struct Sound {
    FMOD::Sound* audiofont = nullptr;
    bool paused = false;
    glm::vec3 pos = { 0, 0, 0 };
    float minDist = 2;
    float maxDist = 20;
    bool looping = false;
    float volume = 1;
    FMOD::Channel* curr_channel = nullptr;
    FMOD::DSP* dsp = nullptr;

    Sound(const char* path, bool loop, bool threedimensional, glm::vec3 position,
        float minDistance, float maxDistance, float vol) {
        int mode = threedimensional ? FMOD_3D_LINEARROLLOFF : FMOD_2D;
        FMOD_SYS->createSound(path, mode, nullptr, &audiofont);

        pos = position;
        minDist = minDistance;
        maxDist = maxDistance;
        looping = loop;
        volume = vol;

        AllSounds.push_back(this);
    }

    void useEffect(FMOD_DSP_TYPE type) {
        FMOD_SYS->createDSPByType(type, &dsp);
        curr_channel->addDSP(0, dsp);
    }

    void updateValues() {
        audiofont->set3DMinMaxDistance(minDist, maxDist);
        if (looping) { audiofont->setMode(FMOD_LOOP_NORMAL); }
        if (!looping) { audiofont->setMode(FMOD_LOOP_OFF); }

        FMOD_VECTOR position = { pos.x, pos.y, pos.z };
        FMOD_VECTOR vel = { 0.0f, 0.0f, 0.0f };
        curr_channel->set3DAttributes(&position, &vel);
        curr_channel->setPaused(paused);
        curr_channel->setVolume(volume);
    }

    void play() {
        updateValues();
        FMOD_SYS->playSound(audiofont, nullptr, false, &curr_channel);
    }
};

// PHYSICS
struct Physics {
    struct GLDebugDrawer : public btIDebugDraw {
        int m_debugMode = DBG_DrawWireframe;

        void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
            debugLines.push_back(from.getX());
            debugLines.push_back(from.getY());
            debugLines.push_back(from.getZ());
            debugLines.push_back(color.getX());
            debugLines.push_back(color.getY());
            debugLines.push_back(color.getZ());

            debugLines.push_back(to.getX());
            debugLines.push_back(to.getY());
            debugLines.push_back(to.getZ());
            debugLines.push_back(color.getX());
            debugLines.push_back(color.getY());
            debugLines.push_back(color.getZ());
        }

        void setDebugMode(int debugMode) {
            m_debugMode = debugMode;
        }

        int getDebugMode() const {
            return m_debugMode;
        }

        void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) {}
        void reportErrorWarning(const char* warningString) {
            std::cerr << "Bullet Warning: " << warningString << std::endl;
        }
        void draw3dText(const btVector3&, const char*) {}
    };

    static btBroadphaseInterface* broadphase;
    static btDefaultCollisionConfiguration* collisionConfig;
    static btCollisionDispatcher* dispatcher;
    static btSequentialImpulseConstraintSolver* solver;
    static btDiscreteDynamicsWorld* DynamicWorld;
    static float maxCollisionDistance;

    static GLuint debugVAO, debugVBO;
    static std::vector<float> debugLines;
    static GLDebugDrawer* debugDrawer;

    struct Shape {
        btCollisionShape* shape = nullptr;
        btGImpactMeshShape* gshape = nullptr;
        btRigidBody::btRigidBodyConstructionInfo info;
        btDefaultMotionState motion;
        Shape(btCollisionShape* _shape = nullptr, btRigidBody::btRigidBodyConstructionInfo _info = { 0, nullptr, nullptr }, btDefaultMotionState _motion = { btTransform::getIdentity() }, btGImpactMeshShape* _gshape = nullptr)
            : shape(_shape), gshape(_gshape), info(_info), motion(_motion)
        {
        }
    };

    struct Rigidbody {
        btRigidBody* body;
        Shape shape;
        Rigidbody(Shape _shape) : shape(_shape) {
            body = new btRigidBody(this->shape.info);
            body->setUserPointer(this);
            body->setCcdMotionThreshold(0.001f);
            body->setCcdSweptSphereRadius(0.3f);
        }

        void activate() {
            if (body) {
                body->activate();
            }
        }
        void applyForce(Vector3 force, Vector3 relPos) {
            if (body) {
                body->applyForce(btVector3(force.x, force.y, force.z), btVector3(relPos.x, relPos.y, relPos.z));
            }
        }
        void applyImpulse(Vector3 impulse, Vector3 relPos) {
            if (body) {
                body->applyImpulse(btVector3(impulse.x, impulse.y, impulse.z), btVector3(relPos.x, relPos.y, relPos.z));
            }
        }
        void applyTorque(Vector3 torque) {
            if (body) {
                body->applyTorque(btVector3(torque.x, torque.y, torque.z));
            }
        }
        void applyCentralForce(Vector3 force) {
            if (body) {
                body->applyCentralForce(btVector3(force.x, force.y, force.z));
            }
        }
        void applyCentralImpulse(Vector3 impulse) {
            if (body) {
                body->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
            }
        }
        void applyTorqueImpulse(Vector3 torqueImpulse) {
            if (body) {
                body->applyTorqueImpulse(btVector3(torqueImpulse.x, torqueImpulse.y, torqueImpulse.z));
            }
        }
        void setLinearVelocity(Vector3 velocity) {
            if (body) {
                body->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
            }
        }
        void setAngularVelocity(Vector3 velocity) {
            if (body) {
                body->setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));
            }
        }
        void setTransform(Vector3 position, Vector3 rotation) {
            if (body) {
                btTransform transform;
                transform.setOrigin(btVector3(position.x, position.y, position.z));

                float xRad = rotation.x;
                float yRad = rotation.y;
                float zRad = rotation.z;

                btQuaternion rot;
                rot.setEulerZYX(zRad, yRad, xRad);
                transform.setRotation(rot);

                body->setWorldTransform(transform);
            }
        }
        void setLinearFactor(Vector3 factor) {
            if (body) {
                body->setLinearFactor(btVector3(factor.x, factor.y, factor.z));
            }
        }
        void setAngularFactor(Vector3 factor) {
            if (body) {
                body->setAngularFactor(btVector3(factor.x, factor.y, factor.z));
            }
        }
        void setCollisionShape(Shape* newShape) {
            if (body) {
                body->setCollisionShape(newShape->shape);
            }
        }
        void clearForces();
        Vector3 getPosition() {
            if (body) {
                btTransform transform;
                body->getMotionState()->getWorldTransform(transform);
                btVector3 pos = transform.getOrigin();
                return Vector3(pos.getX(), pos.getY(), pos.getZ());
            }
        }
        Vector3 getRotation() {
            if (body) {
                btTransform transform;
                body->getMotionState()->getWorldTransform(transform);
                btQuaternion rot = transform.getRotation();
                btScalar roll, pitch, yaw;
                rot.getEulerZYX(yaw, pitch, roll);
                return Vector3(roll, pitch, yaw);
            }
        }
        void setMass(float mass, Vector3 inertia) {
            if (body) {
                btVector3 _inertia(inertia.x, inertia.y, inertia.z);
                if (mass != 0.0f)
                    shape.shape->calculateLocalInertia(mass, _inertia);
                body->setMassProps(mass, _inertia);
            }
        }
        void setFriction(float friction) {
            if (body) {
                body->setFriction(friction);
            }
        }
        void setRollingFriction(float friction) {
            if (body) {
                body->setRollingFriction(friction / 5);
            }
        }
        void setDamping(float damping) {
            if (body) {
                body->setDamping(damping, damping);
            }
        }
        void lockAxis(Vector3 axis) {
            if (body) {
                body->setAngularFactor(btVector3(axis.x, axis.y, axis.z));
            }
        }
        void setBouncingFactor(float factor) {
            if (body) {
                body->setRestitution(factor);
            }
        }
    };

    struct Vehicle {
        btRaycastVehicle::btVehicleTuning* tuning;
        btVehicleRaycaster* raycaster;
        btRaycastVehicle* vehicle;

        struct WheelInfo {
            btWheelInfo* info;
        };

        Vehicle(Rigidbody* chassiBody) {
            tuning = new btRaycastVehicle::btVehicleTuning;
            raycaster = new btDefaultVehicleRaycaster(DynamicWorld);
            vehicle = new btRaycastVehicle(*tuning, chassiBody->body, raycaster);
            chassiBody->body->setActivationState(DISABLE_DEACTIVATION);
        }
        void addWheel(Vector3 relativePosition, Vector3 wheelDirectionCS0, Vector3 wheelAxleCS,
            float suspensionRestLength, float wheelRadius, bool isFrontWheel) {
            vehicle->addWheel(btVector3(relativePosition.x, relativePosition.y, relativePosition.z),
                btVector3(wheelDirectionCS0.x, wheelDirectionCS0.y, wheelDirectionCS0.z),
                btVector3(wheelAxleCS.x, wheelAxleCS.y, wheelAxleCS.z),
                suspensionRestLength, wheelRadius, *tuning, isFrontWheel);
        }
        int getNumWheels() {
            return vehicle->getNumWheels();
        }
        WheelInfo& getWheelInfo(int index) {
            Vehicle::WheelInfo* info = new WheelInfo;
            info->info = &vehicle->getWheelInfo(index);
            return *info;
        }

        void update(float deltaTime) {
            vehicle->updateVehicle(deltaTime);
            vehicle->updateSuspension(deltaTime);
            vehicle->updateFriction(deltaTime);
        }

        void applyEngineForce(float force, int wheelIndex) {
            vehicle->applyEngineForce(force, wheelIndex);
        }
        void setSteeringValue(float value, int wheelIndex) {
            vehicle->setSteeringValue(value, wheelIndex);
        }
        void setBrake(float brake, int wheelIndex) {
            vehicle->setBrake(brake, wheelIndex);
        }
        Vector3 getWheelWorldPosition(int index) {
            WheelInfo* info = new WheelInfo;
            info->info = &vehicle->getWheelInfo(index);

            return Vector3(info->info->m_worldTransform.getOrigin().getX(),
                info->info->m_worldTransform.getOrigin().getY(),
                info->info->m_worldTransform.getOrigin().getZ());
        }
        Vector3 getWheelRotation(int index) {
            WheelInfo* info = new WheelInfo;
            info->info = &vehicle->getWheelInfo(index);

            return Vector3(info->info->m_worldTransform.getRotation().getX(),
                info->info->m_worldTransform.getRotation().getY(),
                info->info->m_worldTransform.getRotation().getZ());
        }
        float getCurrentSpeedKmh() {
            return vehicle->getCurrentSpeedKmHour();
        }
    };

    static struct Raycast {
        static bool CheckCollisionWithBody(Physics::Rigidbody* body, Vector3 origin, Vector3 end) {
            btCollisionWorld::ClosestRayResultCallback rayCallback(btVector3(origin.x, origin.y, origin.z), btVector3(end.x, end.y, end.z));
            DynamicWorld->rayTest(btVector3(origin.x, origin.y, origin.z), btVector3(end.x, end.y, end.z), rayCallback);

            if (rayCallback.hasHit())
            {
                const btRigidBody* hitBody = btRigidBody::upcast(rayCallback.m_collisionObject);

                if (body->body == hitBody) {
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
        static const btRigidBody* GetFirstBodyCollided(Vector3 origin, Vector3 end) {
            btCollisionWorld::ClosestRayResultCallback rayCallback(btVector3(origin.x, origin.y, origin.z), btVector3(end.x, end.y, end.z));
            DynamicWorld->rayTest(btVector3(origin.x, origin.y, origin.z), btVector3(end.x, end.y, end.z), rayCallback);

            if (rayCallback.hasHit())
            {
                const btRigidBody* hitBody = btRigidBody::upcast(rayCallback.m_collisionObject);

                if (hitBody)
                    return hitBody;
            }
            else
            {
                return nullptr;
            }
        }
    };

    static void DrawDebugWorld(glm::mat4 projection, glm::mat4 view) {
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(projection));
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view));
        DynamicWorld->debugDrawWorld();
        glUseProgram(physicsdebugShader);
        if (!debugLines.empty()) {
            if (debugVAO == 0) {
                glGenVertexArrays(1, &debugVAO);
                glGenBuffers(1, &debugVBO);
            }

            glBindVertexArray(debugVAO);
            glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
            glBufferData(GL_ARRAY_BUFFER, debugLines.size() * sizeof(float), debugLines.data(), GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(0); // position
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1); // color
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

            glUseProgram(physicsdebugShader);
            glm::mat4 vp = projection * view;
            glUniformMatrix4fv(glGetUniformLocation(physicsdebugShader, "viewProj"), 1, GL_FALSE, glm::value_ptr(vp));

            glDrawArrays(GL_LINES, 0, debugLines.size() / 6);

            glBindVertexArray(0);
            glUseProgram(0);
            debugLines.clear();
        }
        glEnable(GL_DEPTH_TEST);
    }

    static void CreatePhysicsWorld(Vector3 gravity, int maxIterations) {
        broadphase = new btDbvtBroadphase();
        collisionConfig = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfig);
        solver = new btSequentialImpulseConstraintSolver();

        DynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
        DynamicWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
        DynamicWorld->getSolverInfo().m_numIterations = maxIterations;

        debugDrawer = new GLDebugDrawer();
        debugDrawer->setDebugMode(
            btIDebugDraw::DBG_DrawWireframe
        );
        DynamicWorld->setDebugDrawer(debugDrawer);
    }
    static Shape CreateCapsuleShape(Vector3 position, Vector3 rotation, float radius, float height, float mass) {
        btCollisionShape* newshape = new btCapsuleShape(radius, height);
        btTransform start;
        start.setIdentity();
        start.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
        start.setOrigin(btVector3(position.x, position.y, position.z));
        btVector3 inertia(0, 0, 0);
        newshape->calculateLocalInertia(mass, inertia);
        btDefaultMotionState* motion = new btDefaultMotionState(start);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motion, newshape, inertia);

        Shape* pshape = new Shape(newshape, info, *motion, nullptr);
        return *pshape;
    }
    static Shape CreateBoxShape(Vector3 position, Vector3 rotation, Vector3 scale, float mass) {
        btCollisionShape* newshape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
        btTransform start;
        start.setIdentity();
        start.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
        start.setOrigin(btVector3(position.x, position.y, position.z));
        btVector3 inertia(0, 0, 0);
        newshape->calculateLocalInertia(mass, inertia);
        btDefaultMotionState* motion = new btDefaultMotionState(start);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motion, newshape, inertia);

        Shape pshape(newshape, info, *motion, nullptr);
        return pshape;
    }
    static Shape CreateCyllinderShape(Vector3 position, Vector3 rotation, float radius, float height, float mass) {
        btCollisionShape* newshape = new btCylinderShape(btVector3(radius, height, radius));
        btTransform start;
        start.setIdentity();
        start.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
        start.setOrigin(btVector3(position.x, position.y, position.z));
        btVector3 inertia(0, 0, 0);
        newshape->calculateLocalInertia(mass, inertia);
        btDefaultMotionState* motion = new btDefaultMotionState(start);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motion, newshape, inertia);

        Shape pshape(newshape, info, *motion, nullptr);
        return pshape;
    }
    static Shape CreateSphereShape(Vector3 position, Vector3 rotation, float radius, float mass) {
        btCollisionShape* newshape = new btSphereShape(radius);
        btTransform start;
        start.setIdentity();
        start.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
        start.setOrigin(btVector3(position.x, position.y, position.z));
        btVector3 inertia(0, 0, 0);
        newshape->calculateLocalInertia(mass, inertia);
        btDefaultMotionState* motion = new btDefaultMotionState(start);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motion, newshape, inertia);

        Shape pshape(newshape, info, *motion, nullptr);
        return pshape;
    }
    static Shape CreateConeShape(Vector3 position, Vector3 rotation, float radius, float height, float mass) {
        btCollisionShape* newshape = new btConeShape(radius, height);
        btTransform start;
        start.setIdentity();
        start.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
        start.setOrigin(btVector3(position.x, position.y, position.z));
        btVector3 inertia(0, 0, 0);
        newshape->calculateLocalInertia(mass, inertia);
        btDefaultMotionState* motion = new btDefaultMotionState(start);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motion, newshape, inertia);

        Shape pshape(newshape, info, *motion, nullptr);
        return pshape;
    }

    static btTriangleMesh* LoadMeshFromFile(const char* path, Vector3 scale) {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string err, warn;

        if (!loader.LoadBinaryFromFile(&model, &err, &warn, path)) {
            std::cerr << "Failed to load GLB: " << err << std::endl;
            return nullptr;
        }

        btTriangleMesh* triMesh = new btTriangleMesh();
        glm::mat4 globalScale = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));

        std::function<void(int, glm::mat4)> processNode;
        processNode = [&](int nodeIndex, glm::mat4 parentTransform) {
            const auto& node = model.nodes[nodeIndex];

            glm::mat4 local(1.0f);
            if (!node.matrix.empty()) {
                local = glm::make_mat4(node.matrix.data());
            }
            else {
                glm::vec3 T(0.0f), S(1.0f);
                glm::quat R(1, 0, 0, 0);
                if (!node.translation.empty()) T = glm::make_vec3(node.translation.data());
                if (!node.rotation.empty()) R = glm::make_quat(node.rotation.data());
                if (!node.scale.empty()) S = glm::make_vec3(node.scale.data());
                local = glm::translate(glm::mat4(1.0f), T)
                    * glm::mat4_cast(R)
                    * glm::scale(glm::mat4(1.0f), S);
            }

            glm::mat4 globalTransform = parentTransform * local;

            if (node.mesh >= 0) {
                const auto& mesh = model.meshes[node.mesh];
                for (const auto& prim : mesh.primitives) {
                    if (prim.mode != TINYGLTF_MODE_TRIANGLES) continue;

                    const auto& posAcc = model.accessors[prim.attributes.at("POSITION")];
                    const auto& posView = model.bufferViews[posAcc.bufferView];
                    const auto& posBuf = model.buffers[posView.buffer];
                    const float* posData = reinterpret_cast<const float*>(
                        &posBuf.data[posView.byteOffset + posAcc.byteOffset]);

                    std::vector<glm::vec3> vertices(posAcc.count);
                    for (size_t i = 0; i < posAcc.count; ++i) {
                        glm::vec4 v(posData[i * 3 + 0], posData[i * 3 + 1], posData[i * 3 + 2], 1.0f);
                        v = globalScale * globalTransform * v;
                        vertices[i] = glm::vec3(v);
                    }

                    const auto& idxAcc = model.accessors[prim.indices];
                    const auto& idxView = model.bufferViews[idxAcc.bufferView];
                    const auto& idxBuf = model.buffers[idxView.buffer];
                    const void* idxData = &idxBuf.data[idxView.byteOffset + idxAcc.byteOffset];

                    for (size_t i = 0; i < idxAcc.count; i += 3) {
                        uint32_t i0, i1, i2;
                        switch (idxAcc.componentType) {
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                            i0 = ((uint8_t*)idxData)[i + 0];
                            i1 = ((uint8_t*)idxData)[i + 1];
                            i2 = ((uint8_t*)idxData)[i + 2];
                            break;
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                            i0 = ((uint16_t*)idxData)[i + 0];
                            i1 = ((uint16_t*)idxData)[i + 1];
                            i2 = ((uint16_t*)idxData)[i + 2];
                            break;
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                            i0 = ((uint32_t*)idxData)[i + 0];
                            i1 = ((uint32_t*)idxData)[i + 1];
                            i2 = ((uint32_t*)idxData)[i + 2];
                            break;
                        default:
                            std::cerr << "Unsupported index type\n";
                            return nullptr;
                        }

                        triMesh->addTriangle(
                            btVector3(vertices[i0].x, vertices[i0].y, vertices[i0].z),
                            btVector3(vertices[i1].x, vertices[i1].y, vertices[i1].z),
                            btVector3(vertices[i2].x, vertices[i2].y, vertices[i2].z)
                        );
                    }
                }
            }

            for (int child : node.children) {
                processNode(child, globalTransform);
            }
            };

        for (int nodeIndex : model.scenes[model.defaultScene].nodes) {
            processNode(nodeIndex, glm::mat4(1.0f));
        }

        return triMesh;
    }
    static Shape CreateMeshShape(const char* path, Vector3 position, Vector3 rotation, Vector3 scale, float mass) {
        btGImpactMeshShape* newshape = new btGImpactMeshShape(LoadMeshFromFile(path, scale));
        btTransform start;
        start.setIdentity();
        start.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
        start.setOrigin(btVector3(position.x, position.y, position.z));
        btVector3 inertia(0, 0, 0);
        newshape->calculateLocalInertia(mass, inertia);
        btDefaultMotionState* motion = new btDefaultMotionState(start);
        btRigidBody::btRigidBodyConstructionInfo info(mass, motion, newshape, inertia);
        Shape pshape(nullptr, info, *motion, newshape);
        return pshape;
    }

    static bool CheckCollisionBetween(Rigidbody* bodyA, Rigidbody* bodyB) {
        int numManifolds = DynamicWorld->getDispatcher()->getNumManifolds();

        btVector3 posA = bodyA->body->getWorldTransform().getOrigin();
        btVector3 posB = bodyB->body->getWorldTransform().getOrigin();

        if ((posA - posB).length2() > maxCollisionDistance * maxCollisionDistance) {
            return false;
        }

        for (int i = 0; i < numManifolds; ++i) {
            btPersistentManifold* manifold = DynamicWorld->getDispatcher()->getManifoldByIndexInternal(i);
            const btCollisionObject* objA = manifold->getBody0();
            const btCollisionObject* objB = manifold->getBody1();

            if ((objA == bodyA->body && objB == bodyB->body) || (objA == bodyB->body && objB == bodyA->body)) {
                int numContacts = manifold->getNumContacts();
                for (int j = 0; j < numContacts; ++j) {
                    const btManifoldPoint& pt = manifold->getContactPoint(j);
                    if (pt.getDistance() < 0.0f) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

btBroadphaseInterface* Physics::broadphase;
btDefaultCollisionConfiguration* Physics::collisionConfig;
btCollisionDispatcher* Physics::dispatcher;
btSequentialImpulseConstraintSolver* Physics::solver;
btDiscreteDynamicsWorld* Physics::DynamicWorld;
float Physics::maxCollisionDistance = 50.0f;
GLuint Physics::debugVAO = 0, Physics::debugVBO = 0;
std::vector<float> Physics::debugLines;
Physics::GLDebugDrawer* Physics::debugDrawer;

struct Engine {
    GLFWwindow* window;

    AudioSystem* AUDIOSYSTEM;

    float lastFPSTime;
    float lastFrame;
    float FPS;

    Model* linkStaticModel;
    Model* horseSkinnedModel;
    Image2D* exampleImage;
    Image3D* exampleImage3D;
    Font* exampleFont;
    Video* exampleVideo;
    Physics::Rigidbody* groundBody;
    Physics::Rigidbody* carChassiBody;
    Physics::Vehicle* vehicle;

    void init() {
        glfwInit();
        GLFWmonitor* monitor;
        monitor = glfwGetPrimaryMonitor();
        glfwWindowHint(GLFW_RESIZABLE, false);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROJECT_NAME, NULL, NULL);
        if (!window) {
            std::cerr << "ERR 0x001 - Failed to initialize GLFW Window\n";
            glfwTerminate();
            system("pause");
            std::exit(-1);
        }

        //glfwSetWindowMonitor(window, monitor, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 70);

        glfwSwapInterval(0);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "ERR 0x002 - Failed to initialize GLAD\n";
            glfwTerminate();
            system("pause");
            std::exit(-2);
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Console Init
        int cpuInfo[4] = { -1 };
        char cpuBrand[0x40];
        __cpuid(cpuInfo, 0x80000000);
        unsigned int nExIds = cpuInfo[0];

        memset(cpuBrand, 0, sizeof(cpuBrand));
        for (unsigned int i = 0x80000002; i <= nExIds && i <= 0x80000004; i++) {
            __cpuid((int*)(cpuInfo), i);
            memcpy(cpuBrand + (i - 0x80000002) * 16, cpuInfo, sizeof(cpuInfo));
        }

        MEMORYSTATUSEX status;
        status.dwLength = sizeof(status);
        GlobalMemoryStatusEx(&status);
        DWORDLONG total = status.ullTotalPhys;
        DWORDLONG avail = status.ullAvailPhys;

        std::cout << "==============FISCINA3D=============" << std::endl;
        std::cout << "CPU: " << cpuBrand << std::endl;
        std::cout << "RAM: " << total / (1024 * 1024) << " MB" << std::endl;
        std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "OPENGL VERSION: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "====================================" << std::endl;

        // Initiate Shaders
        File* staticModelShaderVertFile = new File("shaders/static_model.vert");
        File* staticModelShaderFragFile = new File("shaders/static_model.frag");
        File* skinnedModelShaderVertFile = new File("shaders/skinned_model.vert");
        staticModelShader = LoadShader(staticModelShaderVertFile->file.c_str(), staticModelShaderFragFile->file.c_str());
        skinnedModelShader = LoadShader(skinnedModelShaderVertFile->file.c_str(), staticModelShaderFragFile->file.c_str());

        File* imageShaderVertFile = new File("shaders/image.vert");
        File* imageShaderFragFile = new File("shaders/image.frag");
        imageShader = LoadShader(imageShaderVertFile->file.c_str(), imageShaderFragFile->file.c_str());

        File* textShaderVertFile = new File("shaders/text.vert");
        File* textShaderFragFile = new File("shaders/text.frag");
        textShader = LoadShader(textShaderVertFile->file.c_str(), textShaderFragFile->file.c_str());

        File* physicsdebugShaderVertFile = new File("shaders/physicsdebug.vert");
        File* physicsdebugShaderFragFile = new File("shaders/physicsdebug.frag");
        physicsdebugShader = LoadShader(physicsdebugShaderVertFile->file.c_str(), physicsdebugShaderFragFile->file.c_str());

        File* videoShaderVertFile = new File("shaders/video.vert");
        File* videoShaderFragFile = new File("shaders/video.frag");
        videoShader = LoadShader(videoShaderVertFile->file.c_str(), videoShaderFragFile->file.c_str());

        File* image3DShaderVertFile = new File("shaders/image3d.vert");
        File* image3DShaderFragFile = new File("shaders/image3d.frag");
        image3Dshader = LoadShader(image3DShaderVertFile->file.c_str(), image3DShaderFragFile->file.c_str());

        Physics::CreatePhysicsWorld(Vector3(0, -9.81f, 0), 10);

        AUDIOSYSTEM = new AudioSystem();
        AUDIOSYSTEM->init();

        Scene::LightDirection = Vector3(0.0f, -0.5f, 0.0f);
        Scene::LightColor = Vector3(1.0f, 1.0f, 1.0f);
        Scene::LightIntensity = 1.0f;
        Scene::AmbientLightIntensity = 0.8f;
        Scene::AmbientLightColor = Vector3(1.0f, 1.0f, 1.0f);

        // Create Scene
        // anim blending; pontual lights; fog; transparency map; transform all glm::vec3 used by user into Vector3
        linkStaticModel = new Model("assets/models/camera_test_anim.glb");
        linkStaticModel->CreateInstance(
            glm::vec3(0, 0, -3),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.02f));
        linkStaticModel->CreateInstance(
            glm::vec3(0, 5, 0),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.02f));
        linkStaticModel->AllInstances[0].playAnimation("CameraAction", false);

        horseSkinnedModel = new Model("assets/models/camel.glb");
        horseSkinnedModel->CreateInstance(
            glm::vec3(2, 0, -3),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f));
        horseSkinnedModel->CreateInstance(
            glm::vec3(-5, 0, -3),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f));
        horseSkinnedModel->AllInstances[0].playAnimation("Armature|WalkCycle", true);
        horseSkinnedModel->AllInstances[1].playAnimation("Armature|Idle_01", true);

        exampleImage = new Image2D("assets/images/didi.png");
        exampleImage->scale = glm::vec2(0.4f, 0.4f);
        exampleImage->position = Vector2(300, 180);
        exampleImage3D = new Image3D("assets/images/didi.png");
        exampleFont = new Font("assets/ui/fonts/FOT-RodinHimawari.otf", 28);
        exampleVideo = new Video("assets/spheres.mp4");
        exampleVideo->scale = glm::vec2(0.5f, 0.5f);
        //exampleVideo->play();

        // VEHICLE TEST
        Physics::Shape groundShape = Physics::CreateBoxShape(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(30.0f, 0.01f, 30.0f), 0.0f);
        groundBody = new Physics::Rigidbody(groundShape);
        groundBody->setBouncingFactor(0.0f);
        Physics::DynamicWorld->addRigidBody(groundBody->body);

        // ==== Car ====
        Physics::Shape carShape = Physics::CreateBoxShape(
            Vector3(-10, 4, 0),
            Vector3(0, 0, 0),
            Vector3(0.8f, 0.5f, 1.7f),
            880.0f
        );
        carChassiBody = new Physics::Rigidbody(carShape);
        Physics::DynamicWorld->addRigidBody(carChassiBody->body);

        vehicle = new Physics::Vehicle(carChassiBody);

        Vector3 wheelDirectionCS0(0, -1, 0);
        Vector3 wheelAxleCS(-1, 0, 0);

        float suspensionRestLength = 0.6;
        float wheelRadius = 0.5;

        vehicle->addWheel(Vector3(1.0, 0.1f, 1.5), wheelDirectionCS0, wheelAxleCS,
            suspensionRestLength, wheelRadius, true); // front left

        vehicle->addWheel(Vector3(-1.0, 0.1f, 1.5), wheelDirectionCS0, wheelAxleCS,
            suspensionRestLength, wheelRadius, true); // frontt right

        vehicle->addWheel(Vector3(1.0, 0.1f, -1.5), wheelDirectionCS0, wheelAxleCS,
            suspensionRestLength, wheelRadius, false); // back left

        vehicle->addWheel(Vector3(-1.0, 0.1f, -1.5), wheelDirectionCS0, wheelAxleCS,
            suspensionRestLength, wheelRadius, false); // back right


        Physics::DynamicWorld->addVehicle(vehicle->vehicle);

        for (int i = 0; i < vehicle->getNumWheels(); ++i) {
            Physics::Vehicle::WheelInfo& wheel = vehicle->getWheelInfo(i);

            wheel.info->m_suspensionStiffness = 14.0f;             // holds well the weight
            wheel.info->m_wheelsDampingCompression = 2.0f;         // absorves impacts
            wheel.info->m_wheelsDampingRelaxation = 3.5f;          // relaxes smoothly

            wheel.info->m_maxSuspensionTravelCm = 150.0f;          // vertical spacement for the wheel to move
            wheel.info->m_maxSuspensionForce = 10000.0f;           // max suspension force

            wheel.info->m_frictionSlip = 1500.0f;                  // great traction
            wheel.info->m_rollInfluence = 0.1f;                    // great grip on the ground
            wheel.info->m_bIsFrontWheel = (i < 2);                 // front
        }
    }

    void update() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        FPS++;

        if (currentFrame - lastFPSTime >= 1.0f) {
            //std::cout << "FPS: " << FPS << std::endl;
            FPS = 0;
            lastFPSTime = currentFrame;
        }

        Physics::DynamicWorld->stepSimulation(deltaTime, 10);
        vehicle->update(deltaTime);
        carChassiBody->body->setActivationState(DISABLE_DEACTIVATION);

        if (Input::GetKeyPressed(window, KEY_I)) {
            vehicle->applyEngineForce(800, 0);
            vehicle->applyEngineForce(800, 1);
        }
        else {
            vehicle->setBrake(2, 0);
            vehicle->setBrake(2, 1);
            vehicle->applyEngineForce(0, 0);
            vehicle->applyEngineForce(0, 1);
        }
        if (Input::GetKeyPressed(window, KEY_K)) {
            linkStaticModel->AllInstances[0].playAnimation("CameraAction", false);
            vehicle->setBrake(10, 0);
            vehicle->setBrake(10, 1);
            vehicle->applyEngineForce(-1000, 0);
            vehicle->applyEngineForce(-1000, 1);
        }
        if (Input::GetKeyPressed(window, KEY_J)) {
            linkStaticModel->AllInstances[1].playAnimation("CameraAction", false);
            vehicle->setSteeringValue(0.5f, 0);
            vehicle->setSteeringValue(0.5f, 1);
        }
        else if (Input::GetKeyPressed(window, KEY_L)) {
            vehicle->setSteeringValue(-0.4f, 0);
            vehicle->setSteeringValue(-0.4f, 1);
        }
        else {
            vehicle->setSteeringValue(0, 0);
            vehicle->setSteeringValue(0, 1);
        }
        if (Input::GetKeyPressed(window, KEY_T)) {
            carChassiBody->setTransform(Vector3(3, 10, -4), Vector3(0, 0, 0));
        }

        exampleVideo->update();
        linkStaticModel->update(deltaTime);
        horseSkinnedModel->update(deltaTime);

        AUDIOSYSTEM->listenerPos = { camera.position.x, camera.position.y, camera.position.z };

        if (linkStaticModel->AllInstances.empty() || !linkStaticModel->AllInstances[0].drivesCamera) camera.update(window);
        glfwPollEvents();
    }

    void draw() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetView();
        glm::mat4 perspective = glm::perspective(glm::radians(60.0f), float(SCREEN_WIDTH) / SCREEN_HEIGHT, 0.001f, 1000.0f);

        linkStaticModel->draw(view, perspective);
        horseSkinnedModel->draw(view, perspective);

        exampleImage3D->draw(view, perspective);

        exampleImage->draw();
        DrawText(exampleFont, "Fiscina3D", glm::vec2(20, 20), 0.5f, glm::vec4(1.0f), 0.0f);
        exampleVideo->draw(glm::vec2(600.0f, -100.0f));
        exampleVideo->scale = glm::vec2(0.3f);

        Physics::DrawDebugWorld(perspective, view);

        glfwSwapBuffers(window);
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            update();
            draw();
        }
    }
};

// =================== Shader Loader ===================
GLuint LoadShader(const char* vertexSrc, const char* fragmentSrc) {
    std::hash<std::string> hasher;
    size_t vertexHash = hasher(std::string(vertexSrc));
    size_t fragHash = hasher(std::string(fragmentSrc));
    std::string binaryPath = "cache/shaders/" + std::to_string(vertexHash + fragHash) + ".bin";

    // ───── Tentativa de carregar shader binário ─────
    if (std::filesystem::exists(binaryPath)) {
        std::ifstream in(binaryPath, std::ios::binary);
        if (in) {
            GLenum format;
            in.read(reinterpret_cast<char*>(&format), sizeof(format));

            in.seekg(0, std::ios::end);
            size_t fileSize = static_cast<size_t>(in.tellg());
            size_t size = fileSize - sizeof(format);
            in.seekg(sizeof(format), std::ios::beg);

            std::vector<char> binary(size);
            in.read(binary.data(), size);
            in.close();

            GLuint program = glCreateProgram();
            glProgramBinary(program, format, binary.data(), static_cast<GLint>(size));

            GLint success = 0;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (success) {
                return program;
            }
            else {
                glDeleteProgram(program);
                std::cerr << "ERR 0x005: Shader program couldn't be loaded from " << binaryPath << std::endl;
                glfwTerminate();
                system("pause");
                std::exit(-10);
            }
        }
    }

    // ───── Compilar do zero ─────
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSrc, nullptr);
    glCompileShader(vs);
    GLint success;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vs, 512, nullptr, infoLog);
        std::cerr << "ERR 0x006::VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        system("pause");
        std::exit(-4);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSrc, nullptr);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fs, 512, nullptr, infoLog);
        std::cerr << "ERR 0x007::FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        system("pause");
        std::exit(-5);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERR 0x008::SHADER_PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
        glfwTerminate();
        system("pause");
        std::exit(-6);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    // ───── Tentar salvar o binário ─────
    GLint numFormats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &numFormats);
    if (numFormats > 0) {
        GLint length = 0;
        glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &length);

        if (length > 0) {
            std::vector<char> binary(length);
            GLenum format = 0;
            glGetProgramBinary(program, length, nullptr, &format, binary.data());

            std::ofstream out(binaryPath, std::ios::binary);
            out.write(reinterpret_cast<const char*>(&format), sizeof(format));
            out.write(binary.data(), binary.size());
            out.close();
        }
    }

    return program;
}

int main() {
    Engine* ENGINE;
    ENGINE = new Engine();
    ENGINE->init();
    ENGINE->run();
    glfwTerminate();
    return 0;
}