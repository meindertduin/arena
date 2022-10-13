#pragma once

#include "component.h"

#include <string>

namespace ui {
   class Frame : public Component {
   public:
       explicit Frame(std::string text);
       void render() override;
   private:
       std::string text;
   };
}