// C++ implementation of the above approach 
#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <stdexcept>

// Thread-safe queue 
template <typename T>
class TSQueue {
private:
	// Underlying queue 
	std::queue<T> m_queue;

	// mutex for thread synchronization 
	std::mutex m_mutex;

	// Condition variable for signaling 
	std::condition_variable m_cond;

	bool is_adding_complete = false;

public:
	// Pushes an element to the queue 
	void push(T item)
	{
		// Acquire lock 
		std::unique_lock<std::mutex> lock(m_mutex);

		// Add item 
		m_queue.push(item);

		// Notify one thread that is waiting 
		m_cond.notify_one();
	}

	// Pops an element off the queue 
	// Always throws exception if the queue is Complete
	T pop()
	{
		// acquire lock 
		std::unique_lock<std::mutex> lock(m_mutex);

		// wait until queue is not empty 
		// It goes back to sleep if 'Predicate' is false, it continues if predicate is ture
		m_cond.wait(lock, [this]() { return is_adding_complete || !m_queue.empty(); });

		if (isComplete())
		{
			printf("In pop function: Queue is complete \n");
			throw std::invalid_argument("Exception: Queue is complete");
		}

		// retrieve item 
		T item = m_queue.front();
		m_queue.pop();

		// return item 
		return item;
	}

	void addingComplete()
	{
		// acquire lock 
		std::unique_lock<std::mutex> lock(m_mutex);

		is_adding_complete = true;

		m_cond.notify_one();
	}

	bool isComplete()
	{
		return (is_adding_complete && m_queue.empty());
	}
};