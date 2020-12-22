#ifndef DAN_ENTITY_H_INCLUDED
#define DAN_ENTITY_H_INCLUDED

#include <array>
#include <memory>
#include <vector>

#include <arashpartow/exprtk.hpp>
#include <sol/sol.hpp>

#include "../api/RenderConfig.h"
#include "../sprite/Renderable.h"
#include "../sprite/AbsRenderConf.h"
#include "../api/Script.h"

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
        typedef std::shared_ptr<AbsRenderConf> disp_t;
        typedef std::vector<std::pair<std::string, float>> constants_t;

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

        api::Script script;

        void initEquation(const std::vector<symbolTable_t> &symbols, const constants_t &constants, const std::string &eq);

        bool f2b(float f);
        float b2f(bool b);

    public:

        Entity(
            Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation,
            const std::vector<symbolTable_t> &as, const constants_t &constants,
            float x, float y, float width, float height, bool autoGC
        );

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
        float getRotation() const;

        // `self` == this
        void setScript(const std::shared_ptr<Entity> &self, sol::state_view lua, sol::function func, const std::vector<sol::object> &params);

        void setParam(const std::string &name, float value);

        // NB: This action is irreversible!
        void regSymbolTable(symbolTable_t &table);

        bool isGC();
        bool isAutoGC();
        sol::function getHitCallback();

        void run(sol::state_view lua);
        void render(Context &c) override;

    };
}

#endif
