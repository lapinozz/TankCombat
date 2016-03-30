#include "inc/command_queue.hpp"

namespace tc {
	void CommandQueue::push(const Command &command) {
		this->queue.push(command);
		return;
	}

	Command CommandQueue::pop() {
		Command ret = this->queue.front();
		this->queue.pop();
		return ret;
	}

	bool CommandQueue::is_empty() const {
		return this->queue.empty();
	}
}
