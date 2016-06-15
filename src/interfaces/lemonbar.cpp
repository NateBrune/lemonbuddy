#include "interfaces/lemonbar.hpp"
#include "services/logger.hpp"
#include "utils/io.hpp"
#include "utils/macros.hpp"
#include "utils/proc.hpp"
#include "utils/string.hpp"

using namespace lemonbar;
using namespace std::chrono_literals;

Lemonbar::Lemonbar(const Options& opts)
  : opts(opts)
  , logger(get_logger())
{
  this->run_state = false;

  lemonbar_xconnect();

  for (auto &f : opts.fonts)
    lemonbar_font_load(f->id.c_str(), f->offset);

  xcb_rectangle_t bar_bounds;
  bar_bounds.width = opts.width;
  bar_bounds.height = opts.height;
  bar_bounds.x = opts.offset_x;
  bar_bounds.y = opts.offset_y;

  lemonbar_initialize(bar_bounds, opts.monitor->bounds, opts.wm_name.c_str(),
    !opts.bottom, opts.dock, opts.clickareas, opts.lineheight,
    opts.background.c_str(), opts.foreground.c_str(), opts.linecolor.c_str(),
    opts.border_top, opts.border_bottom, opts.border_top_color.c_str(), opts.border_bottom_color.c_str());

  this->connection = lemonbar_get_xconnection();
  this->gc = lemonbar_get_gc();
  this->bar = lemonbar_get_bar();

  if (this->connection == nullptr)
    throw LemonbarError("Not connected to X server");
  if (pipe(this->fd_stdin) == -1)
    throw LemonbarError("Failed to create stdin pipe: "+ StrErrno());
  if (pipe(this->fd_stdout) == -1)
    throw LemonbarError("Failed to create stdout pipe: "+ StrErrno());
  // if ((this->read_stream = fdopen(this->get_stdin(PIPE_READ), "r")) == nullptr)
  //   throw LemonbarError("Failed to open read stream: "+ StrErrno());

  this->pollfd[0].fd = xcb_get_file_descriptor(this->connection);
  this->pollfd[0].events = POLLIN;
}

Lemonbar::~Lemonbar()
{
  log_trace("lemonbar_cleanup");
  lemonbar_cleanup();
  close(this->fd_stdin[PIPE_READ]);
  close(this->fd_stdin[PIPE_WRITE]);
  close(this->fd_stdout[PIPE_READ]);
  close(this->fd_stdout[PIPE_WRITE]);
  // fclose(this->read_stream);
}

void Lemonbar::start()
{
  this->run_state = true;
  this->process_event_thread = std::thread(&Lemonbar::process_events, this);
}

void Lemonbar::stop()
{
  this->run_state = false;

  if (this->process_event_thread.joinable())
    this->process_event_thread.join();
}

bool Lemonbar::running() {
  return this->run_state;
}

int Lemonbar::get_stdin(int fd) {
  return this->fd_stdin[fd];
}

int Lemonbar::get_stdout(int fd) {
  return this->fd_stdout[fd];
}

void Lemonbar::process_events()
{
  while (this->running())
  {
    if (this->has_errors())
      break;

    if (!xcb::connection::check(this->connection))
      break;

    if (poll(this->pollfd, 1, -1) <= 0)
      break;

    if (!(this->pollfd[0].revents & POLLIN))
      continue;

    xcb_generic_event_t *evt;

    while ((evt = xcb_poll_for_event(this->connection)) != nullptr) {
      if (evt->response_type == 0) {
        xcb_generic_error_t *error = (xcb_generic_error_t *) evt;
        this->logger->warning("Received X11 error, error_code = "+ IntToStr(error->error_code));
        free(evt);
        continue;
      }

      int type = (evt->response_type & ~0x80);

      switch (type) {
        case XCB_EXPOSE:
          this->handle_expose((xcb_expose_event_t *) evt);
          break;
        case XCB_BUTTON_PRESS:
          this->handle_button_press((xcb_button_press_event_t *) evt);
          break;
        case XCB_VISIBILITY_NOTIFY:
          // this->logger->error("XCB_VISIBILITY_NOTIFY");
          break;
        case XCB_CLIENT_MESSAGE:
          // this->logger->error("XCB_CLIENT_MESSAGE");
          break;
        case XCB_DESTROY_NOTIFY:
          // this->logger->error("XCB_DESTROY_NOTIFY");
          break;
        case XCB_UNMAP_NOTIFY:
          // this->logger->error("XCB_UNMAP_NOTIFY");
          break;
        case XCB_MAP_NOTIFY:
          // this->logger->error("XCB_MAP_NOTIFY");
          break;
        case XCB_PROPERTY_NOTIFY:
          // this->logger->error("XCB_PROPERTY_NOTIFY");
          break;
        case XCB_CONFIGURE_REQUEST:
          // this->logger->error("XCB_CONFIGURE_REQUEST");
          break;
      }
      free(evt);
    }
    std::this_thread::sleep_for(200ms);
  }
}

void Lemonbar::set_content(std::string data)
{
  if (this->has_errors())
    return;
  lemonbar_parse_data(data.c_str());
  this->redraw();
}

void Lemonbar::write_stdout(std::string data)
{
  if (this->has_errors())
    return;
  if (dprintf(this->get_stdout(PIPE_WRITE), "%s\n", string::strip_trailing_newline(data).c_str()) == -1)
    throw LemonbarWriteError("Failed to write to stdout: "+ StrErrno());
}

void Lemonbar::redraw()
{
  if (this->has_errors())
    return;

  lemonbar_draw_borders();
  xcb_copy_area(this->connection, this->bar->pixmap, this->bar->window, this->gc[GC_DRAW], 0, 0, 0, 0, this->bar->rect.width, this->opts.height + opts.border_top+opts.border_bottom);
  xcb_flush(this->connection);
}

bool Lemonbar::has_errors()
{
  if (this->connection != nullptr && xcb_connection_has_error(this->connection)) {
    fprintf(stderr, "xcb_connection_has_error\n");
    return true;
  }
  return false;
}

void Lemonbar::handle_expose(xcb_expose_event_t *evt)
{
  xcb_copy_area(this->connection, this->bar->window, evt->window, this->gc[GC_DRAW], 0, 0, 0, 0, opts.width, opts.height + opts.border_top + opts.border_bottom);
  xcb_flush(this->connection);
}

void Lemonbar::handle_button_press(xcb_button_press_event_t *evt)
{
  lemonbar_area_t *area = lemonbar_area_get(evt->event, evt->detail, evt->event_x);
  if (area == nullptr)
    return;
  area->cmd[std::strlen(area->cmd)] = '\0';
  this->write_stdout(std::string(area->cmd));
  this->redraw();
}
