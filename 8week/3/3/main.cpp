#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>

template < typename T, typename Container = std::vector<T>,  typename Compare = std::less<typename Container::value_type> >
class Threadsafe_PriorityQueue
{
public:

    Threadsafe_PriorityQueue() = default;

    Threadsafe_PriorityQueue(const Threadsafe_PriorityQueue & other)
    {
        std::lock_guard < std::mutex > lock(other.m_mutex);
        m_priority_queue = other.m_priority_queue;
    }

    Threadsafe_PriorityQueue & operator=(const Threadsafe_PriorityQueue & other)
    {
        std::scoped_lock lock(m_mutex, other.m_mutex);
        m_priority_queue = other.m_priority_queue;
    }

public:

    void push(T value)
    {
        std::lock_guard < std::mutex > lock(m_mutex);
        m_priority_queue.push(value);
        m_condition_variable.notify_one();
    }

    void wait_and_pop(T & value)
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        m_condition_variable.wait(lock, [this] {return !m_priority_queue.empty(); });
        value = m_priority_queue.top();
        m_priority_queue.pop();
    }

    std::shared_ptr < T > wait_and_pop()
    {
        std::unique_lock < std::mutex > lock(m_mutex);

        m_condition_variable.wait(lock, [this] {return !m_priority_queue.empty(); });
        auto result = std::make_shared < T > (m_priority_queue.top());
        m_priority_queue.pop();

        return result;
    }

    bool try_pop(T & value)
    {
        std::lock_guard < std::mutex > lock(m_mutex);

        if (m_priority_queue.empty())
        {
            return false;
        }

        value = m_priority_queue.top();
        m_priority_queue.pop();

        return true;
    }

    std::shared_ptr < T > try_pop()
    {
        std::lock_guard < std::mutex > lock(m_mutex);

        if (m_priority_queue.empty())
        {
            return std::shared_ptr < T > ();
        }

        auto result = std::make_shared < T > (m_priority_queue.top());
        m_priority_queue.pop();

        return result;
    }

    bool empty() const
    {
        std::lock_guard < std::mutex > lock(m_mutex);
        return m_priority_queue.empty();
    }

private:
    
    std::priority_queue <T, Container, Compare> m_priority_queue;
    std::condition_variable m_condition_variable;

private:

    mutable std::mutex m_mutex;
};

int main(int argc, char ** argv)
{
    Threadsafe_PriorityQueue < int, std::vector<int>, std::greater<int> > p_queue;

    p_queue.push(42);

    auto ptr = p_queue.wait_and_pop();

    int value;
    bool result = p_queue.try_pop(value);
    std::cout << result << std::endl;


    return 0;
}
