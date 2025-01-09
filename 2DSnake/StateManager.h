#pragma once
#include <stack>
#include <memory>
#include "State.h"

using namespace std;

namespace Engine {
	class StateManager
	{
	private:
		stack<unique_ptr<State>> m_stateStack;
		unique_ptr<State> m_newState;

		bool m_add;
		bool m_replace;
		bool m_remove;

	public:

		StateManager() {};
		~StateManager() {};

		void add(unique_ptr<State> toAdd, bool replace = false) {};
		void popCurrent() {};
		void processStateChange() {};
		unique_ptr<State> getCurrent() {};
	};
}
