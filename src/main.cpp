#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <sys/ioctl.h>

#include "resolution.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {

  // path-only for now
  std::string src = "./video.mp4";

  cv::VideoCapture Capture(src);

  Resolution video = getVideoRes(Capture);
  Resolution terminalRes = getTerminalRes();

  Resolution scaled = video.scale(terminalRes / 2);

  if (!Capture.isOpened()) {
    std::cerr << "Error while opening video";
    return -1;
  }

  float videoFPS = Capture.get(cv::CAP_PROP_FPS);

  cv::Mat frame, frameGray, frameResized;

  while (true) {

    Resolution newTerminalRes = getTerminalRes();
    if (terminalRes != newTerminalRes) {
      terminalRes = newTerminalRes;
      scaled = video.scale(terminalRes / 2);
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
