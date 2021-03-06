#include "drawtypes/icon.hpp"
#include "utils/config.hpp"

namespace drawtypes
{
  std::unique_ptr<Icon> Icon::clone()
  {
    return std::unique_ptr<Icon> { new Icon(
      this->text, this->fg, this->bg, this->ul, this->ol, this->font, this->padding, this->margin) };
  }

  std::unique_ptr<Icon> get_config_icon(std::string config_path, std::string icon_name, bool required, std::string def)
  {
    auto label = get_config_label(config_path, icon_name, required, def);
    return std::unique_ptr<Icon> { new Icon(label->text, label->fg, label->bg, label->ul, label->ol, label->font) };
  }

  std::unique_ptr<Icon> get_optional_config_icon(std::string config_path, std::string icon_name, std::string def) {
    return get_config_icon(config_path, icon_name, false, def);
  }


  // IconMap

  void IconMap::add(std::string id, std::unique_ptr<Icon> &&icon) {
    this->icons.insert(std::make_pair(id, std::move(icon)));
  }

  std::unique_ptr<Icon> &IconMap::get(std::string id, std::string fallback_id)
  {
    auto icon = this->icons.find(id);
    if (icon == this->icons.end())
      return this->icons.find(fallback_id)->second;
    return icon->second;
  }

  bool IconMap::has(std::string id) {
    return this->icons.find(id) != this->icons.end();
  }
}
