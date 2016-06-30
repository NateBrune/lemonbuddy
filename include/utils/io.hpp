#pragma once

#include <string>
#include <functional>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

namespace io
{
  namespace socket
  {
    int open(std::string path);
    int send(int fd, std::string data, int flags = 0);
    int recv(int fd, char *buffer, int recv_bytes, int flags = 0);
  }

  namespace file
  {
    class FilePtr
    {
      FILE *fptr = nullptr;

      public:
        std::string path;
        std::string mode;

        FilePtr(std::string path, std::string mode = "a+")
          : path(std::string(path)), mode(std::string(mode))
        {
          this->fptr = fopen(this->path.c_str(), this->mode.c_str());
        }

        ~FilePtr()
        {
          if (this->fptr != nullptr)
            fclose(this->fptr);
        }

        operator bool() {
          return this->fptr != nullptr;
        }

        FILE *operator()() {
          return this->fptr;
        }
    };

    bool exists(std::string fname);
    std::string get_contents(std::string fname);
    bool is_fifo(std::string fname);
    std::size_t write(FilePtr *fptr, std::string data);
    std::size_t write(std::string fpath, std::string data);
  }

  std::string read(int read_fd, int bytes_to_read = -1);
  std::string read(int read_fd, int bytes_to_read, int &bytes_read_loc, int &status_loc);
  std::string readline(int read_fd, int &bytes_read);
  std::string readline(int read_fd);

  int write(int write_fd, std::string data);
  int writeline(int write_fd, std::string data);

  void tail(int read_fd, std::function<void(std::string)> callback);
  void tail(int read_fd, int writeback_fd);

  bool poll_read(int fd, int timeout_ms = 1);
  // bool poll_write(int fd, int timeout_ms = 1);
  bool poll(int fd, short int events, int timeout_ms = 1);

  // int get_flags(int fd);
  // int set_blocking(int fd);
  // int set_non_blocking(int fd);

  void interrupt_read(int write_fd);
}
