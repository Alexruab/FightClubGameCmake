#include "raylib.h"

#if defined(_WIN32)           
	#define NOGDI             // All GDI defines and routines
	#define NOUSER            // All USER defines and routines
#endif


#if defined(_WIN32) 
    #include <Windows.h> // or any library that uses Windows.h
#endif

#if defined(_WIN32)           // raylib uses these names as function parameters
	#undef near
	#undef far
#endif

#include <iostream>
#include <optional>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>




template <typename T>
// static bool parse(T& data, const std::string& JSONstr)
static std::optional<T> parse(const std::string& JSONstr)
{
    try
    {
        const auto json = nlohmann::json::parse(JSONstr);
        return json.get<T>();
    }
    catch (nlohmann::json::out_of_range& e)
    {
        std::cout << "JSON parse error : " << e.what() << std::endl;
    }

    return std::nullopt;
}

struct ChuckResponse
{
    std::string value;
    std::string id;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChuckResponse, value, id)
};

std::string RequestJoke()
{
    std::string Joke;
    cpr::Response response = cpr::Get(cpr::Url{"http://api.chucknorris.io/jokes/random"});

    std::cout << response.status_code << std::endl;
    std::cout << response.header["content-type"] << std::endl;
    std::cout << response.text << std::endl;

    if (response.status_code == 200)
    {
        const auto chuckResponse = parse<ChuckResponse>(response.text);

        if (chuckResponse)
        {
            Joke = chuckResponse->value;
            std::cout << std::endl << chuckResponse->value << std::endl;
            std::cout << std::endl << chuckResponse->id << std::endl;
        }
    }

    return Joke;
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Chuck Norris jokes");

    SetTargetFPS(60);

    std::string joke = RequestJoke();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            joke = RequestJoke();
        }


        BeginDrawing();
        ClearBackground(DARKPURPLE);
        DrawText(joke.c_str(), 190, 200, 20, LIGHTGRAY);
        EndDrawing();

    }
    CloseWindow(); 

    return EXIT_SUCCESS;
}
