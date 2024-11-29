#pragma once

#include <functional>
#include <unordered_map>
#include <mutex>
#include <vector>
#include <memory>

template <typename Result, typename... Args>
class SignalEx
{
public:
    SignalEx() : _currentID{ 0 } {}

    SignalEx(const SignalEx&) = delete;
    SignalEx& operator=(const SignalEx&) = delete;

    /**
     * Connect a member function to this SignalEx
     */
    template <typename T>
    int connect(std::shared_ptr<T> inst, Result(T::* funct)(Args...)) {
        std::lock_guard<std::mutex> lock(_mutex);
        return connect([wptr = std::weak_ptr<T>(inst), funct](Args... args) -> Result {
            if (auto sptr = wptr.lock()) {
                return (sptr.get()->*funct)(args...);
            }
            return Result();
            });
    }

    /**
     * Connect a const member function to this SignalEx
     */
    template <typename T>
    int connect(std::shared_ptr<T> inst, Result(T::* funct)(Args...) const) {
        std::lock_guard<std::mutex> lock(_mutex);
        return connect([wptr = std::weak_ptr<T>(inst), funct](Args... args) -> Result {
            if (auto sptr = wptr.lock()) {
                return (sptr.get()->*funct)(args...);
            }
            return Result();
            });
    }

    /**
     * Connect std::function to this SignalEx
     */
    int connect(const std::function<Result(Args...)>& slot) {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots[++_currentID] = slot;
        return _currentID;
    }

    /**
     * Disconnect a previously connected function
     */
    void disconnect(int id) {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots.erase(id);
    }

    /**
     * Disconnect all previously connected functions
     */
    void disconnectAll() {
        std::lock_guard<std::mutex> lock(_mutex);
        _slots.clear();
    }

    /**
     * Call all connected functions and collect their results
     */
    std::vector<Result> emit(Args... args) const {
        std::vector<Result> results;
        std::lock_guard<std::mutex> lock(_mutex);
        for (const auto& [id, slot] : _slots) {
            results.push_back(slot(args...)); // Collect return values
        }
        return results;
    }

private:
    mutable std::unordered_map<int, std::function<Result(Args...)>> _slots;
    mutable std::mutex _mutex;
    int _currentID;
};
