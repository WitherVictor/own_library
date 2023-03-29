#include <ranges>
/* own::print_container()
*/

#include <iostream>
/* class timer
*/

#include <string>
/* class timer
*/

#include <algorithm>
/* std::iter_swap()
*/

#include <chrono>
/* class timer
 *
*/

namespace own
{
    // print_container begin
    template <std::ranges::range Container>
    void print_container(const Container& m_container)
    {
        if (std::begin(m_container) == std::end(m_container))
            return;
            
        std::cout << "[";
        for (auto iter = std::begin(m_container); iter != std::end(m_container); iter++)
        {
            std::cout << *iter;

            //如果迭代器指向的不是最后一个元素，那么正常插入 ", " 作为间隔，否则插入 "]" 结束
            iter != std::prev( std::end(m_container) ) ? std::cout << ", " : std::cout << "]";
        }

        std::cout << std::endl;
    }
    // print_container end

    //  quick_sort begin
    template <typename Iterator_Type>
    requires std::random_access_iterator<Iterator_Type>				// 要求传入的迭代器满足 "随机访问迭代器要求"
    void quick_sort(Iterator_Type begin, Iterator_Type end)
    {
        if (begin < end && !std::is_sorted(begin, end))				// 若 begin 和 end 表示的范围有效，且范围内元素非有序
        {            
            Iterator_Type position = begin + (end - begin) / 2;		// position 指向划归范围的中间值
            Iterator_Type first = begin;							// first 指向第一个元素
            Iterator_Type last = end - 1;							// last 指向最后一个元素

            while (first != last)									// 如果 first 与 last 没有相遇
            {
                while (*first < *position)							// first 向前查找直至找到大于 position 指向的值 
                    first++;

                std::iter_swap(first, position);					// 交换 first 与 position 指向的元素并更新 position 指向
                position = first;

                while (*position < *last)							// last 向后查找直至找到小于 position 指向的值
                    last--;

                std::iter_swap(position, last);						// 交换 position 与 last 指向的元素并更新 position 指向
                position = last;
            }

            quick_sort(begin, position);							// 递归自左向右进行快速排序
            quick_sort(position + 1, end);							//
        }
    }
    //  quick_sort end

    // class timer begin
	template <typename clock_type = std::chrono::steady_clock>
    class timer
    {
	public:
		timer() = default;

		timer(std::string clock_name)
			: m_clock_name(clock_name) {}

		~timer()
		{	if (!m_clock_name.empty())
				m_clock_name += " ";
			std::cout << "Clock " << m_clock_name << "Time Elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock_type::now() - m_start_time) << std::endl;
		}
	private:
		std::string m_clock_name{};
		std::chrono::time_point<clock_type> m_start_time{ clock_type::now() };
    };
}   //  namespace own end