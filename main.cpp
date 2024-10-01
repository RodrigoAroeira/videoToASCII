#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <sys/ioctl.h>

#include "opencv2/videoio.hpp"
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

int main(int argc, char *argv[]) {

  // path only for now
  std::string src = "./video.mp4";

  cv::VideoCapture Capture(src);

  Resolution video = getVideoRes(Capture);
  Resolution terminal = getTerminalRes();

  Resolution scaled = video.scale(terminal / 2);

  if (!Capture.isOpened()) {
    std::cerr << "Error while opening video";
    return -1;
  }

  float videoFPS = Capture.get(cv::CAP_PROP_FPS);

  cv::Mat frame, frameGray, frameResized;

  while (true) {

    Resolution newTerminal = getTerminalRes();
    if (terminal != newTerminal) {
      terminal = newTerminal;
      scaled = video.scale(terminal / 2);
    }

    Capture >> frame;

    if (frame.empty())
      break;

    // Better for checking pixel brightness
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

    cv::resize(frameGray, frameResized, cv::Size(scaled.width, scaled.height),
               0, 0, cv::INTER_LINEAR);

    std::string frameStr;

    for (int i = 0; i < scaled.height; i++) {
      for (int j = 0; j < scaled.width; j++) {
        auto pixel = frameResized.at<uchar>(i, j);
        frameStr += pixelToChar(pixel);
      }
      frameStr += "\n";
    }

    system("clear");
    std::cout << frameStr;
    // cv::waitKey(1000 / videoFPS);
  }

  return 0;
}
