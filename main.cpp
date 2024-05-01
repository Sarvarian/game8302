#include "pch.hpp"

using namespace ab;

#define MAIN_LOOP_RATE_PER_SECOND 60
#define WINDOW_SCREEN_WIDTH 800
#define WINDOW_SCREEN_HEIGHT 600
#define WINDOW_TITLE "Game Window"
#define SPRITE_SHEET_FILE_NAME "art.bmp"

#define DEBUG_PRINT_FPS_EVERY_SECOND 1
#define DEBUG_MESSAGE_DESTROY 0

class CMDLine
{
public:

	static int argc()
	{
		return argc_;
	}

	static char** argv()
	{
		return argv_;
	}

private:
	friend int main(int, char**);

	static int argc_;
	static char** argv_;

};

int CMDLine::argc_ = 0;
char** CMDLine::argv_ = nullptr;

class ExitCode
{
public:

	void set(int code)
	{
		exit_code_ = code;
	}

private:
	friend int main(int, char**);

	static int exit_code_;

};

int ExitCode::exit_code_ = 0;

void Error(const char* title, const char* message)
{
	std::cerr << "Error: " << title << " : " << message << '\n';
	SDL_ShowSimpleMessageBox(
		SDL_MESSAGEBOX_ERROR,
		title,
		message,
		nullptr
	);
}

void SilentError(const char* title, const char* message)
{
	SDL_Log("Error: %s : %s", title, message);
}

void DebugLog(const char* message)
{
	SDL_Log("DEBUG: %s", message);
}

void app_main();

int main(int argc, char** argv)
{
	CMDLine::argc_ = argc;
	CMDLine::argv_ = argv;

	int res = SDL_Init(SDL_INIT_EVERYTHING);
	if (res != 0)
	{
		const char* error_message = SDL_GetError();
		Error("SDL_Init Failed", error_message);
		goto exit;
	}

	try
	{
		app_main();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

exit:
	SDL_Quit();

	return ExitCode::exit_code_;
}

class StackNode
{
private:
	friend class Stack;
	void* object_ = nullptr;
	void (*destroy_routine_)(void*) = nullptr;
	StackNode* next_node_ = nullptr;
};

class Stack
{
public:
	Stack() { }
	~Stack()
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Stack destruction starts here");
#endif

		StackNode* node = last_node_;
		while (node != nullptr)
		{

			node->destroy_routine_(node->object_);
			StackNode* next_node = node->next_node_;
			delete node;
			node = next_node;
		}

#if DEBUG_MESSAGE_DESTROY
		DebugLog("Stack destruction ends here");
#endif

	}

	void add(void* object, void (*destroy_routine)(void*))
	{
		StackNode* node = new StackNode;
		node->object_ = object;
		node->destroy_routine_ = destroy_routine;
		node->next_node_ = last_node_;
		last_node_ = node;
	}

private:
	StackNode* last_node_ = nullptr;

};

class MainLoopTiming
{
public:

	static constexpr u64 one_second = 1;
	static constexpr u64 miliseconds_per_seconds = 1000;
	static constexpr u64 max_frame_time_in_miliseconds =
		(u64)(
			(((double)(one_second)) / ((double)(MAIN_LOOP_RATE_PER_SECOND)))
			* ((double)(miliseconds_per_seconds))
			);

	u64 get_tick()
	{
		return SDL_GetTicks64();
	}

	void begin_frame()
	{
		{
			frame_started_at = get_tick();
		}
	}

	void end_frame()
	{
		{
			previous_frame_ended_at = frame_ended_at;
			frame_ended_at = get_tick();
		}

#if DEBUG_PRINT_FPS_EVERY_SECOND
		{
			print_fps_every_second();
		}
#endif

		{
			u32 delay_time = calculate_delay_time();
			SDL_Delay(delay_time);
		}
	}

private:

	u64 frame_started_at = 0;
	u64 frame_ended_at = 0;
	u64 previous_frame_ended_at = 0;

	u32 calculate_delay_time()
	{
		i64 from_start_of_frame = (i64)(frame_ended_at - frame_started_at);
		i64 from_last_frame = (i64)(previous_frame_ended_at - frame_ended_at);

		i64 frame_time_1 = from_start_of_frame;
		i64 frame_time_2 = from_last_frame - max_frame_time_in_miliseconds;

		return
			(u32)(
				(i64)(
					((i64)(max_frame_time_in_miliseconds)) - ((i64)(frame_time_1))
					)
				)
			;
	}

#if DEBUG_PRINT_FPS_EVERY_SECOND
	u64 last_print = 0;
	std::vector<int> fps_data = std::vector<int>((size_t)120);

	void print_fps_every_second()
	{
		int fps = (previous_frame_ended_at - frame_ended_at);
		fps_data.push_back(fps);
		if (last_print - frame_ended_at < miliseconds_per_seconds)
		{
			int data_sum = 0;
			for (int datum : fps_data)
			{
				data_sum += datum;
			}
			int average_fps = data_sum / fps_data.size();
			SDL_Log("FPS: %d", average_fps);
			last_print = frame_ended_at;
			fps_data.clear();
		}
	}

#endif

};

struct GlobalState
{
public:
	Stack destruction_stack = Stack();
	MainLoopTiming main_timing = MainLoopTiming();
	bool did_init = false;
	bool do_run_main_loop = false;
	class Window* window = nullptr;
	class SpriteSheet* sheet = nullptr;

};

void initialization(GlobalState*);
void main_loop(GlobalState*);

void app_main()
{
	GlobalState state = GlobalState();

	initialization(&state);
	if (state.did_init == false)
	{
		return;
	}
	else
	{
		state.do_run_main_loop = true;
		while (state.do_run_main_loop)
		{
			state.main_timing.begin_frame();
			main_loop(&state);
			state.main_timing.end_frame();
		}
	}
}

class Window
{
public:

	static Window* create(GlobalState* state)
	{
		Window* window = new Window();
		state->destruction_stack.add(window, Window::destroy);

		window->sdl_handle_ = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT,
			0
		);
		if (window->sdl_handle_ == nullptr)
		{
			const char* error_message = SDL_GetError();
			Error("SDL_CreateWindow Failed", error_message);
			return nullptr;
		}
		else
		{
			window->main_surface_ = SDL_GetWindowSurface(window->sdl_handle_);
			if (window->main_surface_ == nullptr)
			{
				const char* error_message = SDL_GetError();
				Error("SDL_GetWindowSurface Failed", error_message);
				return nullptr;
			}
			else
			{
				return window;
			}
		}
	}

	void blit(SDL_Surface* src_surface, const SDL_Rect* src_rect, SDL_Rect* dist_rect)
	{
		SDL_BlitSurface(src_surface, src_rect, main_surface_, dist_rect);
	}

	void update()
	{
		int res = SDL_UpdateWindowSurface(sdl_handle_);
		if (res != 0)
		{
			const char* error_message = SDL_GetError();
			SilentError("SDL_UpdateWindowSurface Failed", error_message);
		}
	}

private:

	SDL_Window* sdl_handle_ = nullptr;
	SDL_Surface* main_surface_ = nullptr;

	static void destroy(void* ptr)
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("window destruction starts here.");
#endif

		Window* window = (Window*)ptr;
		if (window->sdl_handle_ != nullptr)
		{
			SDL_DestroyWindow(window->sdl_handle_);
			window->sdl_handle_ = nullptr;
		}
		delete window;

#if DEBUG_MESSAGE_DESTROY
		DebugLog("window destruction ends here.");
#endif
	}

};

class SpriteSheet
{
public:

	static SpriteSheet* create(GlobalState* state)
	{
		SpriteSheet* sheet = new SpriteSheet();
		state->destruction_stack.add(sheet, destroy);

		sheet->surface_ = SDL_LoadBMP(SPRITE_SHEET_FILE_NAME);
		if (sheet->surface_ == nullptr)
		{
			const char* error_message = SDL_GetError();
			Error("SDL_LoadBMP(SPRITE_SHEET_FILE_NAME) Failed", error_message);
			return nullptr;
		}
		else
		{
			return sheet;
		}
	}

	SDL_Surface* get()
	{
		return surface_;
	}

private:

	SDL_Surface* surface_ = nullptr;

	static void destroy(void* ptr)
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Sprite sheet destruction starts here.");
#endif

		SpriteSheet* sheet = (SpriteSheet*)ptr;
		if (sheet->surface_ != nullptr)
		{
			SDL_FreeSurface(sheet->surface_);
			sheet->surface_ = nullptr;
		}
		delete sheet;

#if DEBUG_MESSAGE_DESTROY
		DebugLog("Sprite sheet destruction ends here.");
#endif
	}

};

void initialization(GlobalState* state)
{
	state->did_init = true;

	state->window = Window::create(state);
	if (state->window == nullptr)
	{
		state->did_init = false;
		const char* error_message = SDL_GetError();
		Error("Window::create Failed", error_message);
		return;
	}

	state->sheet = SpriteSheet::create(state);

}

void main_loop(GlobalState* state)
{
	SDL_Event event = {};
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			state->do_run_main_loop = false;
		}
	}

	SDL_Rect src = {};
	src.x = 0;
	src.y = 0;
	src.w = 128;
	src.h = 128;
	SDL_Rect dist = {};
	dist.x = 100;
	dist.y = 100;
	dist.w = 128;
	dist.h = 128;
	state->window->blit(state->sheet->get(), &src, &dist);

	state->window->update();

}

