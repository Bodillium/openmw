#ifndef GAME_MWMECHANICS_AIWANDER_H
#define GAME_MWMECHANICS_AIWANDER_H

#include "aipackage.hpp"

#include <vector>

#include <OgreVector3.h>

#include "pathfinding.hpp"
#include "obstacle.hpp"

#include "../mwworld/timestamp.hpp"


#include "aistate.hpp"

namespace ESM
{
    namespace AiSequence
    {
        struct AiWander;
    }
}

namespace MWMechanics
{    
    
    
    /// \brief Causes the Actor to wander within a specified range
    class AiWander : public AiPackage
    {
        public:
            /// Constructor
            /** \param distance Max distance the ACtor will wander
                \param duration Time, in hours, that this package will be preformed
                \param timeOfDay Start time of the package, if it has a duration. Currently unimplemented
                \param idle Chances of each idle to play (9 in total)
                \param repeat Repeat wander or not **/
            AiWander(int distance, int duration, int timeOfDay, const std::vector<unsigned char>& idle, bool repeat);

            AiWander (const ESM::AiSequence::AiWander* wander);

            

            virtual AiPackage *clone() const;

            virtual bool execute (const MWWorld::Ptr& actor, AiState& state, float duration);

            virtual int getTypeId() const;

            /// Set the position to return to for a stationary (non-wandering) actor
            /** In case another AI package moved the actor elsewhere **/
            void setReturnPosition (const Ogre::Vector3& position);

            virtual void writeState(ESM::AiSequence::AiSequence &sequence) const;

            
            enum GreetingState {
                Greet_None,
                Greet_InProgress,
                Greet_Done
            };
        private:
            // NOTE: mDistance and mDuration must be set already
            void init();
            
            void stopWalking(const MWWorld::Ptr& actor);
            void playIdle(const MWWorld::Ptr& actor, unsigned short idleSelect);
            bool checkIdle(const MWWorld::Ptr& actor, unsigned short idleSelect);
            void getRandomIdle(unsigned short& playedIdle);

            int mDistance; // how far the actor can wander from the spawn point
            int mDuration;
            int mTimeOfDay;
            std::vector<unsigned char> mIdle;
            bool mRepeat;

            

            bool mHasReturnPosition; // NOTE: Could be removed if mReturnPosition was initialized to actor position,
                                    // if we had the actor in the AiWander constructor...
            Ogre::Vector3 mReturnPosition;



           

            // if false triggers calculating allowed nodes based on mDistance
            bool mStoredAvailableNodes;


            

            MWWorld::TimeStamp mStartTime;

            // allowed pathgrid nodes based on mDistance from the spawn point
            std::vector<ESM::Pathgrid::Point> mAllowedNodes;
            ESM::Pathgrid::Point mCurrentNode;
            bool mTrimCurrentNode;
            void trimAllowedNodes(std::vector<ESM::Pathgrid::Point>& nodes,
                                  const PathFinder& pathfinder);

//             PathFinder mPathFinder;

//             ObstacleCheck mObstacleCheck;
            float mDoorCheckDuration;
            int mStuckCount;


    };
    
    
}

#endif
