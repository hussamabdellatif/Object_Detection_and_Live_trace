#include "Screen.h"


    Screen::Screen():m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer(NULL){}
    bool Screen::init(){
        if(SDL_Init(SDL_INIT_VIDEO)<0) return false;
        m_window = SDL_CreateWindow(
            "Live Trace ;)",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );
        if(!m_window){return false;}
        m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_PRESENTVSYNC);
        m_texture  = SDL_CreateTexture(
                                       m_renderer,
                                       SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_STATIC,
                                       SCREEN_WIDTH,SCREEN_HEIGHT
                                   );
        if(!m_renderer || !m_texture){
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyTexture(m_texture);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        memset(m_buffer,0x0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        return true;
    }
    bool Screen::processEvents(){
        bool quit = false;
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN) quit = true;
            if(e.type == SDL_MOUSEBUTTONDOWN) quit = true;
            return quit;
        }
        return false;
    }
    void Screen::update(){
        SDL_UpdateTexture(m_texture,NULL,m_buffer,SCREEN_WIDTH*sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer,m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }
    void Screen::close(){
        delete[] m_buffer;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
        if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    		return;
    	}
        Uint32 color = 0;
        color<<= 8;
        color += green;
        color <<= 8;
        color += blue;
        color <<= 8;
        color += 0xFF;
        m_buffer[(y*SCREEN_WIDTH)+x] = color;
    }
    void Screen::setBuf(){
        memset(m_buffer,0x0,SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    }
