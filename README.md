# TODAY'S TASK: Video to Ascii

STARTING: 2024-09-30 10:47

ENDED: 2024-10-01 11:18

## About

Convert video files and YouTube links to colored ASCII art, played directly in your terminal in real-time.

## Features

- Real-time ASCII video playback in terminal
- 24-bit true color output
- Automatic terminal resize detection during playback
- YouTube video support via yt-dlp
- ASCII character density maps to pixel brightness

## Build Requirements

- C++17 compatible compiler
- CMake ≥ 3.10
- Terminal with 24-bit true color support (recommended for full color output)

## Dependencies

Runtime dependencies for video playback:

### Debian/Ubuntu
```bash
sudo apt install libopencv-dev yt-dlp
```

### Arch-based
```bash
sudo pacman -S opencv yt-dlp
```

Note: `yt-dlp` is only required for YouTube video support.

## Build

```bash
# Create build directory and compile
mkdir -p build && cd build
cmake ..
make

# Compiled binary is located at ./build/videoToASCII
```

## Usage

Run the compiled binary with a video path or YouTube URL:

```bash
# From project root (after building)
./build/videoToASCII video.mp4

# Play YouTube video
./build/videoToASCII "https://www.youtube.com/watch?v=VIDEO_ID"

# Use default video (./video.mp4) if no arguments provided
./build/videoToASCII
```

Local video paths can be absolute or relative to the current working directory.

### Convenience Run Target

After building, use the `run` make target to build and execute in one step:
```bash
cd build && make run
```
