//Create an empty SDL Window testing

#include<SDL.h>
#include<stdio.h>
#include<math.h>
#include<iostream>

using namespace std;

int main(){
    const int Screen_width  = 600;
    const int Screen_height = 800;
    const int delay_time = 100 * pow(1,3); //10 seconds
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout<<"Failed to Link SDL Library"<<endl;
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Particle Fire Explosition",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,Screen_width, Screen_height,SDL_WINDOW_SHOWN);
    if(window==NULL){
        printf("Could not create window: %s\n",SDL_GetError());
        SDL_Quit();
        return 2;
    }
//                                                        synchronize with window when window is refereashing
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture  *texture  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, Screen_width,Screen_height); //each pixel is represented by 4 byte
    Uint32 *buffer = new Uint32[Screen_width * Screen_height];
    memset(buffer,(0),Screen_width*Screen_height*sizeof(Uint32));

    int i=0; int max = Screen_width*Screen_height;
    int r = max;

    if(renderer || texture){
        SDL_Event e;
        bool quit = false;
        while(!quit){
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT) quit = true;
                if(e.type == SDL_KEYDOWN) quit = true;
                if(e.type == SDL_MOUSEBUTTONDOWN) quit = true;
            }
            buffer[i%max]  = 0x0000FFFF;
            if(r == 0) r = max;
            buffer[r] = 0xFF00FFFF;
            SDL_UpdateTexture(texture,NULL,buffer,Screen_width*sizeof(Uint32));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer); i++;r--;

            //counter++;
        }
    }else{
        cout<<"Error in Creating Texture || Renderer"<<endl;
    }

    delete[] buffer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}
