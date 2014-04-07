//GameObject.hpp
#ifndef _GameObject_hpp_included_
#define _GameObject_hpp_included_

#include <InputComponent.hpp>
#include <PhysicsComponent.hpp>
#include <GraphicsComponent.hpp>
#include <CombatComponent.hpp>
#include <SocialComponent.hpp>

#include <DataTypes.hpp>

#include <vector>


//============GameObject====================
//
class GameObject {
public:

									GameObject( InputComponent*,
												PhysicsComponent*,
												GraphicsComponent*,
												CombatComponent*,
												SocialComponent* );

	void							update(float, struct config*, World&);

	InputComponent*&				getInput();
	PhysicsComponent*&				getPhysics();
	GraphicsComponent*&				getGraphics();
	CombatComponent*&				getCombat();
	SocialComponent*&				getSocial();

	void							setInput(InputComponent*);
	void							setPhysics(PhysicsComponent*);
	void							setGraphics(GraphicsComponent*);
	void							setCombat(CombatComponent*);
	void							setSocial(SocialComponent*);


private:

	InputComponent*					mInput;
	PhysicsComponent*				mPhysics;
	GraphicsComponent*				mGraphics;
	CombatComponent*				mCombat;
	SocialComponent*				mSocial;

};
//
//==========================================


#endif