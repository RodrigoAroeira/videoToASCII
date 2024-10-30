#include <regex>
#include <string>

#include "resolution.hpp"

std::string pixelToChar(int pixelBrightness) {

  // most intense to least inetense
  const std::string chars = "@%#*+=-_. ";

  int idx = pixelBrightness / 255.0F * (chars.length() - 1);

  return std::string(1, chars[idx]);
}

Resolution getTerminalRes() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return {w.ws_col, w.ws_row};
}

Resolution getVideoRes(const cv::VideoCapture &cap) {

  int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  return {width, height};
}

bool isValidYTUrl(const std::string &url) noexcept {
  const std::regex pattern(
      R"((https?:\/\/)?(www\.)?(youtube\.com\/watch\?v=|youtu\.be\/)([\w\-]{11})(\S*)?)",
      std::regex::icase);
  return std::regex_match(url, pattern);
}

#ifdef DEBUG
int main(int argc, char *argv[]) {
  std::string url;

  std::cout << "Digite a url: ";
  std::cin >> url;

  std::cout << isValidYTUrl(url) << std::endl;
  return 0;
}
#endif
