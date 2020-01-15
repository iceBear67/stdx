﻿#include <stdx/async/task.h>

stdx::_TaskFlag::_TaskFlag()
	:m_lock()
	, m_locked(false)
	, m_wait_queue()
{}

stdx::_TaskFlag::~_TaskFlag()
{
	if (m_locked && (!m_wait_queue.empty()))
	{
		bool i = !m_wait_queue.empty();
		while (i)
		{
			auto ce = m_wait_queue.front();
			m_wait_queue.pop();
			ce.set_exception(std::make_exception_ptr(std::logic_error("the flag has been free!")));
			ce.run();
			i = !m_wait_queue.empty();
		}
	}
}

stdx::task<void> stdx::_TaskFlag::lock()
{
	stdx::task_complete_event<void> ce;
	std::unique_lock<stdx::spin_lock> lock(m_lock);
	if (m_locked)
	{
		m_wait_queue.push(ce);
	}
	else
	{
		m_locked = true;
		lock.unlock();
		ce.set_value();
		ce.run_on_this_thread();
	}
	return ce.get_task();
}

void stdx::_TaskFlag::unlock() noexcept
{
	std::lock_guard<stdx::spin_lock> guard(m_lock);
	if (!m_wait_queue.empty())
	{
		auto ce = m_wait_queue.front();
		ce.set_value();
		ce.run();
	}
	else
	{
		m_locked = false;
	}
}