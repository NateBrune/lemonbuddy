#pragma once

#include <map>
#include <memory>

#include "bar.hpp"
#include "registry.hpp"
#include "exception.hpp"
#include "modules/base.hpp"
#include "services/logger.hpp"
#include "interfaces/lemonbar.hpp"

DefineBaseException(EventLoopTerminate);
DefineBaseException(EventLoopTerminateTimeout);

class EventLoop
{
  const int STATE_STOPPED = 1;
  const int STATE_STARTED = 2;

  std::shared_ptr<Bar> bar;
  std::shared_ptr<Registry> registry;
  std::shared_ptr<Logger> logger;
  std::unique_ptr<lemonbar::Lemonbar> lemonbar;

  std::mutex pid_mtx;
  std::vector<pid_t> pids;

  concurrency::Atomic<int> state { 0 };

  std::thread t_write;
  std::thread t_read;

  int fd_stdin = STDIN_FILENO;
  int fd_stdout = STDOUT_FILENO;

  // <tag, module_name>
  // std::map<std::string, std::string> stdin_subs;
  std::vector<std::string> stdin_subs;

  bool write_stdout = false;

  protected:
    void loop_write();
    void loop_read();

    void read_stdin();

    bool running();

  public:
    EventLoop(bool write_stdout);

    void start();
    void stop();
    void wait();

    void cleanup(int timeout_ms = 5000);

    void register_forked_pid(pid_t pid);
    void unregister_forked_pid(pid_t pid);
};
