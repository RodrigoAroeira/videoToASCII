#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <sys/ioctl.h>

#include "resolution.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {

  // path-only for now
  std::string src = argc > 1 ? argv[1] : "./video.mp4";

  cv::VideoCapture Capture(src);

  Resolution terminalRes = getTerminalRes();

  if (!Capture.isOpened()) {
    std::cerr << "Error while opening video";
    return -1;
  }

  float videoFPS = Capture.get(cv::CAP_PROP_FPS);

  cv::Mat frame, frameGray, frameResized;

  std::string frameStr;
  while (true) {
    frameStr.clear();

    Resolution newTerminalRes = getTerminalRes();
    if (terminalRes != newTerminalRes) {
      terminalRes = newTerminalRes;
    }

    Capture >> frame;

    if (frame.empty())
      break;

    // Better for checking pixel brightness
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

    cv::resize(frameGray, frameResized,
               cv::Size(terminalRes.width, terminalRes.height), 0, 0,
               cv::INTER_LINEAR);

    for (int i = 0; i < terminalRes.height; i++) {
      for (int j = 0; j < terminalRes.width; j++) {
        auto pixel = frameResized.at<uchar>(i, j);
        frameStr += pixelToChar(pixel);
      }
      frameStr += "\n";
    }

    system("clear");
    std::cout << frameStr;
    // cv::waitKey(1000 / videoFPS);
  }
}
