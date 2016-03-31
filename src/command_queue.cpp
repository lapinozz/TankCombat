#include "inc/command_queue.hpp"

namespace tc {
	/**
	 * \brief The push method.
	 *
	 * Pushes the command into the queue.
	 *
	 * @param command The command to be pushed.
	 */
	void CommandQueue::push(const Command &command) {
		this->queue.push(command);
		return;
	}

	/**
	 * \brief The pop method.
	 *
	 * Pops the front and returns it.
	 *
	 * @return The queue front, just popped.
	 */
	Command CommandQueue::pop() {
		Command ret = this->queue.front();
		this->queue.pop();
		return ret;
	}

	/**
	 * \brief The emptiness checker.
	 *
	 * Checks if the queue is empty.
	 *
	 * @return The emptiness state.
	 */
	bool CommandQueue::is_empty() const {
		return this->queue.empty();
	}
}
