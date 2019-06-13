#ifndef YEALINK_ADD_ON_CONTENT_PATTERNS_H_
#define YEALINK_ADD_ON_CONTENT_PATTERNS_H_

#include <string>

namespace cricket {

enum class ContentPattern {
  kMain,
  kSlides,
};

std::string ContentPatternToString(ContentPattern pattern);

ContentPattern ContentPatternFromString(const std::string& pattern_str);

}  // namespace cricket

#endif  // YEALINK_ADD_ON_CONTENT_PATTERNS_H_
