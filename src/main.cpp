#include <sys/ioctl.h>

#include <cassert>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

#include "resolution.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {

  const std::string input = argc > 1 ? argv[1] : "./video.mp4";
  std::string videoName = "./video.mp4";

  if (isValidYTUrl(input)) {
    downloadVideo(input, videoName);
  } else {
    videoName = input;
  }

  cv::VideoCapture Capture(videoName);

  Resolution terminalRes = getTerminalRes();

  if (!Capture.isOpened()) {
    std::cerr << "Error while opening video." << std::endl;
    return -1;
  }

  float videoFPS = Capture.get(cv::CAP_PROP_FPS);

  cv::Mat frame, frameResized;

  char *coloredPixel = (char *)alloca(25 * sizeof(char));
  std::string frameStr;
  Resolution newTerminalRes;
  while (true) {
    frameStr.clear();

    newTerminalRes = getTerminalRes();
    if (terminalRes != newTerminalRes) {
      terminalRes = newTerminalRes;
    }

    Capture >> frame;
    frameStr.resize(frame.rows * frame.cols);

    if (frame.empty())
      break;

    cv::resize(frame, frameResized,
               cv::Size(terminalRes.width, terminalRes.height), 0, 0,
               cv::INTER_LINEAR);

    for (int i = 0; i < terminalRes.height; i++) {
      for (int j = 0; j < terminalRes.width; j++) {
        auto pixel = frameResized.at<cv::Vec3b>(i, j);
        pixelToColoredChar(pixel, coloredPixel);
        frameStr += coloredPixel;
      }
      frameStr += i < terminalRes.height - 1 ? "\n" : "";
    }

    std::cout << "\033[H" << frameStr;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(int(1000 / videoFPS)));
  }
}
