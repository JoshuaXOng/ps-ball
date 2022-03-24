#pragma once 
#include <SDL2/SDL.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <functional>
#include <future>

class TimeUtils {
	public:
		static void setTimeout(int timeout, std::function<void()> callback) {
      auto unblockAt = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout);
      callback();
      std::this_thread::sleep_until(unblockAt);
    };

		static void setIntervalThreaded(int interval, std::function<void()> callback) {
			std::thread([callback, interval]() { 
        while (true) { 
					auto unblockAt = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
					callback();
					std::this_thread::sleep_until(unblockAt);
        }
    	}).detach();
		};
		
		static void setIntervalAsync(int interval, std::function<void()> callback) {
			// std::future<void> promise = std::async([]() {});
			// promise.wait();
			// promise.get();
		};
};
