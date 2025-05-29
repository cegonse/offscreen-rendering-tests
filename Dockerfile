FROM ubuntu:25.10

ENV DEBIAN_FRONTEND=noninteractive

RUN sudo apt-get update && sudo apt-get install -y \
  build-essential libmagickwand-dev libosmesa-dev imagemagick ffmpeg curl git
