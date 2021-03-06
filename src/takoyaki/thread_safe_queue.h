// Copyright(c) 2015 kittikun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub license, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <queue>
#include <mutex>

namespace Takoyaki
{
    template<typename T>
    class ThreadSafeQueue
    {
        ThreadSafeQueue(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue(ThreadSafeQueue&&) = delete;
        ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

    public:
        ThreadSafeQueue() = default;

        bool empty() const
        {
            std::lock_guard<std::mutex> lock{ mutex_ };

            return queue_.empty();
        }

        void push(T value)
        {
            std::lock_guard<std::mutex> lock{ mutex_ };

            queue_.push(std::move(value));
            cond_.notify_one();
        }

        bool tryPop(T& value)
        {
            std::lock_guard<std::mutex> lock{ mutex_ };

            if (queue_.empty())
                return false;

            value = std::move(queue_.front());
            queue_.pop();
            return true;
        }

        void waitPop(T& value)
        {
            std::unique_lock<std::mutex> lock{ mutex_ };

            cond_.wait(lock, [this] { return !queue_.empty(); });
            value = std::move(queue_.front());
            queue_.pop();
        }

    private:
        mutable std::mutex mutex_;
        std::queue<T> queue_;
        std::condition_variable cond_;
    };
} // namespace Takoyaki