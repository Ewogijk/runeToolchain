FROM ubuntu:latest
WORKDIR /runeToolchain

COPY GCC GCC/
COPY Binutils Binutils/
COPY LibC LibC/
COPY Tools/x86_64-rune/build-native.sh Tools/x86_64-rune/

# Install system dependencies
RUN apt-get update
RUN apt-get install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo ninja-build python3-pip python3-venv

# Setup python venv
ENV VIRTUAL_ENV=/opt/venv
RUN python3 -m venv $VIRTUAL_ENV
ENV PATH="$VIRTUAL_ENV/bin:$PATH"
# Install python dependencies
RUN pip install click meson

ENTRYPOINT ["./Tools/x86_64-rune/build-native.sh"]