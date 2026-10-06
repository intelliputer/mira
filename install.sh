#!/usr/bin/env sh
set -eu

if [ "$(id -u)" -ne 0 ]; then
    echo "Run with sudo: sudo ./install.sh" >&2
    exit 1
fi

apt-get update
apt-get install --assume-yes \
    build-essential \
    cmake \
    pkg-config \
    libsdl2-dev \
    libsdl2-image-dev \
    libglew-dev \
    libgl1-mesa-dev
