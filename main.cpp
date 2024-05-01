#include "pch.hpp"

#include "game_objects.hpp"

using namespace ab;

#define MAIN_LOOP_RATE_PER_SECOND 60
#define WINDOW_SCREEN_WIDTH 800
#define WINDOW_SCREEN_HEIGHT 600
#define WINDOW_TITLE "Game Window"
#define SPRITE_SHEET_FILE_NAME "art.bmp"
#define SPRITE_SIZE 128

#define DEBUG_PRINT_MAIN_LOOP_FPS_EVERY_SECOND 0
#define DEBUG_LOG_MAIN_LOOP_DELAY_TIME 0
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
	static constexpr u64 max_frame_time_in_milliseconds =
		(u64)(
			(((double)(one_second)) / ((double)(MAIN_LOOP_RATE_PER_SECOND)))
			* ((double)(miliseconds_per_seconds))
			);

	static u64 get_tick()
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
		previous_frame_ended_at = frame_ended_at;
		frame_ended_at = get_tick();
		calculate_delay_time();

#if DEBUG_PRINT_MAIN_LOOP_FPS_EVERY_SECOND

		print_fps_every_second();
#endif

		if (delay_time > 0)
		{
#if DEBUG_LOG_MAIN_LOOP_DELAY_TIME
			SDL_Log("delay time: %u", delay_time);
#endif
			SDL_Delay(delay_time);
		}
	}

private:

	u64 frame_started_at = 0;
	u64 frame_ended_at = 0;
	u64 previous_frame_ended_at = 0;
	u32 delay_time = 0;
	u32 previous_delay_time = 0;


	void calculate_delay_time()
	{
		previous_delay_time = delay_time;

		i32 actual_delay = (i32)(frame_started_at - previous_frame_ended_at);
		i32 from_start_of_frame = (i32)(frame_ended_at - frame_started_at);
		i32 from_last_frame_ended = (i32)(frame_ended_at - previous_frame_ended_at);

		// i32 frame_time_method_1 = from_start_of_frame;
		i32 frame_time_method_2 = 0;

		if (actual_delay > max_frame_time_in_milliseconds)
		{
			frame_time_method_2 = from_last_frame_ended - max_frame_time_in_milliseconds;
		}
		else
		{
			frame_time_method_2 = from_start_of_frame;
		}

		i32 frame_time = frame_time_method_2;

		if (frame_time >= max_frame_time_in_milliseconds)
		{
			delay_time = 0;
		}
		else
		{
			delay_time = max_frame_time_in_milliseconds - frame_time;
		}
	}

#if DEBUG_PRINT_MAIN_LOOP_FPS_EVERY_SECOND
	u64 last_print = 0;
	std::vector<int> fps_data = std::vector<int>((size_t)120);

	void print_fps_every_second()
	{
		int fps = 0;
		int frame_time = (int)(frame_ended_at - previous_frame_ended_at);
		if (frame_time > 0)
		{
			fps = (int)miliseconds_per_seconds / frame_time;
		}
		fps_data.push_back(fps);
		if (frame_ended_at - last_print > miliseconds_per_seconds)
		{
			int data_sum = 0;
			for (int datum : fps_data)
			{
				data_sum += datum;
			}
			isize average_fps = data_sum / fps_data.size();
			SDL_Log("FPS: %lld", average_fps);
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
	bool did_init = false;
	bool do_run_main_loop = false;
	class Window* window = nullptr;
	class SpriteSheet* sheet = nullptr;
	class GameState* game_state = nullptr;

};

void initialization(GlobalState*);
void main_loop(GlobalState*);

void app_main()
{
	GlobalState state = GlobalState();
	MainLoopTiming timing = MainLoopTiming();

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
			timing.begin_frame();
			main_loop(&state);
			timing.end_frame();
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

	void clear()
	{
		SDL_FillRect(main_surface_, nullptr, 0x000000);
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

	void blit(const GameObject* object, Window* window)
	{
		SDL_Rect src = {};
		src.x = SPRITE_SIZE * object->sprite_index_x;
		src.y = SPRITE_SIZE * object->sprite_index_y;
		src.w = SPRITE_SIZE;
		src.h = SPRITE_SIZE;
		SDL_Rect dist = {};
		dist.x = object->pos_x;
		dist.y = object->pos_y;
		dist.w = SPRITE_SIZE;
		dist.h = SPRITE_SIZE;
		window->blit(surface_, &src, &dist);
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

class GameState
{
public:
	static GameState* create(GlobalState* state)
	{
		GameState* game_state = new GameState();
		state->destruction_stack.add(game_state, destroy);

		return game_state;
	}

	Ship ship = {};

private:

	static void destroy(void* ptr)
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Game state destruction starts here.");
#endif

		GameState* game_state = (GameState*)ptr;
		delete game_state;

#if DEBUG_MESSAGE_DESTROY
		DebugLog("Game state destruction ends here.");
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
	if (state->sheet == nullptr)
	{
		state->did_init = false;
		Error("SpriteSheet::create Failed", "state->sheet == nullptr");
		return;
	}

	state->game_state = GameState::create(state);
	if (state->game_state == nullptr)
	{
		state->did_init = false;
		Error("GameState::create Failed", "state->game_state == nullptr");
		return;
	}
}

void main_loop(GlobalState* global_state)
{
	GameState* game_state = global_state->game_state;
	Ship* ship = &(game_state->ship);

	SDL_Event event = {};
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			global_state->do_run_main_loop = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				ship->pos_x -= ship->speed;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				ship->pos_x += ship->speed;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				ship->pos_y -= ship->speed;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				ship->pos_y += ship->speed;
			}
		}
	}

	global_state->window->clear();

	global_state->sheet->blit(ship, global_state->window);

	global_state->window->update();

}

