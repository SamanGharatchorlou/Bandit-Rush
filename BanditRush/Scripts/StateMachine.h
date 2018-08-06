#pragma once

#include "State.h"
#include <memory>
#include <stack>
#include <vector>

namespace srac
{
	typedef std::unique_ptr<State> stateRef;

	class StateMachine
	{
	private:
		stateRef _newState;
		std::stack<stateRef> _states;

		bool _isAdding, _isRemoving, _isReplacing;

	public:
		void addState(stateRef state);
		void removeState();
		void replaceState(stateRef state);
		void clearStates();

		int stateCount();

		void processStateChanges();

		stateRef& getActiveState();
	};
}