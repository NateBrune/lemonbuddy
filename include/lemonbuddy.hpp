#pragma once

#include "exception.hpp"
#include "bar.hpp"

DefineBaseException(ApplicationError);

void register_pid(pid_t pid);
void unregister_pid(pid_t pid);
