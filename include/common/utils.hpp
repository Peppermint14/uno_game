#ifndef UTILS_HPP
#define UTILS_HPP

#include <queue>
#include <mutex>
#include <atomic>

namespace util {

    template<class Type>
    class BlockQueue {
        std::queue<Type> queue;
        std::mutex mutex;
        using Lock = std::lock_guard<std::mutex>;
    public:
        BlockQueue() {}
        BlockQueue(BlockQueue& _other){
            queue = _other.queue;
        }
        BlockQueue(BlockQueue&&) = default;

        [[nodiscard]] Type& front() noexcept {
            Lock lock(mutex);
            return queue.front();
        }

        [[nodiscard]] Type& back() noexcept {
            Lock lock(mutex);
            return queue.back();
        }

        [[nodiscard]] bool empty() noexcept {
            Lock lock(mutex);
            return queue.empty();
        }

        [[nodiscard]] size_t size() noexcept {
            Lock lock(mutex);
            return queue.size();
        }

        void push(Type _value) noexcept {
            Lock lock(mutex);
            queue.push(_value);
        }

        void pop() noexcept {
            Lock lock(mutex);
            queue.pop();
        }

    };

    template <typename T>
    struct atomwrapper {
        std::atomic<T> _a;
        atomwrapper() : _a() {}
        atomwrapper(const std::atomic<T> &a) : _a(a.load()) {}
        atomwrapper(const atomwrapper &other) : _a(other._a.load()) {}
        atomwrapper &operator=(const atomwrapper &other) {
            _a.store(other._a.load());
        }
    };
}

#endif /* UTILS_HPP */
