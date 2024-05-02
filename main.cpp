#define MAIN_LOOP_RATE_PER_SECOND 60
#define WINDOW_SCREEN_WIDTH 800
#define WINDOW_SCREEN_HEIGHT 600
#define WINDOW_TITLE "Game Window"
#define SPRITE_SHEET_FILE_NAME "art.bmp"
#define SPRITE_SIZE 16

#define DEBUG_PRINT_MAIN_LOOP_FPS_EVERY_SECOND 0
#define DEBUG_LOG_MAIN_LOOP_DELAY_TIME 0
#define DEBUG_MESSAGE_DESTROY 0

#if DEBUG_PRINT_MAIN_LOOP_FPS_EVERY_SECOND
#include <vector>
#endif

#include <iostream>
#include "SDL2/SDL.h"
#include "glm/glm.hpp"

typedef Sint8      i8;
typedef Sint16     i16;
typedef Sint32     i32;
typedef Sint64     i64;
typedef Uint8      u8;
typedef Uint16     u16;
typedef Uint32     u32;
typedef Uint64     u64;

typedef intptr_t   isize;
typedef uintptr_t  usize;

using glm::ivec2;
using glm::uvec2;

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
	Stack() = default;
	~Stack()
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Stack destruction starts here");
#endif

		StackNode* node = last_node_;
		while (node != nullptr)
		{
			if (node->destroy_routine_ != nullptr)
			{
				node->destroy_routine_(node->object_);
			}
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

		if (actual_delay > (i32)max_frame_time_in_milliseconds)
		{
			frame_time_method_2 = from_last_frame_ended - max_frame_time_in_milliseconds;
		}
		else
		{
			frame_time_method_2 = from_start_of_frame;
		}

		i32 frame_time = frame_time_method_2;

		if (frame_time >= (i32)max_frame_time_in_milliseconds)
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
	class InputSystem* input_system = nullptr;

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
		SDL_BlitScaled(src_surface, src_rect, main_surface_, dist_rect);
		// SDL_BlitSurface(src_surface, src_rect, main_surface_, dist_rect);
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

struct GameObject
{
public:
	ivec2 position() const
	{
		return position_;
	}

	uvec2 sprite_index() const
	{
		return sprite_index_;
	}

protected:
	ivec2 position_ = {};
	uvec2 sprite_index_ = {};
};

struct Ship : public GameObject
{
public:

	Ship()
	{
		position_.x = 100;
		position_.y = 100;
	}

	void move(const ivec2& dir)
	{
		position_ += speed_ * dir;
	}

private:
	i32 speed_ = 5;

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
		src.x = SPRITE_SIZE * object->sprite_index().x;
		src.y = SPRITE_SIZE * object->sprite_index().y;
		src.w = SPRITE_SIZE;
		src.h = SPRITE_SIZE;
		SDL_Rect dist = {};
		dist.x = object->position().x;
		dist.y = object->position().y;
		dist.w = SPRITE_SIZE * 4;
		dist.h = SPRITE_SIZE * 4;
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

class InputNode
{
private:
	friend class InputSystem;

	InputNode() = default;
	~InputNode() = default;

	void* object_ = nullptr;
	void (*input_proc_)(void* object, const SDL_Event* event) = nullptr;
	InputNode* next_ = nullptr;

};

class InputSystem
{
public:

	static InputSystem* create(GlobalState* state)
	{
		InputSystem* system = new InputSystem;
		state->destruction_stack.add(system, destroy);
		return system;
	}

	void process(const SDL_Event* event)
	{
		InputNode* node = next_;
		while (node != nullptr)
		{
			if (node->input_proc_ != nullptr)
			{
				node->input_proc_(node->object_, event);
			}
			node = node->next_;
		}

	}

	void add(void* object, void (*input_proc_)(void* object, const SDL_Event* event))
	{
		InputNode* new_node = new InputNode();
		new_node->object_ = object;
		new_node->input_proc_ = input_proc_;

		InputNode** node = &next_;
		while (*node != nullptr)
		{
			node = &((*node)->next_);
		}
		(*node) = new_node;
	}

private:

	InputNode* next_ = nullptr;

	static void destroy(void* ptr)
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Input system destruction starts here.");
#endif

		InputSystem* sys = (InputSystem*)ptr;

		InputNode* node = sys->next_;
		while (node != nullptr)
		{
			InputNode* next_node = node->next_;
			delete node;
			node = next_node;
		}

		delete sys;

#if DEBUG_MESSAGE_DESTROY
		DebugLog("Input system destruction ends here.");
#endif
	}

};

class IControlMapper
{
public:

protected:
	friend class ControlMapperManager;

	virtual void apply_control() = 0;

	virtual ~IControlMapper() = default;

private:

};

class ControlMapperManager
{
public:

	static ControlMapperManager* create(GlobalState* state)
	{
		ControlMapperManager* manager = new ControlMapperManager();
		state->destruction_stack.add(manager, destroy);
		return manager;
	}

	/// @brief 
	/// @tparam T should be of type IControlMapper
	/// @return 
	template<typename T>
	T* new_mapper()
	{
		T* mapper = new T();
		add_to_array(mapper);
		return mapper;
	}

	void apply_control()
	{
		for (int i = 0; i < array_size; i++)
		{
			array[i]->apply_control();
		}
	}

private:
	IControlMapper** array = nullptr;
	isize array_cap = 0;
	isize array_size = 0;


	void add_to_array(IControlMapper* mapper)
	{
		if (array_size == array_cap)
		{
			expand_array();
		}
		array[array_size] = mapper;
		array_size += 1;
	}

	void delete_array()
	{
		if (array != nullptr)
		{
			for (isize i = (array_size - 1); i > -1; i--)
			{
				delete array[i];
			}

			delete[] array;
		}
	}

	void copy_content_to_new_array(IControlMapper** new_array)
	{
		if (array != nullptr)
		{
			for (int i = 0; i < array_size; i++)
			{
				new_array[i] = array[i];
			}
		}
	}

	void expand_array()
	{
		static constexpr isize initial_cap = 32;
		isize new_cap = array_cap + initial_cap;
		IControlMapper** new_array = new IControlMapper * [new_cap];
		array_cap = new_cap;
		copy_content_to_new_array(new_array);
		delete_array();
		array = new_array;
	}

	ControlMapperManager()
	{
		expand_array();
	}

	~ControlMapperManager()
	{
		delete_array();
	}

	static void destroy(void* ptr)
	{
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Controller mapper manager destruction starts here.");
#endif
		ControlMapperManager* manager = (ControlMapperManager*)ptr;
		delete manager;
#if DEBUG_MESSAGE_DESTROY
		DebugLog("Controller mapper manager destruction ends here.");
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

	ControlMapperManager* control_mapper_manager = nullptr;
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

class AppQuitControlMapper : public IControlMapper
{
public:
	bool* do_run_main_loop_variable;

	void register_to_input_system(InputSystem* input_system)
	{
		input_system->add(this, process_input);
	}

protected:
	virtual void apply_control() override { }

private:
	void process_input(const SDL_Event* event)
	{
		if (event->type == SDL_QUIT)
		{
			(*do_run_main_loop_variable) = false;
		}
	}

	static void process_input(void* ptr, const SDL_Event* event)
	{
		((AppQuitControlMapper*)ptr)->process_input(event);
	}

};

class ShipMoveControlMapper : public IControlMapper
{
public:
	Ship* ship = nullptr;

	void register_to_input_system(InputSystem* input_system)
	{
		input_system->add(this, process_input);
	}

protected:

	virtual void apply_control() override
	{
		ship->move(direction);
	}

private:

	ivec2 direction = ivec2(0, 0);

	void process_input(const SDL_Event* event)
	{
		if (event->type == SDL_KEYDOWN)
		{
			if (event->key.repeat != 0)
			{
				return;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				direction.x -= 1;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				direction.x += 1;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_UP)
			{
				direction.y -= 1;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				direction.y += 1;
			}
		}
		else if (event->type == SDL_KEYUP)
		{
			if (event->key.repeat != 0)
			{
				return;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				direction.x += 1;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				direction.x -= 1;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_UP)
			{
				direction.y += 1;
			}
			else if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				direction.y -= 1;
			}
		}
	}

	static void process_input(void* ptr, const SDL_Event* event)
	{
		((ShipMoveControlMapper*)ptr)->process_input(event);
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

	state->input_system = InputSystem::create(state);
	if (state->input_system == nullptr)
	{
		state->did_init = false;
		Error("InputSystem::create Failed", "state->input_system == nullptr");
		return;
	}

	state->game_state = GameState::create(state);
	if (state->game_state == nullptr)
	{
		state->did_init = false;
		Error("GameState::create Failed", "state->game_state == nullptr");
		return;
	}

	state->game_state->control_mapper_manager = ControlMapperManager::create(state);
	if (state->game_state->control_mapper_manager == nullptr)
	{
		state->did_init = false;
		Error("ControlMapperManager::create Failed", "state->game_state->control_mapper_manager == nullptr");
		return;
	}

	AppQuitControlMapper* app_quit_control_map =
		state->game_state->control_mapper_manager->new_mapper<AppQuitControlMapper>();
	app_quit_control_map->do_run_main_loop_variable = &(state->do_run_main_loop);
	app_quit_control_map->register_to_input_system(state->input_system);

	ShipMoveControlMapper* ship_move_control_map
		= state->game_state->control_mapper_manager->new_mapper<ShipMoveControlMapper>();
	ship_move_control_map->ship = &(state->game_state->ship);
	ship_move_control_map->register_to_input_system(state->input_system);

}

void receive(InputSystem* input_system);
void think(GameState* game_state);
void present(GameState* game_state, SpriteSheet* sheet, Window* window);

void main_loop(GlobalState* state)
{
	receive(state->input_system);
	think(state->game_state);
	present(state->game_state, state->sheet, state->window);
}

void receive(InputSystem* input_system)
{
	SDL_Event event = {};
	while (SDL_PollEvent(&event))
	{
		input_system->process(&event);
	}
}

void think(GameState* game_state)
{
	game_state->control_mapper_manager->apply_control();

}

void present(GameState* game_state, SpriteSheet* sheet, Window* window)
{
	window->clear();

	sheet->blit(&(game_state->ship), window);

	window->update();
}


