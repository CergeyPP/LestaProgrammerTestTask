#pragma once
#include <stdint.h>

#include <optional>
#include <mutex>
#include <memory>

/*
	Кольцевой буфер, написанный в стиле С
	Плюсы: 
		- Простая реализация
		- Не требуются последние стандарты С++(полезно при работе с легаси кодом)
	Минусы:
		- Непотокобезопасная реализация
		- Не используются преимущества библиотеки STL
*/
template<typename T = unsigned char>
class RingBuffer 
{
public:

	RingBuffer(uint64_t capacity)
	{
		m_buffer = new T[capacity];
		m_capacity = capacity;
		m_head = 0;
		m_tail = 0;
		m_size = 0;
	}
	~RingBuffer()
	{
		delete[] m_buffer;
	}

	/*
		Возвращает true, если в буфере есть данные, иначе false.
		В случае успеха, элемент сохраняется по ссылке
	*/
	bool tryGet(T& head)
	{
		if (m_size == 0)
			return false;

		head = m_buffer[m_head];

		if (++m_head == m_capacity)
			m_head = 0;
		m_size--;

		return true;
	}
	/*
		Возвращает true, если буфер не переполнен и удалось записать новый элемент, иначе false
	*/
	bool tryPut(T value)
	{
		if (m_size == m_capacity)
			return false;

		m_buffer[m_tail++] = value;
		if (m_tail == m_capacity)
			m_tail = 0;

		m_size++;
		return true;
	}

	void reset()
	{
		m_size = 0;
		m_head = 0;
		m_tail = 0;
	}

	inline uint64_t size() const
	{
		return m_size;
	}
	inline uint64_t capacity() const
	{
		return m_capacity;
	}

private:
	T* m_buffer;
	uint64_t m_capacity;
	uint64_t m_size;

	uint64_t m_head;
	uint64_t m_tail;
};


/*
	Кольцевой буфер с использованием библиотеки STL
	Плюсы:
		- Потокобезопасная реализация
	Минусы:
		- Необходим стандарт С++17
*/
template<class T = unsigned char>
class RingBufferCPP 
{
public:

	RingBufferCPP(size_t capacity) : 
		m_buffer(std::unique_ptr<T[]>(new T[capacity])),
		m_capacity(capacity),
		m_size(0), m_head(0), m_tail(0)
	{	}

	inline const size_t capacity() const { return m_capacity; }
	inline size_t size() const { return m_size; }

	void put(const T& value)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_size == m_capacity)
			throw std::overflow_error("Ring buffer is full");
		m_buffer[m_tail++] = value;
		if (m_tail == m_capacity)
			m_tail = 0;

		m_size++;
	}

	std::optional<T> get()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_size == 0)
			return std::nullopt;

		m_size--;
		T& value = m_buffer[m_head++];
		if (m_head == m_capacity)
			m_head = 0;

		return value;
	}

	void reset()
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_head = 0;
		m_tail = 0;
		m_size = 0;
	}

private:
	std::unique_ptr<T[]> m_buffer;
	std::mutex m_mutex;
	const size_t m_capacity;
	size_t m_head;
	size_t m_tail;
	size_t m_size;
};