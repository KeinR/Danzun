#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

struct other {
    int *fefesf = new int(22);
    ~other() {
        std::cout << "Other dtor callled" << '\n';
        delete fefesf;
    }
};

struct ff {
    other o;
    ff() {
        std::cout << "ff ctor" << '\n';
    }
    void run(sol::table table) {
        std::cout << "table size = " << table.size() << '\n';
        for (int i = 1; i <= table.size(); i++) {
            std::cout << "Hello, " << table.get<int>(i) << '\n';
        }
    }
};

int main () {
	sol::state lua;
    
	lua.set_function("bark", [](sol::this_state s, int a, int b ){
		lua_State* L = s; // current state
		return a + b + lua_gettop(L);
	});
	
	lua.script("first = bark(2, 2)"); // only takes 2 arguments, NOT 3
		
	// Can be at the end, too, or in the middle: doesn't matter
	// lua.set_function("bark", []( int a, int b, sol::state_view s ){
	// 	lua_State* L = s; // current state
	// 	return a + b + lua_gettop(L);
	// });

	lua.script("second = bark(2, 2)"); // only takes 2 arguments
	int first = lua["first"];
	assert(first == 6);
	int second = lua["second"];
	assert(second == 6);

    sol::usertype<ff> player_type = lua.new_usertype<ff>("ff", sol::constructors<ff()>());

	// typical member function that returns a variable
	player_type["run"] = &ff::run;


	lua.script("f = ff.new() \n f:run({4, 3, 2, 1, 0, -1})"); // only takes 2 arguments, NOT 3

	return 0;
}