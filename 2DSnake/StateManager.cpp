#include "StateManager.h"
#include "State.h"

using namespace std;

Engine::StateManager::StateManager() {
	m_add = false;
	m_remove = false;
	m_replace = false;
}

Engine::StateManager::~StateManager() {

}

void Engine::StateManager::add(unique_ptr<State> toAdd, bool replace) {
	m_add = true;
	m_newState = move(toAdd);

	m_replace = replace;
}

void Engine::StateManager::popCurrent() {
	m_remove = true;
}

void Engine::StateManager::processStateChange() {

	if (m_remove && (!m_stateStack.empty())) {
		m_stateStack.pop();

		if (!m_stateStack.empty()) {
			m_stateStack.top()->start();
		}
		m_remove = false;
	}

	if (m_add)
	{
		if (m_replace && !m_stateStack.empty()) {

			m_stateStack.pop();
			m_replace = false;
		}

		if (!m_stateStack.empty()) {
			m_stateStack.top()->pause();
		}

		m_stateStack.push(move(m_newState));
		m_stateStack.top()->Init();
		m_stateStack.top()->start();
		m_add = false;
	}

}

unique_ptr<Engine::State>& Engine::StateManager::getCurrent() {
	return m_stateStack.top();
}