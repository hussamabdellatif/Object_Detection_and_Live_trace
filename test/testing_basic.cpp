//to compile run this command: g++ <name of file>.cpp
//-o <name of executable> -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks
//-framework SDL2


//testing if sdl.h library is installed and imported and linked correctly

#include <SDL.h>
#include <iostream>

using namespace std;

int main(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
        cout<<"SDL Library Failed To Link/Imported"<<endl;
        cout<<"Make Sure SDL2.framework is in the directory: "<<endl;
        cout<<"/Library/Frameworks"<<endl;
        cout<<"Also make sure you have authenticated it, and registered it on your macbook privacy settings" << endl;
        return 1;
    }else{
        cout<<"Success: You can proceed to developing you application"<<endl;
    }
    SDL_Quit();
    return 0;
}
