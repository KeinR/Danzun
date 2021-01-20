#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <vector>
#include <map>
#include <utility>
#include <list>
#include <unordered_set>
#include <memory>

#include <sol/sol.hpp>
#include <arashpartow/exprtk.hpp>

#include "../time/Timer.h"
#include "Group.h"
#include "Entity.h"
#include "../time/Clock.h"
#include "Player.h"
#include "../audio/Speaker.h"
#include "../win/enums.h"

namespace dan {
    class Context;
    class Engine;
}

namespace dan {
    /**
     * The game singleton, takes care of really everything related to
     * the game such as entity management, hitbox collisions, rendering,
     * garbage collection, etc.
     * */
    class Game {
    public:
        /// The entity type
        typedef std::shared_ptr<Entity> entity_t;
        /// The collsions restult type (from running groups)
        typedef std::vector<std::pair<entity_t, entity_t>> collisionResult_t;
        /// A list of entitys
        typedef std::list<entity_t> entities_t;
        /// A single renderable object (that has a render() method)
        typedef std::shared_ptr<Renderable> renderable_t;
        /// Queue for renderable objects that want to be removed from
        /// the render loop
        typedef std::unordered_set<Renderable*> remRenderQueue_t;
        /// The render loop (queue), sorted by priority
        typedef std::multimap<int, renderable_t, std::less<int>> renderQueue_t;
        /// The audio speaker type
        typedef std::shared_ptr<audio::Speaker> speaker_t;
        /// A set of speakers
        typedef std::unordered_set<speaker_t> speakers_t;
        /// A vector of keys
	typedef std::vector<keyt> pkeys_t;
    private:
        /// The parent driving engine
        Engine *engine;

        /// The game speed; factor applied to the
        /// change in time (delta time)
        float speed;
        /// If the game is running, and therefore
        // should update hitboxes and garbage collect, etc.
        bool running;

        /// The width of the game area
        int width;
        /// The height of the game area
        int height;

        /// Factor applied to the autoGC radius
        /// (before the constant is added)
        float gcFactor;
        /// Constant applied to the audoGC radius
        float gcConstant;

        /// Timer for when to run the garbage collector
        /// Runs off of real time, not game time
        Timer gcTimer;
        /// Used to keep track of the game time
        Clock clock;

        Player player;

        /// The hitboxes, organized into groups
        std::map<std::string, Group> groups;

        /// The entities
        entities_t entities;
        /// Elements that are a part of the render loop
        renderQueue_t renderQueue;
        /// Elements waiting to be removed from the render loop
        /// To avoid problems arising from concurrent modification
        remRenderQueue_t remRenderQueue;

        /// Global expression symbols
        /// Should be applied to all expressions
        Entity::symbolTable_t globalSymbols;

        /// Speakers that are currently playing.
        /// Prevents them from being destructed before
        /// the finish playing
        speakers_t speakers;

        /// @{
        /// Keys relating to player movement
	pkeys_t upKeys;
	pkeys_t downKeys;
	pkeys_t leftKeys;
	pkeys_t rightKeys;
        /// @}

        /**
         * Clean up loose memory
         * */
        void gc();
        /**
         * Delete an entity and clean up its hooks
         * */
        entities_t::iterator eraseEntity(const entities_t::iterator &it);
        /**
         * Get of one of a list of keys is pressed
         * \param keys The keys
         * \return true if yes
         * */
	bool arePressed(const pkeys_t &keys);

    public:
        /**
         * Construct a game with a parent engine
         * \param e The engine
         * */
        Game(Engine &e);

        /// @{
        /**
         * Get direction keys
         * \return The keys
         * */
	pkeys_t &getUpKeys();
	pkeys_t &getDownKeys();
	pkeys_t &getLeftKeys();
	pkeys_t &getRightKeys();
        /// @}

        /**
         * \return The parent engine
         * */
        Engine &getEngine() const;
        /**
         * \return The game time clock
         * */
        Clock &getClock();
        /**
         * \return The player
         * */
        Player &getPlayer();
        /**
         * \return The global symbol table
         * */
        Entity::symbolTable_t &getGlobalSymbols();

        /**
         * Add a speaker to this game's monitor.
         * It will stay alive as long as it's playing
         * */
        void addSpeaker(const speaker_t &speaker);

        /**
         * Get a hitbox group by name
         * If it doesn't exist, it is created
         * \param name The name of the group
         * \return The group
         * */
        Group &getGroup(const std::string &name);
        /**
         * Delete all groups
         * */
        void clearGroups();
        /**
         * Clear the content of all groups
         * */
        void resetGroups();
        /**
         * Search and delete for a given entity's hitboxes
         * through all groups
         * \param ptr The entity
         * */
        void remFromGroups(Entity *ptr);
        /**
         * Test collisions between two groups.
         * Returns an array of pairs that represent the collision pairs for each collsion
         * */
        collisionResult_t testCollisions(const std::string &a, const std::string &b);

        /**
         * Add a new entity
         * \param e The entity
         * */
        void addEntity(const entity_t &e);
        /**
         * Add a new renderable to the render loop
         * \param priority The render priority
         * \param rend The renderable
         * */
        void submitRenderable(int priority, const renderable_t &rend);
        /**
         * Deletes the given renderable from the render loop
         * (only executes at the start of the next cycle)
         * */
        void removeRenderable(Renderable *rend);

        /// @{
        /**
         * Set game properties
         * */
        void setWidth(int w);
        void setHeight(int h);
        void setGCFactor(float f);
        void setGCConstant(float c);
        void setRunning(bool v);
        void setSpeed(float v);
        void setGCTimeMilliseconds(unsigned int v);
        /// @{

        /// @{
        /**
         * Get game properties
         * */
        int getWidth();
        int getHeight();
        float getGCFactor();
        float getGCConstant();
        bool isRunning();
        float getSpeed();
        unsigned int getGCTimeMilliseconds();
        /// @{

        /**
         * Execute game logic (garbage collection, hitbox
         * invalidation, time advancement, player movement...)
         * \note WILL NOT EXECUTE if running has not yet been set to true
         * \param deltaTime The ammount of game time that has passed
         * */
        void logic(float deltaTime);
        /**
         * Removes those in the remove queue, then renders
         * those in the render queue (loop)
         * \param c The render context
         * */
        void render(Context &c);

        /**
         * Gets the game object from the lua state
         * \param lua The state
         * \return The game
         * */
        static Game &fromLua(sol::state_view lua);
    };
}

#endif
