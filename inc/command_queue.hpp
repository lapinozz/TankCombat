#ifndef COMMAND_QUEUE_HPP
#define COMMAND_QUEUE_HPP

#include <queue>
#include "inc/command.hpp"
namespace tc {
	/**
	 * \brief An easy command queue wrapper.
	 *
	 * Hides unneeded API and makes pop return front on pop.
	 */
	class CommandQueue {
		public:
			void push(const Command &command);
			Command pop();
			bool is_empty() const;
		private:
			std::queue<Command> queue;
	};
}
#endif
