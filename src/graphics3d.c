#include "graphics3d.h"
#include "simple_logger.h"
#include "shader.h"

static SDL_GLContext __graphics3d_gl_context;
static SDL_Window  * __graphics3d_window = NULL;
static GLuint        __graphics3d_shader_program;
static GLuint        __graphics3d_shader_program2;
static GLuint        __graphics3d_shader_program3;
static Uint32        __graphics3d_frame_delay = 33;
void graphics3d_close();

GLuint graphics3d_get_shader_program()
{
    return __graphics3d_shader_program;
}


GLuint graphics3d_get_shader_program2()
{
	return __graphics3d_shader_program2;
}

GLuint graphics3d_get_shader_program3()
{
	return __graphics3d_shader_program3;
}

void graphics3d_next_frame()
{
	
    static Uint32 then = 0;
    Uint32 now;
    SDL_GL_SwapWindow(__graphics3d_window);
	//number of ticks that pass when sdl begin tick=milisec
    now = SDL_GetTicks();
    if ((now - then) < __graphics3d_frame_delay)
    {
        SDL_Delay(__graphics3d_frame_delay - (now - then));        
    }
    then = now;
}

int graphics3d_init(int sw,int sh,int fullscreen,const char *project,Uint32 frameDelay)
{
    const unsigned char *version;
    GLenum glew_status;
      //setup SDL  
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        slog("failed to initialize SDL!");
        return -1;
    }
	//close sdl
    atexit(SDL_Quit);
    __graphics3d_frame_delay = frameDelay;
    //creates window,window height width etc
    __graphics3d_window = SDL_CreateWindow(project?project:"gametest3d",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              sw, sh,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    
	
	//void SDL_GetWindowSize(SDL_Window* __graphics3d_window, int* width, int* height);

    if(__graphics3d_window  == NULL)
	{
		slog("Fatal:Failed to create sdl window");
		return -1;
	}
    __graphics3d_gl_context = SDL_GL_CreateContext(__graphics3d_window);
    if (__graphics3d_gl_context == NULL)
    {
        slog("There was an error creating the OpenGL context!\n");
        return -1;
    }
    //make the current window is the one were draing to
    version = glGetString(GL_VERSION);
    if (version == NULL) 
    {
        slog("There was an error creating the OpenGL context!\n");
        return -1;
    }
    
    SDL_GL_MakeCurrent(__graphics3d_window, __graphics3d_gl_context);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    //MUST make a context AND make it current BEFORE glewInit()!
    glewExperimental = GL_TRUE;
    glew_status = glewInit();
    if (glew_status != 0) 
    {
        slog("Error: %s", glewGetErrorString(glew_status));
        return -1;
    }
    
    
    __graphics3d_shader_program = BuildShaderProgram("shaders/vs1.glsl", "shaders/fs1.glsl");
    if (__graphics3d_shader_program == -1)
    {
        slog("Error: failed to create shader program");
		return -1;
    }
    
    slog("Using program %d", __graphics3d_shader_program);
    


	__graphics3d_shader_program2 = BuildShaderProgram("shaders/vs1_hud.glsl", "shaders/fs1_hud.glsl");
	if (__graphics3d_shader_program2 == -1)
	{
		slog("Error: failed to create shader program");
		return -1;
	}

	slog("Using program %d", __graphics3d_shader_program2);

	__graphics3d_shader_program3 = BuildShaderProgram("shaders/vs1_buttons.glsl", "shaders/fs1_buttons.glsl");
	if (__graphics3d_shader_program3 == -1)
	{
		slog("Error: failed to create shader program");
		return -1;
	}

	slog("Using program %d", __graphics3d_shader_program3);




    atexit(graphics3d_close);
    return 0;
}

SDL_Window* getwindow()
{
	return __graphics3d_window;
}


void graphics3d_close()
{
    SDL_GL_DeleteContext(__graphics3d_gl_context);
}


/*eol@eof*/
