#ifndef DANZUN_ENTITY_H_INCLUDED
#define DANZUN_ENTITY_H_INCLUDED

#include <array>
#include <memory>
#include <vector>
#include <set>
#include <string>

#include <arashpartow/exprtk.hpp>
#include <sol/sol.hpp>

#include "Renderable.h"
#include "Element.h"
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
        typedef std::shared_ptr<Element> disp_t;

    private:
        std::weak_ptr<Entity> self;

        // x, y
        std::array<float, 2> pos;
        std::array<float, 2> pivot; // For polygon

        float startingTime;
        float rotation; // For polygon
        float width;
        float height;
        float autoGC;
        float gc;
        float display;
        float tangible;

        // Each having one increases mem and construction penalty, but increases
        // performance frame-to-frame
        symbolTable_t symbols;
        expression_t exp;

        disp_t disp;

        sol::function hitCallback;

        api::Script script;

        std::set<std::string> groups;
        int renderPriority;

        void initEquation(Game &g, const std::vector<symbolTable_t> &symbols, const std::string &eq);

        bool f2b(float f);
        float b2f(bool b);

    public:

        Entity(
            Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation,
            const std::vector<symbolTable_t> &as
        );

        static std::shared_ptr<Entity> make(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation,
            const std::vector<symbolTable_t> &as);

        // Cannot default move or copy due to symbol table referencing members
        Entity(Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity &operator=(Entity&) = delete;
        Entity &operator=(Entity&&) = delete;

        symbolTable_t &getTable();

        float getX() const;
        float getY() const;
        float getPivotX() const;
        float getPivotY() const;
        float getWidth() const;
        float getHeight() const;
        float getRotation() const;

        int getRenderPriority();
        void setRenderPriority(int value);

        std::set<std::string> &getGroups();

        void setScript(const api::Script &s);

        bool isGC();
        bool isAutoGC();
        bool isTangible();
        sol::function getHitCallback();

        void run(sol::state_view lua);
        void render(Context &c) override;

    };
}

#endif
