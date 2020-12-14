#ifndef DAN_ENTITY_H_INCLUDED
#define DAN_ENTITY_H_INCLUDED

#include <array>
#include <memory>

#include <arashpartow/exprtk.h>
#include <sol/sol.hpp>

#include "../sprite/AbsRemderConf.h"
#include "../sprite/Renderable.h"

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
        typedef std::shared_ptr<Hitbox> hitbox_t;
        typedef std::shared_ptr<AbsRenderConf> disp_t;

    private:

        // x, y
        std::array<float, 2> pos;
        float startingTime;
        float rotation;
        float width;
        float height;
        bool autoGC;
        bool gc;

        // Each having one increases mem and construction penalty, but increases
        // performance frame-to-frame
        symbolTable_t symbols;
        expression_t exp;

        disp_t disp;

        sol::function hitCallback;

        void initEquation(Game &g, const std::string &eq);

    public:

        Entity();
        Entity(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation, float x, float y, float width, float height, bool autoGC);

        // Cannot move or copy due to symbol table
        // (I mean, COULD write custom move funcs, but nahhh)
        Entity(Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity &operator=(Entity&) = delete;
        Entity &operator=(Entity&&) = delete;

        void setParam(const std::string &name, const std::vector<float> &vector);
        void setParam(const std::string &name, float value);
        void setParam(const std::string &name, const std::string &string);

        bool isGC();
        bool isAutoGC();
        sol::function getHitCallback();

        void run();
        void render(Context &c) override;

    };
}

#endif
