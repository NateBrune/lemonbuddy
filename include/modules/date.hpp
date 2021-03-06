#pragma once

#include "modules/base.hpp"

namespace modules
{
  DefineModule(DateModule, TimerModule)
  {
    static constexpr auto TAG_DATE = "<date>";

    static constexpr auto EVENT_TOGGLE = "datetoggle";

    std::unique_ptr<Builder> builder;

    std::string date;
    std::string date_detailed;

    char date_str[256] = {};
    concurrency::Atomic<bool> detailed { false };

    public:
      explicit DateModule(std::string name);

      bool update();
      bool build(Builder *builder, std::string tag);

      std::string get_output();
      bool handle_command(std::string cmd);

      bool register_for_events() const {
        return true;
      }
  };
}
