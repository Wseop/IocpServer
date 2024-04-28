#pragma once

using JobFunc = function<void(void)>;

class Job
{
public:
	Job(JobFunc&& jobFunc);

	template<typename T, typename Ret, typename... Args>
	inline Job(shared_ptr<T> owner, Ret(T::*func)(Args...), Args... args)
	{
		_jobFunc = [owner, func, args...]()
			{
				(owner.get()->*func)(args...);
			};
	}

	void execute();

private:
	JobFunc _jobFunc;
};

