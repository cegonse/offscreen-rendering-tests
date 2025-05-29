FROM ubuntu:25.10

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  build-essential libmagickwand-dev libosmesa-dev imagemagick ffmpeg curl git
