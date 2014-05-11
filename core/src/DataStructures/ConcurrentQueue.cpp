#include <DataStructures/ConcurrentQueue.h>

#include <thread>


template <typename T>
T ConcurrentQueue<T>::pop()
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

template <typename T>
void ConcurrentQueue<T>::push(const T &item)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push(item);
    lock.unlock();
    // Notify one waiting thread
    m_conditionVar.notify_one();
}

template <typename T>
void ConcurrentQueue<T>::push(T&& item)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    // Transfer ownership
    m_queue.push(std::move(item));
    lock.unlock();
    m_conditionVar.notify_one();
}
