#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL_image.h>


// g++ src/main.cpp -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o build/digidash.exe
// ./build/digidash.exe
// Neon virheä (R, G, B)=(57, 255, 20)
// Neon keltainen (255, 255, 51)

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    

    TTF_Font* font = TTF_OpenFont("assets/fonts/Roboto-VariableFont_wdth,wght.ttf", 32);

    SDL_Window* window = SDL_CreateWindow(
        "Dashboard",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        600,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* backgnd = IMG_LoadTexture(renderer, "assets/textures/carbon.jpg");
    SDL_Texture* vikavalot = IMG_LoadTexture(renderer, "assets/textures/vikavalot.png");

    SDL_Rect handBrake = {0, 0, 205, 235};
    SDL_Rect checkEngine = {205, 0, 205, 235};
    SDL_Rect akku = {410, 0, 205, 235};
    SDL_Rect hehku = {615, 0, 205, 235};
    SDL_Rect takaSumu = {820, 0, 205, 235};

    SDL_Rect luisunEsto = {0, 235, 205, 235};
    SDL_Rect bensa = {205, 235, 205, 235};
    SDL_Rect kaasujalka = {410, 235, 205, 235};
    SDL_Rect lampotila = {615, 235, 205, 235};
    SDL_Rect ABS = {820, 235, 205, 235};

    SDL_Rect hatavilkku = {0, 470, 205, 235};
    SDL_Rect puhallus = {205, 470, 205, 235};
    SDL_Rect ilmatyyny = {410, 470, 205, 235};
    SDL_Rect ilmanpaine = {615, 470, 205, 235};
    SDL_Rect oljy = {820, 470, 205, 235};

    bool running = true;
    SDL_Event event;

    // --- Simulointia varten ---
    int gear = 1;
    int gearMaxSpd[] = {0, 40, 70, 110, 160, 220, 300};
    float acceleration[]={0, 0.5, 0.4, 0.3, 0.2, 0.15, 0.1};


    float speed = 0;
    float RPM = 800 + rand() % 50;
    float targetRPM = 800;

    float temp = 50;
    float fuel = 100;
    

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }

            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_w){
                    if(speed < gearMaxSpd[gear]){
                        speed += acceleration[gear];
                    }
                    temp += 0.01;
                }

                if(event.key.keysym.sym == SDLK_s){
                    speed -= 2;
                }

                if(event.key.keysym.sym == SDLK_e){
                    if(gear<6){
                        gear++;
                    }
                }
                if(event.key.keysym.sym == SDLK_q){
                    if(gear>1){
                        gear--;
                    }
                }

                if(speed < 0){
                    speed = 0;
                }
                if(speed > 300){
                    speed = 300;
                }

                if(RPM > 8500){
                    RPM = 8500;
                }
                if(RPM < 800){
                    RPM = 800;
                }

                if(temp < 0){
                    temp = 0;
                }
                if(temp>100){
                    temp = 100;
                }
            }
            fuel -= 0.01;
            targetRPM = 800 + (speed * 125) / gear;
            RPM += (targetRPM -RPM) * 0.05;
            while(temp < 50){
                temp += 5;
            }
        }
        
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // --- Tausta ---
        SDL_RenderCopy(renderer, backgnd, NULL, NULL);


        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

        // --- Speed ---
        SDL_Rect spd = {0, 50, 750, 70};
        SDL_RenderDrawRect(renderer, &spd);

        SDL_Rect spdFill = {0, 50, (int)(speed*2), 70};
        SDL_SetRenderDrawColor(renderer, 57, 255, 20, 255);
        SDL_RenderFillRect(renderer, &spdFill);

        SDL_Color white = {255,255,255};
        std::string speedText = std::to_string((int)speed) + " KM/H";
        SDL_Surface* surface = TTF_RenderText_Solid(font, speedText.c_str(),white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {760, 70, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        // --- RPM ---
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

        SDL_Rect rpm = {0, 130, 850, 40};
        SDL_RenderDrawRect(renderer, &rpm);

        SDL_Rect rpmFill = {0, 130, (int)(RPM/10), 40};
        if(RPM > 7000){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rpmFill);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 51, 255);
            SDL_RenderFillRect(renderer, &rpmFill);
        }

        std::string rpmText = std::to_string((int)RPM);
        SDL_Surface* surface2 = TTF_RenderText_Solid(font, rpmText.c_str(),white);
        SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
        SDL_Rect textRect2 = {870, 130, surface2->w, surface2->h};
        SDL_RenderCopy(renderer, texture2, NULL, &textRect2);

        // --- Fuel ---
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect fuelR = {0, 450, 430, 40};
        SDL_RenderDrawRect(renderer, &fuelR);

        SDL_Rect fuelFill = {0, 450, (int)fuel, 40};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &fuelFill);
        

        // --- Temp ---
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect tempR = {0, 330, 430, 40};
        SDL_RenderDrawRect(renderer, &tempR);

        SDL_Rect tempFill = {0, 330, (int)temp, 40};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &tempFill);
        

        // --- Vikavalot ---
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect dstRect = {800, 350, 205, 235};
        SDL_RenderCopy(renderer, vikavalot, &bensa, &dstRect);// Tähän pitää erikseen laittaa minkä vikavalon haluaa esille
        // Myöhemmin jotkut syttyy toiminnoista esim liian kuuma, tai vaikka bensa lopussa

        SDL_Rect warning = {800, 350, 200, 250};
        SDL_RenderDrawRect(renderer, &warning);
        


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(backgnd);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_Quit();

    return 0;
}