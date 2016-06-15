#pragma once

#include <memory>
#include <string>
#include <thread>
#include <sys/poll.h>

#include <lemonbar.h>

#include "exception.hpp"
#include "services/logger.hpp"
#include "utils/concurrency.hpp"
#include "bar.hpp"

namespace lemonbar
{
  DefineBaseException(LemonbarError);
  DefineBaseException(LemonbarReadError);
  DefineBaseException(LemonbarWriteError);

  static const int FD_STDIN = 0;
  static const int FD_XCB = 1;

  class Lemonbar
  {
    const Options& opts;
    std::shared_ptr<Logger> logger;

    xcb_connection_t *connection;
    xcb_gcontext_t *gc;
    lemonbar_bar_t *bar;

    int fd_stdin[2];
    int fd_stdout[2];
    FILE *read_stream;

    struct pollfd pollfd[1];

    concurrency::Atomic<bool> run_state;

    std::thread process_event_thread;

    void redraw();
    bool has_errors();

    void handle_expose(xcb_expose_event_t *evt);
    void handle_button_press(xcb_button_press_event_t *evt);

    public:
      Lemonbar(const Options& opts);
      ~Lemonbar();

      void start();
      void stop();
      bool running();

      void set_content(std::string data);
      void process_events();

      int get_stdin(int fd);
      int get_stdout(int fd);

      void read_stdin();
      void write_stdout(std::string data);
  };
}
