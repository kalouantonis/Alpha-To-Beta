#ifndef CONCURRENT_QUEUE_H_
#define CONCURRENT_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue
{
public:
    /**
     * @brief Pop off the front of the queue
     * @return Item in the front of queue
     */
    T pop();

    void push(const T& item);
    /**
     * @brief Push R-Value reference. Used for std correctness
     */
    void push(T&& item);

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_conditionVar;
};


#endif // CONCURRENT_QUEUE_H_
