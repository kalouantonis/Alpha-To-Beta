#ifndef CONCURRENT_QUEUE_H_
#define CONCURRENT_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template <typename T>
class ConcurrentQueue
{
public:
    /**
     * @brief Pop off the front of the queue
     * @return Item in the front of queue
     */
    T pop()
    {
        // Lock queue
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_queue.empty())
        {
            // Block current thread until notification is received
            // Also releases lock to other waiting threads
            m_conditionVar.wait(lock);
        }

        // Get item off front
        auto item = m_queue.front();
        // Remove front item from queue
        m_queue.pop();
        return item;
    }

    /**
     * @brief Check if queue is empty
     */
    bool empty()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        return m_queue.empty();
    }

    /**
     * @brief Push new item on to queue

     * @param item constant reference to item to push
     */
    void push(const T& item)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(item);
        lock.unlock();
        // Notify one waiting thread
        m_conditionVar.notify_one();
    }

    /**
     * @brief Push R-Value reference. Used for std correctness
     */
    void push(T&& item)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        // Transfer ownership
        m_queue.push(std::move(item));
        lock.unlock();
        m_conditionVar.notify_one();
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_conditionVar;
};


#endif // CONCURRENT_QUEUE_H_
