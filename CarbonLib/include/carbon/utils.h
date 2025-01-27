#pragma once

#include <string>

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define PAD(size) \
	private: \
    char CONCAT(pad_, __LINE__)[size];

#define PUB \
	public:

#define SINGLETON(type) \
	private: \
		void operator=(const type&) = delete; \
		type(const type&) = delete; \
	public: \
		template <bool guaranteed = false> \
		[[nodiscard]] static type* GetInstance() { \
			if constexpr (guaranteed) { \
				auto t = *reinterpret_cast<type**>(Carbon::Offsets::Rebased::type); \
				while (!t == nullptr) { \
					Carbon::SM::UTILS::CERROR("Failed to get instance of {}", #type); \
					Sleep(1000); \
				}\
				return t; \
			} \
			else { \
				return *reinterpret_cast<type**>(Carbon::Offsets::Rebased::type); \
			} \
			auto instance = *reinterpret_cast<type**>(Carbon::Offsets::Rebased::type); \
			while (!instance) { \
				instance = *reinterpret_cast<type**>(Carbon::Offsets::Rebased::type); \
			} \
			return instance; \
