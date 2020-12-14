#ifndef DAN_ENTITY_H_INCLUDED
#define DAN_ENTITY_H_INCLUDED

#include <array>
#include <memory>

#include <arashpartow/exprtk.hpp>
#include <sol/sol.hpp>

#include "../api/RenderConfig.h"
#include "../sprite/Renderable.h"
#include "LuaRef.h"

namespace dan {
    class Game;
    class Context;
}

namespace dan {
    class Entity: public Renderable {
    public:
        typedef exprtk::symbol_table<float> symbolTable_t;
        typedef exprtk::expression<float> expression_t;
        typedef exprtk::parser<float> parser_t;
        typedef LuaRef<api::RenderConfig> disp_t;

        bool f2b(float f);
        float b2f(bool b);

    private:

        // x, y
        std::array<float, 2> pos;
        float startingTime;
        float rotation;
        float width;
        float height;
        float autoGC;
        float gc;

        // Each having one increases mem and construction penalty, but increases
        // performance frame-to-frame
        symbolTable_t symbols;
        expression_t exp;

        disp_t disp;

        sol::function hitCallback;

        void initEquation(Game &g, const std::string &eq);

    public:

        Entity(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation, float x, float y, float width, float height, bool autoGC);

        // Cannot move or copy due to symbol table
        // (I mean, COULD write custom move funcs, but nahhh)
        Entity(Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity &operator=(Entity&) = delete;
        Entity &operator=(Entity&&) = delete;

        // TODO: Seperation of sprite and hitbox
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
        int getRotation() const;

        void setParam(const std::string &name, float value);

        bool isGC();
        bool isAutoGC();
        sol::function getHitCallback();

        void run();
        void render(Context &c) override;

    };
}

#endif
