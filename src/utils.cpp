#include "utils.hpp"
#include "resolution.hpp"

#include <cstdio>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <regex>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

char pixelToChar(int pixelBrightness) {

  // most intense to least intense
  static const char *chars = "@%#*+=-:. ";
  static const int n = strlen(chars);

  int idx = pixelBrightness / 255.0F * (n - 1);

  return chars[idx];
}

Resolution getTerminalRes() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return {w.ws_col, w.ws_row};
}

[[gnu::unused]] Resolution getVideoRes(const cv::VideoCapture &cap) {

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

std::string getStreamURL(const std::string &ytURL) {
  std::stringstream result;
  const std::string command = "yt-dlp -g -f best " + ytURL;
  FILE *pipe = popen(command.c_str(), "r");
  char buff[128];
  while (fgets(buff, sizeof(buff), pipe))
    result << buff;

  pclose(pipe);
  return result.str();
}

bool fileExists(const std::string &filename) {
  return std::filesystem::is_regular_file(filename);
}

void tempRename(const std::string &filename, const std::string &dest) {
  std::filesystem::rename(filename, dest);
}

void downloadVideo(const std::string &ytURL, const std::string &outputName) {

  const auto downloadCommand =
      "yt-dlp " + ytURL + " -o " + outputName + " --force-overwrites";
  system(downloadCommand.c_str());
}

void pixelToColoredChar(const cv::Vec3b &pixel, char str_out[25]) {
  int r = pixel[2];
  int g = pixel[1];
  int b = pixel[0];
  // this follows the escape code \033[38;2;<r>;<g>;<b>m for 24-bit color
  char c = pixelToChar((r + g + b) / 3);
  sprintf(str_out, "\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, c);
}
