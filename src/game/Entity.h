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
    /**
     * A single game entity.
     * This is the foundation of the engine.
     * An entity is a multipurpose class that supports
     * hitboxes, expressions, rendering, and scripting.
     * */
    class Entity: public Renderable {
    public:
        /// Type of the symbol table
        typedef exprtk::symbol_table<float> symbolTable_t;
        /// Type of the expression
        typedef exprtk::expression<float> expression_t;
        /// Type of the expression parser
        typedef exprtk::parser<float> parser_t;
        /// Type of the display element
        typedef std::shared_ptr<Element> disp_t;

    private:
        /// Weak reference to self to allow for
        // passing a shared ref of self to callbacks,
        // while not creating a mem leak
        std::weak_ptr<Entity> self;

        /// The x/y position of the entity
        std::array<float, 2> pos;
        /// The pivot x/y position of the entity
        /// Used by the polygon hitbox
        std::array<float, 2> pivot;

        /// The game time at which the entity
        // was created (or is supposed to be)
        float startingTime;
        /// The rotation of the entity, in radians
        /// Used by the polygon hitbox
        float rotation;
        /// The width of the entity
        float width;
        /// The height of the entity
        float height;
        /// If this entity should be considered during
        /// the game's autoGC runs
        float autoGC;
        /// If this entity should be deleted
        float gc;
        /// If this entity should be rendered
        float display;
        /// If this entity's hitboxes should be enabled.
        /// So, if false, effectively disables hitbox collisions for
        /// this entity
        float tangible;

        /// The symbols local to this entity
        symbolTable_t symbols;
        /// The expression
        expression_t exp;

        /// The display function (for rendering)
        /// )can be null)
        disp_t disp;

        /// Callback called when the entity comes on contact with another
        sol::function hitCallback;

        /// Script that executes custom, scheduled events
        /// (can be empty)
        api::Script script;

        /// Groups that this entity's hitboxes reside in
        std::set<std::string> groups;
        /// This entity's render priority
        int renderPriority;

        /// If this entity has been added to the render loop
        bool activated;

        sol::table luaTable;
        bool tableInit;

        /***
         * Initializes the expession
         * */
        void initEquation(Game &g, const std::vector<symbolTable_t> &symbols, const std::string &eq);

        /**
         * Static casts a float to a bool
         * \param f The float
         * \return The bool representation
         * */
        bool f2b(float f);
        /**
         * Static casts a bool to a float
         * \param b The bool
         * \return The floating point representation
         * */
        float b2f(bool b);

    public:

        /**
         * DO NOT CALL - USE THE FACTORY!
         * Ony public bc templates.
         * 
         * Constructs an entity.
         * \param g The game singleton
         * \param hitCallback The hit callback, called on collisions
         * \param disp The function for rendering the entity (can be null)
         * \param equation The equation representing the behavior of the entity
         * \parama as Symbol tables to register with the expression before creation
         * */
        Entity(
            Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation,
            const std::vector<symbolTable_t> &as
        );

        /**
         * Factory method that creates an entity.
         * See ctor for param desc
         * */
        static std::shared_ptr<Entity> make(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation,
            const std::vector<symbolTable_t> &as);

        /// @{
        /**
         * Cannot use deafult move/copy because of how the symbol table
         * is reference counted, and it references member variables.
         * If the need arises, must write cusom
         * */
        Entity(Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity &operator=(Entity&) = delete;
        Entity &operator=(Entity&&) = delete;
        /// @}

        /**
         * \return The expression symbol table
         * */
        symbolTable_t &getTable();

        /**
         * \return true if the entity has been added to the render loop
         * */
        bool isActivated();
        /**
         * Set if the entity has been added to the render loop
         * \param true if yes
         * */
        void setActivated(bool value);

        /// @{
        /**
         * Get properties of the entity.
         * See variable decl. for detail
         * \return The value
         * */
        float getX() const;
        float getY() const;
        float getPivotX() const;
        float getPivotY() const;
        float getWidth() const;
        float getHeight() const;
        float getRotation() const;
        bool isGC();
        bool isAutoGC();
        bool isTangible();
        sol::function getHitCallback();
        /// @{

        sol::table getLuaTable(sol::state_view lua);

        /**
         * \return The render priority
         * */
        int getRenderPriority();
        /**
         * Set the render priority
         * \param value The new render priority
         * */
        void setRenderPriority(int value);

        /**
         * Get the hitbox groups - groups that
         * contain this entity's hitboxes.
         * \return The groups
         * */
        std::set<std::string> &getGroups();

        /**
         * Set the script for this entity
         * The script will be executed regularly on calls to \ref run
         * */
        void setScript(const api::Script &s);

        /**
         * Runs logic for this entity - expression and script
         * execution
         * */
        void run(sol::state_view lua);

        /**
         * If disp is not null and \ref display is not set to false,
         * calls augRender on it.
         * That is, it renders the entity
         * */
        void render(Context &c) override;

    };
}

#endif
