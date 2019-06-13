#include "yealink/add_on/content_patterns.h"

#include "rtc_base/checks.h"

namespace {
static const char* kContentPatternMain = "main";
static const char* kContentPatternSlides = "slides";
}  // namespace

namespace cricket {

std::string ContentPatternToString(ContentPattern pattern) {
  switch (pattern) {
    case ContentPattern::kMain:
      return kContentPatternMain;
    case ContentPattern::kSlides:
      return kContentPatternSlides;
  }
  FATAL();
  // Not reachable; avoids compile warning.
  return "";
}

ContentPattern ContentPatternFromString(const std::string& pattern_str) {
  if (pattern_str == kContentPatternMain) {
    return ContentPattern::kMain;
  } else if (pattern_str == kContentPatternSlides) {
    return ContentPattern::kSlides;
  }
  FATAL();
  // Not reachable; avoids compile warning.
  return static_cast<ContentPattern>(-1);
}

}  // namespace cricket
