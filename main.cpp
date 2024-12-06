//#define _CRT_SECURE_NO_WARNINGS
////#include <iostream>
//#include <fstream>
//#include <sstream>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <freetype/freetype.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//#include <map>
//
//
//using namespace std;   
//
//unsigned int compileShader(GLenum type, const char* source);
//unsigned int createShader(const char* vsSource, const char* fsSource);
//
//void processInput(GLFWwindow* window);
//
//void drawRectangle(float x, float y, float width, float height, unsigned int shaderProgram, float r, float g, float b, float a);
//void drawNumericKeyboard(unsigned int program, unsigned int textProgram, glm::mat4 projection);
//void drawDigitalClock(unsigned int program);
//
//int initTextRendering();
//void generateCharacters(FT_Library ftLibrary, FT_Face face);
//void renderText(unsigned int shaderProgram, std::string text, float x, float y, float scale, float r, float g, float b, glm::mat4 projection);
//
//typedef struct my_vec3
//{
//    float x;
//    float y;
//    float z;
//} my_vec3;
//
//typedef struct my_vec2
//{
//    int x;
//    int y;
//} my_vec2;
//
//
//struct Character {
//    unsigned int TextureID;  // ID handle of the glyph texture
//    my_vec2   Size;       // Size of glyph
//    my_vec2   Bearing;    // Offset from baseline to left/top of glyph
//    unsigned int Advance;    // Offset to advance to next glyph
//};
//
//std::map<char, Character> Characters;
//
//unsigned int VAOchar, VBOchar;
//
//const char* vertexShaderSource = "basic.vert";
//const char* fragmentShaderSource = "basic.frag";
//
//const char* vertexTextShaderSource = "text.vert";
//const char* fragmentTextShaderSource = "text.frag";
//
//unsigned int wWidth = 1200;
//unsigned int wHeight = 800;
//const char wTitle[] = "[Microwave]";
//
//int main(void) {
//   
//    
//
//	if (!glfwInit()) {
//		std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
//		return 1;
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window;
//	unsigned int wWidth = 1200;
//	unsigned int wHeight = 800;
//	const char wTitle[] = "[Microwave]";
//	window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);
//
//	if (window == NULL) {
//		std::cout << "Prozor nije napravljen! :(\n";
//		glfwTerminate();
//		return 2;
//	}
//
//	glfwMakeContextCurrent(window);
//    glViewport(0, 0, wWidth, wHeight);
//
//    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(wWidth), 0.0f, static_cast<float>(wHeight));
//	
//	if (glewInit() != GLEW_OK) {
//		std::cout << "GLEW nije mogao da se ucita! :'(\n";
//		return 3;
//	}
//
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    unsigned int program = createShader(vertexShaderSource, fragmentShaderSource);
//    unsigned int textProgram = createShader(vertexTextShaderSource, fragmentTextShaderSource);
//
//    
//    initTextRendering();
//	
//	while (!glfwWindowShouldClose(window)) {
//        processInput(window);
//
//        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        drawRectangle(-0.8f, -0.8f, 1.6f, 1.4f, program, 0.2f, 0.2f, 0.2f, 1.0f);
//
//        drawRectangle(-0.750f, -0.750f, 1.50f, 1.30f,  program, 0.3f, 0.3f, 0.5f, 1.0f);
//
//        drawRectangle(-0.6f, -0.4f, 0.8f, 0.6f, program, 0.2f, 0.2f, 0.2f, 0.3f);
//
//        drawRectangle(0.30f, -0.75f, 0.45f, 1.30f, program, 0.0f, 0.0f, 0.5f, 0.0f);
//
//        drawNumericKeyboard(program, textProgram, projection);
//
//        glfwSwapBuffers(window); 
//        glfwPollEvents();
//
//	}
//
//    glDeleteProgram(program);
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//}
//
//
//unsigned int compileShader(GLenum type, const char* source)
//{
//    //Uzima kod u fajlu na putanji "source", kompajlira ga i vraca sejder tipa "type"
//    //Citanje izvornog koda iz fajla
//    std::string content = "";
//    std::ifstream file(source);
//    std::stringstream ss;
//    if (file.is_open())
//    {
//        ss << file.rdbuf();
//        file.close();
//        std::cout << "Uspjesno procitao fajl sa putanje \"" << source << "\"!" << std::endl;
//    }
//    else {
//        ss << "";
//        std::cout << "Greska pri citanju fajla sa putanje \"" << source << "\"!" << std::endl;
//    }
//    std::string temp = ss.str();
//    const char* sourceCode = temp.c_str(); //Izvorni kod sejdera koji citamo iz fajla na putanji "source"
//
//    int shader = glCreateShader(type); //Napravimo prazan sejder odredjenog tipa (vertex ili fragment)
//
//    int success; //Da li je kompajliranje bilo uspjesno (1 - da)
//    char infoLog[512]; //Poruka o gresci (Objasnjava sta je puklo unutar sejdera)
//    glShaderSource(shader, 1, &sourceCode, NULL); //Postavi izvorni kod sejdera
//    glCompileShader(shader); //Kompajliraj sejder
//
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //Provjeri da li je sejder uspjesno kompajliran
//    if (success == GL_FALSE)
//    {
//        glGetShaderInfoLog(shader, 512, NULL, infoLog); //Pribavi poruku o gresci
//        if (type == GL_VERTEX_SHADER)
//            printf("VERTEX");
//        else if (type == GL_FRAGMENT_SHADER)
//            printf("FRAGMENT");
//        printf(" sejder ima gresku! Greska: \n");
//        printf(infoLog);
//    }
//    return shader;
//}
//unsigned int createShader(const char* vsSource, const char* fsSource)
//{
//    //Pravi objedinjeni sejder program koji se sastoji od Vertex sejdera ciji je kod na putanji vsSource
//
//    unsigned int program; //Objedinjeni sejder
//    unsigned int vertexShader; //Verteks sejder (za prostorne podatke)
//    unsigned int fragmentShader; //Fragment sejder (za boje, teksture itd)
//
//    program = glCreateProgram(); //Napravi prazan objedinjeni sejder program
//
//    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource); //Napravi i kompajliraj vertex sejder
//    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource); //Napravi i kompajliraj fragment sejder
//
//    //Zakaci verteks i fragment sejdere za objedinjeni program
//    glAttachShader(program, vertexShader);
//    glAttachShader(program, fragmentShader);
//
//    glLinkProgram(program); //Povezi ih u jedan objedinjeni sejder program
//    glValidateProgram(program); //Izvrsi provjeru novopecenog programa
//
//    int success;
//    char infoLog[512];
//    glGetProgramiv(program, GL_VALIDATE_STATUS, &success); //Slicno kao za sejdere
//    if (success == GL_FALSE)
//    {
//        glGetShaderInfoLog(program, 512, NULL, infoLog);
//        std::cout << "Objedinjeni sejder ima gresku! Greska: \n";
//        std::cout << infoLog << std::endl;
//    }
//
//    //Posto su kodovi sejdera u objedinjenom sejderu, oni pojedinacni programi nam ne trebaju, pa ih brisemo zarad ustede na memoriji
//    glDetachShader(program, vertexShader);
//    glDeleteShader(vertexShader);
//    glDetachShader(program, fragmentShader);
//    glDeleteShader(fragmentShader);
//
//    return program;
//}
//
//
//void drawRectangle(float x, float y, float width, float height, unsigned int shaderProgram, float r, float g, float b, float a) {
//    float vertices[] = {
//        x, y, 0.0f,
//        x + width, y, 0.0f,
//        x + width, y + height, 0.0f,
//        x, y + height, 0.0f
//    };
//
//    unsigned int indices[] = {
//        0, 1, 2,
//        2, 3, 0
//    };
//
//    unsigned int VAOrect, VBOrect, EBOrect;
//    glGenVertexArrays(1, &VAOrect);
//    glGenBuffers(1, &VBOrect);
//    glGenBuffers(1, &EBOrect);
//
//    glBindVertexArray(VAOrect);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBOrect);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOrect);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glUseProgram(shaderProgram);
//    glUniform4f(glGetUniformLocation(shaderProgram, "uColor"), r, g, b, a);
//
//    glBindVertexArray(VAOrect);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//    glDeleteBuffers(1, &VBOrect);
//    glDeleteBuffers(1, &EBOrect);
//    glDeleteVertexArrays(1, &VAOrect);
//}
//
//void drawDigitalClock(unsigned int program) {
//
//}
//
//void drawNumericKeyboard(unsigned int program, unsigned int textProgram, glm::mat4 projection) {
//    float keyWidth = 0.105f, keyHeight = 0.105f;
//    float startX = 0.35f, startY = 0.06f;
//    float spacing = 0.025f;
//
//    float textScale = 0.002f;
//
//    for (int row = 0; row < 3; ++row) {
//        for (int col = 0; col < 3; ++col) {
//            float x = startX + col * (keyWidth + spacing);
//            float y = startY - row * (keyHeight + spacing);
//
//            int number = row * 3 + col + 1;
//            std::string text = std::to_string(number);
//
//            drawRectangle(x, y, keyWidth, keyHeight, program, 0.3f, 0.5f, 0.7f, 1.0f);
//
//
//            float textX = (x + 1.0f) / 2.0f * wWidth - (text.size() * 10.0f * textScale / 2.0f);
//            float textY = (y + 1.0f) / 2.0f * wHeight - (10.0f * textScale / 2.0f);
//
//            // Render text in orthographic space
//            renderText(textProgram, text, textX, textY, 0.9, 1.0f, 1.0f, 1.0f, projection);
//
//        }
//    }
//    
//    startY = startY - 3 * (keyHeight + spacing);
//    drawRectangle(startX, startY, keyWidth, keyHeight, program, 0.3f, 0.5f, 0.7f, 1.0f); //zero
//    renderText(textProgram, "0",
//        (startX + 1.0f) / 2.0f * wWidth - (10.0f * textScale / 2.0f),
//        (startY + 1.0f) / 2.0f * wHeight - (10.0f * textScale / 2.0f),
//        1.0f, 1.0f, 1.0f, 1.0f, projection);
//    
//    startX = startX + keyWidth + spacing;
//    drawRectangle(startX, startY, keyWidth*2+spacing, keyHeight, program, 0.3f, 0.5f, 0.7f, 1.0f); //start button
//    renderText(textProgram, "START",
//        (startX + 1.0f) / 2.0f * wWidth - (10.0f * textScale / 2.0f),
//        (startY + 1.0f) / 2.0f * wHeight - (10.0f * textScale / 2.0f),
//        1.0f, 1.0f, 1.0f, 1.0f, projection);
//}
//
//int initTextRendering() {
//    FT_Library ftLibrary;
//    FT_Face     face;
//
//    if (FT_Init_FreeType(&ftLibrary)) {
//        std::cout << "ERROR::FREETYPE: Could not initialize FreeType Library\n";
//        return 1;
//    }
//
//    FT_Error error = FT_New_Face(ftLibrary, "assets/fonts/OpenSans.ttf", 0, &face);
//    if (error == FT_Err_Unknown_File_Format) {
//        std::cout << "ERROR::FREETYPE: Font format is unsupported\n";
//        return 1;
//    }
//    else if (error) {
//        std::cout << "ERROR::FREETYPE: Font file could not be opened or read or it is broken.\n";
//        return 1;
//    }
//
//    /*int glyph_index = FT_Get_Char_Index(face, 65);  
//    if (FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT)) {
//        std::cout << "ERROR::FREETYPE: Character could not be loaded.\n";
//        return 1;
//    }
//
//    FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);*/
//
//    generateCharacters(ftLibrary, face);
//
//    return 0;
//}
//
//void generateCharacters(FT_Library ftLibrary, FT_Face face) {
//    
//    FT_Set_Pixel_Sizes(face, 0, 36);
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//    for (unsigned char c = 0; c < 128; c++)
//    {
//        // load character glyph 
//        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//        {
//            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//            continue;
//        }
//        // generate texture
//        unsigned int texture;
//        glGenTextures(1, &texture);
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glTexImage2D(
//            GL_TEXTURE_2D,
//            0,
//            GL_RED,
//            face->glyph->bitmap.width,
//            face->glyph->bitmap.rows,
//            0,
//            GL_RED,
//            GL_UNSIGNED_BYTE,
//            face->glyph->bitmap.buffer
//        );
//        // set texture options
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        
//        my_vec2 size;
//        size.x = face->glyph->bitmap.width;
//        size.y = face->glyph->bitmap.rows;
//        my_vec2 bearing;
//        bearing.x = face->glyph->bitmap_left;
//        bearing.y = face->glyph->bitmap_top;
//        Character character = {
//            texture,
//            size,
//            bearing,
//            static_cast<unsigned int>(face->glyph->advance.x)
//        };
//        Characters.insert(std::pair<char, Character>(c, character));
//    }
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//    FT_Done_Face(face);
//    FT_Done_FreeType(ftLibrary);
//
//    glGenVertexArrays(1, &VAOchar);
//    glGenBuffers(1, &VBOchar);
//    glBindVertexArray(VAOchar);
//    glBindBuffer(GL_ARRAY_BUFFER, VBOchar);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//    void renderText(unsigned int shaderProgram, std::string text, float x, float y, float scale, float r, float g, float b, glm::mat4 projection) {
//        glUseProgram(shaderProgram);
//        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//        glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), r, g, b);
//        glActiveTexture(GL_TEXTURE0);
//        glBindVertexArray(VAOchar);
//
//        for (char c : text) {
//            Character ch = Characters[c];
//
//            float xpos = x + ch.Bearing.x * scale;
//            float ypos = y - (ch.Size.x - ch.Bearing.y) * scale;
//
//            float w = ch.Size.x * scale;
//            float h = ch.Size.y * scale;
//
//            float vertices[6][4] = {
//                { xpos,     ypos + h,   0.0f, 0.0f },
//                { xpos,     ypos,       0.0f, 1.0f },
//                { xpos + w, ypos,       1.0f, 1.0f },
//
//                { xpos,     ypos + h,   0.0f, 0.0f },
//                { xpos + w, ypos,       1.0f, 1.0f },
//                { xpos + w, ypos + h,   1.0f, 0.0f }
//            };
//
//            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//
//            glBindBuffer(GL_ARRAY_BUFFER, VBOchar);
//            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//
//            x += (ch.Advance >> 6) * scale;
//        }
//                
//        glBindVertexArray(0);
//        glBindTexture(GL_TEXTURE_2D, 0);
//    }
