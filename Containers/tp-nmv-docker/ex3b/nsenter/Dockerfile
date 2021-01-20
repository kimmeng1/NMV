FROM gcc
RUN apt-get update \
&&  apt-get install -y \
    git \
    build-essential \
    libncurses5-dev \
    libslang2-dev \
    gettext \
    zlib1g-dev \
    libselinux1-dev \
    debhelper \
    lsb-release \
    pkg-config \
    po-debconf \
    autoconf \
    automake \
    autopoint \
    libtool \
    bison

RUN git clone git://git.kernel.org/pub/scm/utils/util-linux/util-linux.git util-linux
WORKDIR /util-linux
RUN ./autogen.sh \
&& ./configure --without-python --disable-all-programs --enable-nsenter \
&& make
