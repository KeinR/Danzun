#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

// #include <arashpartow/exprtk.hpp>

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include <unordered_map>
#include <map>

#include <cstdio>

struct other {
    int *fefesf = new int(22);
	std::map<std::string, int> some_map;
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
    void run(sol::userdata othe) {
		// std::cout << othe->o->fefesf << '\n';
		std::cout << *othe.as<ff*>()->o.fefesf << '\n';
    }
};

template<typename T>
struct hashFunc {
	std::size_t operator()(const T& o) const {
		return static_cast<std::size_t>(o.registry_index());
	}
};

template<typename T>
struct lessThan {
	bool operator()(const T& self, const T& o) const {
		return self.registry_index() < o.registry_index();
	}
};

int main () {
	sol::state lua;
    
	lua.set_function("bark", [](sol::this_state s, int a, int b ){
		lua_State* L = s; // current state
		return a + b + lua_gettop(L);
	});
	
	lua.script("first = { a =  \"fweg\"}"); // only takes 2 arguments, NOT 3
		
	// Can be at the end, too, or in the middle: doesn't matter
	// lua.set_function("bark", []( int a, int b, sol::state_view s ){
	// 	lua_State* L = s; // current state
	// 	return a + b + lua_gettop(L);
	// });

	lua.script("second = { 32 , 235, 3}"); // only takes 2 arguments
	// int first = lua["first"];
	// assert(first == 6);
	// int second = lua["second"];
	// assert(second == 6);

    sol::usertype<ff> player_type = lua.new_usertype<ff>("ff", sol::constructors<ff()>());

	// typical member function that returns a variable
	player_type["run"] = &ff::run;


	lua.script("f = ff.new() \n b = ff.new() \n f:run(b)"); // only takes 2 arguments, NOT 3

	// std::map<sol::table, std::string, lessThan<sol::table>> someMap;

	// someMap[lua["first"].get_or_create<sol::table>()] = "fesg";
	// someMap[lua["second"].get_or_create<sol::table>()] = "22";


	// typedef exprtk::symbol_table<double> symbol_table_t;
   	// typedef exprtk::expression<double>     expression_t;
	// typedef exprtk::parser<double>             parser_t;

	// std::string expression_string = R"(
	// 	v[0] := v[0] - 10;
	// 	x := x + 1;
	// 	x := { 3 , 4 };
	// 	result1 := 'I am t';
	// 	x;
	// )";

	// std::string expression_string =
	// 				" var x := 123.456;\n     "
	// 				" var s := 'ijk';\n       "
	// 				" result0 := x + 78.90;\n "
	// 				" result1 := s + '123';\n  ";

	// std::string expression_string = R"(
	// 	var x := 123.456;
	// 	var s := 'ijk';
	// 	result0 := x + 78.90;
	// 	result1 := s + '123';
	// )";

	// double result0;
	// std::string result1;
	// // float y = 31;

	// std::array<double, 2> vec = {
	// 	44,
	// 	55
	// };

	// symbol_table_t symbol_table;
	// symbol_table.add_variable("result0", result0);
	// symbol_table.add_vector("v", vec.data(), vec.size());
	// symbol_table.add_stringvar("result1", result1);
	// // symbol_table.add_variable("y", y);
	// // symbol_table.add_constants();

	// expression_t expression;
	// expression.register_symbol_table(symbol_table);

	// parser_t parser;
	// parser.enable_unknown_symbol_resolver();
	// if (!parser.compile(expression_string,expression)) {
	// 	std::cerr << "Exp err: " << parser.error().c_str() << '\n';
	// 	return 1;
	// }

	// std::cout << "vec[0] = " << vec[0] << '\n';
	// std::cout << "expression.value() = " << expression.value() << '\n';
	// std::cout << "expression.value() = " << expression.value() << '\n';
	// std::cout << "expression.value() = " << expression.value() << '\n';
	// std::cout << "vec[0] = " << vec[0] << '\n';
	// std::cout << "result1 = " << result1 << '\n';

	// typedef exprtk::symbol_table<float> symbol_table_t;
	// typedef exprtk::expression<float>     expression_t;
	// typedef exprtk::parser<float>             parser_t;

	// std::string expression_string =
	// 				" var x := 123.456;     "
	// 				" var s := 'ijk';       "
	// 				" result0 := x + 78.90; "
	// 				" result1 := s + '123'  ";

	// float      result0;
	// std::string result1;

	// symbol_table_t symbol_table;
	// symbol_table.add_variable ("result0",result0);
	// symbol_table.add_stringvar("result1",result1);

	// expression_t expression;
	// expression.register_symbol_table(symbol_table);

	// parser_t parser;
	// parser.compile(expression_string,expression);

	// expression.value();

	// printf("Result0: %15.5f\n", result0        );
	// printf("Result1: %s\n"    , result1.c_str());

	return 0;
}
