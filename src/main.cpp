#include <SDL2/SDL.h>

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Dashboard",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1000,
        600,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    SDL_Event event;

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
                    speed += 5;
                    temp += 0.01;
                }

                if(event.key.keysym.sym == SDLK_s){
                    speed -= 5;
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
            targetRPM = 800 + speed * 25;
            RPM += (targetRPM -RPM) * 0.05;
            while(temp < 50){
                temp += 5;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //Speed
        SDL_Rect spd = {0, 50, 750, 70};
        SDL_RenderDrawRect(renderer, &spd);

        SDL_Rect spdFill = {0, 50, (int)(speed*2), 70};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &spdFill);

        //RPM
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect rpm = {0, 130, 850, 40};
        SDL_RenderDrawRect(renderer, &rpm);

        SDL_Rect rpmFill = {0, 130, (int)(RPM/10), 40};
        if(RPM > 7000){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rpmFill);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderFillRect(renderer, &rpmFill);
        }

        //Fuel
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect fuelR = {0, 450, 430, 40};
        SDL_RenderDrawRect(renderer, &fuelR);

        SDL_Rect fuelFill = {0, 450, (int)fuel, 40};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &fuelFill);
        

        //Temp
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect tempR = {0, 330, 430, 40};
        SDL_RenderDrawRect(renderer, &tempR);

        SDL_Rect tempFill = {0, 330, (int)temp, 40};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &tempFill);
        

        //Vikavalot
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Rect warning = {800, 350, 200, 250};
        SDL_RenderDrawRect(renderer, &warning);
        


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}