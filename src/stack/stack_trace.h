/**
 * @file: stack_trace.h
 * @brief: 打印栈的内容，用于追踪崩溃问题
 * @author: Jimmy Nie (nieshihua@126.com)
 * @date: 2024-05-16
 */
#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace bv
{
/// \brief StackTrace class.
class StackTrace {
public:
    ///\brief Return the call stack addr
    /** <p>On Linux, to obtain function names, remember to link with the -rdynamic flag, if HAVE_EXECINFO_H</p>*/
    static std::vector<std::string> get_stack_trace(int frames_skip = 0, void * secret = nullptr);

private:
    static uint16_t max_frames_;
};
}