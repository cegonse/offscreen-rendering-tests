FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  build-essential libmagickwand-dev libmagickcore-dev libosmesa-dev imagemagick ffmpeg curl git
