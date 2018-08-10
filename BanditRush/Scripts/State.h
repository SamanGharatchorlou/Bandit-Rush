#pragma once

// abstract class to be inherited by all game state objects
namespace srac
{
	struct State
	{
		// pure virtual functions - require override
		virtual void init() = 0;
		virtual void preProcess() = 0;
		virtual void update(float dt) = 0;
		virtual void handleInput() = 0;
		virtual void draw() = 0;


		// optional functions
		virtual void pause() {  }
		virtual void resume() {  }

		virtual void exit() {  }
	};


}