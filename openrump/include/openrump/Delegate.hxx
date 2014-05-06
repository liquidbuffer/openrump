// ----------------------------------------------------------------------------

template <class RET_TYPE, class... PARAMS>
class Delegate
{
	typedef RET_TYPE (*Type)(void* callee, PARAMS...);
public:

	Delegate(void* callee, Type func) :
		m_Callee(callee),
		m_CallbackFunction(func)
	{
	}

	RET_TYPE operator()(PARAMS... params) const
	{
		return (*m_CallbackFunction)(m_Callee, params...);
	}

	bool operator==(const Delegate& other) const
	{
		return m_Callee == other.m_Callee && m_CallbackFunction == other.m_CallbackFunction;
	}

private:

	template <class CLASS, RET_TYPE (CLASS::*TMethod)(PARAMS...)>
	static RET_TYPE methodCaller(void* callee, PARAMS... params)
	{
		CLASS* p = static_cast<CLASS*>(callee);
		return (p->*TMethod)(params...);
	}

	void* m_Callee;
	Type m_CallbackFunction;
};

template <class CLASS, class RET_TYPE, class... PARAMS>
class DelegateMaker
{
public:

	template <RET_TYPE (CLASS::*func)(PARAMS...)>
	static RET_TYPE methodCaller(void* callee, PARAMS... params)
	{
		return (static_cast<CLASS*>(callee)->*func)(params...);
	}

	template <RET_TYPE (CLASS::*func)(PARAMS...)>
	inline static Delegate<RET_TYPE, PARAMS...> bind(CLASS* callee)
	{
		return Delegate<RET_TYPE, PARAMS...>(
			callee, &DelegateMaker::methodCaller<func>
		);
	}
};

template <class CLASS, class RET_TYPE, class... PARAMS>
DelegateMaker<CLASS, RET_TYPE, PARAMS...>
makeDelegate(RET_TYPE (CLASS::*)(PARAMS...))
{
	return DelegateMaker<CLASS, RET_TYPE, PARAMS...>();
}

#define DELEGATE(funcPtr, objPtr) (makeDelegate(funcPtr).bind<funcPtr>(objPtr))

