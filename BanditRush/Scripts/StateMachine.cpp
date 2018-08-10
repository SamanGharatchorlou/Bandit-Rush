#include "StateMachine.h"

#include <iostream>
namespace srac
{
	void StateMachine::addState(stateRef state)
	{
		_isAdding = true;
		_isRemoving = false;
		_isReplacing = false;
		_newState = std::move(state);
	}

	void StateMachine::removeState()
	{
		_isRemoving = true;
		_isAdding = false;
		_isReplacing = false;

		if (_states.size() == 0)
			std::cout << "no states!" << std::endl;
	}

	void StateMachine::replaceState(stateRef state)
	{
		_isReplacing = true;
		_isAdding = false;
		_isRemoving = false;
		_newState = std::move(state);
	}

	void StateMachine::processStateChanges()
	{
		// add new state
		if (_isAdding)
		{
			_states.push(std::move(_newState));
			_states.top()->init();

			_isAdding = false;
		}
		// remove top state
		else if (_isRemoving)
		{
			if (_states.size() > 1)
			{
				_states.pop();
				_states.top()->resume();
			}

			_isRemoving = false;
		}
		// replace top state
		else if (_isReplacing)
		{
			if (_states.size() > 0)
			{
				_states.pop();

				_states.push(std::move(_newState));
				_states.top()->init();

				_isReplacing = false;
			}
		}
	}

	void StateMachine::clearStates()
	{
		while (_states.size() > 1)
		{
			_states.pop();
		}
	}

	stateRef& StateMachine::getActiveState()
	{
		if(_states.size() > 0)
			return _states.top();
		else
		{
			std::cout << "no state" << std::endl;
		}
	}

	int StateMachine::stateCount()
	{
		return _states.size();
	}

}