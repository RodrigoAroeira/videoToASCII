#pragma once
#include "resolution.hpp"

#include <opencv2/videoio.hpp>
#include <string>

std::string pixelToChar(int pixelBrightness);

Resolution getTerminalRes();

Resolution getVideoRes(const cv::VideoCapture &cap);
