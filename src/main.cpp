#include <SDL2/SDL.h>

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Dashboard",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    SDL_Event event;

    float speed = 0;
    float rpm = 1000;
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
                    rpm += speed * 20;
                    temp += 0.001;
                }

                if(event.key.keysym.sym == SDLK_s){
                    speed -= 5;
                    rpm -= speed * 20;
                }

                if(speed < 0){
                    speed = 0;
                }
                if(speed > 300){
                    speed = 300;
                }

                if(rpm > 7000){
                    rpm = 7000;
                }
                if(rpm < 1000){
                    rpm = 1000;
                }

                if(temp < 50){
                    temp = 50;
                }
                if(temp>100){
                    temp = 100;
                }
            }
            fuel -= 0.01;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Speed
        SDL_Rect spd = {50, 50, (int)speed, 30};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &spd);

        //RPM
        SDL_Rect rpmBar = {50, 100, (int)rpm/20, 30};
        if(rpm > 6000){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        SDL_RenderFillRect(renderer, &rpmBar);

        //Fuel
        SDL_Rect fuelBar = {50, 150, (int)fuel, 30};
        if(fuel > 20){
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        }
        if(fuel < 20){
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        SDL_RenderFillRect(renderer, &fuelBar);

        //Temp
        SDL_Rect tempBar = {50, 200, (int)temp, 30};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &tempBar);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}